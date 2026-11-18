"""Check the declarations and layouts used to read a BML archive's model table."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[2]
HEADER = "pso/system/BmlAccessors.h"
PROVIDER = "src/pso/unk/TLobby_8001EF5C.cpp"
ACCESSORS = {"get_bml_model": "NJS_OBJECT", "get_bml_texlist": "GinjaTextureList"}


class BmlAccessorContractTests(unittest.TestCase):
    def test_accessors_share_one_typed_declaration_and_definition(self):
        for name, result in ACCESSORS.items():
            signature = rf"\b{result}\s*\*\s*{name}\s*\(BmlResource\s*\*resource,\s*s32 index\)"
            with self.subTest(accessor=name):
                self.assertRegex((ROOT / "include" / HEADER).read_text(), signature + r"\s*;")
                self.assertRegex((ROOT / PROVIDER).read_text(), signature + r"\s*\{")

    def test_consumers_use_the_shared_declarations(self):
        for directory in ("src", "include/pso"):
            for path in (ROOT / directory).rglob("*"):
                if path.suffix not in (".h", ".c", ".cpp") or path == ROOT / "include" / HEADER:
                    continue
                source = re.sub(r"/\*.*?\*/|//[^\n]*", "", path.read_text(), flags=re.DOTALL)
                for name in ACCESSORS:
                    if not re.search(rf"\b{name}\s*\(", source):
                        continue
                    with self.subTest(path=path.relative_to(ROOT), accessor=name):
                        self.assertIn(f'#include "{HEADER}"', source)
                        self.assertNotRegex(source, rf"#\s*define\s+{name}\b")
                        self.assertNotRegex(
                            source, rf"(?:^|[;{{\n])\s*(?:extern\s+\"C\"\s+)?"
                            rf"(?:int|s32|u32|u8|void|[A-Z]\w*)\s*\**\s*{name}\([^;{{}}]*\)\s*;",
                        )

    def test_table_fields_supply_the_accessor_results(self):
        layout = (ROOT / "include/pso/system/BmlResource.h").read_text()
        provider = (ROOT / PROVIDER).read_text()
        for name, field in (("get_bml_model", "model"), ("get_bml_texlist", "m_c")):
            with self.subTest(accessor=name):
                self.assertRegex(layout, rf"\b{ACCESSORS[name]}\s*\*{field};")
                self.assertRegex(provider, rf"\b{name}\([^)]*\)\s*\{{\s*"
                                           rf"return resource->models\[index\]\.{field};\s*\}}")


if __name__ == "__main__":
    unittest.main()
