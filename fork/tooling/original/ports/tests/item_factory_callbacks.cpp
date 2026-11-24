#include <cassert>
#include "pso/item/ItemCreateFunction.h"

// Complete the opaque record/result types for this callback-boundary test.
// This checks dispatch and pointer identity, not the matching build's layout.
struct TItemData { u8 bytes[20]; };
struct TItem { int tag; };

static TItem byte_result = { 1 };
static TItem money_result = { 4 };
static TItemData *expected_record;
static unsigned calls;

static TItem *create_bytes(u8 *bytes) {
    assert(bytes == reinterpret_cast<u8 *>(expected_record));
    assert(bytes[2] == 37);
    ++calls;
    return &byte_result;
}

static TItem *create_money(TItemData *record) {
    assert(record == expected_record);
    assert(record->bytes[19] == 123);
    ++calls;
    return &money_result;
}

int main() {
    static TItemData record = {};
    expected_record = &record;
    record.bytes[2] = 37;
    record.bytes[19] = 123;

    // All non-money entries retain the ordinary byte-buffer callback type.
    for (u8 type = 0; type < 4; ++type) {
        record.bytes[0] = type;
        assert(invoke_item_factory(create_bytes,
                                  reinterpret_cast<u8 *>(&record), type) == &byte_result);
    }

    // Round-trip the money callback through the table's storage type. The
    // invocation must restore the actual type before the indirect call.
    ItemCreateFunction stored_money = reinterpret_cast<ItemCreateFunction>(create_money);
    record.bytes[0] = 4;
    assert(invoke_item_factory(stored_money,
                              reinterpret_cast<u8 *>(&record), 4) == &money_result);
    assert(calls == 5);
}
