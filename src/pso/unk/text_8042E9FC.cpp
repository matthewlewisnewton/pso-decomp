// Native reconstruction of the restore at 0x8042E9FC..0x8042EA10.
// This local fragment is not a separately callable C++ operation. Preserve
// its existing symbol/extent without asserting an original source boundary.
// The native linker otherwise discards it because no relocation names it.
// See docs/evidence/loader-restore-retention.md for the exception and port plan.
#ifdef __MWERKS__
#pragma push
#pragma force_active on
extern "C" {
static asm void pad_03_8042E9FC_text(void) {
#include "orig_asm/pso/unk/text_8042E9FC/pad_03_8042E9FC_text.inc"
}
}
#pragma pop
#else
#include <pso/port/LoaderTransfer.h>

namespace pso { namespace port {
bool step_loader_restore(LoaderState& state, LoaderBackend& backend) {
    switch (state.pc) {
    case 0x8042E9FCu: {
        const uint32_t stack = state.gpr[1];
        for (unsigned reg = 26; reg < 32; ++reg)
            state.gpr[reg] = backend.load_u32_be(uint32_t(stack + 8u + (reg - 26u) * 4u));
        break;
    }
    case 0x8042EA00u:
        state.gpr[0] = backend.load_u32_be(uint32_t(state.gpr[1] + 0x24u));
        break;
    case 0x8042EA04u:
        state.lr = state.gpr[0];
        break;
    case 0x8042EA08u:
        state.gpr[1] = uint32_t(state.gpr[1] + 0x20u);
        break;
    case 0x8042EA0Cu:
        state.pc = state.lr & ~uint32_t(3);
        return true;
    default:
        return false;
    }
    state.pc += 4u;
    return true;
}
} }
#endif
