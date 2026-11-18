#ifndef PSO_TCHCRLOADGMNJREQ_H
#define PSO_TCHCRLOADGMNJREQ_H

#include "pso/TObject.h"
#include "types.h"
#include <stddef.h>

struct BmlResource;

class TChCrLoadGmNjReq : public TObject {
public:
 u8 unk_1C[0x4];
 s32 completion_mask; // 0x20
 s32 load_slot; // 0x24
 u32 *completion_flags; // 0x28; borrowed from the request owner
 s32 load_state; // 0x2C
 char name_buffer[0x30]; // 0x30; fixed-size copy, not necessarily terminated
 void *model_ids; // 0x60
 void *motion_ids; // 0x64
 BmlResource *loaded_bml; // 0x68
 s32 slot_claimed;
 s32 lifetime_remaining;
 s32 load_timer; // 0x74

public:
    virtual ~TChCrLoadGmNjReq();
    void sub_8028C8A8();
    void start_character_load_task();
    s32 try_acquire_slot();
    void update_model_load();
    virtual void run_task();
};

typedef char TChCrLoadGmNjReq_size[sizeof(TChCrLoadGmNjReq) == 0x78 ? 1 : -1];
typedef char TChCrLoadGmNjReq_completion_mask_offset[offsetof(TChCrLoadGmNjReq, completion_mask) == 0x20 ? 1 : -1];
typedef char TChCrLoadGmNjReq_completion_flags_offset[offsetof(TChCrLoadGmNjReq, completion_flags) == 0x28 ? 1 : -1];
typedef char TChCrLoadGmNjReq_load_slot_offset[offsetof(TChCrLoadGmNjReq, load_slot) == 0x24 ? 1 : -1];
typedef char TChCrLoadGmNjReq_load_state_offset[offsetof(TChCrLoadGmNjReq, load_state) == 0x2C ? 1 : -1];
typedef char TChCrLoadGmNjReq_name_buffer_offset[offsetof(TChCrLoadGmNjReq, name_buffer) == 0x30 ? 1 : -1];
typedef char TChCrLoadGmNjReq_slot_claimed_offset[offsetof(TChCrLoadGmNjReq, slot_claimed) == 0x6C ? 1 : -1];
typedef char TChCrLoadGmNjReq_lifetime_remaining_offset[offsetof(TChCrLoadGmNjReq, lifetime_remaining) == 0x70 ? 1 : -1];
typedef char TChCrLoadGmNjReq_model_ids_offset[offsetof(TChCrLoadGmNjReq, model_ids) == 0x60 ? 1 : -1];
typedef char TChCrLoadGmNjReq_load_timer_offset[offsetof(TChCrLoadGmNjReq, load_timer) == 0x74 ? 1 : -1];

#endif
