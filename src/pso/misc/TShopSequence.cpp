#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TShopSequence.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/ui/TMessageWindowController.h"

struct VObj_802235A0_8022356C {
    virtual void m0(int);
};

struct RecoveredGlobal_802238D8___vt__13TShopSequence { s32 value; u8 remaining[0x34]; };
typedef char RecoveredGlobal_802238D8___vt__13TShopSequence_size[sizeof(RecoveredGlobal_802238D8___vt__13TShopSequence) == 0x38 ? 1 : -1];
struct Del_80223850 {
    virtual ~Del_80223850();
};

extern "C" {
s32 get_entity_id(u32);
void *__ct__15TShopWindowBaseFv(void *arg0);
extern RecoveredGlobal_802238D8___vt__13TShopSequence __vt__13TShopSequence;
extern s32 TShopSequence__class_name;
u8 *TShopSequence__ct(u8 *arg0);
void *__dt__15TShopWindowBaseFv(void *self, s16 m);
s32 __dl__7TObjectFPv(void *);
s32 load_character_from_card__23TAdSinglePlyChrSelectGCFi(s32);
s32 activate_body_collision__10TObjPlayerFv();
s32 deactivate_body_collision__10TObjPlayerFv();
void *get_player_by_client_id(s32 i);
s32 is_split_screen();
int TShopSequence::vfunc_10() {
    if (this->message != NULL) {
        return this->message->is_ready();
    }
    return 1;
}

void TShopSequence::close_message_window() {
    if (this->message != NULL) {
        this->message->close();
        delete this->message;
        this->message = NULL;
    }
}

u32 TShopSequence::create_message_window(s32 arg1, s32 arg2) {
    if (this->message != NULL) {
        if (this->player != NULL) {
            return (u32)this->message->create_message_window(arg1, arg2, (s32)((u16)get_entity_id((u32)this->player)));
        }
        return (u32)this->message->create_window(arg1, arg2);
    }
    return 0U;
}

void TShopSequence::display_guild_message(s32 index, s32 flags) {
    if (this->message != NULL) {
        this->message->format_guild_message(index, flags);
    }
}
void TShopSequence::vfunc_8(s32 index, s32 flags) {
    if (this->message != NULL) {
        this->message->send_message(index, flags);
    }
}
void TShopSequence::display_message(const char *text, s32 flags) {
    if (this->message != NULL) {
        this->message->display_message(text, flags);
    }
}
void TShopSequence::vfunc_6(s32 index, s32 flags) {
    if (this->message != NULL) {
        this->message->format_shop_message(index, flags);
    }
}
void TShopSequence::close_if_single_screen() {
    if ((TAdSinglePlyChrSelectGC::get_game_mode() != 0) && (is_split_screen() == 0)) {
        load_character_from_card__23TAdSinglePlyChrSelectGCFi(0);
    }
}
void TShopSequence::close_window() {
    s32 var_r31;

    if (this->player != NULL) {
        unsuppress_player_window((u16)get_entity_id((u32)this->player));
        if (TRaderMapCore::is_not_split_screen() != 1) {
            var_r31 = 0;
            do {
                if (get_player_by_client_id(var_r31) != 0U) {
                    activate_body_collision__10TObjPlayerFv();
                }
                var_r31 += 1;
            } while (var_r31 < 4);
        }
        TObjPlayer::clear_lobby_flag(this->player);
    }
}
void TShopSequence::restore_player_state() {
    s32 var_r31;

    if (this->player != NULL) {
        this->player->init_effect_5f0();
        if (TRaderMapCore::is_not_split_screen() != 1) {
            var_r31 = 0;
            do {
                if (get_player_by_client_id(var_r31) != 0U) {
                    deactivate_body_collision__10TObjPlayerFv();
                }
                var_r31 += 1;
            } while (var_r31 < 4);
        }
        suppress_player_window((u16)get_entity_id((u32)this->player));
    }
}
void *__dt__13TShopSequenceFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = &__vt__13TShopSequence.value;
        if (((TShopSequence *)arg0)->message != NULL) {
            delete ((TShopSequence *)arg0)->message;
            ((TShopSequence *)arg0)->message = NULL;
        }
        __dt__15TShopWindowBaseFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}
u8 *TShopSequence__ct(u8 *shop_window_base) {
    TShopSequence *self = (TShopSequence *)shop_window_base;
    __ct__15TShopWindowBaseFv(shop_window_base);
    *(s32 **)((s8 *)shop_window_base + 0x18) = &__vt__13TShopSequence.value;
    *(s32 *)((s8 *)shop_window_base + 0) = (s32) TShopSequence__class_name;
    self->message = new TMessageWindowController();
    return shop_window_base;
}

}
