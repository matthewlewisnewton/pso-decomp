struct NJS_OBJECT;
#ifndef PSO_MISC_PHOTONBLASTSUMMON_H
#define PSO_MISC_PHOTONBLASTSUMMON_H

#include "types.h"
class TUnk_804C3248;

extern "C" {
void apply_all_default__8TFogCtrlFv(TUnk_804C3248 *);
void spawn_photon_blast_attachment_effects(TUnk_804C3248 *, s32);
}
void clear_deferred_photon_blast_hits(void);
void clear_photon_blast_hits(void);
void copy_effect_params(u8 *arg0, u8 *arg1);
extern "C" {
void *destroy_photon_motion_object(void *arg0, s16 arg1);
void *photon_base_ct(void *arg0);
}
void publish_photon_blast_joint_origins(NJS_OBJECT *);
void queue_deferred_photon_blast_hit(u32 arg0, s32 arg1, s32 arg2, f32 unused);
extern "C" {
void queue_deferred_photon_blast_support(u32 identity, s32 kind, s32 allow_duplicate);
void queue_photon_blast_hit(u32 identity, s32 kind, s32 allow_duplicate, f32 scale);
}
void queue_photon_blast_support(u32 identity, s32 kind, s32 allow_duplicate);
extern "C" {
void reset_state__10TSceneSoraFv(s32 _w0);
void spawn_photon_blast_opening_effects(s32 arg0, s32 arg1);
s32 update_all_default__8TFogCtrlFv(TUnk_804C3248 *);
}

#endif
