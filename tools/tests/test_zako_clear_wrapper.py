"""Characterize the checked-in clear wrapper and cleanup call ordering.

The real wrapper header is used by two fixture translation units. The actual
wrapper and cleanup bodies call fixture methods/destructor; no enemy/resource
layout, buffer storage, native return-register state or rendering is modeled.
Native compilation and full object validation remain separate requirements.
"""
from pathlib import Path
import os
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
WRAPPER = ROOT / "src/pso/boss/TBoss4ZakoDraw_8030AD38.cpp"
CLEANUP = ROOT / "src/pso/object/TObjDFHorming.cpp"
HEADER = "pso/boss/TBoss4ZakoDraw_8030AD38.h"

PRELUDE = r'''
#include "pso/boss/TBoss4ZakoDraw_8030AD38.h"
#include <cassert>
#include <cstring>
#include <type_traits>
static_assert(std::is_same<decltype(&TBoss4DarkFalz__sub_8030AD38),
                           void (*)()>::value, "The wrapper has no input/result");
struct TBoss4DarkFalz {
    static void clear_uro_link_state();
    static void free_global_instance();
    static void cleanup_global();
};
static unsigned events[3], event_count, clear_calls;
static void record(unsigned event) {
    assert(event_count < 3);
    events[event_count++] = event;
}
void TBoss4DarkFalz::free_global_instance() { record(1); }
void TBoss4DarkFalz::clear_uro_link_state() { ++clear_calls; record(2); }
struct BmlResource { ~BmlResource() { record(3); } };
static BmlResource *darkfalz_dat_resource;
void call_from_other_unit();
'''
CASES = r'''
int main(int argc, char **argv) {
    assert(argc == 2);
    if (std::strcmp(argv[1], "once") == 0 ||
        std::strcmp(argv[1], "repeat") == 0) {
        unsigned count = std::strcmp(argv[1], "once") == 0 ? 1 : 10000;
        for (unsigned i = 0; i < count; ++i) {
            event_count = 0;
            call_from_other_unit();
            assert(clear_calls == i + 1);
            assert(event_count == 1 && events[0] == 2);
        }
    } else {
        assert(std::strcmp(argv[1], "resource") == 0 ||
               std::strcmp(argv[1], "null") == 0);
        bool has_resource = std::strcmp(argv[1], "resource") == 0;
        darkfalz_dat_resource = has_resource ? new BmlResource : nullptr;
        TBoss4DarkFalz::cleanup_global();
        assert(clear_calls == 1);
        assert(event_count == (has_resource ? 3u : 2u));
        assert(events[0] == 1 && events[1] == 2);
        if (has_resource) assert(events[2] == 3);
        assert(darkfalz_dat_resource == nullptr);
    }
}
'''
CALLER = r'''
#include "pso/boss/TBoss4ZakoDraw_8030AD38.h"
void call_from_other_unit() { TBoss4DarkFalz__sub_8030AD38(); }
'''


class ZakoClearWrapper(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = shutil.which("g++")
        if compiler is None:
            raise unittest.SkipTest("g++ is required for source characterization")
        wrapper = re.search(r"(?m)^void TBoss4DarkFalz__sub_8030AD38\(void\) \{[^\n]*\}",
                            WRAPPER.read_text())
        cleanup = re.search(r"(?m)^void TBoss4DarkFalz::cleanup_global\(\) \{[^\n]*\}",
                            CLEANUP.read_text())
        if wrapper is None or cleanup is None:
            raise AssertionError("Cannot find the checked-in wrapper/cleanup body")
        for path in (WRAPPER, CLEANUP):
            if f'#include "{HEADER}"' not in path.read_text():
                raise AssertionError(f"Missing shared wrapper declaration in {path.name}")
        if '#include "pso/boss/TBoss4DarkFalz.h"' not in WRAPPER.read_text():
            raise AssertionError("Wrapper must use the canonical class declaration")
        if "clear_uro_link_state__14TBoss4DarkFalzFv" in WRAPPER.read_text():
            raise AssertionError("Raw incompatible clearer alias remains")
        tmp = tempfile.TemporaryDirectory()
        cls.addClassCleanup(tmp.cleanup)
        path = Path(tmp.name)
        fixture, caller = path / "wrapper.cpp", path / "caller.cpp"
        fixture.write_text(PRELUDE + wrapper.group(0) + "\n" + cleanup.group(0) + CASES)
        caller.write_text(CALLER)
        cls.binary = path / "clear_wrapper"
        flags = ["-std=c++17", "-O2", "-Wall", "-Wextra", "-Werror"]
        if os.environ.get("PSO_TEST_SANITIZERS") == "1":
            flags += ["-fsanitize=address,undefined", "-fno-sanitize-recover=all",
                      "-fno-omit-frame-pointer", "-fno-pie", "-no-pie"]
        result = subprocess.run([compiler, *flags, "-iquote", str(ROOT / "include"),
                                 str(fixture), str(caller), "-o", str(cls.binary)],
                                capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise AssertionError(result.stdout + result.stderr)

    def run_case(self, name):
        env = dict(os.environ, UBSAN_OPTIONS="halt_on_error=1:print_stacktrace=1",
                   ASAN_OPTIONS="halt_on_error=1:detect_leaks=1")
        result = subprocess.run([str(self.binary), name], capture_output=True,
                                text=True, timeout=5, env=env)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_wrapper_calls_clear_once(self):
        self.run_case("once")

    def test_repeated_wrapper_calls(self):
        self.run_case("repeat")

    def test_cleanup_order_and_resource_reset(self):
        self.run_case("resource")

    def test_cleanup_with_null_resource(self):
        self.run_case("null")


if __name__ == "__main__":
    unittest.main()
