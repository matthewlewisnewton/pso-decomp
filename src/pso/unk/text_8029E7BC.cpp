#include "types.h"
#include "pso/map/CsnQuery.h"
#include "pso/unk/text_8029E7BC.h"
#include "pso/system/vector.h"
#include "pso/map/FloorArea.h"
#include "pso/player/TObjPlayer_80011014.h"

extern const f32 lbl_805DDD88;
s32 fn_8029E7BC(s32 arg0, u8 *arg1) {
  Vec position;
  s32 area;
  s32 var_r31;
  CsnHit *hit;
  area = get_current_floor_area();
  var_r31 = 0x56EF;
  if (area == AREA_BARBA_RAY)
  {
    var_r31 = 0x4000;
  }
  VecCopy(&position, (const Vec *)arg0);
  position.y += lbl_805DDD88;
  hit = csnVecterUnder(&position, var_r31);
  if (hit != 0)
  {
    if (!(hit->contact->flags & 0x4000)) return 0;
    if (arg1 != 0)
    {
      ((Vec *)arg1)[0].x = hit->contact->point.x;
      ((Vec *)arg1)[0].y = hit->contact->point.y;
      ((Vec *)arg1)[0].z = hit->contact->point.z;
      ((Vec *)arg1)[1].x = hit->contact->normal.x;
      ((Vec *)arg1)[1].y = hit->contact->normal.y;
      ((Vec *)arg1)[1].z = hit->contact->normal.z;
    }
    return 1;
  }
  return 0;
}
