#ifndef PSO_PORT_LOADER_TRANSFER_H
#define PSO_PORT_LOADER_TRANSFER_H

#include <stdint.h>

namespace pso { namespace port {

// Guest addresses and registers, never host pointers or the host C++ frame.
// A backend retains all other PPC state (FPRs, MSR, etc.) unchanged.
struct LoaderState {
    uint32_t gpr[32];
    uint32_t lr, ctr, cr, xer, pc;
};

struct LoaderBackend {
    virtual ~LoaderBackend() {}
    // Read a numeric big-endian guest word. The backend owns address mapping,
    // alignment/access checks and fault handling; failure must not return a word.
    virtual uint32_t load_u32_be(uint32_t address) = 0;
    // Implement the guest instruction-stream synchronization boundary, including
    // any translated-code invalidation needed by the execution backend.
    virtual void synchronize_instructions() = 0;
};

// Execute one completed instruction at its original guest PC. False means this
// handler does not own the PC; neither state nor backend is touched. On true,
// dispatch the resulting guest PC, without a host function-pointer call.
bool step_loader_handoff(LoaderState& state, LoaderBackend& backend);
bool step_loader_restore(LoaderState& state, LoaderBackend& backend);

inline bool step_loader_boundary(LoaderState& state, LoaderBackend& backend) {
    return step_loader_handoff(state, backend) || step_loader_restore(state, backend);
}

} }
#endif
