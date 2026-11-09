"""The #207 carrier must not admit every intervening or subsequent upstream PR."""
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from tools import list_port_exceptions as inventory


class CatchupScopeTests(unittest.TestCase):
    def check_row(self, upstream):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "src").mkdir()
            (root / "src/unit.cpp").write_text("")
            register = root / "register.md"
            register.write_text(
                "## 7. Upstream catch-up (rewrite later)\n"
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


if __name__ == "__main__":
    unittest.main()
