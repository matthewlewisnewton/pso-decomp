#ifndef PSO_MISC_TOMINETRAP_H
#define PSO_MISC_TOMINETRAP_H

#include "types.h"
#include "pso/misc/TOMine.h"

struct TObjPlayer;
class TObjChara;

extern "C" {
// Whether the player has check_flag 0x10000 set.
s32 fn_80171314(TObjPlayer *player);
}

struct TOMineTrap : public TOMine {
    TOMineTrap(TObjPlayer *owner, s16 trap_index, s16 trap_id);
    virtual ~TOMineTrap();
    virtual void spawn_disp_objects();
    virtual void vfunc_86();
    virtual void vfunc_82();
    void sub_80171348(u16);
    virtual const char *get_name();
    virtual void run_task();
    u32 m_374;
    u32 m_378;
    u8 _pad37C[0x2];
    u16 m_37e;
    s32 m_380;
    u16 get_trap_type();
    static int get_trap_count();
    static void set_instance(int a0);
    static void set_trap_count(int a0);
    void bswap_6x80_trigger_trap();
    void send_and_handle_60();
    s32 matches_id(u16 arg1);
    void set_state();
    s32 find_target_in_range();
    void set_triggered();
    static void destroy_matching_traps();
    void*get_mine_data_ptr();
    s32 check_trigger(u32 arg1);
    s32 can_trigger(u32 arg1);
    void spawn_effect();
    void attach_to_keymachine();
    void detonate_if_triggered();
    void sync_position();
    void send_state_packet(u16 idx);
    int update_trap_sub();
    static s32 show_owner_message(TOMineTrap *trap, TObjChara *actor);
    void strike_actor(TObjChara *actor, TObjPlayer *owner);
    void strike_player(TObjChara *actor);
    void strike_enemy(TObjChara *actor, TObjPlayer *owner);
};

typedef char TOMineTrap_size[sizeof(TOMineTrap) == 0x384 ? 1 : -1];
#endif
