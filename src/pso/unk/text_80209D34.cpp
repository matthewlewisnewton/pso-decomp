#include "types.h"
#include "string.h"
#include "pso/unk/TLobby.h"
#include "pso/unk/TLobby_8020A568.h"
#include "pso/unk/text_802097B0.h"
#include "pso/unk/TLobby_80207644.h"
#include "pso/unk/TLobby_80209BD8.h"


struct SetHeader_80209D34 {
    s32 data_offset;
    s32 record_offset;
    s32 record_count;
    s32 unk_c;
};

struct SetRecord_80209D34 {
    s32 base_id;
    s16 x;
    s16 z;
    s16 type;
    s16 first_index;
    s16 drop_min;
    s16 drop_max;
    u8 spawn_min;
    u8 spawn_max;
    s16 group_count;
    s32 data;
};

struct SetEntry_80209D34 {
    s32 id;
    s16 x;
    s16 z;
    s16 type;
    s16 index;
    s32 drops;
    s32 data;
};

struct SpawnSlot_80209D34 {
    u8 pad0[0xC];
    s16 type;
    s16 index;
    u8 pad10[0x48 - 0x10];
};

extern "C" {
void reserve_enemy_set_actor_ids(SpawnSlot_80209D34 *slots, s32 count, s32 floor);
extern u8 *challenge_event_source;
extern SpawnSlot_80209D34 *challenge_enemy_buffer;
extern SetEntry_80209D34 *challenge_event_buffer;
extern s32 challenge_event_count;
extern u8 *challenge_action_buffer;
extern s32 challenge_action_size;
extern s32 challenge_event_source_size;
void build_challenge_enemy_set__Fl(s32 floor);
u8 *alloc_heap_slot__6TLobbyFll(s32 floor, s32 size);
s32 init_floor_enemy_count__6TLobbyFlPUcUl(s32 floor, u8 *slots, u32 size);
}

#pragma push
#pragma cplusplus off
#pragma dont_inline off
void build_challenge_enemy_set__Fl(s32 floor_id) {
  void append_swapped_u32__6TLobbyFPl(void *value);
  struct SetHeader_80209D34 hdr;
  u32 val;
  u8 ent[4];
  u32 out_hdr[4];
  struct SetRecord_80209D34 rec;
  s32 off;
  u8 *p;
  s32 rem;
  s32 slots;
  s16 index;
  s16 id;
  s32 i;
  s32 groups;
  s32 spawns;
  s32 area;
  s32 aligned;
  s32 total;
  s32 size;
  void *dst;
  hdr = *((struct SetHeader_80209D34 *) challenge_event_source);
  swap_endian__20ChallengeEventHeaderFv((u8 *) &hdr);
  p = ((u8 *) challenge_event_source) + hdr.record_offset;
  rem = challenge_event_source_size - ((hdr.record_count * 0x18) + 0x10);
  memset(challenge_enemy_buffer, 0, 0x9000);
  memset(challenge_event_buffer, 0, 0x1400);
  challenge_event_count = 0;
  memset(challenge_action_buffer, 0, 0x1000);
  challenge_action_size = (off = 0);
  slots = 0;
  for (i = 0; i < hdr.record_count; i++, p += 0x18)
  {
    TLobby__sub_8020A618(&rec, p);
    swap_endian__20ChallengeRandomEventFv(&rec);
    groups = clamp_min_drop__6TLobbyFUlUl(1, (rec.group_count) + 1);
    id = rec.base_id;
    index = rec.first_index;
    while ((groups--) > 0)
    {
      spawns = clamp_min_drop__6TLobbyFUlUl(rec.spawn_min, (rec.spawn_max) + 1);
      TLobby__sub_802097B0(rec.type);
      while ((spawns--) > 0)
      {
        if (pick_random_slot__6TLobbyFPv((s16 *) (((u8 *) challenge_enemy_buffer) + off)) == 0)
        {
          *((s16 *) ((((u8 *) challenge_enemy_buffer) + off) + 0xe)) = index;
          *((s16 *) ((((u8 *) challenge_enemy_buffer) + off) + 0xc)) = rec.type;
          slots++;
          off += 0x48;
        }
      }

      if (groups > 0)
      {
        *((s32 *) (((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14))) = id;
        *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 4)) = rec.x;
        *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 6)) = rec.z;
        *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 8)) = rec.type;
        *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 0xa)) = index;
        *((s32 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 0xc)) = clamp_min_drop__6TLobbyFUlUl(rec.drop_min, (rec.drop_max) + 1);
        *((s32 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 0x10)) = rem + challenge_action_size;
        id = (s16) (((rec.base_id) + 0x2710) + index);
        ent[0] = 0xc;
        append__21ChallengeEventCommandCFv(ent);
        val = (u16) id;
        append_swapped_u32__6TLobbyFPl(&val);
        ent[0] = 1;
        append__21ChallengeEventCommandCFv(ent);
        challenge_event_count++;
        index++;
      }
    }

    TLobby__sub_8020A618(&rec, p);
    swap_endian__20ChallengeRandomEventFv(&rec);
    *((s32 *) (((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14))) = id;
    *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 4)) = rec.x;
    *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 6)) = rec.z;
    *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 8)) = rec.type;
    *((s16 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 0xa)) = index;
    *((s32 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 0xc)) = clamp_min_drop__6TLobbyFUlUl(rec.drop_min, (rec.drop_max) + 1);
    *((s32 *) ((((u8 *) challenge_event_buffer) + (challenge_event_count * 0x14)) + 0x10)) = rec.data;
    challenge_event_count++;
  }

  if (slots > 0)
  {
    area = get_floor_area(floor_id);
    reserve_enemy_set_actor_ids(challenge_enemy_buffer, slots, area);
    init_floor_enemy_count__6TLobbyFlPUcUl(floor_id, (u8 *) challenge_enemy_buffer, slots * 0x48);
  }
  if (challenge_event_count > 0)
  {
    total = challenge_event_count * 0x14;
    size = challenge_action_size + 3;
    aligned = size;
    aligned &= ~3;
    total += rem;
    size = total;
    size += aligned;
    size += 0x10;
    dst = alloc_heap_slot__6TLobbyFll(floor_id, size);
    if (dst != 0)
    {
      out_hdr[0] = (challenge_event_count * 0x14) + 0x10;
      out_hdr[1] = 0x10;
      out_hdr[2] = challenge_event_count;
      move_data(dst, out_hdr, 0x10);
      if (challenge_event_count > 0)
      {
        dst = ((u8 *) dst) + 0x10;
        move_data(dst, challenge_event_buffer, challenge_event_count * 0x14);
      }
      if (rem > 0)
      {
        dst = ((u8 *) dst) + (challenge_event_count * 0x14);
        move_data(dst, ((u8 *) challenge_event_source) + hdr.data_offset, rem);
      }
      if (aligned > 0)
      {
        dst = ((u8 *) dst) + rem;
        move_data(dst, challenge_action_buffer, aligned);
      }
    }
  }
}
#pragma pop
