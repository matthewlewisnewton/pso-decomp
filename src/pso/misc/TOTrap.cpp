#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/player/demo_mode.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_80087278.h"
#include "pso/object/TObjMotion.h"
#include "pso/misc/TOTrap.h"
#include "pso/misc/TLobby.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/render/render_util.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803D8F74.h"

extern "C" {
void *get_player_by_client_id(s32 i);

s32 submit_cursor_candidate(void *, s32);
extern u32 trap_scale_factor_table[];
extern s32 game_difficulty_selection;
s32 fn_80171314(void *);
void send_6x2C_impose_hold(void *, void *, s32, int, f32);
f32 TOTrap::vfunc_87(f32 farg0) {
    u32 v[4];
    v[0] = trap_scale_factor_table[0];
    v[1] = trap_scale_factor_table[1];
    v[2] = trap_scale_factor_table[2];
    v[3] = trap_scale_factor_table[3];
    return farg0 * ((f32*)v)[game_difficulty_selection];
}

void TOTrap::vfunc_89() {  }

s32 TOTrap::is_any_player_matching_stat() {
    s32 i;
    void *p;
    for (i = 0; i < 4; i++) {
        p = ((void *)get_player_by_client_id(i));
        if (p != 0) {
            if (((s16)((TObjBase *)p)->get_room() == (s16)get_room()) && (fn_80171314(p) != 0)) {
                return 1;
            }
        }
    }
    return 0;
}

void TOTrap::vfunc_82() {
    void *pl;

    calc_attach_pos();
    refresh_collision_body_centers();
    if ((s32) this->set_params[0] < 0) {
        u8 *p;
        this->receive_physical_attack(this->target, 1.0f);
        p = this->target;
        if (p != NULL) {
            u32 v = get_entity_id((TObjChara *)p);
            if (v < 0x1000U) {
                pl = get_player_by_client_id(v);
                if (TObjPlayer::is_locally_controlled(pl) != 0 && ((TLobby *)pl)->check_player_flag1() != 0) {
                    TObjPlayer::send_code_45_1((s32)pl);
                }
            }
        }
    }
    submit_cursor_candidate(this, -1);
}

void TOTrap::vfunc_81() {
    u8 *pl;
    calc_attach_pos();
    this->player = find_nearest_visible_player(this, 0, this->range);
    if (this->player != 0xFFFF) {
        pl = (u8 *)get_player_by_client_id(this->player);
        this->target = pl;
        if (this->target != 0) {
            if (horizontal_distance_squared(&((TObjChara *)this->target)->position, &position) < this->dist * this->dist) {
                this->mode = 3;
                if (TObjPlayer::is_locally_controlled(pl) != 0) {
                    ((void (*)(f32, void *, void *, s32, int))send_6x2C_impose_hold)(this->dist, pl, &position, this->set_params[0], 0);
                }
            } else {
                this->player = 0xFFFF;
                this->target = 0;
            }
        }
    } else {
        this->target = 0;
    }
}

void TOTrap::submit_cursor_and_notify() {
    submit_cursor_candidate(this, -1);
    this->find_target_player();
}

void TOTrap::find_target_player() {
    calc_attach_pos();
    this->player = find_nearest_visible_player(this, 0, this->range);
    if (this->player != (u16)0xFFFF) {
        this->target = (u8 *)get_player_by_client_id(this->player);
        if (this->target != 0) {
            if (horizontal_distance_squared(&((TObjChara *)this->target)->position, &position) < this->range * this->range) {
                this->mode = 2;
            }
        } else {
            this->player = 0xFFFF;
            this->target = 0;
        }
    } else {
        this->target = 0;
    }
}

void TOTrap::play_sounds() {
    spawn_particle_effect(&body_center_position, 0x45);
    spawn_particle_effect(&body_center_position, 0x46);
}

void TOTrap::vfunc_6(s16 *arg1, s32 arg2) {
    if ((s16) *arg1 == 4) {
        if (arg2 == 1) {
            play_sounds();
        }
        set_flag8();
        queue_destruction();
    }
}

f32 TOTrap::receive_physical_attack(void *source, f32) {
    s16 msg;
    void *pl;
    u16 id;
    if (this->entity_id >= 0x4000U && this->set_entry != NULL && access_object_saved_state(&msg, 1) != 0) {
        this->mode = 4;
        msg = this->mode;
        access_object_saved_state(&msg, 0);
        send_object_state_update(&msg);
        if (source != NULL) {
            id = get_entity_id((TObjBase *)source);
            if (id < 0x1000U) {
                pl = get_player_by_client_id(id);
                if (pl != NULL && TObjPlayer::is_locally_controlled(pl) != 0 && ((TLobby *)pl)->check_player_flag1() != 0) {
                    TObjPlayer::send_code_45_1((s32)pl);
                }
            }
        }
    }
    return 0.0f;
}

void TOTrap::run_task() {
    if (check_demo_mode() == 1) {
        this->vfunc_88();
        return;
    }
    if (TObjPlayer::is_any_teammate_in_state() == 0) {
        this->vfunc_84();
        switch (this->mode) {
        case 0:
            if (this->is_any_player_matching_stat() != 0) {
                this->mode = 1;
            }
            this->find_target_player();
            return;
        case 1:
            this->submit_cursor_and_notify();
            return;
        case 2:
            this->vfunc_81();
            return;
        case 3:
            this->vfunc_82();
            break;
        }
    }
}

}

#include "types.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/misc/TOTrap.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"

extern "C" {


void TOTrap::render() {
    if (TObjPlayer::is_any_teammate_in_state() == 0) {
        this->m_340 = update_object_view_visibility(400.0f, 20.0f);
        if ((s32) this->m_340 == 1) {
            push_matrix();
            post_translate_matrix(&this->position.x);
            rotate_matrix_y(NULL, this->rotation.yaw);
            set_current_texture_list((GinjaTextureList *)(this->texlist));
            if (check_demo_mode() == 1) {
                draw_chunk_object(this->model);
            } else {
                draw_model_motion((void *)this->model, (void *)this->current_motion, this->frame);
            }
            pop_matrix();
        }
    }
}

}

#include "types.h"
#include "pso/misc/TOTrap_801791EC.h"
#include "pso/player/TObjChara.h"
#include "pso/misc/TOTrap.h"

extern "C" {
extern const char *lbl_805D3198;


TOTrap::~TOTrap() {}

TOTrap::TOTrap(TObject *parent, void *creator) : TObjChara(parent) {
    m_name = lbl_805D3198;
    range = dist = 0.0f;
    player = 0xFFFF;
    m_340 = 1;
}

void TOTrap::vfunc_84() {  }

}

#include "types.h"
#include "pso/misc/TOTrap_801792AC.h"
#include "pso/misc/TOTrap.h"

void TOTrap::vfunc_86() {  }
void TOTrap::vfunc_88() {  }

s32 TOTrap::try_start_action(s32 arg1, s32) {
    return (u8) (arg1 != (s32)this->target);
}

s32 TOTrap::roll_physical_accuracy(void *source, s32, f32) {
    return source != target;
}
