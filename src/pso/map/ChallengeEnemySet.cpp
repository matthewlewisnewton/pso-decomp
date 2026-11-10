#include <stddef.h>
#include <string.h>

#include "pso/map/ChallengeEnemySet.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TLobby_80207644.h"
#include "pso/misc/TLobby_80209BD8.h"
#include "pso/misc/TLobby_8020A568.h"
#include "pso/unk/text_802097B0.h"
#include "pso/unk/text_8020A768.h"

typedef char ChallengeEventHeaderSize[sizeof(ChallengeEventHeader) == 0x10 ? 1 : -1];
typedef char ChallengeRandomEventSize[sizeof(ChallengeRandomEvent) == 0x18 ? 1 : -1];
typedef char ChallengeFixedEventSize[sizeof(ChallengeFixedEvent) == 0x14 ? 1 : -1];
typedef char ChallengeEnemyPlacementSize[sizeof(SpawnRecord_8020A9C4) == 0x48 ? 1 : -1];
typedef char ChallengeEnemyRoomOffset[offsetof(SpawnRecord_8020A9C4, room) == 0x0C ? 1 : -1];
typedef char ChallengeEnemyWaveOffset[offsetof(SpawnRecord_8020A9C4, wave) == 0x0E ? 1 : -1];

void build_challenge_enemy_set(s32 floor) {
    // Declaration order keeps the native register allocation across the two loops.
    s32 enemyOffset;
    ChallengeRandomEvent *nextEvent;
    u32 commandSize;
    s32 enemyCount;
    s16 wave;
    s16 id;
    s32 eventIndex;
    s32 waves;
    s32 enemies;
    u32 addedSize;
    u8 *output;
    s32 area;
    s32 nextId;

    ChallengeEventHeader input = *reinterpret_cast<const ChallengeEventHeader *>(challenge_event_source);
    input.swap_endian();
    nextEvent = reinterpret_cast<ChallengeRandomEvent *>(challenge_event_source + input.eventOffset);
    commandSize = challenge_event_source_size -
                  (input.eventCount * sizeof(ChallengeRandomEvent) + sizeof(ChallengeEventHeader));

    memset(challenge_enemy_buffer, 0, ChallengeEnemyBufferSize);
    memset(challenge_event_buffer, 0, ChallengeEventBufferSize);
    challenge_event_count = 0;
    memset(challenge_action_buffer, 0, ChallengeCommandBufferSize);
    challenge_action_size = enemyOffset = 0;
    enemyCount = 0;
    ChallengeRandomEvent event;
    for (eventIndex = 0; eventIndex < input.eventCount; ++eventIndex) {
        TLobby__sub_8020A618(&event, nextEvent);
        event.swap_endian();
        waves = TLobby::clamp_min_drop(1, event.maxWaves + 1);
        wave = event.wave;
        id = event.id;
        while (waves-- > 0) {
            enemies = TLobby::clamp_min_drop(event.minEnemies, event.maxEnemies + 1);
            TLobby__sub_802097B0(event.room);
            while (enemies-- > 0) {
                u8 *placement = challenge_enemy_buffer + enemyOffset;
                if (pick_random_slot__6TLobbyFPv(reinterpret_cast<s16 *>(placement)) == 0) {
                    reinterpret_cast<SpawnRecord_8020A9C4 *>(challenge_enemy_buffer + enemyOffset)->wave = wave;
                    reinterpret_cast<SpawnRecord_8020A9C4 *>(challenge_enemy_buffer + enemyOffset)->room = event.room;
                    ++enemyCount;
                    enemyOffset += sizeof(SpawnRecord_8020A9C4);
                }
            }

            if (waves > 0) {
                challenge_event_buffer[challenge_event_count].id = id;
                challenge_event_buffer[challenge_event_count].flags = event.flags;
                challenge_event_buffer[challenge_event_count].eventType = event.eventType;
                challenge_event_buffer[challenge_event_count].room = event.room;
                challenge_event_buffer[challenge_event_count].wave = wave;
                challenge_event_buffer[challenge_event_count].delay =
                    TLobby::clamp_min_drop(event.minDelay, event.maxDelay + 1);
                challenge_event_buffer[challenge_event_count].commandOffset = commandSize + challenge_action_size;

                // When this wave ends, its action stream triggers the next event.
                id = event.id + 10000 + wave;
                ChallengeEventCommand command;
                command.opcode = ChallengeEventCommand::TriggerEvent;
                command.append();
                nextId = static_cast<u16>(id);
                TLobby::append_swapped_u32(&nextId);
                command.opcode = ChallengeEventCommand::Stop;
                command.append();
                ++challenge_event_count;
                ++wave;
            }
        }

        // The final wave uses the original event's action stream.
        TLobby__sub_8020A618(&event, nextEvent);
        event.swap_endian();
        challenge_event_buffer[challenge_event_count].id = id;
        challenge_event_buffer[challenge_event_count].flags = event.flags;
        challenge_event_buffer[challenge_event_count].eventType = event.eventType;
        challenge_event_buffer[challenge_event_count].room = event.room;
        challenge_event_buffer[challenge_event_count].wave = wave;
        challenge_event_buffer[challenge_event_count].delay = TLobby::clamp_min_drop(event.minDelay, event.maxDelay + 1);
        ++nextEvent;
        challenge_event_buffer[challenge_event_count].commandOffset = event.commandOffset;
        ++challenge_event_count;
    }

    if (enemyCount > 0) {
        area = get_floor_area(floor);
        reserve_enemy_set_actor_ids(
            reinterpret_cast<SpawnRecord_8020A9C4 *>(challenge_enemy_buffer), enemyCount, area);
        TLobby::init_floor_enemy_count(floor, challenge_enemy_buffer, enemyCount * sizeof(SpawnRecord_8020A9C4));
    }

    if (challenge_event_count > 0) {
        addedSize = (challenge_action_size + 3) & ~3;
        output = TLobby::alloc_heap_slot(
            floor, sizeof(ChallengeEventHeader) + challenge_event_count * sizeof(ChallengeFixedEvent) +
                       commandSize + addedSize);
        if (output != NULL) {
            // The original copies all 16 bytes and leaves the format word unwritten.
            ChallengeEventHeader header;
            header.eventOffset = sizeof(ChallengeEventHeader);
            header.eventCount = challenge_event_count;
            header.commandOffset = challenge_event_count * sizeof(ChallengeFixedEvent) + sizeof(ChallengeEventHeader);
            move_data(output, &header, sizeof(header));
            if (challenge_event_count > 0) {
                output += sizeof(header);
                move_data(output, challenge_event_buffer, challenge_event_count * sizeof(ChallengeFixedEvent));
            }
            if (static_cast<s32>(commandSize) > 0) {
                output += challenge_event_count * sizeof(ChallengeFixedEvent);
                move_data(output, challenge_event_source + input.commandOffset, commandSize);
            }
            if (static_cast<s32>(addedSize) > 0) {
                // Keep the address increment separate for CodeWarrior scheduling.
                u8 *tail = output;
                tail += commandSize;
                move_data(tail, challenge_action_buffer, addedSize);
            }
        }
    }
}
