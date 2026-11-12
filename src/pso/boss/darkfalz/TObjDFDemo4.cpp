#include "types.h"
#include "pso/boss/darkfalz/TObjDFDemo4.h"

TObjDFDemo4 *TObjDFDemo4::create(TObject *parent, const Vec *position, s32 angle) {
    return new TObjDFDemo4(parent, position, angle);
}
