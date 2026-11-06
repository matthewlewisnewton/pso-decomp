"""Weak inline copies resolved by link order; synthetic inputs only."""
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import link_units as link

GLOBAL, WEAK = (1, 2), (2, 2)


class WeakCopiesFollowLinkOrder(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        root = Path(self.tmp.name)
        self.obj, self.split = root / "src", root / "obj"
        for name in ("pso/Owner", "pso/User"):
            for base in (self.obj, self.split):
                (base / name).parent.mkdir(parents=True, exist_ok=True)
                (base / f"{name}.o").write_bytes(b"")
        self.report = root / "report.json"
        self.report.write_text("{}")
        self.config = root / "config.json"
        self.owner = {"name": "psov3/pso/Owner", "functions": [{"name": "slot"}],
                      "metadata": {"source_path": "src/pso/Owner.cpp"}}
        self.user = {"name": "psov3/pso/User", "functions": [{"name": "own"}],
                     "metadata": {"source_path": "src/pso/User.cpp"}}
        self.bindings = {
            self.obj / "pso/User.o": {"slot": WEAK, "own": GLOBAL},
            self.split / "pso/Owner.o": {"slot": GLOBAL},
            self.obj / "pso/Owner.o": {"slot": WEAK},
        }

    def discarded(self, order):
        self.config.write_text(json.dumps({"units": [{"name": n} for n in order]}))
        link._link_order.cache_clear()
        with patch.multiple(link, OBJ_DIR=self.obj, SPLIT_OBJ_DIR=self.split,
                            REPORT=self.report, SPLIT_CONFIG=self.config), \
                patch.object(link, "elf_symbol_bindings", lambda p: self.bindings.get(p, {})), \
                patch.object(link, "_dol_symbol_names", lambda: {"slot", "own"}), \
                patch.object(link, "_canonical_function_owners", lambda *_: {"slot": self.owner}), \
                patch.object(link, "_read_list", lambda _: ["pso/Owner.cpp"]):
            return link.discarded_weak_functions(self.user)

    def test_weak_owner_copy_that_links_first_is_kept_by_the_linker(self):
        self.assertEqual(self.discarded(["pso/Owner.cpp", "pso/User.cpp"]), {"slot"})

    def test_weak_owner_copy_that_links_later_stays_an_error(self):
        self.assertEqual(self.discarded(["pso/User.cpp", "pso/Owner.cpp"]), set())


if __name__ == "__main__":
    unittest.main()
