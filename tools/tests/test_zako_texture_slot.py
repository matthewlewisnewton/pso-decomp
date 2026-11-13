"""Check the actual Zako reader expression through the shared pointer declaration.

The fixture uses the real slot and setter headers in separate translation units,
but supplies its own storage and setter. Its allocated opaque objects are not a
claim about native Ginja layouts, the integer-returning BML getter, asset loading,
cache lifetime, or the rest of the renderer. No original files are required.
"""
from pathlib import Path
import os
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
READER = ROOT / "src/pso/boss/TBoss4ZakoDraw_8030A96C.cpp"
WRITER = ROOT / "src/pso/boss/TBoss4ZakoDraw_8030AD58.cpp"
HEADER = "pso/boss/TBoss4ZakoTexture.h"

PRELUDE = r'''
#include "pso/boss/TBoss4ZakoTexture.h"
#include "pso/system/CurrentTextureList.h"
#include <cassert>
#include <cstring>
#include <type_traits>
static_assert(std::is_same<decltype(falz_zako_texture_list), GinjaTextureList *>::value,
              "The shared cache must hold a pointer");
struct GinjaTextureList { unsigned fixture_only; };
void publish_fixture(GinjaTextureList *);
static GinjaTextureList *observed;
static unsigned calls;
s32 set_current_texture_list(GinjaTextureList *list) {
    observed = list;
    ++calls;
    return 1;
}
void read_actual_expression() {
'''
CASES = r'''
}
int main(int argc, char **argv) {
    assert(argc == 2);
    GinjaTextureList *first = new GinjaTextureList{1};
    GinjaTextureList *second = new GinjaTextureList{2};
    assert(first != second);
    for (unsigned i = 0; i < 10000; ++i) {
        GinjaTextureList *expected;
        if (std::strcmp(argv[1], "null") == 0) {
            expected = nullptr;
        } else if (std::strcmp(argv[1], "allocated") == 0) {
            expected = first;
        } else {
            assert(std::strcmp(argv[1], "replace") == 0);
            expected = i % 3 == 0 ? nullptr : (i % 3 == 1 ? first : second);
        }
        publish_fixture(expected);
        observed = expected == first ? second : first;
        unsigned before = calls;
        read_actual_expression();
        assert(calls == before + 1);
        assert(observed == expected);
        assert(falz_zako_texture_list == expected);
    }
    publish_fixture(nullptr);
    delete first;
    delete second;
}
'''
STORAGE = r'''
#include "pso/boss/TBoss4ZakoTexture.h"
GinjaTextureList *falz_zako_texture_list;
void publish_fixture(GinjaTextureList *value) {
    falz_zako_texture_list = value;
}
'''


class ZakoTextureSlot(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++")
        if compiler is None:
            raise unittest.SkipTest("g++ is required for source characterization")
        source = READER.read_text()
        match = re.search(r"(?ms)^void TObjPlayer::draw_area_chunk_objects\(\) \{(.*?)^\}", source)
        if match is None:
            raise AssertionError("Cannot find the checked-in reader")
        statements = re.findall(r"(?m)^\s*(set_current_texture_list\([^;]*\);)", match.group(1))
        if statements != ["set_current_texture_list(falz_zako_texture_list);"]:
            raise AssertionError("Expected one direct typed reader expression")
        for path in (READER, WRITER):
            if f'#include "{HEADER}"' not in path.read_text():
                raise AssertionError(f"Missing shared declaration in {path.name}")
            if re.search(r"extern\s+[^;\n]+\bfalz_zako_texture_list\s*;", path.read_text()):
                raise AssertionError(f"Duplicate local slot declaration in {path.name}")
        tmp = tempfile.TemporaryDirectory()
        cls.addClassCleanup(tmp.cleanup)
        path = Path(tmp.name)
        reader, storage = path / "reader.cpp", path / "storage.cpp"
        reader.write_text(PRELUDE + statements[0] + CASES)
        storage.write_text(STORAGE)
        cls.binary = path / "texture_slot"
        flags = ["-std=c++17", "-O2", "-Wall", "-Wextra", "-Werror"]
        if os.environ.get("PSO_TEST_SANITIZERS") == "1":
            flags += ["-fsanitize=address,undefined", "-fno-sanitize-recover=all",
                      "-fno-omit-frame-pointer", "-fno-pie", "-no-pie"]
        result = subprocess.run([compiler, *flags, "-iquote", str(ROOT / "include"),
                                 str(reader), str(storage), "-o", str(cls.binary)],
                                capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)

    def run_case(self, name):
        env = dict(os.environ, UBSAN_OPTIONS="halt_on_error=1:print_stacktrace=1",
                   ASAN_OPTIONS="halt_on_error=1:detect_leaks=1")
        result = subprocess.run([str(self.binary), name], capture_output=True,
                                text=True, timeout=5, env=env)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_allocated_pointer_is_passed_unchanged(self):
        self.run_case("allocated")

    def test_null_is_passed_unchanged(self):
        self.run_case("null")

    def test_reader_observes_replaced_slot_each_time(self):
        self.run_case("replace")


if __name__ == "__main__":
    unittest.main()
