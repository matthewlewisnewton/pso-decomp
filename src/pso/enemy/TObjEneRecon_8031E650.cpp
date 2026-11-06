#include "types.h"
#include "pso/enemy/TObjEneRecon_8031BC38.h"
#include "pso/enemy/TObjEneRecon.h"

struct Base_8031E650 { char pad[0xC]; };
struct VObj_8031E650 : Base_8031E650 {
    virtual void m0(int);
};

extern struct VObj_8031E650 *boss3_volopt_instance;

void TObjEneRecon::release_static_instance() {
    TObjEneRecon__sub_8031BC38();
    if (boss3_volopt_instance != 0) {
        if (boss3_volopt_instance != 0) {
            boss3_volopt_instance->m0(1);
        }
        boss3_volopt_instance = 0;
    }
}
