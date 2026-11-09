#ifndef PSO_TCHCRLOADGMNJREQ_H
#define PSO_TCHCRLOADGMNJREQ_H

#include "pso/TObject.h"
#include "types.h"
#include <stddef.h>

struct TLobby;
struct BmlResource;

class TChCrLoadGmNjReq : public TObject {
public:
 u8 unk_1C[0x4];
 void * m_20; // 0x20
 TLobby *lobby; // 0x24
 void * m_28; // 0x28
 u8 unk_2C[0x34];
 void *model_ids; // 0x60
 void *motion_ids; // 0x64
 BmlResource *loaded_bml; // 0x68
 u32 m_6c;
 u32 m_70;
 s32 load_timer; // 0x74

public:
    virtual ~TChCrLoadGmNjReq();
    void sub_8028C8A8();
    void update_model_load();
    virtual void run_task();
};

typedef char TChCrLoadGmNjReq_size[sizeof(TChCrLoadGmNjReq) == 0x78 ? 1 : -1];
typedef char TChCrLoadGmNjReq_model_ids_offset[offsetof(TChCrLoadGmNjReq, model_ids) == 0x60 ? 1 : -1];
typedef char TChCrLoadGmNjReq_load_timer_offset[offsetof(TChCrLoadGmNjReq, load_timer) == 0x74 ? 1 : -1];

#endif
