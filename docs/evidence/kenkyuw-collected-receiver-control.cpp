// Independent compiler-lifetime control; not PSO source or a PSO ABI.
struct Receiver { unsigned state; };
struct Event { unsigned code, body; };
extern "C" Event *collect_event(Receiver *);
extern "C" void notify_miss(Receiver *);
extern "C" int check_event(Receiver *, unsigned);
extern "C" void complete_event(Receiver *, unsigned);

// A real post-check read/update keeps the active receiver and event alive.
// The configured fallback also survives because it is returned to the caller.
extern "C" Receiver *collect_check_and_get_fallback(
    Receiver *active, Receiver *fallback, int use_fallback) {
    Event *event = collect_event(active);
    if (event == 0) {
        notify_miss(active);
        return fallback;
    }
    Receiver *receiver = use_fallback ? fallback : active;
    if (check_event(receiver, event->code)) {
        unsigned code = event->code;
        if (code != 0) {
            active->state = event->body;
            complete_event(active, code);
        }
    }
    return fallback;
}

#ifdef KENKYUW_WITNESS_HOST_CHECK
#include <cassert>
#include <cstdio>
static Receiver *expected_active, *expected_receiver;
static Event *event_result;
static int allow_check, mutation;
static unsigned collect_calls, miss_calls, check_calls, complete_calls;
static unsigned checked_code, completed_code;
extern "C" Event *collect_event(Receiver *receiver) {
    assert(receiver == expected_active); ++collect_calls; return event_result;
}
extern "C" void notify_miss(Receiver *receiver) {
    assert(receiver == expected_active); ++miss_calls;
}
extern "C" int check_event(Receiver *receiver, unsigned code) {
    assert(receiver == expected_receiver && code == checked_code); ++check_calls;
    if (mutation == 1) event_result->code = 0;
    if (mutation == 2) event_result->code = 7;
    event_result->body = 29;
    return allow_check;
}
extern "C" void complete_event(Receiver *receiver, unsigned code) {
    assert(receiver == expected_active); ++complete_calls; completed_code = code;
}
int main() {
    const unsigned codes[] = {0, 1, 0x7fffffffU, 0x80000000U, 0xffffffffU};
    const int selections[] = {0, 1, -1, 2};
    unsigned cases = 0;
    for (unsigned i = 0; i < 6; ++i)
    for (unsigned j = 0; j < 4; ++j)
    for (allow_check = 0; allow_check < 2; ++allow_check)
    for (mutation = 0; mutation < 3; ++mutation) {
        Receiver active = {11}, fallback = {22};
        Event event = {i < 5 ? codes[i] : 0, 19};
        event_result = i < 5 ? &event : 0;
        expected_active = &active;
        expected_receiver = selections[j] ? &fallback : &active;
        checked_code = event.code;
        collect_calls = miss_calls = check_calls = complete_calls = 0;
        Receiver *result = collect_check_and_get_fallback(&active, &fallback, selections[j]);
        assert(result == &fallback && collect_calls == 1 && fallback.state == 22);
        assert(miss_calls == (event_result ? 0U : 1U));
        assert(check_calls == (event_result ? 1U : 0U));
        unsigned post_code = mutation == 1 ? 0 : mutation == 2 ? 7 : checked_code;
        bool complete = event_result && allow_check && post_code;
        assert(complete_calls == (complete ? 1U : 0U));
        assert(active.state == (complete ? 29U : 11U));
        if (complete) assert(completed_code == post_code);
        ++cases;
    }
    std::printf("PASS: collector, receiver and post-check lifetimes; %u cases\n", cases);
}

#endif
