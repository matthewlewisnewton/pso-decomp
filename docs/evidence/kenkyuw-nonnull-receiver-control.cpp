// Independent compiler reference-contract control; not a PSO ABI change.
struct Receiver { unsigned state; };
struct Event { unsigned code, body; };
extern "C" Event *collect_event(Receiver *);
extern "C" void notify_miss(Receiver *);
extern "C" int check_event(Receiver *, unsigned);
extern "C" void complete_event(Receiver *, unsigned);

// Independent reference-contract control. The receiver is a valid object;
// collection may still fail. No PSO declaration or ABI is changed.
extern "C" void check_collected_reference(Receiver &active) {
    Event *event = collect_event(&active);
    Receiver *receiver = event != 0 ? &active : 0;
    if (receiver == 0) {
        notify_miss(&active);
    } else if (check_event(receiver, event->code)) {
        unsigned code = event->code;
        if (code != 0) {
            active.state = event->body;
            complete_event(&active, code);
        }
    }
}

#ifdef KENKYUW_WITNESS_HOST_CHECK
#include <cassert>
#include <cstdio>
#include <vector>
static Receiver *expected_active;
static Event *event_result;
static int allow_check, mutation;
static std::vector<unsigned> observed;
extern "C" Event *collect_event(Receiver *r) {
    assert(r == expected_active); observed.push_back(100); return event_result;
}
extern "C" void notify_miss(Receiver *r) {
    assert(r == expected_active); observed.push_back(200); r->state = 3;
}
extern "C" int check_event(Receiver *r, unsigned code) {
    assert(r == expected_active); observed.push_back(300); observed.push_back(code);
    if (mutation == 1) event_result->code = 0;
    if (mutation == 2) event_result->code = 7;
    event_result->body = 29;
    return allow_check;
}
extern "C" void complete_event(Receiver *r, unsigned code) {
    assert(r == expected_active && r->state == 29);
    observed.push_back(400); observed.push_back(code);
}
static void reference_dispatch(Receiver &active) {
    Event *event = collect_event(&active);
    if (event == 0) {
        notify_miss(&active);
    } else if (check_event(&active, event->code)) {
        unsigned code = event->code;
        if (code != 0) {
            active.state = event->body;
            complete_event(&active, code);
        }
    }
}
int main() {
    const unsigned codes[] = {0, 1, 0x7fffffffU, 0x80000000U, 0xffffffffU};
    unsigned cases = 0;
    for (unsigned i = 0; i < 6; ++i)
    for (allow_check = 0; allow_check < 2; ++allow_check)
    for (mutation = 0; mutation < 3; ++mutation) {
        Receiver active = {11}; expected_active = &active;
        Event before = {i < 5 ? codes[i] : 0, 19}, after = before;
        event_result = i < 5 ? &before : 0; observed.clear();
        reference_dispatch(active);
        std::vector<unsigned> expected = observed;
        unsigned expected_state = active.state;
        active.state = 11;
        event_result = i < 5 ? &after : 0; observed.clear();
        check_collected_reference(active);
        assert(observed == expected && active.state == expected_state);
        assert(before.code == after.code && before.body == after.body);
        ++cases;
    }
    std::printf("PASS: nonnull receiver, nullable collection, post-check mutation; %u cases\n", cases);
}

#endif
