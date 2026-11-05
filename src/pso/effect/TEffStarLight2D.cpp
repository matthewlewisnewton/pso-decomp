#include "pso/effect/TEffStarLight2D.h"
#include "pso/system/vector.h"
#include "pso/effect/TEffStarLightChild.h"
#include "types.h"

// IEEE bits of 2, 0, 255 and -15. A const float is copied into the literal
// pool, which duplicates the slot the other effect units load by name.
__declspec(section ".sdata2") extern const unsigned int lbl_805D9450 = 0x40000000u;
__declspec(section ".sdata2") extern const unsigned int lbl_805D9454 = 0;
__declspec(section ".sdata2") extern const unsigned int lbl_805D9458 = 0x437F0000u;
__declspec(section ".sdata2") extern const int lbl_805D945C = (int)0xC1700000u;

struct Vec_800851B0 { f32 x; f32 y; f32 z; };

struct P2_800851B0 { f32 x; f32 z; };

struct Star_800851B0 {
    u8 pad0[0x1C];
    f32 curX;
    f32 curZ;
    f32 prevX;
    f32 prevZ;
    Vec_800851B0 pos;
    f32 f38;
    f32 f3C;
};

struct O_80085388 { u32 f0; u8 pad4[0x14]; void *vptr; f32 f1c; f32 f20; f32 f24; f32 f28; };

struct P2_80085388 { f32 x; f32 z; };

struct Vec_80085424 { f32 x, y, z; };

struct Star_80085424 {
    u8 pad0[0x1C];
    f32 angle;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
};

struct Vec_800855F8 { f32 x, y, z; };

struct Pt_800855F8 { f32 x, y; };

struct Star_800855F8 {
    s32 name;
    u8 pad4[0x18 - 0x4];
    void *vt;
    f32 angle;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
};

extern "C" {
void *__nw__7TObjectFUl(u32);
void matrix_mult_vec(int, void *, void *);
void __ct__7TObjectFP7TObject(void *, void *);
void project_world_to_screen(int, void *, void *);
extern u32 TEffStarLight2D__name;
void queue_destruction__7TObjectFv(void *arg0);
f32 approach_vector_fixed_distance(void *, void *, void *, f32);
f32 vector_length(void *);
s32 normalize_vector(void *);
f32 newton_sqrtf(f32);
extern void *__vt__18TEffStarLightChild[];
extern s32 TEffStarLightChild__name;
void run_task__15TEffStarLight2DFv(Star_800851B0 *self);
void run_task__18TEffStarLightChildFv(Star_80085424 *self);
Star_800855F8 *__ct__18TEffStarLightChildFv(Star_800855F8 *self, Pt_800855F8 *a, Pt_800855F8 *b, void *parent, f32 w, f32 speed);
void run_task__15TEffStarLight2DFv(Star_800851B0 *self) {
    P2_800851B0 scr;
    Vec_800851B0 view;
    f32 dx;
    f32 dz;
    void *child;

    matrix_mult_vec(0, &self->pos, &view);
    if (view.z > (*(float *)&lbl_805D9454)) {
        return;
    }
    project_world_to_screen(0, &self->pos, &scr);
    if (scr.x >= -100.0f && scr.x <= 740.0f && scr.z >= -100.0f && scr.z <= 580.0f) {
        self->prevX = self->curX;
        self->prevZ = self->curZ;
        self->curX = scr.x;
        self->curZ = scr.z;
        dx = self->curX - self->prevX;
        dz = self->curZ - self->prevZ;
        if (dx * dx + dz * dz >= 1.0f) {
            child = __nw__7TObjectFUl(0x30);
            if (child != NULL) {
                ((void *(*)(void *, void *, void *, void *, f32, f32))__ct__18TEffStarLightChildFv)(child, &self->prevX, &self->curX, self, self->f38, self->f3C);
            }
        }
    }
}
void TEffStarLight2D::copy_from_subobject(void* a1) { ((TEffStarLight2D *)((char*)this + 0x38))->copy_from(a1); }
void TEffStarLight2D::copy_from(void* q) { *(f32 *)&this->m_name = *(f32*)((char*)q + 0x0); *(f32 *)&this->m_flags = *(f32*)((char*)q + 0x4); *(u8 *)&this->m_prev = *(u8*)((char*)q + 0x8); *(u8*)((char*)this + 0x9) = *(u8*)((char*)q + 0x9); *(u8*)((char*)this + 0xa) = *(u8*)((char*)q + 0xa); *(u8*)((char*)this + 0xb) = *(u8*)((char*)q + 0xb); *(u32 *)&this->m_next = *(u32*)((char*)q + 0xc); *(f32 *)&this->m_up = *(f32*)((char*)q + 0x10); }

}

extern "C" void __dt__7TObjectFv(void *, int);
extern "C" void __dl__7TObjectFPv(void *);
extern "C" void *__vt__15TEffStarLight2D[];
extern "C" void *__dt__15TEffStarLight2DFv(void *self, s16 flag) {
    if (self != NULL) {
        *(void **)((char *)self + 0x18) = __vt__15TEffStarLight2D;
        __dt__7TObjectFv(self, 0);
        if (flag > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}

#pragma push
#pragma opt_common_subs off
TEffStarLight2D::TEffStarLight2D(void *arg1, void *arg2, TObject *object) : TObject(object) {
    P2_80085388 p;
    ((O_80085388 *)this)->f0 = TEffStarLight2D__name;
    ((TEffStarLight2D *)((u8 *)this + 0x38))->copy_from(arg2);
    VecCopy((Vec *)((u8 *)this + 0x2C), (const Vec *)arg1);
    project_world_to_screen(0, (u8 *)this + 0x2C, &p);
    ((O_80085388 *)this)->f24 = p.x;
    ((O_80085388 *)this)->f28 = p.z;
    ((O_80085388 *)this)->f1c = ((O_80085388 *)this)->f24;
    ((O_80085388 *)this)->f20 = ((O_80085388 *)this)->f28;
}

#pragma pop

extern "C" void render__18TEffStarLightChildFv(void *self) {}
void run_task__18TEffStarLightChildFv(Star_80085424 *self) {
    Vec_80085424 a;
    Vec_80085424 b;
    Vec_80085424 c;
    s32 inside = 0;
    c.z = (*(float *)&lbl_805D9454);
    c.x = 0.5f * (self->x0 + self->x1);
    c.y = 0.5f * (self->y0 + self->y1);
    a.z = (*(float *)&lbl_805D9454);
    a.x = self->x0;
    a.y = self->y0;
    b.z = (*(float *)&lbl_805D9454);
    b.x = self->x1;
    b.y = self->y1;
    approach_vector_fixed_distance(&a, &c, &a, self->angle);
    self->x0 = a.x;
    self->y0 = a.y;
    approach_vector_fixed_distance(&b, &c, &b, self->angle);
    self->x1 = b.x;
    self->y1 = b.y;
    if (self->x0 >= -100.0f && self->x0 <= 740.0f) {
        if (self->y0 >= -100.0f && self->y0 <= 580.0f) {
            if (self->x1 >= -100.0f && self->x1 <= 740.0f) {
                if (self->y1 >= -100.0f && self->y1 <= 580.0f) {
                    inside = 1;
                }
            }
        }
    }
    if (inside == 0) {
        queue_destruction__7TObjectFv(self);
    } else if (c.x == b.x && c.y == b.y) {
        queue_destruction__7TObjectFv(self);
    }
}

extern "C" void *__dt__18TEffStarLightChildFv(void *self, s16 flag) {
    if (self != NULL) {
        *(void **)((char *)self + 0x18) = __vt__18TEffStarLightChild;
        __dt__7TObjectFv(self, 0);
        if (flag > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}

#pragma push
#pragma fp_contract on
Star_800855F8 *__ct__18TEffStarLightChildFv(Star_800855F8 *self, Pt_800855F8 *a, Pt_800855F8 *b, void *parent, f32 w, f32 speed) {
    Vec_800855F8 d;
    __ct__7TObjectFP7TObject(self, parent);
    self->vt = __vt__18TEffStarLightChild;
    self->name = TEffStarLightChild__name;
    if (speed <= (*(float *)&lbl_805D9454)) {
        speed = 1.0f;
    }
    d.x = b->x - a->x;
    d.y = b->y - a->y;
    d.z = (*(float *)&lbl_805D9454);
    if ((*(float *)&lbl_805D9454) != vector_length(&d)) {
        normalize_vector(&d);
    } else {
        d.x = (*(float *)&lbl_805D9454);
        d.y = (*(float *)&lbl_805D9454);
        d.z = (*(float *)&lbl_805D9454);
    }
    self->x0 = d.y * w + b->x;
    self->y0 = d.x * w + b->y;
    self->x1 = -d.y * w + b->x;
    self->y1 = -d.x * w + b->y;
    if (self->y0 <= self->y1) {
        f32 t0 = self->y0;
        f32 t1 = self->y1;
        self->y1 = t0;
        self->y0 = t1;
    }
    self->angle = newton_sqrtf((self->x0 - self->x1) * (self->x0 - self->x1) + (self->y0 - self->y1) * (self->y0 - self->y1)) / 2.0f / speed;
    return self;
}
#pragma pop

// Unread word after the 0.5 literal. Nothing loads it; force_active keeps it.
__declspec(section ".sdata2") extern const unsigned char lbl_805D9474[4] = {0, 0, 0, 0};
