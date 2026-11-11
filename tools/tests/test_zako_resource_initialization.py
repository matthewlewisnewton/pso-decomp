"""Characterize the actual Zako resource initializer with allocated host fixtures.

This checks source control flow and field updates, not the native pointer layout,
constructor ABI, rendering, or arbitrary invalid BML resources. The texture getter
returns the existing integer handle; its zero fixture avoids a host pointer claim.
"""
from pathlib import Path
import os
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pso/boss/TBoss4ZakoDraw_8030AD58.cpp"

PRELUDE = r"""
#include <cassert>
#include <cstdint>
#include <cstring>
using s32 = std::int32_t;
using u32 = std::uint32_t;
struct GinjaTextureList {};
struct BmlResource {};
struct NJS_OBJECT { u32 evalflags; void *model; NJS_OBJECT *child; };
struct TBoss4Uro { static BmlResource *get_instance_count(); };
struct TBoss4DarkFalz { static void init_uro_link(); static void clear_uro_link_state(); };
static BmlResource resource;
static NJS_OBJECT root, child;
static GinjaTextureList old_texture;
static int old_model, new_model;
static int resource_calls, model_calls, texture_calls, clear_calls;
static GinjaTextureList *falz_zako_texture_list;
static void *falz_zako_chunk_model;
static s32 TBoss4ZakoDraw__rotation_phase;
BmlResource *TBoss4Uro::get_instance_count() { ++resource_calls; return &resource; }
s32 TObjFish__sub_8001EDB0(BmlResource *r, s32 index) {
    assert(r == &resource && index == 8); ++texture_calls; return 0;
}
NJS_OBJECT *get_bml_model(BmlResource *r, s32 index) {
    assert(r == &resource && index == 8); ++model_calls; return &root;
}
void TBoss4DarkFalz::clear_uro_link_state() { ++clear_calls; }
"""

CASES = r"""
int main(int argc, char **argv) {
    assert(argc == 2);
    const bool has_model = std::strcmp(argv[1], "model") == 0;
    root.child = &child;
    child.evalflags = 0xA5A5A5A7u;
    child.model = has_model ? &new_model : nullptr;
    falz_zako_texture_list = &old_texture;
    falz_zako_chunk_model = &old_model;
    TBoss4ZakoDraw__rotation_phase = 3;
    TBoss4DarkFalz::init_uro_link();
    assert(resource_calls == 2 && texture_calls == 1 && model_calls == 1);
    assert(child.evalflags == 0xA5A5A5A5u);
    assert(falz_zako_texture_list == nullptr);
    assert(falz_zako_chunk_model == (has_model ? &new_model : &old_model));
    assert(TBoss4ZakoDraw__rotation_phase == (has_model ? 0 : 3));
    assert(clear_calls == (has_model ? 1 : 0));
}
"""

class ZakoResourceInitialization(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++")
        if compiler is None:
            raise unittest.SkipTest("g++ is required for source characterization")
        body = re.search(r"(?ms)^void TBoss4DarkFalz::init_uro_link\(\) \{.*?^\}", SOURCE.read_text())
        if body is None:
            raise AssertionError("Cannot find the checked-in initializer")
        tmp = tempfile.TemporaryDirectory()
        cls.addClassCleanup(tmp.cleanup)
        path = Path(tmp.name)
        harness = path / "zako_resource.cpp"
        harness.write_text(PRELUDE + body.group(0) + CASES)
        cls.binary = path / "zako_resource"
        flags = ["-std=c++17", "-O2"]
        if os.environ.get("PSO_TEST_SANITIZERS") == "1":
            flags += ["-fsanitize=address,undefined", "-fno-omit-frame-pointer"]
        result = subprocess.run([compiler, *flags, str(harness), "-o", str(cls.binary)],
                                capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)

    def run_case(self, name):
        result = subprocess.run([str(self.binary), name], capture_output=True, text=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_child_model_resets_state_and_publishes_model(self):
        self.run_case("model")

    def test_null_child_model_preserves_previous_model_and_phase(self):
        self.run_case("null")

if __name__ == "__main__":
    unittest.main()
