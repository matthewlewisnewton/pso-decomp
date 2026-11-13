#ifndef PSO_TITEMEFFEQUIP_H
#define PSO_TITEMEFFEQUIP_H

#include "pso/TObject.h"
#include <stddef.h>
class TUnk_8049F038;
class TParticleCtrl;

// Plays an initial particle effect at a player joint, switches it after ten
// frames, and queues its task for destruction after twenty.
class TItemEffEquip : public TObject {
public:
    TItemEffEquip(TObject *parent, u16 client_id, s32 joint, s32 effect_id, s32 next_effect_id);
    virtual ~TItemEffEquip();
    virtual void run_task();
    void spawn_equip_particle_effect(s32 effect_id);
    void release_effect();
    static void create(TObject *parent, u16 client_id, s32 joint, s32 effect_id, s32 next_effect_id);

    TUnk_8049F038 *attachment;
    TParticleCtrl *effect;
    s32 next_effect_id;
};
typedef char TItemEffEquip_size[sizeof(TItemEffEquip) == 0x28 ? 1 : -1];
typedef char TItemEffEquip_attachment_offset[offsetof(TItemEffEquip, attachment) == 0x1c ? 1 : -1];
typedef char TItemEffEquip_effect_offset[offsetof(TItemEffEquip, effect) == 0x20 ? 1 : -1];
typedef char TItemEffEquip_next_effect_id_offset[offsetof(TItemEffEquip, next_effect_id) == 0x24 ? 1 : -1];
#endif
