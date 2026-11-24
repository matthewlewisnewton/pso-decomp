#define PSMTXMultVecArraySR __hdr_PSMTXMultVecArraySR
#include <dolphin.h>
#include <dolphin/mtx.h>
#undef PSMTXMultVecArraySR


asm void PSMTXMultVec(const register Mtx44 m, const register Vec* src, register Vec* dst) {
#include "orig_asm/mtx/mtxvec/PSMTXMultVec.inc"
}

asm void PSMTXMultVecArray(const register GC_Mtx m, const register Vec* srcBase,
                           register Vec* dstBase, register u32 count) {
#include "orig_asm/mtx/mtxvec/PSMTXMultVecArray.inc"
}

asm void PSMTXMultVecSR(const register Mtx44 m, const register Vec* src, register Vec* dst) {
#include "orig_asm/mtx/mtxvec/PSMTXMultVecSR.inc"
}

asm void PSMTXMultVecArraySR(const register GC_Mtx m, const register Vec* srcBase, register Vec* dstBase,
                             register u32 count) {
#include "orig_asm/mtx/mtxvec/PSMTXMultVecArraySR.inc"
}
