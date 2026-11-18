#ifndef PSO_MISC_TOVS2_WALL_RESOURCES_H
#define PSO_MISC_TOVS2_WALL_RESOURCES_H

#include "pso/object/TObjMotion.h"

struct BmlResource;
struct BmlResourceDescriptor;
struct TObjChipParams;

extern "C" {
extern BmlResource *TOVS2Wall01__bml_resource;
extern BmlResourceDescriptor bm_o_vs2_resource_descriptor;
extern CollisionBody ovs2wall01_collision_parts[7];
extern const TObjChipParams vs2_wall_debris_desc;
extern const char *lbl_805D31C4;
extern const char *lbl_805D31C8;
extern const char *lbl_805D31CC;
extern const char *lbl_805D31D0;
extern const char *lbl_805D31D4;
extern const char *lbl_805D31D8;
extern const char *TOVS2Wreck06__class_name;
extern const char *TOVS2Wall01__class_name;
}

#endif
