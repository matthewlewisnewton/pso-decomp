#include "types.h"
#include "pso/misc/TWindowCallBack.h"
#include "pso/ui/TAdEnterSerialAccessGC.h"

extern "C" {

void *TAdEnterSerialAccessGC::create_callback(void *arg0, void *arg1, WindowCallback callback) {
    return new TWindowCallBack((u8 *)arg0, (u8 *)arg1, callback);
}

}
