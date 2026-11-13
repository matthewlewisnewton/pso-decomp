#include "types.h"
#include "pso/system/scene/TScene.h"
#include "pso/unk/TLobby.h"

extern "C" {

int get_resource_file_size__6TLobbyFPCv(const void*);

int TScene::update_lobby_scene(const void *name) { return get_resource_file_size__6TLobbyFPCv(name); }

}
