// Standalone compiler-behavior fixture; this is not PSO source or a PSO ABI.
// Both receiver choices and the returned fallback are observable API results.
struct Receiver { unsigned state; };
struct Event { unsigned code; };
extern "C" void deliver_event(Receiver *, unsigned);

extern "C" Receiver *dispatch_and_get_fallback(
    Receiver *active, const Event *event, Receiver *fallback, int use_fallback) {
    Receiver *receiver = use_fallback ? fallback : active;
    deliver_event(receiver, event->code);
    return fallback;
}

#ifdef KENKYUW_WITNESS_HOST_CHECK
#include <cassert>
#include <cstdio>
static Receiver *observed_receiver;
static unsigned observed_code;
static unsigned calls;
extern "C" void deliver_event(Receiver *receiver, unsigned code) {
    observed_receiver = receiver;
    observed_code = code;
    ++calls;
}
int main() {
    Receiver active = {11}, fallback = {22};
    const unsigned codes[] = {0, 1, 0x7fffffffU, 0x80000000U, 0xffffffffU};
    const int selections[] = {0, 1, -1, 2};
    for (unsigned i = 0; i < sizeof(codes) / sizeof(codes[0]); ++i) {
        for (unsigned j = 0; j < sizeof(selections) / sizeof(selections[0]); ++j) {
            Event event = {codes[i]};
            calls = 0;
            Receiver *result = dispatch_and_get_fallback(
                &active, &event, &fallback, selections[j]);
            assert(result == &fallback && calls == 1 && observed_code == codes[i]);
            assert(observed_receiver == (selections[j] ? &fallback : &active));
            assert(active.state == 11 && fallback.state == 22 && event.code == codes[i]);
        }
    }
    std::puts("PASS: event destination and retained fallback; 20 cases");
}
#endif
