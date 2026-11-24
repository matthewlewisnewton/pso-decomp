import gzip
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from materialize import OVERLAY, materialize


def git(root, *args):
    return subprocess.check_output(["git", "-C", str(root), *args], stderr=subprocess.STDOUT)


class MaterializeTest(unittest.TestCase):
    def test_binary_overlay_and_source_checkout_are_isolated(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            source = path / "source"
            source.mkdir()
            git(source, "init", "-q")
            git(source, "config", "user.name", "Fixture")
            git(source, "config", "user.email", "fixture@example.test")
            native = source / "config.txt"
            native.write_text("native\n")
            git(source, "add", ".")
            git(source, "commit", "-qm", "Base")

            native.write_text("local\n")
            fixture = source / "fixture.bin"
            fixture.write_bytes(b"\x00\x80\xff" * 70)
            git(source, "add", ".")
            patch = git(source, "diff", "--cached", "--binary", "--full-index")
            git(source, "restore", "--staged", "--worktree", ".")
            overlay = source / OVERLAY
            overlay.parent.mkdir(parents=True)
            overlay.write_bytes(gzip.compress(patch))
            git(source, "add", ".")
            git(source, "commit", "-qm", "Layer")
            baseline = git(source, "rev-parse", "HEAD")

            output = materialize(source, "HEAD", path / "workspace")
            self.assertEqual((output / "config.txt").read_text(), "local\n")
            self.assertEqual((output / "fixture.bin").read_bytes(), b"\x00\x80\xff" * 70)
            self.assertEqual(git(output, "status", "--porcelain"), b"")
            self.assertEqual(git(output, "rev-parse", "HEAD^"), baseline)
            self.assertEqual(native.read_text(), "native\n")
            self.assertFalse(fixture.exists())
            self.assertEqual(git(source, "rev-parse", "HEAD"), baseline)
            with self.assertRaises(FileExistsError):
                materialize(source, "HEAD", output)
