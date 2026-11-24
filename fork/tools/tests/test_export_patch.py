"""Synthetic-repository tests for the fork layer tools. No game data or compiler needed.

    python3 -m unittest discover -s fork/tools/tests -v
"""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_layer  # noqa: E402
import export_patch  # noqa: E402
from layer import GitError, is_layer_path  # noqa: E402


def run(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout.strip()


class Repo:
    """upstream: one commit. main: upstream plus a layer file. Tests add patch branches."""

    def __init__(self, root: Path):
        self.root = root
        run(root, "init", "-q", "-b", "upstream-master")
        run(root, "config", "user.name", "Test")
        run(root, "config", "user.email", "test@example.invalid")
        self.write("src/a.cpp", "int a() { return 1; }\n")
        self.write("src/b.cpp", "int b() { return 2; }\n")
        self.commit("Upstream base")
        run(root, "checkout", "-q", "-b", "main")
        self.write("fork/README.md", "layer\n")
        self.commit("Add the fork layer")

    def write(self, path, text):
        p = self.root / path
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text)

    def commit(self, message):
        run(self.root, "add", "-A")
        run(self.root, "commit", "-q", "-m", message)
        return run(self.root, "rev-parse", "HEAD")

    def export(self, branch, **kw):
        args = dict(message="Match a", fork_main="main", onto="upstream-master", name=None, force=False)
        args.update(kw)
        return export_patch.export(branch, cwd=self.root, **args)


class LayerPaths(unittest.TestCase):
    def test_paths(self):
        self.assertTrue(is_layer_path("fork"))
        self.assertTrue(is_layer_path("fork/tools/x.py"))
        self.assertTrue(is_layer_path("fork/tooling/workflows/fork-checks.yml"))
        self.assertFalse(is_layer_path(".github/workflows/fork-checks.yml"))
        self.assertFalse(is_layer_path("forklift/x"))
        self.assertFalse(is_layer_path("tools/fork.py"))
        self.assertFalse(is_layer_path(".github/workflows/ci.yml"))


class Export(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.repo = Repo(Path(self.tmp.name))

    def tearDown(self):
        self.tmp.cleanup()

    def test_layer_is_left_out_and_tree_matches(self):
        r = self.repo
        run(r.root, "checkout", "-q", "-b", "patch/a")
        r.write("src/a.cpp", "int a() { return 10; }\n")
        r.commit("Match a")
        r.write("fork/notes/a.md", "how the match was found\n")
        r.write(".github/workflows/fork-checks.yml", "name: Old fork workflow\n")
        r.commit("Add notes and old fork workflow")
        head = run(r.root, "rev-parse", "HEAD")
        out = r.export("patch/a")
        self.assertEqual(out["files"], ["src/a.cpp"])
        self.assertEqual(out["layer_left_out"], [".github/workflows/fork-checks.yml", "fork/notes/a.md"])
        self.assertEqual(run(r.root, "rev-parse", "HEAD"), head, "the checkout must not move")
        self.assertEqual(run(r.root, "status", "--porcelain"), "")
        files = run(r.root, "ls-tree", "-r", "--name-only", "export/a").split()
        self.assertEqual(files, ["src/a.cpp", "src/b.cpp"])
        self.assertEqual(run(r.root, "show", "export/a:src/a.cpp"), "int a() { return 10; }")
        self.assertEqual(run(r.root, "rev-parse", "export/a^"), run(r.root, "rev-parse", "upstream-master"))
        self.assertEqual(run(r.root, "log", "-1", "--format=%s", "export/a"), "Match a")

    def test_layer_only_branch_is_refused(self):
        r = self.repo
        run(r.root, "checkout", "-q", "-b", "patch/notes")
        r.write("fork/notes/x.md", "x\n")
        r.commit("Notes only")
        with self.assertRaisesRegex(GitError, "only fork-layer paths"):
            r.export("patch/notes")

    def test_existing_export_needs_force(self):
        r = self.repo
        run(r.root, "checkout", "-q", "-b", "patch/a")
        r.write("src/a.cpp", "int a() { return 10; }\n")
        r.commit("Match a")
        first = r.export("patch/a")["commit"]
        with self.assertRaisesRegex(GitError, "already exists"):
            r.export("patch/a")
        self.assertEqual(run(r.root, "rev-parse", "export/a"), first)
        r.export("patch/a", force=True)

    def test_patch_depending_on_a_pending_patch(self):
        r = self.repo
        run(r.root, "checkout", "-q", "-b", "patch/a")
        r.write("src/a.cpp", "int a() { return 10; }\n")
        r.commit("Match a")
        run(r.root, "checkout", "-q", "main")
        run(r.root, "merge", "-q", "--no-ff", "-m", "Merge patch/a", "patch/a")
        run(r.root, "checkout", "-q", "-b", "patch/a2")
        r.write("src/a.cpp", "int a() { return 11; }\n")
        r.commit("Refine a")
        with self.assertRaisesRegex(GitError, "does not apply|conflicts"):
            r.export("patch/a2", message="Refine a")
        self.assertEqual(run(r.root, "branch", "--list", "export/a2"), "")
        # patch/a is already merged into main; its own commits are still found.
        self.assertEqual(r.export("patch/a")["files"], ["src/a.cpp"])
        out = r.export("patch/a2", message="Refine a", onto="export/a")
        self.assertEqual(run(r.root, "show", "export/a2:src/a.cpp"), "int a() { return 11; }")
        self.assertEqual(run(r.root, "rev-parse", "export/a2^"), run(r.root, "rev-parse", "export/a"))
        self.assertEqual(out["files"], ["src/a.cpp"])

    def test_branch_that_caught_up_with_main(self):
        r = self.repo
        run(r.root, "checkout", "-q", "-b", "patch/a")
        r.write("src/a.cpp", "int a() { return 10; }\n")
        r.commit("Match a")
        run(r.root, "checkout", "-q", "main")
        r.write("fork/tools/new.py", "pass\n")
        r.commit("Layer work on main")
        run(r.root, "checkout", "-q", "patch/a")
        run(r.root, "merge", "-q", "--no-ff", "-m", "Merge main", "main")
        out = r.export("patch/a")
        self.assertEqual(out["files"], ["src/a.cpp"])
        self.assertEqual(out["layer_left_out"], [])

    def test_fast_forwarded_branch_is_refused(self):
        r = self.repo
        run(r.root, "checkout", "-q", "-b", "patch/a")
        r.write("src/a.cpp", "int a() { return 10; }\n")
        r.commit("Match a")
        run(r.root, "checkout", "-q", "main")
        run(r.root, "merge", "-q", "--ff-only", "patch/a")
        with self.assertRaisesRegex(GitError, "--no-ff"):
            r.export("patch/a")

    def test_new_and_deleted_files(self):
        r = self.repo
        run(r.root, "checkout", "-q", "-b", "patch/c")
        r.write("src/c.cpp", "int c() { return 3; }\n")
        (r.root / "src/b.cpp").unlink()
        r.commit("Replace b with c")
        r.export("patch/c", message="Replace b with c")
        self.assertEqual(run(r.root, "ls-tree", "-r", "--name-only", "export/c").split(), ["src/a.cpp", "src/c.cpp"])


class CheckLayer(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.repo = Repo(Path(self.tmp.name))

    def tearDown(self):
        self.tmp.cleanup()

    def test_pending_files_and_collisions(self):
        r = self.repo
        self.assertEqual(check_layer.pending_patch_files("upstream-master", "main", cwd=r.root), [])
        self.assertEqual(check_layer.upstream_layer_collisions("upstream-master", cwd=r.root), [])
        self.assertEqual(check_layer.upstream_layer_collisions("main", cwd=r.root), ["fork/README.md"])
        r.write("src/a.cpp", "int a() { return 10; }\n")
        r.write(".github/workflows/fork-checks.yml", "name: Old fork workflow\n")
        r.commit("Add a pending patch and a top-level fork workflow")
        self.assertEqual(
            check_layer.pending_patch_files("upstream-master", "main", cwd=r.root),
            [".github/workflows/fork-checks.yml", "src/a.cpp"],
        )

    def test_mixed_commit_is_reported(self):
        r = self.repo
        base = run(r.root, "rev-parse", "HEAD")
        run(r.root, "checkout", "-q", "-b", "patch/mixed")
        r.write("src/a.cpp", "int a() { return 10; }\n")
        r.write("fork/notes/a.md", "note\n")
        mixed = r.commit("Match a with notes")
        r.write("src/b.cpp", "int b() { return 20; }\n")
        r.commit("Match b")
        self.assertEqual(check_layer.mixed_commits(base, "patch/mixed", cwd=r.root), [mixed])


if __name__ == "__main__":
    unittest.main()
