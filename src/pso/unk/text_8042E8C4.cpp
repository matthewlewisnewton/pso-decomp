#ifdef __MWERKS__
#include "pso/network/ModemLaunchContext.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSReset.h"
#include "string.h"

// Copies the launch context and payload to the reserved record at 0x80003100,
// shuts down the OS, clears the image's BSS and relocates its text/data sections.
// The loader reads the image header from ctx->field_104.
//
// The final transfer branches through LR with the loader's frame still in
// place. The following restore is retained separately at 0x8042E9FC.
//
// Source: zeroz41/pso-decomp #172, src/pso/unk/text_8042E8C4.cpp
// (refs/upstream-pr/172, commit d5ab5a472; same text at #189 943ce88c2).

extern "C" {

asm void LaunchDol(register ModemLaunchContext *ctx) {
#include "orig_asm/pso/unk/text_8042E8C4/LaunchDol.inc"
}

}
#else
#include <pso/port/LoaderTransfer.h>

namespace pso { namespace port {
bool step_loader_handoff(LoaderState& state, LoaderBackend& backend) {
    switch (state.pc) {
    case 0x8042E9ECu:
        state.gpr[0] = backend.load_u32_be(uint32_t(state.gpr[26] + 0xE0u));
        break;
    case 0x8042E9F0u:
        backend.synchronize_instructions();
        break;
    case 0x8042E9F4u:
        state.lr = state.gpr[0];
        break;
    case 0x8042E9F8u:
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
