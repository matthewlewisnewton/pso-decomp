#include "pso/system/BmlResourceClass.h"
#include "pso/system/ArrayAllocation.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/vector.h"
#include "pso/system/NinjaTypes.h"
void set_constant_material(const NJS_ARGB *color);
#include "types.h"
#include "pso/misc/MaterialColorFade.h"
#include "pso/system/memory.h"
#include "pso/boss/TObjBoss1MokoHill_Solo.h"
#include "pso/boss/TObjBoss1MokoHill_SoloM.h"
#include <stddef.h>
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TBoss8Dragon_8002CC48.h"
#include "pso/math/VectorNormalize.h"
#include "pso/boss/TObjBoss1Rock.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/object/TObjFish.h"

struct RecoveredGlobal_8002D41C_lbl_80482060 { s32 value; u8 remaining[0x14]; };
typedef char RecoveredGlobal_8002D41C_lbl_80482060_size[sizeof(RecoveredGlobal_8002D41C_lbl_80482060) == 0x18 ? 1 : -1];

struct UV_8002D4C0 { s16 u, v; };

struct Vtx_8002D4C0 { s16 pad; s16 u; s16 v; };

struct Hdr_8002D4C0 { u8 pad[4]; s16 count; };

struct Obj_8002D4C0 { f32 x; u8 pad[4]; f32 z; };

typedef struct Ent_8002CE78 {
    f32 *dst;
    f32 base;
    f32 ofs;
    s32 state;
} Ent_8002CE78;

typedef struct Obj_8002CE78 {
    u8 pad0[0x1C];
    s32 active;
    u8 pad20[0x14];
    f32 unk34;
    s32 unk38;
} Obj_8002CE78;

struct Trail_8002CC48 {
    u8 pad0[0x28];
    u8 pos[0x34 - 0x28];
    f32 f34;
    f32 f38;
    u8 pad3C[0x40 - 0x3C];
    s32 f40;
    s32 state;
    u8 pad48[0x4C - 0x48];
    s32 f4C;
};

struct Vec_8002CFB8 { f32 x; f32 y; f32 z; };
struct Ent_8002CFB8 { u8 pad0[8]; f32 f8; s32 state; };
struct Trail_8002CFB8 {
    u8 pad0[0x10];
    void *f10;
    u8 pad14[0x1C - 0x14];
    s32 f1C;
    Vec_8002CFB8 pos;
    f32 f2C;
    f32 f30;
    f32 f34;
    u8 pad38[4];
    s32 f3C;
};

struct Vtx_8002DB7C { f32 p[3]; f32 n[3]; };

struct Model_8002DB7C {
    u32 *vertices;
    u16 *polygons;
    f32 center[3];
    f32 radius;
};

struct Object_8002DB7C {
    u32 flags;
    Model_8002DB7C *model;
    f32 position[3];
    s32 rotation[3];
    f32 scale[3];
    Object_8002DB7C *child;
    Object_8002DB7C *sibling;
    // Allocation reserves this tail, but the initializer does not write it.
    u8 unknown34[4];
};

struct Grid_8002DB7C {
    s32 width;
    s32 strips;
    s32 stripWords;
    s32 materialWords;
    u32 *vertices;
    u16 *polygons;
    Model_8002DB7C model;
    Object_8002DB7C object;
};

#ifdef __MWERKS__
typedef char Grid_8002DB7C_size[sizeof(Grid_8002DB7C) == 0x68 ? 1 : -1];
typedef char Vtx_8002DB7C_size[sizeof(Vtx_8002DB7C) == 0x18 ? 1 : -1];
typedef char Ent_8002CE78_size[sizeof(Ent_8002CE78) == 0x10 ? 1 : -1];
#endif

typedef struct Obj_8002CD8C {
    s32 unk0;
    u8 pad4[0x14];
    void *vtbl;
    u8 pad1C[0xC];
    u8 pos[0xC];
    f32 unk34;
    f32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
} Obj_8002CD8C;

extern "C" {
s32 get_state__12TBoss8DragonFv(void);
f32 lerp__9TDeadSpotFff(f32 farg0, f32 farg1);
void __ct__7TObjectFP7TObject(void *, void *);
s32 rand(void);
extern s32 __vt__22TObjBoss1MokoHill_Solo[];
extern s32 TObjBoss1MokoHill_Solo__name;
void *TObjBoss1MokoHill_Solo__ct(void *arg0_, void *arg1, int arg2);
extern s32 __vt__23TObjBoss1MokoHill_SoloM[];
extern s32 TObjBoss1MokoHill_SoloM__name;
extern u8 *lbl_805D4B50;
extern s32 dragon_common_texture_list;
extern int lbl_805D4B60;
extern int lbl_805D4B64;
extern int lbl_805D4B68;
extern int lbl_805D4B6C;
extern Hdr_8002D4C0 *lbl_805D4B70;
extern s32 lbl_805D4B74;
extern int lbl_805D4B78;
extern s32 dragon_trail_position_source;
extern s32 dragon_trail_heading_source;
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern s32 model_render_flags;

void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
void push_matrix(void);
s32 pop_matrix(void);
void post_translate_matrix(void *);
void set_chunk_material_override_pair(s32, s32, s32, s32);
void draw_chunk_object(void *);
void queue_destruction__7TObjectFv();
void *__nw__7TObjectFUl(int);
f32 newton_sqrtf(f32);
f32 calc_nearest_crater_distance(void *);
f32 horizontal_distance_squared(void *, void *);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32, f32);
void rotate_matrix_y(int, int);
void rotate_matrix_x(int, int);
u8 *TObjBoss1MokoHill_SoloM__ct(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void update_dragon_trail_uvs(Obj_8002D4C0 *self);
void *TBoss8Dragon__sub_8002DAEC(void *arg0);
void *TBoss8Dragon__sub_8002DB04(void *arg0);
void *destroy__12TBoss8DragonFPvs(void *arg0, s16 arg1);
Grid_8002DB7C *init_grid_mesh__12TBoss8DragonFPviiiPv(Grid_8002DB7C *g, s32 width, s32 strips, s32 materialWords, s16 *material);
f32 rand_signed_unit(void);

}

s32 is_dragon_trail_damaging(u8 *arg0);
#pragma fp_contract on
// Reverse definitions plus deferred emission preserve both native vtable offsets.
// Flush this prefix before defining the default-scale constant below.
#ifdef __MWERKS__
#pragma defer_codegen on
#endif
u8 *TObjBoss1MokoHill_SoloM__ct(u8 *boss1_moko_hill_solo_m, u8 *arg1, u8 *arg2, s32 arg3) {
    __ct__7TObjectFP7TObject(boss1_moko_hill_solo_m, arg1);
    *(s32 **)((s8 *)boss1_moko_hill_solo_m + 0x18) = &(*(RecoveredGlobal_8002D41C_lbl_80482060 *)&__vt__23TObjBoss1MokoHill_SoloM).value;
    *(s32 *)((s8 *)boss1_moko_hill_solo_m + 0) = (s32) TObjBoss1MokoHill_SoloM__name;
    *(s32 *)((s8 *)boss1_moko_hill_solo_m + 0x1C) = 0;
    (*(u8 * *)&dragon_trail_position_source) = arg2;
    dragon_trail_heading_source = arg3;
    VecCopy((Vec *)(boss1_moko_hill_solo_m + 0x20), (const Vec *)arg2);
    ((TObjBoss1MokoHill_SoloM *)boss1_moko_hill_solo_m)->m_2c = (f32) (0.0f);
    *(f32 *)((s8 *)boss1_moko_hill_solo_m + 0x30) = (f32) (-30.0f);
    ((TObjBoss1MokoHill_SoloM *)boss1_moko_hill_solo_m)->m_34 = (f32) (-30.0f);
    if (TObjEneDD::check_v2_mode() != 0) {
        *(s32 *)((s8 *)boss1_moko_hill_solo_m + 0x38) = 1;
    } else {
        *(s32 *)((s8 *)boss1_moko_hill_solo_m + 0x38) = 0;
    }
    ((TObjBoss1MokoHill_SoloM *)boss1_moko_hill_solo_m)->m_3c = 0;
    return boss1_moko_hill_solo_m;
}

TObjBoss1MokoHill_SoloM::~TObjBoss1MokoHill_SoloM() {

}

void TObjBoss1MokoHill_SoloM::spawn_child_object() {
    void *o;
    this->m_1c = 0;
    this->m_34 = (-30.0f);
    this->m_30 = (-30.0f);
    o = __nw__7TObjectFUl(0x50);
    if (o != NULL) {
        TObjBoss1MokoHill_Solo__ct(o, this->m_up, 30);
    }
    this->m_3c = 0;
}

void TObjBoss1MokoHill_SoloM::set_field_1c() { this->m_1c = 1; }

void TObjBoss1MokoHill_SoloM::set_field_3c() { set_field_1c(); this->m_3c = 1; }

s32 is_dragon_trail_damaging(u8 *arg0) {
    return *(f32 *)((s8 *)arg0 + 0x34) >= (-10.0f);
}

void TObjBoss1MokoHill_SoloM::run_task() {
    Trail_8002CFB8 *self = (Trail_8002CFB8 *)this;
    Vec_8002CFB8 pos;
    Vec_8002CFB8 vel;
    f32 outerRadius = 120.0f;
    f32 innerRadius = 50.0f;
    f32 d;
    f32 ax;
    f32 az;
    f32 s;
    f32 c;
    s32 ang;
    void *o;
    Ent_8002CFB8 *p;
    s32 i;

    if (self->f1C != 0) {
        self->f30 += (0.5f);
        if (self->f30 > (0.0f)) {
            self->f30 = (0.0f);
        }
        d = calc_nearest_crater_distance((void *)dragon_trail_position_source);
        self->f34 = self->f30;
        if ((0.0f) != d && d < (95.0f)) {
            self->f34 = (-30.0f) - ((-0.31578946f) * d);
            if (self->f34 > self->f30) {
                self->f34 = self->f30;
            }
        }
        if (self->f34 >= (0.0f)) {
            self->f2C += newton_sqrtf(horizontal_distance_squared((void *)dragon_trail_position_source, &self->pos));
            VecCopy((Vec *)&self->pos, (const Vec *)dragon_trail_position_source);
            if (self->f2C >= (10.0f)) {
                self->f2C = (0.0f);
                if (self->f3C != 0) {
                    o = __nw__7TObjectFUl(0x50);
                    if (o != NULL) {
                        TObjBoss1MokoHill_Solo__ct(o, self->f10, 0);
                    }
                } else {
                    o = __nw__7TObjectFUl(0x50);
                    if (o != NULL) {
                        TObjBoss1MokoHill_Solo__ct(o, self->f10, 0x1E);
                    }
                }
            }
            ang = *(s32 *)dragon_trail_heading_source;
            s = ((f32 (*)(s32))cos_table_lookup)(ang);
            c = sin_table_lookup(ang);
            ax = c * outerRadius + ((Vec_8002CFB8 *)dragon_trail_position_source)->x;
            az = s * outerRadius + ((Vec_8002CFB8 *)dragon_trail_position_source)->z;
            ang += (s32)((10000.0f) * rand_signed_unit());
            s = ((f32 (*)(s32))cos_table_lookup)(ang);
            c = sin_table_lookup(ang);
            pos.x = c * innerRadius + ((Vec_8002CFB8 *)dragon_trail_position_source)->x;
            pos.y = (0.0f);
            pos.z = s * innerRadius + ((Vec_8002CFB8 *)dragon_trail_position_source)->z;
            vel.x = pos.x - ax;
            vel.z = pos.z - az;
            normalize_vector_xz((Vec *)(&vel));
            vel.x *= (1.5f);
            vel.z *= (1.5f);
            vel.y = lerp__9TDeadSpotFff((6.0f), (9.0f));
            o = __nw__7TObjectFUl(0x54);
            if (o != NULL) {
                ((TObjBoss1Rock *)o)->construct(self->f10, &pos, &vel, (void *)1);
            }
        }
        for (p = (Ent_8002CFB8 *)lbl_805D4B78, i = 0; i < lbl_805D4B74; p++, i++) {
            switch (p->state) {
            case 0:
                if (p->f8 < (-8.0f)) {
                    p->f8 = (-8.0f);
                    p->state = (s32)((70.0f) * ((3.0517578125e-05f) * (f32)rand())) + 2;
                } else {
                    p->f8 = p->f8 - (0.2f);
                }
                break;
            case 1: {
                f32 riseStep = 2.0f;
                if (p->f8 > (0.0f)) {
                    p->f8 = (0.0f);
                    p->state = 0;
                } else {
                    p->f8 = p->f8 + riseStep;
                }
                break;
            }
            default:
                p->state--;
                break;
            }
        }
    }
}

void TObjBoss1MokoHill_SoloM::render() {
    Obj_8002CE78 *arg0 = (Obj_8002CE78 *)this;
    Ent_8002CE78 *p;
    s32 i;
    if (arg0->active != 0) {
        set_current_texture_list((GinjaTextureList *)(dragon_common_texture_list));
        update_dragon_trail_uvs((Obj_8002D4C0 *)((struct Obj_8002D4C0 *)dragon_trail_position_source));
        for (p = (Ent_8002CE78 *)lbl_805D4B78, i = 0; i < lbl_805D4B74; i++, p++) {
            *p->dst = p->base + p->ofs;
        }
        push_matrix();
        post_translate_matrix((void *)dragon_trail_position_source);
        translate_matrix(0, (0.0f), arg0->unk34, (0.0f));
        if (arg0->unk38 != 0) {
            saved_model_render_flags = model_render_flags;
            saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
            saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
            model_render_flags |= 0x800;
            set_chunk_material_override_pair(0xFF00, 0x100, chunk_polygon_flags_or_mask, chunk_polygon_flags_and_mask);
            draw_chunk_object(*(void **)(*(u8 **)(lbl_805D4B50 + 0x42C) + 0x38));
            chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
            chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
            model_render_flags = saved_model_render_flags;
        } else {
            draw_chunk_object(*(void **)(*(u8 **)(lbl_805D4B50 + 0x42C) + 0x38));
        }
        pop_matrix();
        for (p = (Ent_8002CE78 *)lbl_805D4B78, i = 0; i < lbl_805D4B74; i++, p++) {
            *p->dst = p->base;
        }
    }
}

#define arg0 ((Obj_8002CD8C *)arg0_)
void *TObjBoss1MokoHill_Solo__ct(void *arg0_, void *arg1, int arg2) {
    f32 r;
    f32 t;
    __ct__7TObjectFP7TObject(arg0, arg1);
    arg0->vtbl = __vt__22TObjBoss1MokoHill_Solo;
    arg0->unk0 = TObjBoss1MokoHill_Solo__name;
    VecCopy((Vec *)arg0->pos, (const Vec *)(((void *(*)(void *))get_state__12TBoss8DragonFv)(arg0)));
    arg0->unk34 = (-32.0f);
    r = (f32)rand();
    arg0->unk38 = (f32)-((2.0f) + (8.0f) * ((3.0517578125e-05f) * r));
    t = (3.0517578125e-05f) * r;
    arg0->unk3C = (s32)((f32 (*)(f32, f32, f32, f32, f32))lerp__9TDeadSpotFff)((20.0f), (40.0f), (8.0f), t, r);
    arg0->unk40 = 0;
    arg0->unk44 = 0;
    if (TObjEneDD::check_v2_mode() != 0) {
        arg0->unk48 = 1;
    } else {
        arg0->unk48 = 0;
    }
    arg0->unk4C = arg2;
    return arg0;
}
#undef arg0

TObjBoss1MokoHill_Solo::~TObjBoss1MokoHill_Solo() {

}

s32 get_state__12TBoss8DragonFv(void) {
    return dragon_trail_position_source;
}

void TObjBoss1MokoHill_Solo::run_task() {
    Trail_8002CC48 *self = (Trail_8002CC48 *)this;
    switch (self->state) {
    case 0:
        self->f34 += (4.0f);
        if (self->f34 >= self->f38) {
            self->f34 = self->f38;
            self->state = 1;
        }
        VecCopy((Vec *)self->pos, (const Vec *)(((void *(*)(void *))get_state__12TBoss8DragonFv)(self)));
        break;
    case 1:
        self->f40++;
        if (self->f40 > self->f4C) {
            self->state = 2;
        }
        break;
    case 2:
        self->f34 -= (0.5f);
        if (self->f34 < (-32.0f)) {
            queue_destruction__7TObjectFv();
        }
        break;
    }
}

#ifdef __MWERKS__
#pragma defer_codegen off
#endif
// This layout check also flushes the deferred functions before the scalar pool.
typedef char UV_8002D4C0_size[sizeof(UV_8002D4C0) == 4 ? 1 : -1];

// The default scale precedes the UV constants in the original scalar pool.
extern "C" {
#ifdef __MWERKS__
__declspec(section ".sdata2")
#endif
extern const f32 lbl_805D81D4 = 16.0f;
}

void update_dragon_trail_uvs(Obj_8002D4C0 *self) {
    s32 cnt;
    s16 n;
    s16 *p = (s16 *)((u8 *)lbl_805D4B70 + 6);
    UV_8002D4C0 *src = (*(UV_8002D4C0 * *)&lbl_805D4B6C);
    s32 i = 0;
    s16 du = (s16)((1024.0f) * ((0.0125f) * self->x));
    s16 dv = (s16)((1024.0f) * ((-0.0125f) * self->z));
    cnt = lbl_805D4B70->count & 0x3FFF;
    for (; i < cnt; i++) {
        n = *p++;
        s32 j;
        if (n < 0) {
            n = -n;
        }
        for (j = 0; j < n; j++) {
            Vtx_8002D4C0 *v = (Vtx_8002D4C0 *)p;
            v->u = src->u + du;
            v->v = src->v + dv;
            src++;
            p += 3;
        }
    }
}

void TBoss8Dragon::free_resources() { ::operator delete[]((void *)lbl_805D4B78); lbl_805D4B78 = 0; ::operator delete[]((void *)lbl_805D4B6C); lbl_805D4B6C = 0; ((int (*)(void*, void*))destroy__12TBoss8DragonFPvs)((void*)lbl_805D4B64, (void*)1); lbl_805D4B64 = 0; ((int (*)(void*, void*))destroy__12TBoss8DragonFPvs)((void*)lbl_805D4B68, (void*)1); lbl_805D4B68 = 0; ((int (*)(void*, void*))destroy__12TBoss8DragonFPvs)((void*)lbl_805D4B60, (void*)1); lbl_805D4B60 = 0; }

void *operator new(size_t bytes);

extern "C" {
extern s16 lbl_804FE238[11];
extern s16 lbl_804FE250[11];

// Keep width propagation in the backend so its dead-load pass removes the
// spare UV induction value before instruction scheduling. See the evidence note.
#ifdef __MWERKS__
#pragma push
#pragma opt_propagation off
#endif
void TBoss8Dragon__sub_8002D5F8(void) {
    f32 x;
    f32 smallX;
    f32 z;
    f32 smallZ;
    UV_8002D4C0 *uv;
    s32 upperV;
    f32 *source;
    Vec direction;
    s32 uvIndex;
    s32 count;
    s32 stripIndex;
    s32 lowerV;
    Vtx_8002DB7C *vertices;
    f32 *modelVertex;
    s32 u;
    s32 uvColumn;
    s32 j;
    s16 length;
    Vtx_8002DB7C *uvVertex;
    NJS_CNK_MODEL *model;
    Ent_8002CE78 *entry;
    s32 smallColumn;
    s32 largeRow;
    s32 vertexCount;
    Vec smallDirection;
    s32 largeColumn;
    s16 *material;
    s32 countVertexIndex;
    s16 *uvPolygons;
    s32 stripCount;
    s32 uvStripIndex;
    Vtx_8002DB7C *smallVertex;
    s32 smallRow;
    f32 *firstVertex;
    s16 *polygons;
    s32 uvRow;
    BmlResource *resource;
    s32 entryVertexIndex;
    Grid_8002DB7C *grid;
    s32 width = 11;
    resource = (BmlResource *)lbl_805D4B50;
    material = ((NJS_CNK_MODEL *)((NJS_OBJECT *)resource->models[4].model)->model)->polygon_list;
    grid = (Grid_8002DB7C *)::operator new(sizeof(Grid_8002DB7C));
    if (grid != NULL) {
        grid = init_grid_mesh__12TBoss8DragonFPviiiPv(grid, width, 10, 8, material);
    }
    lbl_805D4B60 = (s32)grid;
    vertices = (Vtx_8002DB7C *)TBoss8Dragon__sub_8002DB04(grid);
    uvVertex = vertices;
    z = (60.0f);
    for (largeRow = 0; largeRow < 11; largeRow++) {
        x = (60.0f);
        for (largeColumn = 0; largeColumn < 11; largeColumn++) {

            direction.x = x;
            direction.z = z;
            uvVertex->p[0] = x;
            uvVertex->p[1] = apply_default_velocity_scale(&direction);
            uvVertex->p[2] = z;
            uvVertex->n[0] = direction.x;
            uvVertex->n[1] = direction.y;
            uvVertex->n[2] = direction.z;
            uvVertex++;
            x -= (12.0f);
        }
        z -= (12.0f);
    }
    uvVertex = vertices;
    for (uvIndex = 0; uvIndex < 11; uvIndex++, uvVertex++) {
        lbl_804FE238[uvIndex] = (s16)((1024.0f) * ((0.0125f) * uvVertex->p[0]));
        lbl_804FE250[uvIndex] = (s16)((1024.0f) * ((-0.0125f) * uvVertex->p[0]));
    }
    grid = (Grid_8002DB7C *)::operator new(sizeof(Grid_8002DB7C));
    if (grid != NULL) {
        grid = init_grid_mesh__12TBoss8DragonFPviiiPv(grid, 5, 4, 8, material);
    }
    lbl_805D4B68 = (s32)grid;
    smallVertex = (Vtx_8002DB7C *)TBoss8Dragon__sub_8002DB04(grid);
    smallZ = (0.0f);
    for (smallRow = 0; smallRow < 5; smallRow++) {
        smallX = (15.0f);
        for (smallColumn = 0; smallColumn < 5; smallColumn++) {

            smallDirection.x = smallX;
            smallDirection.z = smallZ;
            smallVertex->p[0] = smallX;
            smallVertex->p[1] = (2.0f) + apply_default_velocity_scale(&smallDirection);
            smallVertex->p[2] = smallZ;
            smallVertex->n[0] = smallDirection.x;
            smallVertex->n[1] = smallDirection.y;
            smallVertex->n[2] = smallDirection.z;
            smallVertex++;
            smallX -= (7.5f);
        }
        smallZ -= (7.5f);
    }
    polygons = (s16 *)((Grid_8002DB7C *)lbl_805D4B68)->polygons;
    polygons[7] = (polygons[7] & 0xC000) | 5;
    polygons[8] |= 0x900;
    polygons = (s16 *)TBoss8Dragon__sub_8002DAEC((void *)lbl_805D4B68);
    upperV = 1024;
    lowerV = 768;
    for (uvRow = 0; uvRow < 4; uvRow++) {
        u = 0;
        polygons++;
        for (uvColumn = 0; uvColumn < 5; uvColumn++) {
            polygons[1] = u;
            polygons[2] = upperV;
            polygons[4] = u;
            polygons[5] = lowerV;
            polygons += 6;
            u += 256;
        }
        upperV = lowerV;
        lowerV -= 256;
    }
    grid = (Grid_8002DB7C *)::operator new(sizeof(Grid_8002DB7C));
    if (grid != NULL) {
        grid = init_grid_mesh__12TBoss8DragonFPviiiPv(grid, 11, 1, 8, material);
    }
    lbl_805D4B64 = (s32)grid;
    {
        s16 *stripStart;
        model = (NJS_CNK_MODEL *)((NJS_OBJECT *)((BmlResource *)lbl_805D4B50)->models[3].model)->model;
        modelVertex = (f32 *)model->vertex_list;
        polygons = model->polygon_list;
        polygons[6] = 0x408;
        lbl_805D4B70 = (Hdr_8002D4C0 *)(polygons += 8);
        polygons[0] = 0x242;
        stripCount = polygons[2] & 0x3FFF;
        polygons += 3;
        stripStart = polygons;
        count = 0;
        modelVertex += 2;
        for (stripIndex = 0; stripIndex < stripCount; stripIndex++) {
            length = *polygons++;
            if (length < 0) length = -length;
            count += length;
        }
        lbl_805D4B6C = (s32)::operator new[](count * sizeof(UV_8002D4C0));
        uv = (UV_8002D4C0 *)lbl_805D4B6C;
        uvPolygons = stripStart;
        for (uvStripIndex = 0; uvStripIndex < stripCount; uvStripIndex++) {
            length = *uvPolygons++;
            if (length < 0) length = -length;
            for (j = 0; j < length; j++) {
                // The source is an xyz/normal stream: six floats per strip index.
                source = modelVertex + (u32)(*uvPolygons * 6);
                uvPolygons += 3;
                uv->u = (s16)((1024.0f) * ((0.0125f) * source[0]));
                uv->v = (s16)((1024.0f) * ((-0.0125f) * source[2]));
                uv++;
            }
        }
    }
    vertexCount = ((u32 *)((NJS_CNK_MODEL *)((NJS_OBJECT *)((BmlResource *)lbl_805D4B50)->models[3].model)->model)->vertex_list)[1] >> 16;
    lbl_805D4B74 = 0;
    firstVertex = modelVertex;
    for (countVertexIndex = 0; countVertexIndex < vertexCount; countVertexIndex++, modelVertex += 6) {
        if (modelVertex[1] > (15.0f)) lbl_805D4B74++;
    }
    lbl_805D4B78 = (s32)::operator new[](lbl_805D4B74 * sizeof(Ent_8002CE78));
    entry = (Ent_8002CE78 *)lbl_805D4B78;
    modelVertex = firstVertex;
    for (entryVertexIndex = 0; entryVertexIndex < vertexCount; modelVertex += 6, entryVertexIndex++) {
        if (modelVertex[1] > (15.0f)) {
            entry->dst = &modelVertex[1];
            entry->base = modelVertex[1];
            entry->ofs = (-8.0f);
            entry->state = (s32)((70.0f) * ((3.0517578125e-05f) * (f32)rand())) + 2;
            entry++;
        }
    }
}
#ifdef __MWERKS__
#pragma pop
#endif

}

void *TBoss8Dragon__sub_8002DAEC(void *arg0) {
    Grid_8002DB7C *grid = (Grid_8002DB7C *)arg0;
    return (s16 *)grid->polygons + (grid->materialWords + 3);
}

void *TBoss8Dragon__sub_8002DB04(void *arg0) {
    return ((Grid_8002DB7C *)arg0)->vertices + 2;
}

void *destroy__12TBoss8DragonFPvs(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ::operator delete[]((void *)(*(s32 *)((s8 *)arg0 + 0x10)));
        *(s32 *)((s8 *)arg0 + 0x10) = 0;
        ::operator delete[]((void *)(*(s32 *)((s8 *)arg0 + 0x14)));
        *(s32 *)((s8 *)arg0 + 0x14) = 0;
        *(s32 *)((s8 *)arg0 + 0x18) = 0;
        *(s32 *)((s8 *)arg0 + 0x1C) = 0;
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}

Grid_8002DB7C *init_grid_mesh__12TBoss8DragonFPviiiPv(Grid_8002DB7C *g, s32 width, s32 strips, s32 materialWords, s16 *material) {
    s32 i;
    s32 first;
    s32 second;
    s16 *p;
    s32 row;
    s32 x;
    s32 count;
    u32 *v;
    Vtx_8002DB7C *vt;
    g->width = width;
    g->strips = strips;
    g->materialWords = materialWords;
    g->stripWords = g->width * 6 + 1;
    g->polygons = (u16 *)::operator new[]((g->materialWords + 5 + g->stripWords * g->strips) * 2);
    g->vertices = (u32 *)::operator new[]((g->width * (g->strips + 1) * 6 + 3) * 4);
    p = (s16 *)g->polygons;
    for (i = 0; i < g->materialWords; i++) {
        *p++ = *material++;
    }
    *p++ = 0x242;
    *p++ = g->stripWords * g->strips + 1;
    *p++ = g->strips;
    first = 0;
    second = g->width;
    for (row = 0; row < g->strips; row++) {
        *p++ = g->width * 2;
        for (x = 0; x < g->width;) {
            *p++ = first++;
            x++;
            *p++ = 0;
            *p++ = 0;
            *p++ = second++;
            *p++ = 0;
            *p++ = 0;
        }
    }
    *p++ = 0xff;
    *p = 0xff;
    count = g->width * (g->strips + 1);
    v = g->vertices;
    *v++ = ((count * 6 + 1) << 16) | 0x29;
    *v++ = count << 16;
    vt = (Vtx_8002DB7C *)v;
    for (i = 0; i < count; i++) {
        vt->p[0] = (0.0f);
        vt->p[1] = (0.0f);
        vt->p[2] = (0.0f);
        vt->n[0] = (0.0f);
        vt->n[1] = (0.0f);
        vt->n[2] = (0.0f);
        vt++;
    }
    *(u32 *)vt = 0xff;
    g->model.vertices = g->vertices;
    g->model.polygons = g->polygons;
    g->model.center[0] = (0.0f);
    g->model.center[1] = (0.0f);
    g->model.center[2] = (0.0f);
    g->model.radius = (0.0f);
    g->object.flags = 0x17;
    g->object.model = &g->model;
    g->object.position[0] = (0.0f);
    g->object.position[1] = (0.0f);
    g->object.position[2] = (0.0f);
    g->object.rotation[0] = 0;
    g->object.rotation[1] = 0;
    g->object.rotation[2] = 0;
    g->object.scale[0] = (1.0f);
    g->object.scale[1] = (1.0f);
    g->object.scale[2] = (1.0f);
    g->object.child = NULL;
    g->object.sibling = NULL;
    return g;
}

f32 apply_default_velocity_scale(Vec *v) {
    const f32 *scale = &lbl_805D81D4;
    return apply_velocity_scale(v, (60.0f), *scale);
}

f32 apply_velocity_scale(Vec *v, f32 farg0, f32 farg1) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 var_f31;
    s32 temp_r31;

    temp_f1 = normalize_vector_xz(v);
    if (temp_f1 > farg0) {
        var_f31 = (0.0f);
        v->x = var_f31;
        v->y = (1.0f);
        v->z = var_f31;
    } else {
        temp_r31 = (s32) ((32768.0f) * (temp_f1 / farg0));
        var_f31 = farg1 * ((1.0f) + cos_table_lookup(temp_r31, (32768.0f)));
        temp_f1_2 = sin_table_lookup(temp_r31);
        temp_f2 = v->x * temp_f1_2;
        v->x = temp_f2;
        v->y = (1.0f);
        v->z = v->z * temp_f1_2;
        normalize_vector_checked(v);
    }
    return var_f31;
}

#pragma push
#pragma fp_contract on
f32 lerp__9TDeadSpotFff(f32 farg0, f32 farg1) {
    return ((farg1 - farg0) * ((3.0517578125e-05f) * (f32) rand())) + farg0;
}
#pragma pop

#pragma push
#pragma fp_contract on
f32 rand_signed_unit(void) {
    return (2.0f) * (((3.0517578125e-05f) * (f32) rand()) - (0.5f));
}
#pragma pop
