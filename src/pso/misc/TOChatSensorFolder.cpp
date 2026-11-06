#include "types.h"
#include "pso/misc/TOChatSensorFolder.h"
#include "pso/TOChatSensorFolder.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__18TOChatSensorFolder[];
extern void *chat_sensor_folder_name_ptr;
extern void * TOChatSensorFolder__instance;

void *TOChatSensorFolder__ct(void *chat_sensor_folder) {
    __ct__7TObjectFP7TObject(chat_sensor_folder);
    *(s32 **)((s8 *)chat_sensor_folder + 0x18) = __vt__18TOChatSensorFolder;
    *(void * *)&((TOChatSensorFolder *)chat_sensor_folder)->m_name = chat_sensor_folder_name_ptr;
    TOChatSensorFolder__instance = chat_sensor_folder;
    return chat_sensor_folder;
}

}
