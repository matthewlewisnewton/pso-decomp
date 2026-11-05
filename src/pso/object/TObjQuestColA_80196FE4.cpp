#include "types.h"
#include "pso/object/TObjQuestColA.h"
#include "pso/object/TObjQuestCol.h"

// One original TU. Deferred generation emits last-defined first, so the later
// class is written first: .text and the vtables then come out
// TObjQuestColA (0x80196FE4 / 0x804B8808) then TObjQuestCol (0x8019703C / 0x804B884C).
TObjQuestCol::~TObjQuestCol() {}

TObjQuestColA::~TObjQuestColA() {}
