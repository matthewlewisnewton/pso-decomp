"""Retention checks using synthetic split objects, without game assets or a compiler."""
import contextlib
import io
import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import check_pr, link_units, mwcc_parts
from tools.tests.test_link_units_sections import elf


class ForceActive(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / "checkout"
        self.cfg = self.root / "config/GPOE8P/psov3"
        self.cfg.mkdir(parents=True)
        self.objects = self.root / "build/GPOE8P/obj/pso"
        self.objects.mkdir(parents=True)
        tools = self.root / "tools"
        tools.mkdir()
        for module in (link_units, mwcc_parts):
            shutil.copyfile(module.__file__, tools / Path(module.__file__).name)
        self.script = tools / "link_units.py"
        self.cwd = Path(self.tmp.name) / "elsewhere"
        self.cwd.mkdir()
        (self.cfg / "linked_units.txt").write_text("# Linked from source\npso/unit.cpp\n")
        (self.cfg / "splits.txt").write_text(
            "pso/unit.cpp:\n\t.text start:0x1000 end:0x1040\n"
            "pso/consumer.cpp:\n\t.text start:0x2000 end:0x2004\n")
        (self.cfg / "symbols.txt").write_text(
            "used = .text:0x1000; // type:function size:0x4\n"
            "unused = .text:0x1004; // type:function size:0x4\n"
            "@thunk = .text:0x1008; // type:function size:0x4\n"
            "private = .text:0x100C; // type:function size:0x4 scope:local\n"
            "stripped = .text:0x1010; // type:function size:0x4 stripped\n"
            "hidden = .text:0x1014; // type:function size:0x4 noexport\n"
            "unlinked = .text:0x2000; // type:function size:0x4\n")
        # Original units remain reference consumers even when not linked from source.
        elf(self.objects / "unit.o", [])
        elf(self.objects / "consumer.o", [], [("used", 0, 0, 0, 2)])
        self.inventory = self.root / "build/GPOE8P/config.json"
        self.inventory.write_text(json.dumps({"units": [
            {"object": "build/GPOE8P/obj/pso/unit.o"},
            {"object": "build/GPOE8P/obj/pso/consumer.o"}]}))
        self.config = self.cfg / "config.yml"
        self.set_retention(['"@thunk"', "unused"])

    def set_retention(self, names):
        self.config.write_text("# Keep surrounding settings\nname: fixture\n"
                               + link_units._FA_BEGIN + "\nforce_active:\n"
                               + "".join(f"  - {name}\n" for name in names)
                               + link_units._FA_END + "\nquick_analysis: true\n")

    def files(self):
        return {str(p.relative_to(self.root)): p.read_bytes()
                for p in self.root.rglob("*") if p.is_file()}

    def run_cli(self, *args):
        return subprocess.run([sys.executable, "-B", str(self.script), "force-active", *args],
                              cwd=self.cwd, capture_output=True, text=True)

    def test_in_sync_is_read_only_and_uses_script_root_from_another_cwd(self):
        before = self.files()
        result = self.run_cli("--check")
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("+0", result.stdout)
        self.assertEqual(self.files(), before)

    def test_drift_fails_without_writing_and_plain_report_remains_advisory(self):
        self.set_retention(['"@thunk"', "stale"])
        before = self.files()
        result = self.run_cli("--check")
        self.assertEqual(result.returncode, 1, result.stderr)
        self.assertIn("+1", result.stdout)
        self.assertIn("-1 stale", result.stdout)
        self.assertIn("FAIL", result.stdout)
        self.assertEqual(self.run_cli().returncode, 0)
        self.assertEqual(self.files(), before)

    def test_write_is_idempotent_preserves_linkset_and_passes_check(self):
        self.set_retention(["stale"])
        linked = (self.cfg / "linked_units.txt").read_bytes()
        self.assertEqual(self.run_cli("--write").returncode, 0)
        self.assertIn('  - "@thunk"\n  - unused\n', self.config.read_text())
        self.assertTrue(self.config.read_text().endswith("quick_analysis: true\n"))
        before = self.files()
        self.assertEqual(self.run_cli("--write").returncode, 0)
        self.assertEqual(self.run_cli("--check").returncode, 0)
        self.assertEqual(self.files(), before)
        self.assertEqual((self.cfg / "linked_units.txt").read_bytes(), linked)

    def test_references_come_only_from_active_inventory_not_retired_objects(self):
        elf(self.objects / "retired.o", [], [("unused", 0, 0, 0, 2)])
        self.assertEqual(self.run_cli("--check").returncode, 0)
        inventory = json.loads(self.inventory.read_text())
        inventory["units"].append({"object": "build/GPOE8P/obj/pso/retired.o"})
        self.inventory.write_text(json.dumps(inventory))
        result = self.run_cli("--check")
        self.assertEqual(result.returncode, 1)
        self.assertIn("-1 stale", result.stdout)

    def test_missing_inventory_or_active_object_cannot_pass_or_rewrite(self):
        before = self.config.read_bytes()
        inventory = self.inventory.read_bytes()
        self.inventory.unlink()
        result = self.run_cli("--check")
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("config.json", result.stderr)
        self.inventory.write_bytes(inventory)
        (self.objects / "consumer.o").unlink()
        self.assertNotEqual(self.run_cli("--check").returncode, 0)
        self.assertEqual(self.config.read_bytes(), before)

    def test_missing_linkset_is_not_treated_as_an_empty_selection(self):
        before = self.config.read_bytes()
        (self.cfg / "linked_units.txt").unlink()
        for mode in ("--check", "--write"):
            result = self.run_cli(mode)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn("missing linked-unit inventory", result.stderr)
            self.assertEqual(self.config.read_bytes(), before)

    def test_missing_or_empty_symbol_inventory_cannot_rewrite(self):
        before = self.config.read_bytes()
        for content in ("", "# no symbols\n"):
            (self.cfg / "symbols.txt").write_text(content)
            self.assertNotEqual(self.run_cli("--write").returncode, 0)
            self.assertEqual(self.config.read_bytes(), before)
        (self.cfg / "symbols.txt").unlink()
        self.assertNotEqual(self.run_cli("--check").returncode, 0)

    def test_check_and_write_cannot_be_combined(self):
        before = self.files()
        self.assertEqual(self.run_cli("--check", "--write").returncode, 2)
        self.assertEqual(self.files(), before)

    def test_changed_symbol_inventory_refuses_stale_plan(self):
        before = self.config.read_bytes()
        symbols = self.cfg / "symbols.txt"

        def change_inputs(*args):
            symbols.write_text(symbols.read_text() + "new = .text:0x1018; // type:function\n")
            return ["unused"]

        with patch.object(link_units, "SYMBOLS", symbols), \
             patch.object(link_units, "CONFIG_YML", self.config), \
             patch.object(link_units, "LINKED", self.cfg / "linked_units.txt"), \
             patch.object(link_units, "_force_active_names", side_effect=change_inputs):
            with self.assertRaisesRegex(SystemExit, "changed during scan"):
                link_units.force_active(write=True)
        self.assertEqual(self.config.read_bytes(), before)


class PrGate(unittest.TestCase):
    def test_retention_failure_fails_pr_gate_and_is_recorded(self):
        with tempfile.TemporaryDirectory() as tmp:
            baseline = Path(tmp) / "baseline.json"
            baseline.write_text("{}")
            output = Path(tmp) / "checks.json"

            def run(title, command):
                if command[-2:] == ["force-active", "--check"]:
                    return False, "force_active: +1 -1 stale"
                return True, "OK"

            with patch.object(sys, "argv", ["check_pr", "--no-build", "--baseline", str(baseline),
                                            "--json", str(output)]), \
                 patch.object(check_pr, "run", side_effect=run), \
                 patch.object(check_pr.subprocess, "run",
                              return_value=subprocess.CompletedProcess([], 0, "{}")), \
                 contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(check_pr.main(), 1)
            result = json.loads(output.read_text())
            self.assertEqual(result["result"], "fail")
            self.assertFalse(next(c for c in result["checks"] if c["name"] == "force_active")["ok"])


if __name__ == "__main__":
    unittest.main()
