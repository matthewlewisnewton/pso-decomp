#include "pso/TOChatSensorFolder.h"

extern s32 TOChatSensorFolder__instance;

TOChatSensorFolder::~TOChatSensorFolder() {
    TOChatSensorFolder__instance = 0;
}
