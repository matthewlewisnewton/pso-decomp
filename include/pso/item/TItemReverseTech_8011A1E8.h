#ifndef PSO_ITEM_TITEMREVERSETECH_8011A1E8_H
#define PSO_ITEM_TITEMREVERSETECH_8011A1E8_H

#include "types.h"

struct ReverseTechSceneHook {
    void (*load)();
    void (*release)();
};

enum { ReverseTechSceneHookCount = 7 };
extern ReverseTechSceneHook TItemReverseTech__cleanup_callback_table[ReverseTechSceneHookCount];

extern "C" {
void TItemReverseTech__sub_8011A54C(void *a0);
int TItemReverseTech__sub_8011A55C(void);
int TItemReverseTech__sub_8011A580(void);
void TItemReverseTech__sub_8011A5A4(void);
void free__16TItemReverseTechFv(void);
}

// --- C functions defined in TItemReverseTech_8011A1E8.cpp ---
extern "C" {
void TItemReverseTech__sub_8011A54C(void *a0);
int TItemReverseTech__sub_8011A55C(void);
int TItemReverseTech__sub_8011A580(void);
void TItemReverseTech__sub_8011A5A4(void);
void free__16TItemReverseTechFv(void);
}
// --- end of C functions

#endif
