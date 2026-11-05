#include "types.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
void reset_entry__20TWindowSubStatusDispFPv(void*, int);
}

extern unsigned char lbl_804CF9B0[];
extern const float lbl_805DCF14;
void*TWindowSubStatusDisp::reset_entry(int a1, int a2) { reset_entry__20TWindowSubStatusDispFPv(this, a2); *(int*)((char*)this + 0x4) = (int)lbl_804CF9B0; *(float*)((char*)this + 0x14) = lbl_805DCF14; *(unsigned char *)&this->frame_pad_1c = 51; *(unsigned char *)&this->frame_pad_1c[1] = 51; *(int*)((char*)this + 0x20) = 0; *(int*)((char*)this + 0x24) = 0; *(int*)((char*)this + 0x28) = -1; *(int *)&this->m_2c = -1; *(int*)((char*)this + 0x30) = -1; *(int *)&this->m_34 = -1; *(int*)((char*)this + 0x18) = 0; return this; }
