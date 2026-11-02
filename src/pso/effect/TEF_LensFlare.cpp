#include "types.h"
#include "pso/effect/TEF_LensFlare.h"
#include "pso/effect/TEF_PvrWave.h"
#include <dolphin/mtx/GeoTypes.h>

struct Base_8008194C_80081278 { char pad[0x50]; };
struct VObj_8008194C_80081278 : Base_8008194C_80081278 {
    virtual void m0();
    virtual void m1();
};

// Nine reflected draws advance these ten configuration records by 0x18.
struct LensFlareElement {
    s32 texture;
    f32 displacement, scale, attenuation, alpha, reserved;
};
typedef char LensFlareElement_size[sizeof(LensFlareElement) == 0x18 ? 1 : -1];

extern "C" {
s32 __ct__8TObjBaseFP7TObject(void *, void *);
extern LensFlareElement lens_flare_reflected_element_descriptors[10];
extern s32 __vt__13TEF_LensFlare[];
extern const char *TEF_LensFlare__class_name;
u8 *TEF_LensFlare__ct(u8 *arg0, s32 arg1, s32 arg2);
void *__dt__13TEF_LensFlareFv(void *arg0, s16 arg1);
void __dl__7TObjectFPv(void *);

}
extern "C" {
extern const char TEF_LensFlare__class_name_string[] = "TEF_LensFlare";
const char *TEF_LensFlare__class_name = TEF_LensFlare__class_name_string;

LensFlareElement lens_flare_reflected_element_descriptors[10] = {
    {1, 0.1f, 0.8f, 0.0f, 0.7f, -10.0f},
    {2, 0.4f, 0.6f, 0.5f, 0.7f, -10.1f},
    {3, 0.6f, 0.8f, 0.6f, 0.7f, -10.2f},
    {1, 0.8f, 1.2f, 0.6f, 0.4f, -10.3f},
    {3, 1.0f, 1.2f,-0.3f, 0.7f, -10.4f},
    {4, 1.2f, 0.7f, 1.0f, 0.7f, -10.5f},
    {2, 1.4f, 1.7f, 0.0f, 0.7f, -10.6f},
    {5, 1.5f, 0.6f, 1.0f, 0.7f, -10.7f},
    {6, 1.8f, 1.5f, 0.0f, 0.7f, -10.8f},
    {2, 0.0f, 4.0f, 2.0f, 0.4f, -10.9f},
};
}

TEF_LensFlare::~TEF_LensFlare() {

}
extern "C" {

u8 *TEF_LensFlare__ct(u8 *ef_lens_flare, s32 parent, s32 arg2) {
    __ct__8TObjBaseFP7TObject((void *)ef_lens_flare, (void *)parent);
    *(s32 **)((s8 *)ef_lens_flare + 0x18) = __vt__13TEF_LensFlare;
    ((TEF_LensFlare *)ef_lens_flare)->m_name = TEF_LensFlare__class_name;
    ((TEF_LensFlare *)(ef_lens_flare))->apply_object_set_data((void *)arg2);
    ((TEF_LensFlare *)ef_lens_flare)->elements = lens_flare_reflected_element_descriptors;
    return ef_lens_flare;
}

void TEF_LensFlare::run_task() {  }
void TEF_PvrWave::render() {  }

void TEF_PvrWave::run_task() {
    struct VObj_8008194C_80081278 *o = (struct VObj_8008194C_80081278 *)*(void **)((s8 *)this + 0x1C);
    o->m1();
}

}

// Original renderer copies three float words from this read-only vector.
extern "C" __declspec(section ".rodata") const Vec lbl_80438E40 = {0.0f, 0.0f, -1.0f};
