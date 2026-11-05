#ifndef PSO_MISC_TCHCRLOADAFSTEXTUREREQ_H
#define PSO_MISC_TCHCRLOADAFSTEXTUREREQ_H

#include "types.h"
#include "pso/TObject.h"

struct TLobby;
struct BmlResource;

struct TChCrLoadAfsTextureReq : public TObject {
    virtual ~TChCrLoadAfsTextureReq();
    virtual void run_task();
    u8 _pad1C[0x8];
    TLobby *lobby;
    u32 m_28;
    u32 m_2c;
    u32 m_30;
    u32 m_34;
    u8 _pad38[0x28];
    void *model_ids;
    void *motion_ids;
    BmlResource *loaded_bml;
    u32 m_6c;
    u32 m_70;
    void update_model_load();
    void try_begin_load(void *);
    void update_loading(void *);
    void start_read(void *);
    s32 load_timer;
    u8 unk_78[0x11C];
};

typedef char TChCrLoadAfsTextureReq_size[sizeof(TChCrLoadAfsTextureReq) == 0x194 ? 1 : -1];
#endif
