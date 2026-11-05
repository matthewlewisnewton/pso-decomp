#include "types.h"
#include "pso/ui/TAdChrSelSlotGC.h"
#include "pso/ui/TAdChrSelBSlotGC.h"
#include "pso/ui/ChrSelPlateLayout.h"
#include "pso/TAdChrSelMovePlateGC.h"

extern "C" {

void *__ct__15TAdSubPlyItemGCFv(void *, void *);
void *__ct__19TAdPlyChrSelPlateGCFv(void *, void *, void *);
void *__nw__7TObjectFUl(int);

void TAdChrSelBSlotGC::create_children() {
    void *o;
    void *o2;
    void *o3;
    o = new TAdChrSelSlotGC(this);
    *(void * *)&this->unk_28 = o;
    o2 = __nw__7TObjectFUl(0x3B4);
    if (o2 != NULL) {
        o2 = __ct__19TAdPlyChrSelPlateGCFv(o2, this, (void *)&chr_sel_b_slot_plate_layout);
    }
    this->m_2c = (TAdPlyChrSelPlateGC *)o2;
    o3 = __nw__7TObjectFUl(0x48C);
    if (o3 != NULL) {
        o3 = __ct__15TAdSubPlyItemGCFv(o3, this);
    }
    *(void * *)&this->unk_30 = o3;
    this->m_34 = new TAdChrSelMovePlateGC(this);
}

void TAdChrSelBSlotGC::sub_8030FE04() {
    this->m_1c = 0;
    this->m_20 = 0;
    this->m_24 = -1;
    *(s32 *)&this->unk_28 = 0;
    this->m_2c = 0;
    *(s32 *)&this->unk_30 = 0;
    this->m_34 = 0;
    *(s32 *)&this->unk_38 = 0;
    this->m_3c = 0;
    *(s32 *)&this->unk_40 = 0;
    this->m_44 = 0;
    *(s32 *)&this->unk_48 = 0;
    this->m_4c = 0;
    *(s32 *)&this->unk_50 = 0;
    this->m_54 = 0;
    *(s32 *)&this->unk_58 = 0;
    this->m_5c = 0;
    *(s32 *)&this->unk_60 = 0;
    this->m_64 = 0;
    *(s32 *)&this->unk_68 = 0;
    this->m_6c = 0;
    *(s32 *)&this->unk_70 = 0;
    this->m_74 = 0;
    *(s32 *)&this->unk_78 = 0;
    this->m_7c = 0;
}

// This unit's contiguous .rodata, 0x804758D8..0x80475930. lbl_80475918 is the
// string TAdChrSelBSlotGC__name (.sdata 0x805D4108) points at.
__declspec(section ".rodata") extern const PlateLayout chr_sel_b_slot_plate_layout = {
    {180.0f, 38.0f}, {0xBC, 0x98, 0x36, 0x00}, 0
};
__declspec(section ".rodata") extern const f32 lbl_804758E8[4][2] = {
    {434.0f, 182.0f}, {434.0f, 225.0f}, {434.0f, 268.0f}, {434.0f, 311.0f}
};
__declspec(section ".rodata") extern const CharacterSlotPosition lbl_80475908 = {429.0f, 156.0f};
__declspec(section ".rodata") extern const f32 lbl_80475910[2] = {441.0f, 117.0f};
__declspec(section ".rodata") extern const char lbl_80475918[] = "TAdChrSelBSlotGC";

}
