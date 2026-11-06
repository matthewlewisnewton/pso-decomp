#include "types.h"
#include "pso/misc/TGameProtocol.h"
#include "pso/TGameProtocol.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);
void *__nw__7TObjectFUl(int);

extern s32 __vt__13TGameProtocol[];
extern void *TGameProtocol__class_name;
extern void * TGameProtocol__instance;
extern void *game_protocol_instance;

void *TGameProtocol__ct(void *game_protocol) {
    void *o;
    __ct__7TObjectFP7TObject(game_protocol);
    *(s32 **)((s8 *)game_protocol + 0x18) = __vt__13TGameProtocol;
    *(void * *)&((TGameProtocol *)game_protocol)->m_name = TGameProtocol__class_name;
    TGameProtocol__instance = game_protocol;
    *(u32 *)((s8 *)game_protocol + 0x1C) = 0;
    o = __nw__7TObjectFUl(0x1C);
    if (o != NULL) {
        o = ((void * (*)(void *, void *))__ct__7TObjectFP7TObject)(o, game_protocol);
    }
    game_protocol_instance = o;
    return game_protocol;
}

}
