#include "types.h"
#include "pso/misc/WordSelectMessage.h"
#include <string.h>

struct List_803467CC { s16 *items; s32 count; };
struct Buf_803467CC { s16 *a; s32 n4; s16 *b; s32 nC; };
struct Pair_80344980 { s16 *list; s32 n; };

extern "C" {
s32 TWindowDD__sub_80346DB8(s32 arg0);
s32 TWindowDD_read_indexed_value(s32, s32);
s16 TWindowDD_read_resolved_value(s32, s32);
u8 TWindowDD__sub_80347858(s16 arg0);
s32 get_word_select_context__9TWindowDDFv(u8 *arg0);
extern u8 *TWindowDD__ws_data_table;
s32 format_type6_message__9TWindowDDFlPv(WordSelectMessage *, char *, s32 *);
s32 TWindowDD__sub_8034740C(WordSelectMessage *, char *, s32 *);
s32 TWindowDD__sub_80347474(WordSelectMessage *, s32, char *, s32 *);
s32 append_prompt_newline__9TWindowDDFPl(char *, s32 *);
s32 maybe_scroll__9TWindowDDFPv(char *, s32 *);
s32 append_char__9TWindowDDFSclPl(s32, char *, s32 *);
s32 TWindowDD__sub_8034886C(s32, char *, s32 *);
List_803467CC *get_element_ptr__9TWindowDDFl(s16);
List_803467CC *get_entry__9TWindowDDFl(s32, s16);
extern s32 TWindowDD__window_mode;
extern u32 TWindowDD__word_select_lists;
s32 TWindowDD__sub_80347758(WordSelectMessage *, WordSelectMessage *);
s32 TWindowDD__sub_803474CC(WordSelectMessage *, s32, char *, char *, s32 *);
s32 append_string__9TWindowDDFllPl(const char *, char *, s32 *);
s32 show_message_by_count__9TWindowDDFll(char *, s32 *);
s32 can_append_chars__9TWindowDDFlPl(s32, s32 *);
s32 clamp_range_2C9_552__9TWindowDDFs(s16);
s32 clamp_range_5FA_682__9TWindowDDFs(s16);
char fn_80228C54(char);
extern char **TWindowDD__data_805D6E28;
extern Pair_80344980 *TWindowDD__data_805D6E40;
extern Pair_80344980 *TWindowDD__data_805D6E44;
extern u8 *TWindowDD__data_805D6E48;
s32 TWindowDD__sub_80348B70(s16 arg0);
void TWindowDD__sub_8034694C(WordSelectMessage *, s32, char *, char *, char *, s32 *);
extern const char lbl_805DFCC0[4], lbl_805DFCC4[4];

#pragma opt_common_subs off

s16 TWindowDD__sub_8034435C(u8 *window_dd, u32 arg1, s32 arg2, s32 value_index) {
    s16 v;
    switch (arg1) {
    case 0:
        v = TWindowDD_read_indexed_value(TWindowDD__sub_80346DB8((s32)window_dd), value_index);
        if (v == -0x1E) {
            switch (get_word_select_context__9TWindowDDFv(window_dd)) {
            case 1:
                v = 0x10;
                break;
            case 0:
                v = 0xF;
                break;
            case 3:
                v = 0x12;
                break;
            case 2:
                v = 0x11;
                break;
            case 4:
                v = 0x13;
                break;
            case 5:
                v = 0x14;
                break;
            }
        }
        break;
    case 1:
    case 2:
    case 6:
        v = -0x3C;
        break;
    case 3:
        v = TWindowDD_read_resolved_value(arg2, value_index);
        if (((s32 (*)(s16))TWindowDD__sub_80347858)(v) != 0) {
            if (v == 0x43) {
                v = -0x46;
            } else if (v == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        } else {
            v = -0x3C;
        }
        break;
    case 5:
        v = TWindowDD_read_indexed_value(0xE, value_index);
        break;
    case 12:
        {
            s16 t = TWindowDD_read_resolved_value(0xF9, value_index);
            if (t == 0x43) {
                v = -0x46;
            } else if (t == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        }
        break;
    case 13:
        if (TWindowDD_read_resolved_value(-0x50, value_index) == 0x2C8) {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x78))[*(s16 *)(window_dd + 0xFC) - 0x37];
        } else {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x80))[*(s16 *)(window_dd + 0xFC) - 0x37];
        }
        break;
    case 14:
        v = TWindowDD_read_indexed_value(0xF, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 15:
        v = -0x32;
        break;
    case 17:
        v = TWindowDD_read_indexed_value(0x11, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 18:
        v = -0x32;
        break;
    default:
        v = -1;
        break;
    }
    return v;
}
s16 TWindowDD__sub_80344568(u8 *window_dd, u32 arg1, s32 arg2, s32 value_index) {
    s16 v;
    switch (arg1) {
    case 0:
        v = TWindowDD_read_indexed_value(TWindowDD__sub_80346DB8((s32)window_dd), value_index);
        if (v == -0x1E) {
            switch (get_word_select_context__9TWindowDDFv(window_dd)) {
            case 1:
                v = 0x10;
                break;
            case 0:
                v = 0xF;
                break;
            case 3:
                v = 0x12;
                break;
            case 2:
                v = 0x11;
                break;
            case 4:
                v = 0x13;
                break;
            case 5:
                v = 0x14;
                break;
            }
        }
        break;
    case 1:
    case 2:
    case 6:
        v = -0x3C;
        break;
    case 3:
        v = TWindowDD_read_resolved_value(arg2, value_index);
        if (((s32 (*)(s16))TWindowDD__sub_80347858)(v) != 0) {
            if (v == 0x43) {
                v = -0x46;
            } else if (v == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        } else {
            v = -0x3C;
        }
        break;
    case 5:
        v = TWindowDD_read_indexed_value(0xE, value_index);
        break;
    case 12:
        {
            s16 t = TWindowDD_read_resolved_value(0xF9, value_index);
            if (t == 0x43) {
                v = -0x46;
            } else if (t == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        }
        break;
    case 13:
        if (TWindowDD_read_resolved_value(-0x50, value_index) == 0x2C8) {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x78))[*(s16 *)(window_dd + 0xFC) - 0x37];
        } else {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x80))[*(s16 *)(window_dd + 0xFC) - 0x37];
        }
        break;
    case 14:
        v = TWindowDD_read_indexed_value(0xF, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 15:
        v = -0x32;
        break;
    case 17:
        v = TWindowDD_read_indexed_value(0x11, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 18:
        v = -0x32;
        break;
    default:
        v = -1;
        break;
    }
    return v;
}
s16 TWindowDD__sub_80344774(u8 *window_dd, u32 arg1, s32 arg2, s32 value_index) {
    s16 v;
    switch (arg1) {
    case 0:
        v = TWindowDD_read_indexed_value(TWindowDD__sub_80346DB8((s32)window_dd), value_index);
        if (v == -0x1E) {
            switch (get_word_select_context__9TWindowDDFv(window_dd)) {
            case 1:
                v = 0x10;
                break;
            case 0:
                v = 0xF;
                break;
            case 3:
                v = 0x12;
                break;
            case 2:
                v = 0x11;
                break;
            case 4:
                v = 0x13;
                break;
            case 5:
                v = 0x14;
                break;
            }
        }
        break;
    case 1:
    case 2:
    case 6:
        v = -0x3C;
        break;
    case 3:
        v = TWindowDD_read_resolved_value(arg2, value_index);
        if (((s32 (*)(s16))TWindowDD__sub_80347858)(v) != 0) {
            if (v == 0x43) {
                v = -0x46;
            } else if (v == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        } else {
            v = -0x3C;
        }
        break;
    case 5:
        v = TWindowDD_read_indexed_value(0xE, value_index);
        break;
    case 12:
        {
            s16 t = TWindowDD_read_resolved_value(0xF9, value_index);
            if (t == 0x43) {
                v = -0x46;
            } else if (t == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        }
        break;
    case 13:
        if (TWindowDD_read_resolved_value(-0x50, value_index) == 0x2C8) {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x78))[*(s16 *)(window_dd + 0xFC) - 0x37];
        } else {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x80))[*(s16 *)(window_dd + 0xFC) - 0x37];
        }
        break;
    case 14:
        v = TWindowDD_read_indexed_value(0xF, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 15:
        v = -0x32;
        break;
    case 17:
        v = TWindowDD_read_indexed_value(0x11, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 18:
        v = -0x32;
        break;
    default:
        v = -1;
        break;
    }
    return v;
}

s32 format_word_select_french(WordSelectMessage *src, char *window_dd, s32 arg2) {
    s32 k;
    s32 n;
    s32 m;
    s32 i;
    s32 pos;
    i = 0;
    pos = i;
    n = src->count;
    if (n == 0) {
        window_dd[0] = i;
        return 1;
    }
    switch (src->type) {
    case 1:
        TWindowDD__sub_8034740C(src, window_dd, &pos);
        break;
    case 2:
        if (n > 2) {
            n = 2;
        }
        for (m = 0; m < n; m++) {
            if (m == 1) {
                append_char__9TWindowDDFSclPl(0x20, window_dd, &pos);
            }
            TWindowDD__sub_8034886C(src->ids[m], window_dd, &pos);
        }
        append_char__9TWindowDDFSclPl(0x3F, window_dd, &pos);
        if (src->count > 2) {
            append_prompt_newline__9TWindowDDFPl(window_dd, &pos);
            TWindowDD__sub_8034886C(src->ids[2], window_dd, &pos);
        }
        break;
    case 3:
        if (n > 1) {
            struct { WordSelectMessage dd; u8 pad[0x10]; } tmp;
            TWindowDD__sub_80347758(src, &tmp.dd);
            pos = format_word_select_french(&tmp.dd, window_dd, arg2);
        } else {
            TWindowDD__sub_8034886C(src->ids[0], window_dd, &pos);
        }
        break;
    case 4: {
        s32 id = src->ids[0];
        k = 0;
        if (id == 0x2C4) {
            TWindowDD__sub_8034886C(id, window_dd, &pos);
        } else if (id == 0x2C7) {
            TWindowDD__sub_8034886C(id, window_dd, &pos);
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA58 / 4], window_dd, &pos);
            k = 2;
        } else if (id >= 0x68C && id <= 0x697) {
            TWindowDD__sub_8034886C(id, window_dd, &pos);
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA4C / 4], window_dd, &pos);
            k = 1;
        } else if (id == 0x698) {
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA4C / 4], window_dd, &pos);
            k = 1;
        }
        if (n > 1) {
            i = src->ids[1];
            show_message_by_count__9TWindowDDFll(window_dd, &pos);
            if (k == 0) {
                TWindowDD__sub_8034886C(i, window_dd, &pos);
            } else {
                Pair_80344980 *p;
                if (k == 1) {
                    p = &TWindowDD__data_805D6E40[1];
                } else {
                    p = &TWindowDD__data_805D6E40[0];
                }
                append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[p->list[i - 0x5AC]], window_dd, &pos);
            }
        }
        if (n > 2) {
            show_message_by_count__9TWindowDDFll(window_dd, &pos);
            TWindowDD__sub_80347474(src, src->ids[2], window_dd, &pos);
        }
        if (n > 3) {
            TWindowDD__sub_8034886C(src->ids[3], window_dd, &pos);
        }
        window_dd[0] = fn_80228C54(window_dd[0]);
        break;
    }
    case 5: {
        s32 mode;
        k = src->ids[0];
        TWindowDD__sub_80347474(src, k, window_dd, &pos);
        if (k == 0x2C4) {
            mode = 0;
            i = word_select_player_gender(arg2);
        } else if (k == 0x2C7) {
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA58 / 4], window_dd, &pos);
            mode = 2;
            if (word_select_player_gender(arg2) == 2) {
                i = 3;
            } else {
                i = 1;
            }
        } else if (k >= 0x68C && k <= 0x697) {
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA4C / 4], window_dd, &pos);
            mode = 1;
            i = word_select_player_gender((k - 0x68C) & 0xFFFF);
        } else {
            mode = 3;
            if (k == 0x2C5) {
                i = 0;
            } else if (k == 0x2C6) {
                i = 2;
            } else {
                switch (TWindowDD__data_805D6E48[clamp_range_2C9_552__9TWindowDDFs(k)]) {
                case 0:
                    i = 0;
                    break;
                case 1:
                    i = 1;
                    break;
                case 2:
                    i = 2;
                    break;
                case 3:
                    i = 3;
                    break;
                }
            }
        }
        if (n > 1) {
            s32 found;
            s32 j;
            show_message_by_count__9TWindowDDFll(window_dd, &pos);
            found = 1;
            k = src->ids[1];
            for (j = 0; j < TWindowDD__data_805D6E44[3].n; j++) {
                if (k == TWindowDD__data_805D6E44[3].list[j]) {
                    found = 0;
                    break;
                }
            }
            if (found != 0) {
                switch (mode) {
                case 0:
                    append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0x1A8C / 4], window_dd, &pos);
                    break;
                case 1:
                    append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0x1A94 / 4], window_dd, &pos);
                    break;
                case 2:
                    append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0x1A90 / 4], window_dd, &pos);
                    break;
                case 3:
                    append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0x1A98 / 4], window_dd, &pos);
                    break;
                }
                show_message_by_count__9TWindowDDFll(window_dd, &pos);
            }
            if (i == 0) {
                TWindowDD__sub_80347474(src, k, window_dd, &pos);
            } else {
                Pair_80344980 *p;
                if (i == 1) {
                    p = &TWindowDD__data_805D6E44[0];
                } else if (i == 2) {
                    p = &TWindowDD__data_805D6E44[1];
                } else {
                    p = &TWindowDD__data_805D6E44[2];
                }
                TWindowDD__sub_803474CC(src, k, TWindowDD__data_805D6E28[p->list[clamp_range_5FA_682__9TWindowDDFs(k)]], window_dd, &pos);
            }
        }
        if (n > 2) {
            TWindowDD__sub_8034886C(src->ids[2], window_dd, &pos);
        }
        window_dd[0] = fn_80228C54(window_dd[0]);
        break;
    }
    case 6:
        format_type6_message__9TWindowDDFlPv(src, window_dd, &pos);
        break;
    }
    window_dd[pos++] = 0;
    return pos;
}

s32 format_word_select_german(WordSelectMessage *src, char *window_dd, s32 arg2) {
    s32 pos;
    s32 id;
    s32 kind;
    s32 n;
    pos = 0;
    n = src->count;
    if (n == 0) {
        window_dd[0] = 0;
        return 1;
    }
    switch (src->type) {
    case 1:
        TWindowDD__sub_8034740C(src, window_dd, &pos);
        break;
    case 2:
        if (n > 2) {
            n = 2;
        }
        {
        s32 i;
        for (i = 0; i < n; i++) {
            if (i == 1) {
                append_char__9TWindowDDFSclPl(0x20, window_dd, &pos);
            }
            TWindowDD__sub_8034886C(src->ids[i], window_dd, &pos);
        }
        }
        append_char__9TWindowDDFSclPl(0x3F, window_dd, &pos);
        if (src->count > 2) {
            append_prompt_newline__9TWindowDDFPl(window_dd, &pos);
            TWindowDD__sub_8034886C(src->ids[2], window_dd, &pos);
        }
        break;
    case 3:
        if (n > 1) {
            struct { WordSelectMessage dd; u8 pad[0x10]; } tmp;
            TWindowDD__sub_80347758(src, &tmp.dd);
            pos = format_word_select_german(&tmp.dd, window_dd, arg2);
        } else {
            TWindowDD__sub_8034886C(src->ids[0], window_dd, &pos);
        }
        break;
    case 4: {
        s32 id1;
        s32 k;
        char *s1;
        char *s2;
        s32 id4;
        id4 = src->ids[0];
        s1 = 0;
        k = 0;
        if (id4 == 0x2C4) {
            s1 = (char *)TWindowDD__sub_80348B70(0x2C4);
        } else if (id4 == 0x2C7) {
            TWindowDD__sub_8034886C(id4, window_dd, &pos);
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            k = 2;
            s1 = TWindowDD__data_805D6E28[0x2A6];
        } else if (id4 >= 0x68C && id4 <= 0x697) {
            TWindowDD__sub_8034886C(id4, window_dd, &pos);
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            k = 1;
            s1 = TWindowDD__data_805D6E28[0x2A3];
        } else if (id4 == 0x698) {
            k = 1;
            s1 = TWindowDD__data_805D6E28[0x2A3];
        }
        if (n > 1) {
            id1 = src->ids[1];
            kind = k;
            if (kind == 0) {
                s2 = (char *)TWindowDD__sub_80348B70(id1);
            } else {
                Pair_80344980 *pp;
                if (kind == 1) {
                    pp = &TWindowDD__data_805D6E40[1];
                } else {
                    pp = &TWindowDD__data_805D6E40[0];
                }
                s2 = TWindowDD__data_805D6E28[pp->list[id1 - 0x5AC]];
            }
            if (n > 3 && src->ids[3] == 0x685) {
                if (s1 != 0 && s2 != 0) {
                    TWindowDD__sub_8034694C(src, id1, s1, s2, window_dd, &pos);
                }
            } else {
                append_string__9TWindowDDFllPl(s1, window_dd, &pos);
                show_message_by_count__9TWindowDDFll(window_dd, &pos);
                append_string__9TWindowDDFllPl(s2, window_dd, &pos);
            }
        } else {
            append_string__9TWindowDDFllPl(s1, window_dd, &pos);
        }
        if (n > 2) {
            show_message_by_count__9TWindowDDFll(window_dd, &pos);
            TWindowDD__sub_80347474(src, src->ids[2], window_dd, &pos);
        }
        if (n > 3) {
            TWindowDD__sub_8034886C(src->ids[3], window_dd, &pos);
        }
        window_dd[0] = fn_80228C54(window_dd[0]);
        break;
    }
    case 5: {
        s32 mode;
        char *s3;
        char *s1;
        id = src->ids[0];
        s3 = 0;
        if (id == 0x2C4) {
            mode = 0;
            kind = word_select_player_gender(arg2);
            s1 = (char *)TWindowDD__sub_80348B70(id);
        } else if (id == 0x2C7) {
            TWindowDD__sub_8034886C(id, window_dd, &pos);
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            mode = 2;
            {
            s32 st = word_select_player_gender(arg2);
            kind = 1;
            if (st == 2) {
                kind = 3;
            }
            }
            s1 = TWindowDD__data_805D6E28[0x2A6];
        } else if (id >= 0x68C && id <= 0x697) {
            TWindowDD__sub_8034886C(id, window_dd, &pos);
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            mode = 1;
            kind = word_select_player_gender((id - 0x68C) & 0xFFFF);
            s1 = TWindowDD__data_805D6E28[0x2A3];
        } else {
            mode = 3;
            if (id == 0x2C5) {
                kind = 0;
            } else if (id == 0x2C6) {
                kind = 2;
            } else {
                switch (TWindowDD__data_805D6E48[clamp_range_2C9_552__9TWindowDDFs(id)]) {
                case 0:
                default:
                    kind = 0;
                    break;
                case 1:
                    kind = 2;
                    break;
                case 2:
                    kind = 4;
                    break;
                }
            }
            s1 = (char *)TWindowDD__sub_80348B70(id);
        }
        if (n > 1) {
            s32 found;
            s32 cnt;
            found = 1;
            id = src->ids[1];
            cnt = TWindowDD__data_805D6E44[4].n;
            {
            s32 i;
            for (i = 0; i < cnt; i++) {
                if (TWindowDD__data_805D6E44[4].list[i] == id) {
                    found = 0;
                    break;
                }
            }
            }
            if (found) {
                switch (mode) {
                case 0:
                    s3 = TWindowDD__data_805D6E28[0x6A6];
                    break;
                case 1:
                    s3 = TWindowDD__data_805D6E28[0x6A8];
                    break;
                case 2:
                    s3 = TWindowDD__data_805D6E28[0x6A7];
                    break;
                case 3:
                    s3 = TWindowDD__data_805D6E28[0x6A9];
                    break;
                }
                if (n > 2 && src->ids[2] == 0x685) {
                    if (s1 != 0 && s3 != 0) {
                        TWindowDD__sub_8034694C(src, src->ids[0], s1, s3, window_dd, &pos);
                    }
                } else {
                    TWindowDD__sub_803474CC(src, src->ids[0], s1, window_dd, &pos);
                    show_message_by_count__9TWindowDDFll(window_dd, &pos);
                    append_string__9TWindowDDFllPl(s3, window_dd, &pos);
                }
                show_message_by_count__9TWindowDDFll(window_dd, &pos);
            } else {
                TWindowDD__sub_803474CC(src, src->ids[0], s1, window_dd, &pos);
                show_message_by_count__9TWindowDDFll(window_dd, &pos);
            }
            if (kind == 0) {
                TWindowDD__sub_80347474(src, id, window_dd, &pos);
            } else {
                Pair_80344980 *pp;
                if (kind == 2) {
                    pp = &TWindowDD__data_805D6E44[0];
                } else if (kind == 4) {
                    pp = &TWindowDD__data_805D6E44[1];
                } else if (kind == 1) {
                    pp = &TWindowDD__data_805D6E44[2];
                } else {
                    pp = &TWindowDD__data_805D6E44[3];
                }
                TWindowDD__sub_803474CC(src, id, TWindowDD__data_805D6E28[pp->list[clamp_range_5FA_682__9TWindowDDFs(id)]], window_dd, &pos);
            }
        } else if (src->ids[0] == 0x2C7) {
            append_string__9TWindowDDFllPl(s1, window_dd, &pos);
        } else {
            TWindowDD__sub_80347474(src, src->ids[0], window_dd, &pos);
        }
        if (n > 2) {
            TWindowDD__sub_8034886C(src->ids[2], window_dd, &pos);
        }
        window_dd[0] = fn_80228C54(window_dd[0]);
        break;
    }
    case 6:
        format_type6_message__9TWindowDDFlPv(src, window_dd, &pos);
        break;
    }
    window_dd[pos++] = 0;
    return pos;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
// The word stays live while the separator is appended.
static inline void append_spanish_word_form(s32 id, s32 form, char *buffer, s32 *length) {
    show_message_by_count__9TWindowDDFll(buffer, length);
    if (form == 0) {
        TWindowDD__sub_8034886C(id, buffer, length);
    } else {
        Pair_80344980 *forms;
        if (form == 1) {
            forms = &TWindowDD__data_805D6E40[1];
        } else {
            forms = &TWindowDD__data_805D6E40[0];
        }
        append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[forms->list[id - 0x5AC]], buffer, length);
    }
}

s32 format_word_select_spanish(WordSelectMessage *src, char *buffer, s32 player) {
    s32 selection;
    s32 count;
    s32 wordId;
    s32 value;
    s32 length;
    value = 0;
    length = value;
    count = src->count;
    if (count == 0) {
        buffer[0] = value;
        return 1;
    }
    switch (src->type) {
    case 1:
        TWindowDD__sub_8034740C(src, buffer, &length);
        break;
    case 2:
        if (count > 2) {
            count = 2;
        }
        for (value = 0; value < count; value++) {
            if (value == 1) {
                append_char__9TWindowDDFSclPl(0x20, buffer, &length);
            }
            TWindowDD__sub_8034886C(src->ids[value], buffer, &length);
        }
        append_char__9TWindowDDFSclPl(0x3F, buffer, &length);
        if (src->count > 2) {
            append_prompt_newline__9TWindowDDFPl(buffer, &length);
            TWindowDD__sub_8034886C(src->ids[2], buffer, &length);
        }
        break;
    case 3:
        if (count > 1) {
            struct { WordSelectMessage dd; u8 pad[0x10]; } tmp;
            TWindowDD__sub_80347758(src, &tmp.dd);
            length = format_word_select_spanish(&tmp.dd, buffer, player);
        } else {
            TWindowDD__sub_8034886C(src->ids[0], buffer, &length);
        }
        break;
    case 4: {
        if (count > 3) {
            if (src->ids[3] == 0x685) {
                append_string__9TWindowDDFllPl(lbl_805DFCC0, buffer, &length);
            } else if (src->ids[3] == 0x686) {
                append_string__9TWindowDDFllPl(lbl_805DFCC4, buffer, &length);
            }
        }
        wordId = src->ids[0];
        if (wordId != 0x2C8) {
            TWindowDD__sub_8034886C(wordId, buffer, &length);
        }
        selection = 0;
        if (wordId == 0x2C7) {
            append_char__9TWindowDDFSclPl(0x2C, buffer, &length);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA8C / 4], buffer, &length);
            selection = 2;
        } else if (wordId >= 0x68C && wordId <= 0x697) {
            append_char__9TWindowDDFSclPl(0x2C, buffer, &length);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA80 / 4], buffer, &length);
            selection = 1;
        } else if (wordId == 0x698) {
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA80 / 4], buffer, &length);
            selection = 1;
        }
        if (count > 1) {
            append_spanish_word_form(src->ids[1], selection, buffer, &length);
        }
        if (count > 2) {
            show_message_by_count__9TWindowDDFll(buffer, &length);
            TWindowDD__sub_80347474(src, src->ids[2], buffer, &length);
        }
        if (count > 3) {
            TWindowDD__sub_8034886C(src->ids[3], buffer, &length);
        }
        buffer[0] = fn_80228C54(buffer[0]);
        break;
    }
    case 5: {
        s32 mode;
        if (count > 2) {
            if (src->ids[2] == 0x685) {
                append_string__9TWindowDDFllPl(lbl_805DFCC0, buffer, &length);
            } else if (src->ids[2] == 0x686) {
                append_string__9TWindowDDFllPl(lbl_805DFCC4, buffer, &length);
            }
        }
        selection = src->ids[0];
        TWindowDD__sub_80347474(src, selection, buffer, &length);
        if (selection == 0x2C4) {
            mode = 0;
            value = word_select_player_gender(player);
        } else if (selection == 0x2C7) {
            mode = 2;
            append_char__9TWindowDDFSclPl(0x2C, buffer, &length);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA8C / 4], buffer, &length);
            if (word_select_player_gender(player) == 2) {
                value = 3;
            } else {
                value = 1;
            }
        } else if (selection >= 0x68C && selection <= 0x697) {
            mode = 1;
            append_char__9TWindowDDFSclPl(0x2C, buffer, &length);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[0xA80 / 4], buffer, &length);
            value = word_select_player_gender((selection - 0x68C) & 0xFFFF);
        } else {
            mode = 3;
            if (selection == 0x2C5) {
                value = 0;
            } else if (selection == 0x2C6) {
                value = 2;
            } else {
                switch (TWindowDD__data_805D6E48[clamp_range_2C9_552__9TWindowDDFs(selection)]) {
                case 0: value = 0; break;
                case 1: value = 1; break;
                case 2: value = 2; break;
                case 3: value = 3; break;
                }
            }
        }
        if (count > 1) {
            s32 hasPrefix;

            show_message_by_count__9TWindowDDFll(buffer, &length);
            selection = src->ids[1];
            switch (lbl_805D6E4C[clamp_range_5FA_682__9TWindowDDFs(selection)]) {
            case 0:
                hasPrefix = 1;
                switch (mode) {
                case 0: wordId = 0x697; break;
                case 1: wordId = 0x699; break;
                case 2: wordId = 0x698; break;
                case 3: wordId = 0x69A; break;
                }
                break;
            case 1:
                hasPrefix = 1;
                switch (mode) {
                case 0: wordId = 0x69B; break;
                case 1: wordId = 0x279; break;
                case 2: wordId = 0x69C; break;
                case 3: wordId = 0x69D; break;
                }
                break;
            // Category 2 and unrecognized categories have no prefix.
            case 2:
            default:
                hasPrefix = 0;
                break;
            }
            if (hasPrefix != 0) {
                append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[wordId], buffer, &length);
                show_message_by_count__9TWindowDDFll(buffer, &length);
            }
            if (value == 0) {
                TWindowDD__sub_80347474(src, selection, buffer, &length);
            } else {
                Pair_80344980 *p;
                if (value == 1) {
                    p = &TWindowDD__data_805D6E44[0];
                } else if (value == 2) {
                    p = &TWindowDD__data_805D6E44[1];
                } else {
                    p = &TWindowDD__data_805D6E44[2];
                }
                TWindowDD__sub_803474CC(src, selection, TWindowDD__data_805D6E28[p->list[clamp_range_5FA_682__9TWindowDDFs(selection)]], buffer, &length);
            }
        }
        if (count > 2) {
            TWindowDD__sub_8034886C(src->ids[2], buffer, &length);
        }
        buffer[0] = fn_80228C54(buffer[0]);
        break;
    }
    case 6:
        format_type6_message__9TWindowDDFlPv(src, buffer, &length);
        break;
    }
    buffer[length++] = 0;
    return length;
}

#pragma pop
#pragma push
#pragma opt_common_subs on
s32 format_word_select_english(WordSelectMessage *src, char *window_dd, s32 arg2) {
    s32 b;
    s32 n;
    s32 i;
    s32 pos;
    pos = 0;
    n = src->count;
    if (n == 0) {
        window_dd[0] = 0;
        return 1;
    }
    switch (src->type) {
    case 1:
        TWindowDD__sub_8034740C(src, window_dd, &pos);
        break;
    case 2:
        if (n > 2) {
            n = 2;
        }
        {
        for (i = 0; i < n; i++) {
            if (i == 1) {
                append_char__9TWindowDDFSclPl(0x20, window_dd, &pos);
            }
            TWindowDD__sub_8034886C(src->ids[i], window_dd, &pos);
        }
        }
        append_char__9TWindowDDFSclPl(0x3F, window_dd, &pos);
        if (src->count > 2) {
            append_prompt_newline__9TWindowDDFPl(window_dd, &pos);
            TWindowDD__sub_8034886C(src->ids[2], window_dd, &pos);
        }
        break;
    case 3:
        if (n > 1) {
            struct { WordSelectMessage dd; u8 pad[0x10]; } tmp;
            TWindowDD__sub_80347758(src, &tmp.dd);
            pos = format_word_select_english(&tmp.dd, window_dd, arg2);
        } else {
            TWindowDD__sub_8034886C(src->ids[0], window_dd, &pos);
        }
        break;
    case 4: {
        s32 id;
        s32 k;
        id = src->ids[0];
        if (id != 712) {
            TWindowDD__sub_8034886C(id, window_dd, &pos);
        }
        k = 0;
        if (id == 711) {
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(0xA60 / 4)], window_dd, &pos);
            k = 2;
        } else if (id >= 1676 && id <= 1687) {
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(0xA54 / 4)], window_dd, &pos);
            k = 2;
        } else if (id == 1688) {
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(0xA54 / 4)], window_dd, &pos);
            k = 2;
        }
        if (n > 1) {
            i = src->ids[1];
            show_message_by_count__9TWindowDDFll(window_dd, &pos);
            if (k == 0) {
                TWindowDD__sub_8034886C(i, window_dd, &pos);
            } else {
                append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(TWindowDD__data_805D6E40->list[i - 1452])], window_dd, &pos);
            }
        }
        if (n > 2) {
            show_message_by_count__9TWindowDDFll(window_dd, &pos);
            switch (TWindowDD__data_805D6E48[clamp_range_2C9_552__9TWindowDDFs(src->ids[2])]) {
            case 1:
                append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(0x19E4 / 4)], window_dd, &pos);
                append_char__9TWindowDDFSclPl(0x20, window_dd, &pos);
                break;
            case 2:
                append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(0x19E8 / 4)], window_dd, &pos);
                append_char__9TWindowDDFSclPl(0x20, window_dd, &pos);
                break;
            }
            TWindowDD__sub_80347474(src, src->ids[2], window_dd, &pos);
        }
        if (n > 3) {
            TWindowDD__sub_8034886C(src->ids[3], window_dd, &pos);
        }
        window_dd[0] = fn_80228C54(window_dd[0]);
        break;
    }
    case 5: {
        s32 kind;
        s32 id;
        id = src->ids[0];
        TWindowDD__sub_80347474(src, id, window_dd, &pos);
        if (id == 708) {
            kind = 0;
        } else if (id == 711) {
            kind = 2;
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(0xA60 / 4)], window_dd, &pos);
        } else if (id >= 1676 && id <= 1687) {
            kind = 1;
            append_char__9TWindowDDFSclPl(0x2C, window_dd, &pos);
            append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(0xA54 / 4)], window_dd, &pos);
        } else {
            kind = 3;
            window_dd[0] = fn_80228C54(window_dd[0]);
        }
        if (n > 1) {
            s32 notfound;
            char *str;
            show_message_by_count__9TWindowDDFll(window_dd, &pos);
            b = src->ids[1];
            notfound = 1;
            for (i = 0; i < TWindowDD__data_805D6E44[0].n; i++) {
                if (b == TWindowDD__data_805D6E44[0].list[i]) {
                    notfound = 0;
                    break;
                }
            }
            if (notfound != 0) {
                switch (kind) {
                case 0:
                    append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(6012 / 4)], window_dd, &pos);
                    break;
                case 1:
                case 2:
                    append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(6016 / 4)], window_dd, &pos);
                    break;
                case 3:
                    append_string__9TWindowDDFllPl(TWindowDD__data_805D6E28[(6020 / 4)], window_dd, &pos);
                    break;
                }
                show_message_by_count__9TWindowDDFll(window_dd, &pos);
            }
            str = 0;
            if (kind == 2) {
                for (i = 0; i < TWindowDD__data_805D6E44[1].n; i++) {
                    if (b == TWindowDD__data_805D6E44[1].list[i]) {
                        str = TWindowDD__data_805D6E28[(TWindowDD__data_805D6E44[2].list[i])];
                        break;
                    }
                }
            }
            if (str != 0) {
                TWindowDD__sub_803474CC(src, b, str, window_dd, &pos);
            } else {
                TWindowDD__sub_80347474(src, b, window_dd, &pos);
            }
        }
        if (n > 2) {
            TWindowDD__sub_8034886C(src->ids[2], window_dd, &pos);
        }
        window_dd[0] = fn_80228C54(window_dd[0]);
        break;
    }
    case 6:
        format_type6_message__9TWindowDDFlPv(src, window_dd, &pos);
        break;
    }
    window_dd[pos++] = 0;
    return pos;
}
#pragma pop

s32 format_word_select_japanese(WordSelectMessage *arg0, char *window_dd) {
    s32 pos;
    s32 n;
    pos = 0;
    n = arg0->count;
    if (n == 0) {
        window_dd[0] = 0;
        return 1;
    }
    switch (arg0->type) {
    case 1:
        TWindowDD__sub_8034740C(arg0, window_dd, &pos);
        break;
    case 2:
        if (n > 2) {
            n = 2;
        }
        {
        s32 i;
        for (i = 0; i < n; i++) {
            TWindowDD__sub_8034886C(arg0->ids[i], window_dd, &pos);
        }
        }
        append_char__9TWindowDDFSclPl(0x3F, window_dd, &pos);
        if (arg0->count > 2) {
            append_prompt_newline__9TWindowDDFPl(window_dd, &pos);
            TWindowDD__sub_8034886C(arg0->ids[2], window_dd, &pos);
        }
        break;
    case 3:
        if (n > 3) {
            n = 3;
        }
        {
        s32 i;
        for (i = 0; i < n; i++) {
            if (i != 2) {
                maybe_scroll__9TWindowDDFPv(window_dd, &pos);
            }
            TWindowDD__sub_80347474(arg0, arg0->ids[i], window_dd, &pos);
        }
        }
        if (arg0->count > 3) {
            append_prompt_newline__9TWindowDDFPl(window_dd, &pos);
            TWindowDD__sub_8034886C(arg0->ids[3], window_dd, &pos);
        }
        break;
    case 4:
        if (n > 2) {
            TWindowDD__sub_80347474(arg0, arg0->ids[2], window_dd, &pos);
        }
        if (n > 1) {
            maybe_scroll__9TWindowDDFPv(window_dd, &pos);
            TWindowDD__sub_8034886C(arg0->ids[1], window_dd, &pos);
        }
        if (n > 3) {
            TWindowDD__sub_8034886C(arg0->ids[3], window_dd, &pos);
        }
        append_prompt_newline__9TWindowDDFPl(window_dd, &pos);
        TWindowDD__sub_8034886C(arg0->ids[0], window_dd, &pos);
        break;
    case 5:
        {
        s32 i;
        for (i = 0; i < n; i++) {
            if (i != 2) {
                maybe_scroll__9TWindowDDFPv(window_dd, &pos);
            }
            TWindowDD__sub_80347474(arg0, arg0->ids[i], window_dd, &pos);
        }
        }
        break;
    case 6:
        format_type6_message__9TWindowDDFlPv(arg0, window_dd, &pos);
        break;
    }
    window_dd[pos++] = 0;
    return pos;
}

s16 TWindowDD__sub_80346434(u8 *window_dd, u32 arg1, s32 arg2, s32 value_index) {
    s16 v;
    switch (arg1) {
    case 0:
        v = TWindowDD_read_indexed_value(TWindowDD__sub_80346DB8((s32)window_dd), value_index);
        if (v == -0x1E) {
            switch (get_word_select_context__9TWindowDDFv(window_dd)) {
            case 1:
                v = 0x10;
                break;
            case 0:
                v = 0xF;
                break;
            case 3:
                v = 0x12;
                break;
            case 2:
                v = 0x11;
                break;
            case 4:
                v = 0x13;
                break;
            case 5:
                v = 0x14;
                break;
            }
        }
        break;
    case 1:
    case 2:
    case 6:
        v = -0x3C;
        break;
    case 3:
        v = TWindowDD_read_resolved_value(arg2, value_index);
        if (((s32 (*)(s16))TWindowDD__sub_80347858)(v) != 0) {
            if (v == 0x43) {
                v = -0x46;
            } else if (v == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        } else {
            v = -0x3C;
        }
        break;
    case 5:
        v = TWindowDD_read_indexed_value(0xE, value_index);
        break;
    case 12:
        {
            s16 t = TWindowDD_read_resolved_value(0xF9, value_index);
            if (t == 0x43) {
                v = -0x46;
            } else if (t == 0x44) {
                v = -0x5A;
            } else {
                v = -0x50;
            }
        }
        break;
    case 13:
        if (TWindowDD_read_resolved_value(-0x50, value_index) == 0x2C8) {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x78))[*(s16 *)(window_dd + 0xFC) - 0x37];
        } else {
            v = (*(s16 **)(TWindowDD__ws_data_table + 0x80))[*(s16 *)(window_dd + 0xFC) - 0x37];
        }
        break;
    case 14:
        v = TWindowDD_read_indexed_value(0xF, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 15:
        v = -0x32;
        break;
    case 17:
        v = TWindowDD_read_indexed_value(0x11, *(s16 *)(window_dd + 0xFC) - 0x37);
        break;
    case 18:
        v = -0x32;
        break;
    default:
        v = -1;
        break;
    }
    return v;
}
s32 TWindowDD__sub_80346640(u8 *arg0, u32 arg1, s32 arg2, s32 value_index) {
    s32 var_r31;
    s16 temp_r31;

    switch (arg1) {
    case 0:
        var_r31 = ((s16 (*)(s32, s32))TWindowDD_read_indexed_value)(TWindowDD__sub_80346DB8((s32) arg0), value_index);
        if (var_r31 == -0x1E) {
            switch (((int (*)(u8 *)) get_word_select_context__9TWindowDDFv)(arg0)) {
            case 1:
                var_r31 = 0x10;
                break;
            case 0:
                var_r31 = 0xF;
                break;
            case 3:
                var_r31 = 0x12;
                break;
            case 2:
                var_r31 = 0x11;
                break;
            case 4:
                var_r31 = 0x13;
                break;
            case 5:
                var_r31 = 0x14;
                break;
            }
        }
        break;
    case 1:
    case 2:
    case 6:
        var_r31 = -0x3C;
        break;
    case 3:
        temp_r31 = TWindowDD_read_resolved_value(arg2, value_index);
        if (((s32 (*)(s16)) TWindowDD__sub_80347858)(temp_r31) != 0) {
            var_r31 = ((s16 (*)(s32, s32))TWindowDD_read_indexed_value)(0xF, temp_r31 - 0x37);
        } else {
            var_r31 = -0x3C;
        }
        break;
    case 5:
        var_r31 = ((s16 (*)(s32, s32))TWindowDD_read_indexed_value)(0xE, value_index);
        break;
    case 7:
        var_r31 = ((s16 (*)(s32, s32))TWindowDD_read_indexed_value)(0xF, value_index);
        break;
    case 8:
        var_r31 = ((s16 (*)(s32, s32))TWindowDD_read_indexed_value)(0x10, *(s16 *)(arg0 + 0xFC) - 0x37);
        break;
    case 9:
        var_r31 = -0x32;
        break;
    case 10:
        if (TWindowDD_read_resolved_value(0x118, value_index) == 0x685) {
            var_r31 = -0x3C;
        } else {
            var_r31 = -1;
        }
        break;
    default:
        var_r31 = -1;
        break;
    }
    return var_r31;
}
#define BUF_803467CC ((Buf_803467CC *)TWindowDD__word_select_lists)
void build_item_list__9TWindowDDFPv(u8 *arg0) {
    s32 kind;
    s16 id;
    List_803467CC *sel;
    s32 idx;
    List_803467CC *entry;
    List_803467CC *extra;
    s32 n;
    s16 *a;
    s16 *b;
    s32 i;
    s32 j;
    switch (TWindowDD__window_mode) {
    case 0:
        kind = 0x11;
        id = 0xE;
        break;
    default:
        kind = 0x12;
        id = 0xE;
        break;
    case 4:
        kind = 0x12;
        id = 0xE;
        break;
    case 2:
        kind = 0x12;
        id = 0xE;
        break;
    case 3:
        kind = 0x12;
        id = 0xE;
        break;
    }
    sel = NULL;
    idx = *(s16 *)(arg0 + 0x1C) - 0x7F;
    entry = get_entry__9TWindowDDFl(kind, *(s16 *)(arg0 + 0x1C));
    if (entry != NULL && idx >= 0 && idx < entry->count) {
        sel = get_element_ptr__9TWindowDDFl(entry->items[idx]);
    }
    extra = get_element_ptr__9TWindowDDFl(id);
    n = 0;
    a = BUF_803467CC->a;
    b = BUF_803467CC->b;
    if (sel != NULL) {
        for (i = 0; i < sel->count && n < 0x20; n++, i++) {
            a[n] = b[n] = sel->items[i];
        }
    }
    BUF_803467CC->nC = n;
    for (j = 0; j < extra->count && n < 0x20; j++, n++) {
        a[n] = extra->items[j];
    }
    BUF_803467CC->n4 = n;
}

void TWindowDD__sub_8034694C(WordSelectMessage *src, s32 id, char *verb, char *phrase, char *window_dd, s32 *pos) {
    s32 n;
    s32 len;
    s32 i;

    len = strlen(phrase);
    strlen(verb);
    n = len;
    for (i = 1; i < len; i++) {
        if (phrase[i] == ' ') {
            n = i;
            break;
        }
    }
    if (can_append_chars__9TWindowDDFlPl(n, pos) != 0) {
        strncpy(window_dd + *pos, phrase, n);
        window_dd[*pos] = fn_80228C54(window_dd[*pos]);
        *pos += n;
        show_message_by_count__9TWindowDDFll(window_dd, pos);
        TWindowDD__sub_803474CC(src, id, verb, window_dd, pos);
        len -= n;
        if (len > 0 && can_append_chars__9TWindowDDFlPl(len, pos) != 0) {
            strncpy(window_dd + *pos, phrase + n, len);
            *pos += len;
        }
    }
}
}
