#include <cassert>
#include "pso/system/GinjaParameterHandler.h"

static unsigned calls;
static u32 expected_value;
static u32 expected_changed;

static void unsigned_parameter(u32 value) {
    assert(value == expected_value);
    ++calls;
}

static void signed_parameter(s32 value) {
    assert(value == static_cast<s32>(expected_value));
    ++calls;
}

static void channel_counts(s32 value, s32 changed) {
    assert(value == static_cast<s32>(expected_value));
    assert(changed == static_cast<s32>(expected_changed));
    ++calls;
}

int main() {
    GinjaParameterHandler handlers[11];
    for (unsigned kind = 0; kind < 11; ++kind) {
        handlers[kind] = reinterpret_cast<GinjaParameterHandler>(unsigned_parameter);
    }
    handlers[1] = reinterpret_cast<GinjaParameterHandler>(signed_parameter);
    handlers[2] = reinterpret_cast<GinjaParameterHandler>(channel_counts);
    handlers[3] = 0; // The original table has no handler for this kind.

    // Exercise both ordinary values and signed arguments after round-tripping
    // through the unsigned storage ABI. This tests signatures, not GC layout.
    for (unsigned pass = 0; pass < 2; ++pass) {
        for (u8 kind = 0; kind < 11; ++kind) {
            if (kind == 3) continue;
            expected_value = pass ? static_cast<u32>(-1L) : 37 + kind;
            expected_changed = pass ? static_cast<u32>(-2L) : 0xF000 + kind;
            invoke_ginja_parameter_handler(handlers[kind], kind,
                                           expected_value, expected_changed);
        }
    }
    assert(calls == 20);
}
