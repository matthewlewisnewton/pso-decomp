#include "pso/math/MatrixCopy.h"
#include "types.h"
#include "pso/object/TObjHMS_EZRope_Player.h"
#include "pso/object/TObjEZBoneRotPlayer.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/TObjEZRopeBase.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
extern void *__vt__19TObjEZBoneRotPlayer[];
void __dt__17TObjEZBoneRotBaseFv(void *self, s32 flag);
void __dl__7TObjectFPv(void *p);

void *__dt__19TObjEZBoneRotPlayerFv(void *self, s16 flag) {
    if (self != 0) {
        *(void **)((u8 *)self + 0x18) = __vt__19TObjEZBoneRotPlayer;
        __dt__17TObjEZBoneRotBaseFv(self, 0);
        if (flag > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}
}

struct RotSrc_800FEEA4 {
    s8 bone;
    u8 pad[3];
    f32 angle;
    u8 data[0xC];
};

struct PosSrc_800FEEA4 {
    s8 bone;
    u8 pad[3];
    s32 ofs;
    u8 data[0x10];
};

struct RotDst_800FEEA4 {
    f32 angle;
    u8 data[0xC];
};

struct PosDst_800FEEA4 {
    s32 val;
    u8 data[0xC];
};

struct Model_800FEEA4 {
    u8 pad[0x60];
    s32 base;
};

struct Self_800FEEA4 {
    u8 pad[0x30];
    Model_800FEEA4 *model;
    PosSrc_800FEEA4 *pos_src;
    RotSrc_800FEEA4 *rot_src;
    u8 pad3C[4];
    PosDst_800FEEA4 *pos_dst;
    RotDst_800FEEA4 *rot_dst;
};

extern "C" {
void matrix_mult_vec(s32, void *, void *);
void push_matrix(void);
extern u8 TObjEZBoneRotPlayer__chain_gravity[];

void TObjHMS_EZRope_Player::render() { sub_800FF2D0(); }
void TObjHMS_EZRope_Player::run_task() {
    RotSrc_800FEEA4 *rs;
    RotDst_800FEEA4 *rd;
    PosSrc_800FEEA4 *ps;
    PosDst_800FEEA4 *pd;
    if (((Self_800FEEA4 *)this)->rot_dst != NULL) {
        push_matrix();
        TObjPlayer::invert_matrix_in_place(0);
        rs = ((Self_800FEEA4 *)this)->rot_src;
        rd = ((Self_800FEEA4 *)this)->rot_dst;
        while (rs->bone >= 0) {
            rd->angle = rs->angle;
            push_matrix();
            concat_matrix((MtxP)(0), (const f32 (*)[4])(((TObjMotion *)(((Self_800FEEA4 *)this)->model))->get_item_ptr(rs->bone)));
            matrix_mult_vec(0, rs->data, rd->data);
            pop_matrix();
            rs++;
            rd++;
        }
        pop_matrix();
    }
    push_matrix();
    TObjPlayer::invert_matrix_in_place(0);
    ps = ((Self_800FEEA4 *)this)->pos_src;
    pd = ((Self_800FEEA4 *)this)->pos_dst;
    while (ps->bone >= 0) {
        pd->val = ((Self_800FEEA4 *)this)->model->base + ps->ofs;
        push_matrix();
        concat_matrix((MtxP)(0), (const f32 (*)[4])(((TObjMotion *)(((Self_800FEEA4 *)this)->model))->get_item_ptr(ps->bone)));
        matrix_mult_vec(0, ps->data, pd->data);
        pop_matrix();
        ps++;
        pd++;
    }
    pop_matrix();
    ((TObjEZRopeBase *)((Self_800FEEA4 *)this))->sub_800FF788(TObjEZBoneRotPlayer__chain_gravity);
}

}
