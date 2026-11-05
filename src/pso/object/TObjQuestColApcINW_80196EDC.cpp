#include "types.h"
#include "pso/object/TObjQuestColApcINW.h"
#include "pso/object/TObjQuestColApcIN.h"

// One original TU. Deferred generation emits last-defined first, so the later
// class is written first: .text and the vtables then come out
// TObjQuestColApcINW (0x80196EDC / 0x804B86F8) then TObjQuestColApcIN (0x80196F34 / 0x804B873C).
TObjQuestColApcIN::~TObjQuestColApcIN() {}

TObjQuestColApcINW::~TObjQuestColApcINW() {}
