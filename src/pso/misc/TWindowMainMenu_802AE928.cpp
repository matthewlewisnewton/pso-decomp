#include "pso/misc/TWindowMainMenu.h"
#include "pso/misc/TWindowMenuMainMenu.h"

void *TWindowMainMenu::create_menu(void *position, s32 client) {
    return new TWindowMenuMainMenu(position, client);
}
