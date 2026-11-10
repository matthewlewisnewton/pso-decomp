"""Run modem receive/control bodies with synthetic hardware, without original inputs.

The harness uses 32-bit scalar types and host pointers. It checks state and call
ordering, not native record layout, frame matching, or actual hardware behavior.
"""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def extract_block(source: str, pattern: str) -> str:
    """Extract these conventionally formatted top-level records/functions."""
    match = re.search(pattern, source, re.MULTILINE)
    if match is None:
        raise AssertionError(f"missing source block: {pattern}")
    end = source.index("\n}", match.start()) + 2
    return source[match.start():end]


class ModemReceiveTests(unittest.TestCase):
    @unittest.skipUnless(shutil.which("c++"), "host C++ compiler is unavailable")
    def test_receive_state_and_device_call_order(self):
        source = (ROOT / "src/pso/network/ModemRuntime.cpp").read_text()
        records = "\n".join(
            extract_block(source, rf"^struct {name} \{{") + ";"
            for name in ("ModemSendState", "ModemReceiveState", "ModemExiState")
        )
        functions = "\n".join(
            extract_block(source, rf"^(?:static inline s32|s32|void) {name}\([^;]*?\)\s*\{{")
            for name in (
                "ModemMin",
                "TAdSinglePlyChrSelectGC__sub_8042BF6C",
                "TAdSinglePlyChrSelectGC__sub_8042C124",
                "TAdSinglePlyChrSelectGC__sub_8042D7E0",
            )
        )
        fixture = (ROOT / "tools/tests/fixtures/modem_receive_harness.cpp.in").read_text()
        fixture = fixture.replace("@@RECORDS@@", records).replace("@@FUNCTIONS@@", functions)
        with tempfile.TemporaryDirectory() as temporary:
            cpp = Path(temporary) / "receive.cpp"
            executable = Path(temporary) / "receive"
            cpp.write_text(fixture)
            compiled = subprocess.run(
                [shutil.which("c++"), "-std=c++17", "-O2", str(cpp), "-o", str(executable)],
                capture_output=True, text=True,
            )
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            result = subprocess.run([str(executable)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("8 receive state/order scenarios PASS", result.stdout)


    @unittest.skipUnless(shutil.which("c++"), "host C++ compiler is unavailable")
    def test_dispatch_and_initialization_order(self):
        source = (ROOT / "src/pso/network/ModemRuntime.cpp").read_text()
        records = "\n".join(
            extract_block(source, rf"^struct {name} \{{") + ";"
            for name in (
                "ModemSendState", "ModemReceiveState", "ModemExiState",
                "ModemResponseState", "RecoveredGlobal_8042E768_lbl_805D1D20",
            )
        )
        functions = "\n".join(
            extract_block(source, rf"^(?:static inline (?:s32|u8)|s32|void) {name}\([^;]*?\)\s*\{{")
            for name in (
                "ModemMin", "ModemHighestStatusBit",
                "TAdSinglePlyChrSelectGC__sub_8042C2E4",
                "TAdSinglePlyChrSelectGC__sub_8042CEF8",
            )
        )
        fixture = (ROOT / "tools/tests/fixtures/modem_control_harness.cpp.in").read_text()
        fixture = fixture.replace("@@RECORDS@@", records).replace("@@FUNCTIONS@@", functions)
        with tempfile.TemporaryDirectory() as temporary:
            cpp = Path(temporary) / "control.cpp"
            executable = Path(temporary) / "control"
            cpp.write_text(fixture)
            compiled = subprocess.run(
                [shutil.which("c++"), "-std=c++17", "-O2", str(cpp), "-o", str(executable)],
                capture_output=True, text=True,
            )
            self.assertEqual(compiled.returncode, 0, compiled.stdout + compiled.stderr)
            result = subprocess.run([str(executable)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            self.assertIn("65536 status/mask pairs and control-path scenarios PASS", result.stdout)


if __name__ == "__main__":
    unittest.main()
