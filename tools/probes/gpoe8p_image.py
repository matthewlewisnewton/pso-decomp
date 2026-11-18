"""Run named routines from a matching GPOE8P image with simulated dependencies."""
import hashlib
from pathlib import Path
import re
import struct

from unicorn import Uc, UC_ARCH_PPC, UC_HOOK_CODE, UC_MODE_BIG_ENDIAN, UC_MODE_PPC32
from unicorn import ppc_const as ppc

ROOT = Path(__file__).resolve().parents[2]
SYMBOLS = ROOT / "config/GPOE8P/psov3/symbols.txt"
RETAIL_SHA1 = "0d85744b51d7379efb025a943d0cd5aaae2191a3"
RETURN = 0x80001000
STACK = 0x81108000
MASK = 0xFFFFFFFF


class GameImage:
    def __init__(self, dol):
        if hashlib.sha1(dol).hexdigest() != RETAIL_SHA1:
            raise ValueError("Expected the matching GPOE8P DOL")
        self.symbols = {
            name: int(address, 16) for name, address in
            re.findall(r"^(\S+) = \.\w+:0x([\da-fA-F]+);", SYMBOLS.read_text(), re.MULTILINE)
        }
        self.cpu = Uc(UC_ARCH_PPC, UC_MODE_PPC32 | UC_MODE_BIG_ENDIAN)
        self.cpu.mem_map(0x80000000, 0x700000)
        self.cpu.mem_map(0x81100000, 0x40000)
        for offset, address, size in zip(*(struct.unpack_from(">18I", dol, start)
                                           for start in (0, 0x48, 0x90))):
            if size:
                self.cpu.mem_write(address, dol[offset:offset + size])
        self.cpu.reg_write(ppc.UC_PPC_REG_2, 0x805DFD00)
        self.cpu.reg_write(ppc.UC_PPC_REG_13, 0x805DA600)
        self.calls = {}

    def hook(self, symbol, operation):
        def intercept(cpu, address, instruction_size, user_data):
            args = tuple(cpu.reg_read(reg) for reg in
                         (ppc.UC_PPC_REG_3, ppc.UC_PPC_REG_4, ppc.UC_PPC_REG_5))
            self.calls.setdefault(symbol, []).append(args)
            result = operation(*args)
            if result is not None:
                cpu.reg_write(ppc.UC_PPC_REG_3, result & MASK)
            cpu.reg_write(ppc.UC_PPC_REG_PC, cpu.reg_read(ppc.UC_PPC_REG_LR))

        address = self.symbols[symbol]
        self.cpu.hook_add(UC_HOOK_CODE, intercept, begin=address, end=address)

    def call(self, name, *args, instruction_limit=20_000):
        self.calls.clear()
        self.cpu.reg_write(ppc.UC_PPC_REG_1, STACK)
        for reg, arg in zip((ppc.UC_PPC_REG_3, ppc.UC_PPC_REG_4, ppc.UC_PPC_REG_5), args):
            self.cpu.reg_write(reg, arg & MASK)
        self.cpu.reg_write(ppc.UC_PPC_REG_LR, RETURN)
        self.cpu.emu_start(self.symbols[name], RETURN, count=instruction_limit)
        assert self.cpu.reg_read(ppc.UC_PPC_REG_PC) == RETURN, name
        return self.cpu.reg_read(ppc.UC_PPC_REG_3)
