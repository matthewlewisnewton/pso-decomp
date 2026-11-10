// Independent lvalue control, not a proposed PSO layout or dispatcher.
struct Receiver { unsigned state; };
struct Event { unsigned code, body; };
struct Slots { Receiver *first, *second; };
extern "C" Event *collect_slots(Slots *);
extern "C" void miss_slots(Slots *);
extern "C" int inspect_slot(Receiver *, unsigned);

extern "C" Receiver *check_selected_slot(Slots *slots, int choose_second) {
    Event *event = collect_slots(slots);
    if (event == 0) {
        miss_slots(slots);
        return 0;
    }
    Receiver *&selected = choose_second ? slots->second : slots->first;
    if (inspect_slot(selected, event->code))
        return selected; // The callback may replace the selected slot.
    return 0;
}

#ifdef KENKYUW_WITNESS_HOST_CHECK
#include <cassert>
#include <cstdio>
static Slots *current;
static Event *event_result;
static Receiver *replacement, *seen_receiver;
static unsigned seen_code, checks, misses;
static int allow_check, selected_index;
extern "C" Event *collect_slots(Slots *s) {
    assert(s == current); return event_result;
}
extern "C" void miss_slots(Slots *s) {
    assert(s == current); ++misses;
    s->first = replacement; s->second = replacement;
}
extern "C" int inspect_slot(Receiver *r, unsigned code) {
    ++checks; seen_receiver = r; seen_code = code;
    if (selected_index) current->second = replacement;
    else current->first = replacement;
    return allow_check;
}
int main() {
    Receiver a = {1}, b = {2}, c = {3};
    Receiver *values[] = {0, &a, &b};
    unsigned cases = 0;
    for (unsigned null_event = 0; null_event < 2; ++null_event)
    for (selected_index = 0; selected_index < 2; ++selected_index)
    for (unsigned i = 0; i < 3; ++i)
    for (unsigned j = 0; j < 3; ++j)
    for (allow_check = 0; allow_check < 2; ++allow_check)
    for (unsigned replace_null = 0; replace_null < 2; ++replace_null) {
        Slots slots = {values[i], values[j]}; current = &slots;
        Receiver *original = selected_index ? slots.second : slots.first;
        Event event = {0x80000001U, 19};
        event_result = null_event ? 0 : &event;
        replacement = replace_null ? 0 : &c;
        checks = misses = 0; seen_receiver = 0; seen_code = 0;
        Receiver *result = check_selected_slot(&slots, selected_index);
        assert(misses == null_event && checks == 1 - null_event);
        if (null_event) {
            assert(result == 0 && slots.first == replacement && slots.second == replacement);
        } else {
            assert(seen_receiver == original && seen_code == event.code);
            assert(result == (allow_check ? replacement : 0));
            assert((selected_index ? slots.second : slots.first) == replacement);
            assert((selected_index ? slots.first : slots.second) ==
                   (selected_index ? values[i] : values[j]));
        }
        ++cases;
    }
    std::printf("PASS: conditional lvalue, null/miss and callback replacement; %u cases\n", cases);
}
#endif
