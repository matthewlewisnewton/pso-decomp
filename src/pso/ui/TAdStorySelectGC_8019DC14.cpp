#include "pso/object/TObjWarpResources.h"
#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/ui/TAdStorySelectGC_8019DC14.h"
#include "pso/TAdStorySelectGC.h"
#include "pso/object/TObjMapForceWarp.h"

extern "C" {

int get_bml_motion(void*, void*);

    extern int lbl_805D67C0;
int TAdStorySelectGC__sub_8019DC14(void) {  return lbl_805D67C0; }

int TAdStorySelectGC::get_story_select() {  return (s32)forest_warp_texture_list; }

void TAdStorySelectGC::register_area_warp_object(void* a0) { get_bml_motion(forest_warp_bml_resource, a0); }

void TObjMapForceWarp::register_warp(void* a0) { (int)get_bml_model(forest_warp_bml_resource, (s32)a0); }

void TObjMapForceWarp::slot3C() {  }

}
