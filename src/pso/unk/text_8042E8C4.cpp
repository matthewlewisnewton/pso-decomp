#include "pso/network/ModemLaunchContext.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSReset.h"
#include "string.h"

// Copies the launch context and payload to the reserved record at 0x80003100,
// shuts down the OS, clears the image's BSS and relocates its text/data sections.
// The image header comes from ctx->field_104, not from ctx itself.
//
// The final transfer uses LR without linking or restoring the loader's frame.
// The experimental C++ entry call does not reproduce that transfer. Keep the
// existing generated provider until an exact source replacement is established;
// see docs/evidence/launch-dol-cpp-recovery.md for the bounded compiler evidence.
//
// Source: zeroz41/pso-decomp #172, src/pso/unk/text_8042E8C4.cpp
// (refs/upstream-pr/172, commit d5ab5a472; same text at #189 943ce88c2).

extern "C" {

asm void LaunchDol(register ModemLaunchContext *ctx) {
#include "orig_asm/pso/unk/text_8042E8C4/LaunchDol.inc"
}

}
