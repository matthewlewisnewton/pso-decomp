#ifndef PSO_MISC_TLOBBY_802409AC_TAIL_H
#define PSO_MISC_TLOBBY_802409AC_TAIL_H

LobbyGuildCardRecord::LobbyGuildCardRecord() {
    fn_80077AA4(&ext);
}

extern "C" {
s32 TLobby__sub_802428F8(void *record) {
    return static_cast<LobbyGuildCardRecord *>(record)->f4;
}

int get_com_card_data__6TLobbyFv() {
    return com_card_entry_count;
}
}

#endif
