#include "types.h"
#include "pso/unk/text_8007A6C8.h"
#include "pso/map/TObjMapCsn.h"
extern "C" {
void __construct_array(void *, void *, s32, s32, s32);
extern u8 __ct__10CsnContactFv[];
u8 lbl_804FF9C0[0x380];
u8 lbl_804FFD40[0x400];
__declspec(section ".data") u8 lbl_80500140[8];
u8 csn_query_map_object[0x10];
void *__ct__6CsnHitFv(void *);
void *__ct__14CsnQueryResultFv(void *);
void __sinit_text_8007A6C8_cpp(void) {
    __construct_array(lbl_804FF9C0, __ct__10CsnContactFv, 0, 0x1C, 0x20);
    __ct__6CsnHitFv(lbl_80500140);
    __ct__14CsnQueryResultFv(csn_query_map_object);
}

}

__declspec(section ".ctors") static void *const __sinit_text_8007A6C8_cpp_ref = (void *)__sinit_text_8007A6C8_cpp;
