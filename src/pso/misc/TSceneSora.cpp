#include "pso/system/BmlTextureList.h"
#include "pso/system/BmlResource.h"
#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TLobby_80207DA8.h"
#include "pso/misc/TLobby_80131794.h"
#include "pso/misc/TLobby_80140FF4.h"
#include "pso/misc/TLobby_80207644.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TSceneSora.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/misc/TScene.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/object/TObjMotion.h"
#include "pso/map/FloorArea.h"

struct RecoveredGlobal_802072E0___vt__10TSceneSora {
    s32 value;
    u8 remaining[0x34];
};

struct RecoveredGlobal_802075F8_lbl_80515BA0 {
    s32 value;
    u8 remaining[0x24];
};

struct RecoveredGlobal_80207340___vt__10TSceneSora {
    s32 value;
    u8 remaining[0x34];
};

struct SkyMotion_80207238 { u32 rows; u32 frame_count; };

struct TSceneSora_80207238 {
    u8 pad[0x60];
    s32 yaw;
    u8 pad64[0x94 - 0x64];
    SkyMotion_80207238 *motion;
    void *textures;
    f32 rate;
    f32 frame;
};

struct Ref_80207478 { s32 id; s32 idx; s32 pad; };

struct Ent_80207478 { s32 f0; char *name; };

struct Res_80207478 { void *buf; s32 n; };

extern "C" {
extern s32 TSceneSora__sky_active_flag;
extern s32 TSceneSora__instance;
extern BmlResource *TSceneSora__sky_bml_resource;
void TSceneSora__sub_80207430(void);
s32 __dl__7TObjectFPv(void *);
extern RecoveredGlobal_802072E0___vt__10TSceneSora __vt__10TSceneSora;
u8 *__dt__10TSceneSoraFv(u8 *arg0, s16 arg1);
s32 get_bml_motion(BmlResource *, int);
s32 __ct__8TObjBaseFP7TObject(void *);
extern s32 lbl_805D3624;
extern s32 TSceneSora__has_sky_motion;
static const f32 lbl_805DC608 = 0.0f;
static const f32 lbl_805DC60C = 0.1f;
u8 *TSceneSora__ct(TSceneSora *arg0, s32 _w1);
s32 draw_ginja_model_with_motion(int, int, f32);
s32 rotate_matrix_y(int, int);
s32 push_matrix();

void *get_current_floor();
s32 lookup_scene_object__6TLobbyFPv(void *, Ref_80207478 *);
extern char lbl_8044A9D0[];
extern char lbl_8044A9D8[];
extern char lbl_8044A9E0[];
void TLobby__sub_802075F4(void);
s32 __nw__7TObjectFUl(s32);

extern s32 tl_05;

typedef char RecoveredGlobal_802072E0___vt__10TSceneSora_size[sizeof(RecoveredGlobal_802072E0___vt__10TSceneSora) == 0x38 ? 1 : -1];

void TSceneSora::render() {
    if ((s32) TSceneSora__sky_active_flag != 0) {
        TParticleCtrl::begin_effect_render();
        set_current_texture_list((TObjFish__sub_8001EDB0((BmlResource *)TSceneSora__sky_bml_resource, 0)));
        push_matrix();
        rotate_matrix_y(0, this->rotation.yaw);
        if ((u32) this->m_94 != 0U) {
            draw_ginja_model_with_motion(this->m_90, this->m_94, this->m_a0);
        } else {
            draw_ginja_object((void *)this->m_90);
        }
        pop_matrix();
        TParticleCtrl::end_effect_render();
    }
}

void TSceneSora::run_task() {
    TSceneSora_80207238 *sky = (TSceneSora_80207238 *)this;
    if (sky->motion != NULL) {
        sky->frame += sky->rate;
        if (sky->frame > (sky->motion->frame_count - 1)) {
            sky->frame = lbl_805DC608;
        }
    } else {
        switch (get_current_floor_area()) {
        case AREA_FOREST1:
        case AREA_FOREST2:
            sky->yaw++;
            break;
        }
    }
}

u8 *__dt__10TSceneSoraFv(u8 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = &__vt__10TSceneSora.value;
        TSceneSora__instance = 0;
        __dt__8TObjBaseFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

typedef char RecoveredGlobal_80207340___vt__10TSceneSora_size[sizeof(RecoveredGlobal_80207340___vt__10TSceneSora) == 0x38 ? 1 : -1];
u8 *TSceneSora__ct(TSceneSora *scene_sora, s32 _w1) {
    __ct__8TObjBaseFP7TObject(scene_sora);
    *(s32 **)((s8 *)scene_sora + 0x18) = &(*(RecoveredGlobal_80207340___vt__10TSceneSora *)&__vt__10TSceneSora).value;
    *(s32 *)((s8 *)scene_sora + 0) = lbl_805D3624;
    scene_sora->m_90 = (s32)get_bml_model(TSceneSora__sky_bml_resource, 0);
    if (TSceneSora__has_sky_motion != 0) {
        scene_sora->m_94 = get_bml_motion(TSceneSora__sky_bml_resource, 0);
    } else {
        scene_sora->m_94 = 0;
    }
    scene_sora->m_98 = (s32)TObjFish__sub_8001EDB0((BmlResource *)TSceneSora__sky_bml_resource, 0);
    *(f32 *)((s8 *)scene_sora + 0x9C) = lbl_805DC60C;
    scene_sora->m_a0 = lbl_805DC608;
    return (u8 *)scene_sora;
}

void TSceneSora::create_instance() {
    s32 scene_sora;

    if (TSceneSora__sky_bml_resource != NULL) {
        scene_sora = __nw__7TObjectFUl(0xA4);
        if (scene_sora != 0) {
            scene_sora = ((s32)TSceneSora__ct((TSceneSora *)((u8 *)scene_sora), (s32)tl_05));
        }
        TSceneSora__instance = scene_sora;
        return;
    }
    TSceneSora__instance = 0;
}

void TSceneSora__sub_80207430(void) {
    TSceneSora__sky_active_flag = 1;
    if (TSceneSora__sky_bml_resource != NULL) {
        delete TSceneSora__sky_bml_resource;
        TSceneSora__sky_bml_resource = NULL;
    }
    TSceneSora__instance = 0;
}

void TSceneSora::load_sky_resources() {
    char name2[0x20];
    char name1[0x20];
    Ref_80207478 ref;
    void *model_list[2];
    void *motion_list[2];
    Ent_80207478 *tbl;
    s32 ok;
    AdxfHandle *file;
    BmlResource *loaded;
    TSceneSora__instance = 0;
    TSceneSora__sky_bml_resource = 0;
    TSceneSora__has_sky_motion = 0;
    if (lookup_scene_object__6TLobbyFPv(get_current_floor(), &ref) != 0) {
        ok = 0;
        tbl = (Ent_80207478 *)get_floor_scene_table(ref.id);
        replace_file_extension__6TLobbyFPvPvPv(name1, tbl[ref.idx].name, lbl_8044A9D0);
        if (TRaderMapCore::is_not_split_screen() == 1) {
            replace_file_extension__6TLobbyFPvPvPv(name2, tbl[ref.idx].name, lbl_8044A9D8);
            ok = TScene::update_lobby_scene(name2);
        }
        if (ok <= 0) {
            replace_file_extension__6TLobbyFPvPvPv(name2, tbl[ref.idx].name, lbl_8044A9E0);
        }
        file = ADXF_Open(name2, 0);
        if (file != NULL) {
            model_list[0] = name2;
            ADXF_Close(file);
        } else {
            return;
        }
        file = ADXF_Open(name1, 0);
        if (file != NULL) {
            motion_list[0] = name1;
            TSceneSora__has_sky_motion = 1;
            ADXF_Close(file);
        } else {
            motion_list[0] = NULL;
        }
        model_list[1] = NULL;
        motion_list[1] = NULL;
        loaded = (BmlResource *)::operator new(0x440);
        if (loaded != NULL) {
            loaded = init_from_id_lists(loaded, 1, model_list, motion_list, 0, 0, 0);
        }
        TSceneSora__sky_bml_resource = loaded;
        TSceneSora__sky_active_flag = 1;
    }
}

void TLobby__sub_802075F4(void) {  }
}
extern RecoveredGlobal_802075F8_lbl_80515BA0 lbl_80515BA0;
extern s32 pending_adventure_map_floor;
void prepare_adventure_maps(void);
typedef char RecoveredGlobal_802075F8_lbl_80515BA0_size[sizeof(RecoveredGlobal_802075F8_lbl_80515BA0) == 0x28 ? 1 : -1];
void prepare_adventure_maps(void) {
    randomize_adventure_maps();
    if ((s32) pending_adventure_map_floor != -1) {
        TLobby__sub_80141038((u8 *)&lbl_80515BA0.value, pending_adventure_map_floor, get_floor_map_terrain(pending_adventure_map_floor));
        pending_adventure_map_floor = -1;
    }
}
