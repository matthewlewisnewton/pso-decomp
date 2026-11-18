"""The #207 carrier must not admit every intervening or subsequent upstream PR."""
import tempfile
import unittest
from pathlib import Path
from subprocess import CompletedProcess
from unittest.mock import patch

from tools import list_port_exceptions as inventory


class CatchupScopeTests(unittest.TestCase):
    def check_row(self, upstream, metadata=""):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "src").mkdir()
            (root / "src/unit.cpp").write_text("")
            register = root / "register.md"
            register.write_text(
                "## 7. Upstream catch-up (rewrite later)\n"
                f"{metadata}"
                "| Symbol | Unit | File | Upstream | Type | Fork | Tag |\n"
                "|---|---|---|---|---|---|---|\n"
                f'| fn | unit.cpp | src/unit.cpp | #{upstream} | raw offset cast | #1 | '
                "upstream catch-up, rewrite later |\n"
            )
            with patch.object(inventory, "ROOT", root), patch.object(inventory, "REGISTER", register):
                return inventory.catchup_entries()

    def test_existing_scope_and_selected_carrier_are_valid(self):
        for upstream in [167, 191, 192, 207]:
            with self.subTest(upstream=upstream):
                rows, errors = self.check_row(upstream)
                self.assertEqual(len(rows), 1)
                self.assertEqual(errors, [])

    def test_history_fold_does_not_authorize_other_prs(self):
        for upstream in [166, 193, 196, 198, 206, 208, 213, 228]:
            with self.subTest(upstream=upstream):
                _, errors = self.check_row(upstream)
                self.assertEqual(len(errors), 1)
                self.assertIn("upstream PR must be", errors[0])

    def test_archive_uses_paths_from_the_recorded_tree(self):
        revision = "a" * 40
        marker = f"<!-- register-source-revision: {revision} -->\n"
        with patch.object(inventory.subprocess, "run") as git:
            git.return_value = CompletedProcess([], 0, stdout=b"src/moved.cpp\0")
            _, errors = self.check_row(207, marker)
            self.assertEqual(len(errors), 1)
            self.assertIn("file src/unit.cpp does not exist", errors[0])
            self.assertIn(revision, git.call_args.args[0])
            git.return_value.stdout = b"src/unit.cpp\0"
            self.assertEqual(self.check_row(207, marker)[1], [])
            git.return_value.returncode = 128
            self.assertIn(revision, self.check_row(207, marker)[1][0])

    def test_multiline_compiler_and_section_alignment_overrides(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "configure.py").write_text(
                "EXCEPTIONS = {\n"
                "    # Four-byte alignment preserves the original address.\n"
                "    'pso/scene.cpp': {\n"
                "        'cw_align': '.rodata=4 .sdata=4',\n"
                "        'cflags': _switch(defaults, '-inline deferred'),\n"
                "    },\n}\n"
            )
            with patch.object(inventory, "ROOT", root):
                self.assertEqual(inventory.configure_overrides(), [(
                    "pso/scene.cpp",
                    "cw_align = '.rodata=4 .sdata=4', cflags = _switch(defaults, '-inline deferred')",
                    "Four-byte alignment preserves the original address.",
                )])


if __name__ == "__main__":
    unittest.main()
