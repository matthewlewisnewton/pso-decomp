#include <pso/port/LoaderTransfer.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

using namespace pso::port;

struct Memory : LoaderBackend {
    std::map<uint32_t, uint32_t> words;
    std::vector<uint32_t> reads;
    unsigned syncs;
    Memory() : syncs(0) {}
    uint32_t load_u32_be(uint32_t address) {
        reads.push_back(address);
        if (words.find(address) == words.end()) throw std::runtime_error("guest memory fault");
        return words[address];
    }
    void synchronize_instructions() { ++syncs; }
};

static void require(bool ok, const char* message) {
    if (!ok) { std::cerr << message << '\n'; std::exit(1); }
}

static LoaderState initial() {
    LoaderState state = {};
    for (unsigned i = 0; i < 32; ++i) state.gpr[i] = 0x10000000u + i;
    state.lr = 0x1234567Bu;
    state.ctr = 0x87654321u;
    state.cr = 0xABCD0123u;
    state.xer = 0xE000007Fu;
    return state;
}

static bool same(const LoaderState& a, const LoaderState& b) {
    for (unsigned i = 0; i < 32; ++i) if (a.gpr[i] != b.gpr[i]) return false;
    return a.lr == b.lr && a.ctr == b.ctr && a.cr == b.cr && a.xer == b.xer && a.pc == b.pc;
}

// Decimal, one case per line: 32 GPRs, LR/CTR/CR/XER/PC, number of memory
// words, then address/value pairs. Result: handled, state, syncs, read addresses.
// This also lets the original-code differential probe test these actual units.
static int stream() {
    LoaderState state;
    while (std::cin >> state.gpr[0]) {
        for (unsigned i = 1; i < 32; ++i) std::cin >> state.gpr[i];
        std::cin >> state.lr >> state.ctr >> state.cr >> state.xer >> state.pc;
        Memory memory;
        unsigned count;
        std::cin >> count;
        if (!std::cin || count > 1024) return 2;
        for (unsigned i = 0; i < count; ++i) {
            uint32_t address, word;
            std::cin >> address >> word;
            if (!std::cin) return 2;
            memory.words[address] = word;
        }
        std::cout << step_loader_boundary(state, memory);
        for (unsigned i = 0; i < 32; ++i) std::cout << ' ' << state.gpr[i];
        std::cout << ' ' << state.lr << ' ' << state.ctr << ' ' << state.cr
                  << ' ' << state.xer << ' ' << state.pc << ' ' << memory.syncs;
        for (unsigned i = 0; i < memory.reads.size(); ++i) std::cout << ' ' << memory.reads[i];
        std::cout << '\n';
    }
    return std::cin.eof() ? 0 : 2;
}

int main(int argc, char** argv) {
    if (argc == 2 && std::string(argv[1]) == "--stream") return stream();

    Memory memory;
    LoaderState state = initial();
    state.pc = 0x8042E9ECu;
    const LoaderState before = state;
    memory.words[state.gpr[26] + 0xE0u] = 0x90001003u;
    require(step_loader_boundary(state, memory), "handoff load");
    require(memory.reads.size() == 1 && memory.syncs == 0, "load before synchronization");
    require(step_loader_boundary(state, memory) && memory.syncs == 1, "isync callback");
    require(step_loader_boundary(state, memory) && state.lr == 0x90001003u, "dynamic LR target");
    require(step_loader_boundary(state, memory) && state.pc == 0x90001000u, "masked nonlinking branch");
    LoaderState expected = before;
    expected.gpr[0] = expected.lr = 0x90001003u;
    expected.pc = 0x90001000u;
    require(same(state, expected), "handoff preserves frame and all other state");
    require(!step_loader_boundary(state, memory), "target belongs to execution dispatcher");

    memory = Memory();
    state = initial();
    state.pc = 0x8042E9FCu;
    state.gpr[1] = 0xFFFFFFF0u;
    expected = state;
    for (unsigned i = 0; i < 6; ++i) {
        memory.words[uint32_t(state.gpr[1] + 8u + 4u * i)] = 0xCAFE0000u + i;
        expected.gpr[26 + i] = 0xCAFE0000u + i;
    }
    memory.words[0x14u] = 0xA0000003u;
    for (unsigned i = 0; i < 5; ++i) require(step_loader_boundary(state, memory), "restore instruction");
    expected.gpr[0] = expected.lr = 0xA0000003u;
    expected.gpr[1] = 0x10u;
    expected.pc = 0xA0000000u;
    require(same(state, expected), "full restore including 32-bit wrapping");
    require(memory.syncs == 0 && memory.reads.size() == 7, "restore memory accesses");
    for (unsigned i = 0; i < 6; ++i)
        require(memory.reads[i] == uint32_t(0xFFFFFFF8u + 4u * i), "ordered lmw loads");
    require(memory.reads[6] == 0x14u, "saved LR address uses original stack");

    // Invalid and unaligned PCs must leave state and the backend untouched.
    const uint32_t invalid[] = {0, 0x8042E9E8u, 0x8042E9EDu, 0x8042EA10u, 0xFFFFFFFFu};
    for (unsigned i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
        memory = Memory();
        state = initial(); state.pc = invalid[i]; expected = state;
        require(!step_loader_boundary(state, memory) && same(state, expected), "unowned PC");
        require(memory.reads.empty() && !memory.syncs, "unowned PC has no backend effects");
    }

    memory = Memory();
    state = initial(); state.pc = 0x8042EA00u; expected = state;
    bool faulted = false;
    try { step_loader_boundary(state, memory); }
    catch (const std::runtime_error&) { faulted = true; }
    require(faulted && same(state, expected), "failed load propagates without advancing PC");
    std::cout << "loader transfer tests passed\n";
}
