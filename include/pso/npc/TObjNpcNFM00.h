#ifndef PSO_NPC_TOBJNPCNFM00_H
#define PSO_NPC_TOBJNPCNFM00_H

#include "types.h"
#include "pso/npc/TUnk_804A9F50.h"

struct GinjaTextureList;

struct TObjNpcNFM00 : public TUnk_804A9F50 {
    virtual ~TObjNpcNFM00();
    static void free_resources();
    static void load_assets();
};

typedef char TObjNpcNFM00_size[sizeof(TObjNpcNFM00) == 0x3B8 ? 1 : -1];
extern "C" {
extern s32 *TObjNpcNFM00__shared_named_model_object;
extern GinjaTextureList *TObjNpcNFM00__texture_gvm_handle;
}

#endif
