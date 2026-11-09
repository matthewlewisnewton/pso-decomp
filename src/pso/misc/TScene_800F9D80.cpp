#include "types.h"
#include "pso/misc/TScene.h"
#include "pso/misc/TLobby.h"

extern "C" {

int TScene::update_lobby_scene(const void *name) { return TLobby::get_resource_file_size(name); }

}
