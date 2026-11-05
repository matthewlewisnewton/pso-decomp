#include "types.h"
#include "pso/enemy/TObjEneMe1CanadinLeader.h"

extern "C" {

void *__nw__7TObjectFUl(int);

extern void *tl_04;

TObjEneMe1Canadin *TObjEneMe1CanadinLeader::create_canadin(TObjEneMe1Canadin *leader, Vec *position, s32 id, s32 index) {
    return new TObjEneMe1Canadin((TObject *)tl_04, leader, position, id, index);
}

}
