#ifndef PSO_PLAYER_TPLYITEM_H
#define PSO_PLAYER_TPLYITEM_H

#include "types.h"

class TPlyItem;
class TObject;

extern "C" {
void *TPlyItem__ct(TPlyItem *ply_item, TObject *parent);
}

// --- C functions defined in TPlyItem.cpp ---
extern "C" {
void *TPlyItem__ct(TPlyItem *ply_item, TObject *parent);
}
// --- end of C functions

#endif
