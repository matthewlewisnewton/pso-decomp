#include "pso/misc/QuestDownloadInternal.h"

// Native object layout: code, generated switch tables and owned storage.
// The boundaries preserve the original eight-byte table alignment.
extern "C" {

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

s32 TQuestVmDownLoadServer::calc_item_cost_bonus(u8 kind, u8 v, u8 w, s32 base, s32 add) {
    s32 r = 0;
    switch (kind) {
    case 0:
        if ((v >= 0x14 && v <= 0x19) || v == 0x32) {
            r = 0xF;
        }
        break;
    case 1:
        if (v == 0x1A) {
            r = 0x14;
        }
        break;
    case 2:
        if ((u8)(v - 0x1B) <= 1) {
            r = 0xF;
        }
        break;
    case 3:
        if (v == 0x1F || v == 0x38) {
            r = 0x14;
        }
        break;
    case 4:
        if (v == 0x16) {
            r = 0x14;
        }
        break;
    case 5:
        if (w == 0xFF) {
            if (v >= 1 && v <= 0xD) {
                r = 0xF;
            }
        } else if ((v >= 0x80 && v <= 0x8B && w == 4) || (v == 0xD && w == 0)) {
            r = 0xF;
        }
        break;
    case 6:
        if (v >= 0x14 && v <= 0x19) {
            r = 0xF;
        } else if (v == 0x1F || v == 0x38) {
            r = 0x14;
        }
        break;
    case 7:
        if (v == 0x1D) {
            r = 0xF;
        }
        break;
    case 8:
        if ((v >= 0x14 && v <= 0x19) || (v >= 1 && v <= 0xD)) {
            r = 0x14;
        }
        break;
    }
    if (r == 0) {
        return base;
    }
    return base + r + add;
}

s32 calc_item_entry_cost__22TQuestVmDownLoadServerFUcUcl(QuestDownloadEntryPrefix *a, u8 k, u8 v, s32 base) {
    s32 lvl = 0;
    QuestDownloadItemNode *s = a->src;

    if (s != NULL && ((s->a >= 0x14 && s->a <= 0x19) || s->a == 0x32)) {
        lvl = 1;
        if (s->off + 1 == a->off) {
            lvl = 2;
        }
    }
    if (k == 0xC7) {
        if (InRange_803ED26C(v)) {
            return base + 0x1E;
        }
        return base + 0x19;
    }
    if (k == 0xC8) {
        if (v == 0) {
            return base;
        }
        if (lvl == 2) {
            return base + 0x14;
        }
        return base + 5;
    }
    if (k == 0xC1 || k == 0xE1) {
        if (lvl == 2) {
            base += 5;
        }
        return base;
    }
    if ((u8)(k - 0xC4) <= 1 || (k >= 0xCE && k <= 0xD1)) {
        if ((v >= 1 && v <= 0xD) || (v >= 0x16 && v <= 0x17)) {
            return base + 5;
        }
        return base;
    }
    if (k == 0xC2) {
        if (v == 0) {
            return base;
        }
        if (lvl == 2) {
            base += 3;
        }
        return base;
    }
    if (k >= 0xFC && k <= 0xFD && v >= 1 && v <= 0x17) {
        return base + 0x12;
    }
    if ((k == 0xFA || k == 0xFE) && v >= 0x14 && v <= 0x18) {
        return base + 0x12;
    }
    return base;
}

#pragma pop

s32 TQuestVmDownLoadServer::calc_pair_cost_bonus(u8 arg0, u8 arg1, s32 arg2) {
    if (arg0 >= 0x14 && arg0 <= 0x18) {
        if (arg1 >= 0x14 && arg1 <= 0x18) {
            return arg2 + 3;
        }
        return arg2;
    }
    if (arg0 == 0x1F && arg1 == 0x1F) {
        return arg2 + 0xF;
    }
    if (arg0 == 0x21 || arg0 == 0x26 || arg0 == 0x27) {
        return arg2 + 0x14;
    }
    if (arg0 == 0x20 || arg0 == 0x22) {
        return arg2 + 0xF;
    }
    if (arg0 == 0x1B && arg1 == 0x1C) {
        return arg2 + 0x14;
    }
    if (arg0 == 0x1A && arg1 == 0x1A) {
        return arg2 + 5;
    }
    return arg2;
}

s32 TQuestVmDownLoadServer::calc_item_entry_cost_extra(u8 arg0, u8 arg1, u8 arg2, s32 arg3) {
    if ((arg0 == 0xD) && (arg1 == 0)) {
        if ((arg2 >= 1U) && (arg2 <= 0x17U)) {
            return arg3 + 3;
        }
    } else if ((arg1 >= 4U) && (arg1 <= 6U) && (arg2 >= 1U) && (arg2 <= 0x17U)) {
        if ((arg0 == 0x8D) || ((arg0 == 0x8E) && (arg1 == 6))) {
            return arg3 + 0xA;
        }
        if (arg0 <= 0x8CU) {
            return arg3 + 3;
        }
    } else if ((arg1 == 8) && (arg2 >= 0x14U) && (arg2 <= 0x18U)) {
        if (((arg0 >= 0x80U) && (arg0 <= 0x8EU)) || (arg0 == 0x92) || (arg0 == 0x94) || (arg0 == 0xA0) || (arg0 == 0xA2) || ((u8)(arg0 - 0xAE) <= 1U) || (arg0 == 0xB1) || (arg0 == 1) || ((arg0 >= 0xAU) && (arg0 <= 0xCU))) {
            return arg3 + 0xF;
        }
        return arg3 + 3;
    }
    return arg3;
}

s32 calc_entry_cost__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryPrefix *a, QuestDownloadEntryPrefix *b) {
    QuestDownloadItemNode *s2;
    u8 k;
    u8 bk;
    s32 extra;
    QuestDownloadItemNode *s;
    u8 q;
    u8 p;

    extra = 0;
    p = 0;
    q = 0;
    if ((k = a->a) >= 0x2D && k <= 0x38) {
        p = a->b;
    } else {
        q = a->b;
    }
    if (b == NULL) {
        bk = 0;
    } else if ((s = b->src) == NULL) {
        bk = 0;
    } else {
        if ((bk = s->a) == 0x28) {
            return 0;
        }
        if (bk == 0x29 || (bk == 0x19 && s->off > 0) || (bk == 0x1F && (u32)s->x4 == 0xFFFFFFFFU)) {
            extra = 0x14;
        }
    }
    if ((s2 = a->src) != NULL) {
        if (s2->a == 0x19 && s2->off == 0) {
            extra += 10;
        } else if (s2->a <= 0x19 || s2->a >= 0x1F) {
            extra += 1;
        }
    }
    if (q != 0 || k == 0xD) {
        return TQuestVmDownLoadServer::calc_item_entry_cost_extra(k, q, bk, extra);
    }
    if (k == 0x2D) {
        return TQuestVmDownLoadServer::calc_item_cost_bonus(p, bk, 0xFF, extra, 0);
    }
    if (bk >= 0x32 && bk <= 0x38) {
        if (b->src != NULL) {
            p = b->src->b;
        } else {
            p = 0;
        }
        return TQuestVmDownLoadServer::calc_item_cost_bonus(p, k, q, extra, 2);
    }
    if (k >= 0x14 && k < 0xC0) {
        return TQuestVmDownLoadServer::calc_pair_cost_bonus(k, bk, extra);
    }
    if (k >= 0xC0) {
        return calc_item_entry_cost__22TQuestVmDownLoadServerFUcUcl(a, k, bk, extra);
    }
    return extra;
}

#pragma push
#pragma opt_common_subs off

void TQuestVmDownLoadServer::reset_slot_chain_timers(s32 arg0) {
    QuestDownloadEntryNode *n;
    QuestDownloadItemNode *l;
    QuestDownloadSlot *t = &quest_download_slot_chain_table[arg0];
    for (n = t->entryHead; n != NULL; n = n->next) {
        n->xa = 0;
        l = n->prefix.src;
        if (l != NULL && l->a == 0x19 && l->off == 0) {
            n->xa = 10;
        }
    }
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

s32 TQuestVmDownLoadServer__sub_803ED84C(QuestDownloadEntryNode *entry, s32 index, s32 limit) {
    QuestDownloadEntryNode *next;
    s32 length;
    u32 best;
    u16 score;
    if (entry_source_is_special(entry)) {
        entry->x8 = 0;
        return 0;
    }
    length = entry->prefix.off;
    if (entry->prefix.a == 0xFF || index + length >= limit) {
        best = entry_follow_score(entry, NULL);
    } else {
        if ((next = quest_download_slot_chain_table[index + length].entryHead) == NULL && lbl_805D7888 >= 3) {
            return -1;
        }
        best = 0;
        for (; next != NULL; next = next->next) {
            score = entry_follow_score(entry, next);
            if (score > (u16)best) {
                best = score;
            }
        }
    }
    entry->x8 = best;
    return 0;
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_common_subs off

s32 TQuestVmDownLoadServer::select_best_slot_entry(s32 idx, s32 max, s32 want) {
    QuestDownloadSlot *slot = &quest_download_slot_chain_table[idx];
    QuestDownloadEntryNode *e;
    QuestDownloadEntryNode *best;
    QuestDownloadEntryNode *q;
    for (e = slot->entryHead; e != NULL; e = e->next) {
        if (want < 0 || e->prefix.off == want) {
            if (TQuestVmDownLoadServer__sub_803ED84C(e, idx, max) == -1) {
                return -1;
            }
        }
    }
    if (slot == NULL || slot->entryHead == NULL) {
        return -1;
    }
    best = slot->entryHead;
    for (q = best->next; q != NULL; q = q->next) {
        if (q->x8 > best->x8) {
            best = q;
        }
    }
    Relax_803ED9AC(best, idx, max);
    return best->prefix.off;
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803EDB20(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0x20;
}

s32 TQuestVmDownLoadServer__sub_803EDB3C(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0x40;
}

s32 TQuestVmDownLoadServer__sub_803EDB58(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0x80;
}

s32 TQuestVmDownLoadServer__sub_803EDB74(u8 arg0) {
    return lbl_8047F8B8[arg0] & 0xC0;
}

s32 TQuestVmDownLoadServer::sum_entry_sizes(s32 start, s32 n) {
    QuestDownloadInputEntry *e = &quest_download_entry_table[start];
    s32 sum = 0;
    s32 i;
    for (i = n; i > 0; i--) {
        sum += e->len;
        e++;
    }
    return sum;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
#pragma opt_propagation off

s32 TQuestVmDownLoadServer__sub_803EDC20(u32 input_address) {
    QuestDownloadInputEntry *entry;
    u8 *codes;
    s32 count;
    u8 *input;
    DownloadDecoderState state;
    s32 encoded;
    u16 ch;
    input = reinterpret_cast<u8 *>(input_address);
    codes = lbl_805D78BC;
    count = lbl_805D78C0;
    encoded = count_encoded_download_input(entry);
    for (; *input != 0; input++) {
        if (state.lead != 0) {
            ch = TQuestVmDownLoadServer__sub_803EC69C((state.lead << 8) | *input);
            if (ch != 0) {
                if (count >= 0x24 || encoded >= 0x4E) return -1;
                entry->ch = ch;
                entry->len = 2;
                entry++;
                *codes++ = TQuestVmDownLoadServer__sub_803EC8D8(ch);
                count++;
                encoded += 2;
            }
            state.lead = 0;
        } else if (TQuestVmDownLoadServer::is_sjis_lead_byte(*input)) {
            state.lead = *input;
        } else if ((*input >= 0x20 && *input < 0x7F) || (*input >= 0xA0 && *input < 0xE0)) {
            if (count >= 0x24 || encoded >= 0x4F) return -1;
            entry->ch = *input;
            state.lead = 0;
            entry->len = 1;
            encoded++;
            *codes++ = state.lead;
            entry++;
            count++;
        }
    }
    lbl_805D78C8 = entry;
    lbl_805D78C4 = entry;
    lbl_805D78BC = codes;
    lbl_805D78B8 = codes;
    lbl_805D78C0 = count;
    return count;
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

u8 *TQuestVmDownLoadServer__sub_803EDDA4(u16 *start, u16 *end) {
    s32 len = end - start;
    s32 index;
    u8 **entry;
    u8 *p;
    u8 *limit;
    s32 ch;
    if (len == 0) {
        return lbl_8047F9B8 + 1;
    }
    if ((u32)(len - 1) <= 1) {
        s32 first = (u8)start[0];
        if (first >= 'a' && first <= 'z') {
            index = first - 'a';
        } else if (first >= 'A' && first <= 'Z') {
            index = first - 'A';
        } else {
            return NULL;
        }
        entry = lbl_8047FBD4 + index;
        p = *entry;
        if (len == 1) {
            return p + 1;
        }
        do {
            limit = *++entry;
        } while (limit == NULL);
        ch = Upper_803EDDA4(start[1] & 0xff);
        for (p += 11; p < limit; p += 11) {
            if (*p == ch) {
                return p + 1;
            }
        }
    }
    return NULL;
}

#pragma pop

u8 *TQuestVmDownLoadServer::find_keyword_entry(u16 *start, u16 *end) {
    u8 c;
    u8 *p;
    u16 *s;
    s32 rem;
    s32 len;
    s32 n;
    len = end - start;
    p = quest_download_keyword_table;
    while (*p != 0) {
        n = *p++;
        if (len == n) {
            s = start;
            for (rem = len; rem > 0;) {
                c = *s++;
                if (c >= 0x61U && c <= 0x7AU) {
                    c -= 0x20;
                }
                if (*p != c) {
                    break;
                }
                rem--;
                p++;
            }
            if (rem == 0) {
                return p;
            }
            p += rem;
        } else {
            p += n;
        }
        while (*p++ != 0) {
        }
    }
    return NULL;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

s32 TQuestVmDownLoadServer__sub_803EDF64(const u16 *input, s32 count,
                                      u16 *output, s32 *outputCount) {
    u8 byte;
    u8 first;
    u16 next;
    u16 state;
    const u16 *cursor;
    u8 category;
    s32 consumed;
    u8 *mapping;
    category = lbl_8047F8B8[(u8)*input] & 0xF;
    *outputCount = 1;
    if (category <= 9) {
        if (category <= 5) {
            mapping = lbl_8047F9B8 + 1;
            cursor = input;
            consumed = 1;
            goto fallback_mapping;
        }
        if (category <= 8 || lbl_805D78E4 == 0) {
            output[0] = TQuestVmDownLoadServer__sub_803E721C(*input);
        } else {
            output[0] = TQuestVmDownLoadServer::map_key_to_code(*input);
        }
        return 1;
    }
    {
        state = 0;
        if (category <= 12) {
            if (category == 12) {
                output[0] = TQuestVmDownLoadServer__sub_803E719C(0x73, *input);
                state = 1;
            } else {
                output[0] = TQuestVmDownLoadServer__sub_803E721C(*input);
                if (category == 10) state = 2;
                else state = 3;
            }
        }
        if (count == 1) {
            return state != 0 ? -1 : 0;
        }
        cursor = input + 1;
        {
            u16 raw = *cursor;
            byte = (u8)raw;
            first = (u8)*input;
            if (first == (next = (u8)raw)) {
                if (category == 12) return 2;
                if (category == 13) {
                    output[0] = TQuestVmDownLoadServer__sub_803E719C(0x43, *cursor);
                    return 1;
                }
            }
            if ((first == 'x' || first == 'X') && ((cursor = input + 1, (u8)(next = byte)) == 0x6EU || (u8)next == 0x4EU)) {
                output[0] = TQuestVmDownLoadServer__sub_803E719C(0x73, *input);
                return 2;
            }
            if (state == 1 && (u8)next == 0x27U) return 2;
            category = lbl_8047F8B8[(u8)next] & 0xF;
        }
        if (category == 7 && state == 3) {
            output[0] += 2;
            return 2;
        }
        if (category == 6 && state >= 2) {
            output[0]++;
            if ((s32)(u8)*input == 0xB3) {
                output[0] = TQuestVmDownLoadServer__sub_803E719C(0x74, *cursor);
            }
            return 2;
        }
        if (state >= 2 || (category > 5 && category <= 14 && state == 1)) return 1;
        consumed = 2;
        for (;;) {
            if (category <= 5) {
                mapping = TQuestVmDownLoadServer::find_keyword_entry((u16 *)input, (u16 *)cursor + 1);
                if (mapping != NULL) goto emit_mapping;
                mapping = TQuestVmDownLoadServer__sub_803EDDA4((u16 *)input, (u16 *)cursor);
                if (mapping == NULL) return -2;
fallback_mapping:
                // The pinned classifier has classes 1..13/15, never zero.
                mapping += (category - 1) * 2;
emit_mapping:
                *output++ = TQuestVmDownLoadServer__sub_803E719C(*mapping++, *cursor);
                if (*mapping != 0) {
                    *output = TQuestVmDownLoadServer__sub_803E719C(*mapping, *cursor);
                    *outputCount = 2;
                }
                return consumed;
            }
            if (consumed++ >= count) break;
            cursor++;
            category = lbl_8047F8B8[(u8)*cursor] & 0xF;
            if ((category >= 6 && category <= 12) || consumed > 4) return -2;
        }
    }

    return 0;
}

#pragma pop

void TQuestVmDownLoadServer__sub_803EE2E4(void) {
    lbl_8058DC98[0] = 0;
}

#pragma push
#pragma opt_lifetimes off
#pragma opt_propagation off

void TQuestVmDownLoadServer__sub_803EE2F4(s32 start, s32 end) {
    s32 emittedLength;
    s32 length;
    QuestDownloadTextNode *text;
    QuestDownloadSlot *slot;
    while (start < end && (length = TQuestVmDownLoadServer__sub_803E9F54(start)) != 0) {
        slot = &quest_download_slot_chain_table[start];
        if (start == lbl_805D78F0 && (lbl_805D78E8 == 1 || lbl_805D7834 >= 3)) {
            text = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
        } else {
            text = advance_nodes__22TQuestVmDownLoadServerFPvi(slot->textHead, 0);
        }
        if (lbl_805D7848 != 3 && lbl_805D7834 <= 2) {
        emit_entry:
            TQuestVmDownLoadServer__sub_803EE580(start, length, text, slot->entryHead);
            start += length;
            continue;
        }
        if (slot->x16 != 0 && slot->x16 != slot->x15) {
            char *copyName = (char *)lbl_8058DC98;
            u8 *encoded = lbl_8058DC48;
            s32 n = length;
            strncpy(copyName, (char *)lbl_805A0470.bytes + start, n);
            lbl_8058DC98[length] = 0;
            emittedLength = length;
            if (length != strlen(copyName)) {
                ((char *)lbl_8058DC98)[0] = 0;
            } else {
                s32 count = TQuestVmDownLoadServer__sub_803EB420(start, n, text, lbl_805A0340);
                TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, (u8 *)encoded, count);
            }
            TQuestVmDownLoadServer__sub_803EE580(start, emittedLength, text, slot->entryHead);
        } else {
            if ((u8)((char *)lbl_8058DC98)[0] == 0) goto emit_entry;
            char *appendName = (char *)lbl_8058DC98 + strlen((char *)lbl_8058DC98);
            u8 *appendEncoded = lbl_8058DC48 + strlen((char *)lbl_8058DC48);
            s32 n = text->payload.head.length;
            strncpy(appendName, (char *)lbl_805A0470.bytes + start, n);
            appendName[n] = 0;
            if (n != strlen(appendName)) {
                ((char *)lbl_8058DC98)[0] = 0;
            } else {
                s32 count = TQuestVmDownLoadServer__sub_803EB420(start, n, text, lbl_805A0340);
                TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, appendEncoded, count);
            }
            if ((u8)((char *)lbl_8058DC98)[0] != 0) {
                Req_803EEF2C request;
                request.name = (char *)lbl_8058DC98;
                request.len = (u16)strlen((char *)lbl_8058DC98);
                request.pad6 = 0;
                QuestDownloadItemNode *item;
                if (text == NULL || (item = (QuestDownloadItemNode *)text->payload.head.source) == NULL) {
                    request.x7 = 0x28;
                    request.x8 = 0;
                } else {
                    request.x7 = item->a;
                    request.x8 = item->b;
                }
                request.text = lbl_8058DC48;
                TQuestVmDownLoadServer__sub_803EEF2C(&request);
            }
            ((char *)lbl_8058DC98)[0] = 0;
        }
        start += length;
    }
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

void TQuestVmDownLoadServer__sub_803EE580(s32 start, s32 length, QuestDownloadTextNode *text, QuestDownloadEntryNode *entries) {
    s32 zero = 0;
    QuestDownloadItemNode *selected;
    Req_803EEF2C *completed;
    QuestDownloadRequestView request(&lbl_805A0698);
    s32 *ids;
    s32 count;
    if (text->payload.head.id == -1) {
        selected = NULL;
    } else {
        if ((selected = (QuestDownloadItemNode *)text->payload.head.source) == NULL) return;
    }
    new (quest_download_text_buffer, quest_download_scratch_storage) QuestDownloadScratchIds;
    ids = reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values;
    if (entries == NULL || entries == QUEST_DOWNLOAD_ENTRY_LIST_FAILED) {
        if (selected != NULL) *ids++ = selected->x4;
    } else {
        u32 last = -1;
        do {
            QuestDownloadItemNode *item = entries->prefix.src;
            if (item != NULL) {
                u32 id;
                if ((id = item->x4) != -1 && id != last) {
                    *ids++ = id;
                    last = id;
                }
            }
            entries = entries->next;
        } while (entries != NULL);
    }
    if (selected == NULL) {
        strncpy((char *)lbl_8058DD38, (char *)lbl_805A0470.bytes + start, length);
        lbl_8058DD38[length] = zero;
        count = TQuestVmDownLoadServer__sub_803EB420(start, length, text, lbl_805A0340);
        TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, lbl_8058DCE8, count);
        request.storage->request.name = (char *)lbl_8058DD38;
        request.storage->request.len = length;
        request.storage->request.pad6 = zero;
        request.storage->request.x7 = 0x19;
        completed = &request.storage->request;
        completed->x8 = zero;
        completed->text = lbl_8058DCE8;
        TQuestVmDownLoadServer__sub_803EEDC0(completed, reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values, ids - reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values);
    } else {
        TQuestVmDownLoadServer__sub_803EF958((u32)selected->x4, text->payload.head.id,
            reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values, ids - reinterpret_cast<QuestDownloadScratchIds *>(quest_download_text_buffer)->values);
    }
}

#pragma pop

u16 *TQuestVmDownLoadServer__sub_803EE718(s32 i, s32 len) {
    u16 *out;
    s32 n;
    s32 end;
    s32 r;
    QuestDownloadTextNode *node;
    out = lbl_805A0340;
    end = i + len;
    while (i < end && (n = TQuestVmDownLoadServer__sub_803E9F54(i)) != 0) {
        if (i == lbl_805D78F0) {
            if (lbl_805D78E8 == 1 || lbl_805D7834 >= 3) {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
            } else {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(quest_download_slot_chain_table[i].textHead, 0);
            }
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, (QuestDownloadTextNode *)node, out);
        } else {
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, (QuestDownloadTextNode *)quest_download_slot_chain_table[i].textHead, out);
        }
        out += r;
        i += n;
    }
    TQuestVmDownLoadServer__sub_803EC71C((u16 *)lbl_805A0340, (u8 *)lbl_805A02A8, (s32)(out - lbl_805A0340));
    return lbl_805A02A8;
}

u8 *TQuestVmDownLoadServer__sub_803EE828(void) {
    TQuestVmDownLoadServer__sub_803EC71C((u16 *)(((u8 *)&lbl_805A0340)), (u8 *)(((u8 *)&lbl_805A02A8)), (s32)(TQuestVmDownLoadServer__sub_803EE934()));
    return ((u8 *)&lbl_805A02A8);
}

#pragma push
#pragma opt_propagation off

void TQuestVmDownLoadServer__sub_803EE870(s32 index, s32 mode) {
    QuestDownloadSlot *base = quest_download_slot_chain_table;
    u8 *member = reinterpret_cast<u8 *>(base + index);
    // This character address stays inside the live slot and names its real
    // pointer member (offset/alignment checked in QuestDownloadRecords.h).
    member += offsetof(QuestDownloadSlot, textHead);
    QuestDownloadTextNode **head = reinterpret_cast<QuestDownloadTextNode **>(member);
    QuestDownloadTextNode *node;
    QuestDownloadTextNode *keep;
    QuestDownloadTextNode *next;
    if ((node = *head) == NULL) return;
    if (mode == 1 && (lbl_805D78E8 == 1 || lbl_805D7834 >= 3)) {
        keep = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
        while (node != NULL) {
            if (node == keep) break;
            next = TQuestVmDownLoadServer__sub_803EB878(node);
            push_download_entry__22TQuestVmDownLoadServerFPl(node);
            node = next;
        }
        *head = node;
    }
    free_node_list__22TQuestVmDownLoadServerFv(detach_node_chain__22TQuestVmDownLoadServerFPv(node));
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803EE934(void) {
    s32 r;
    QuestDownloadTextNode *node;
    u16 *out;
    s32 total;
    s32 i;
    s32 n;
    out = lbl_805A0340;
    i = 0;
    total = 0;
    while ((n = TQuestVmDownLoadServer__sub_803E9F54(i)) != 0) {
        if (i == lbl_805D78F0) {
            if (lbl_805D78E8 == 1 || lbl_805D7834 >= 3) {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(lbl_805D78A0, lbl_805D7898);
            } else {
                node = advance_nodes__22TQuestVmDownLoadServerFPvi(quest_download_slot_chain_table[i].textHead, 0);
            }
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, (QuestDownloadTextNode *)node, out);
            lbl_805D78EC = n;
            TQuestVmDownLoadServer__sub_803ECA1C(out, r, 7);
        } else {
            r = TQuestVmDownLoadServer__sub_803EB420(i, n, quest_download_slot_chain_table[i].textHead, out);
            TQuestVmDownLoadServer__sub_803ECA1C(out, r, 6);
        }
        out += r;
        i += n;
        total += r;
    }
    return total;
}

s32 TQuestVmDownLoadServer__sub_803EEA48(s32 arg0, s32 arg1, void *arg2, s32 *arg3) {
    s32 i;
    void *r;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    *arg3 = 0;
    r = format_number_text__22TQuestVmDownLoadServerFiiPvi(arg0, arg1, arg2, lbl_805D78FC);
    if (r != 0) {
        arg2 = r;
        (*arg3)++;
    }
    for (i = 0; i < 4; i++) {
        if (i != lbl_805D78FC) {
            r = format_number_text__22TQuestVmDownLoadServerFiiPvi(arg0, arg1, arg2, i);
            if (r != 0) {
                arg2 = r;
                (*arg3)++;
            }
        }
    }
    return 1;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

void *format_number_text__22TQuestVmDownLoadServerFiiPvi(s32 arg0, s32 arg1, void *arg2, s32 mode) {
    u8 *s = (u8 *)arg0;
    Out_803EEB10 *o = (Out_803EEB10 *)arg2;
    Tbl_803EEB10 *t = &quest_download_number_text_table;
    s32 u;
    u8 **mp;
    u8 **up;
    u8 *p;
    u8 *mark;
    s32 i;
    s32 pos;
    s32 d;
    s32 rem;
    s32 set;

    if (mode >= 2 && ((s16)arg1) > 0xD) {
        return NULL;
    }
    o->mode = mode;
    o->x2 = 0;
    o->x4 = 0;
    p = o->text;
    mp = (u8 **)((u8 *)t->sets + mode * 4);
    mark = p;
    up = &t->units_text;
    for (i = 0; i < ((s16)arg1); i++, s++) {
        d = *s - '0';
        if (mode < 2) {
            *p++ = (*mp)[d * 2];
            *p++ = (*mp)[d * 2 + 1];
            continue;
        }
        rem = ((s16)arg1) - i - 1;
        pos = rem % 4;
        if (d != 0 && !(mode == 2 && d == 1 && (u32)(pos - 1) <= 1)) {
            set = IsSmall_803EEB10(d) ? mode - 1 : 1;
            *p++ = (*(u8 **)((u8 *)t->sets + set * 4))[d * 2];
            *p++ = (*(u8 **)((u8 *)t->sets + set * 4))[d * 2 + 1];
        }
        if (rem == 0) {
            continue;
        }
        if (pos == 0 && mark == p) {
            continue;
        }
        if (pos != 0 && d == 0) {
            continue;
        }
        if (pos == 0) {
            u = rem / 4 + 6;
        } else if (pos == 1) {
            if (mode == 2) {
                u = 4;
            } else {
                u = 0;
            }
        } else {
            u = pos + 3;
        }
        *p++ = (*up)[u * 2];
        *p++ = (*up)[u * 2 + 1];
        if (pos == 0) {
            mark = p;
        }
    }
    if (p == o->text) {
        return NULL;
    }
    *p = 0;
    return p + 1;
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
#pragma opt_common_subs off

s32 TQuestVmDownLoadServer__sub_803EED0C(s32 arg0, s32 arg1, s32 arg2) {
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (Call_803EED0C(arg0, arg1, arg2, lbl_805D78FC) == 0) {
        Call_803EED0C(arg0, arg1, arg2, 0);
    }
    return 1;
}

#pragma pop

s32 TQuestVmDownLoadServer::get_download_state() {
    return lbl_805D7900;
}

s32 TQuestVmDownLoadServer__sub_803EED9C(u32 arg0) {
    TQuestVmDownLoadServer::release_ref_slot(arg0);
    return 3;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

s32 TQuestVmDownLoadServer__sub_803EEDC0(Req_803EEF2C *req, s32 *ids, s32 n) {
    char buf[0x50];
    s32 v;
    if (lbl_805D7900 == 0) {
        return 3;
    }
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, req->name, req->len);
    buf[req->len] = 0;
    if (is_digit_string((u8 *)buf)) {
        req->x7 = 0x1F;
    }
    v = ((TQuestVmDownLoadServer *)ids)->get_max_size_of_indices(n) + 1;
    if (v == 0xFF) {
        release_index_entries(ids, n);
        v = 1;
    }
    TQuestVmDownLoadServer__sub_803E8DA0(buf, req, v);
    TQuestVmDownLoadServer::set_slot_values_for_indices(ids, n, v);
    return 3;
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803EEF2C(Req_803EEF2C *arg0) {
    char buf[0x50];
    if (lbl_805D7900 == 0) {
        return 3;
    }
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, arg0->name, arg0->len);
    if (arg0->x7 == 0x28 || arg0->x7 == 0x29) {
        arg0->x7 = 0x27;
    }
    buf[arg0->len] = 0;
    TQuestVmDownLoadServer__sub_803E8DA0(buf, arg0, 1);
    return 3;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

s32 TQuestVmDownLoadServer__sub_803EEFC8(u8 *rec, Req_803EEF2C *msg) {
    s32 len;
    s32 size;
    u8 *data;
    u8 *end;
    u8 *start;
    u8 *text;
    s32 d;
    s32 n;
    u8 buf[0x80];
    TQuestVmDownLoadServer::copy_sjis_string(msg->text, buf);
    len = TQuestVmDownLoadServer::calc_sjis_string_width(msg->text);
    buf[len] = 0;
    data = rec;
    size = (u16)(rec[0] + (rec[1] << 8));
    end = rec + size;
    rec = rec + 3 + rec[2];
    while ((start = rec) < end) {
        rec += 2;
        if (*rec <= 0xB) {
            rec++;
        }
        text = rec;
        rec = skip_entry_text(rec, end);
        n = rec - text;
        if (start[0] == msg->x7 && n == len && strncmp((char *)text, (char *)buf, n) == 0) {
            break;
        }
    }
    d = rec - start;
    if (d > 0) {
        if (start == data + 3 + data[2] && rec == end) {
            return -1;
        }
        shift_bytes(rec, end, -d);
        data[0] = (size - d) % 256;
        data[1] = (size - d) / 256;
    }
    return d;
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)

s32 TQuestVmDownLoadServer__sub_803EF208(Req_803EEF2C *request) {
    s32 delta;
    char name[0x50];
    u8 *end;
    u8 *record;
    u8 len;
    s32 comparison;
    s32 size;
    s32 removed;
    s32 missing = 1;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (lbl_805D78F8 == 0x8000) {
        return -6;
    }
    strncpy(name, request->name, request->len);
    name[request->len] = 0;
    record = get_cached_page__22TQuestVmDownLoadServerFi(
        find_name_index__22TQuestVmDownLoadServerFv(name));
    for (end = record; (size = (u16)(end[0] + (end[1] << 8))) != 0; end += size) {
    }
    for (; record < end;
         record += (u16)(record[0] + (record[1] << 8))) {
        len = record[2];
        comparison = strncmp((const char *)(record + 3), name, (s16)len);
        if (comparison == 0) {
            if ((s16)len == request->len) {
                missing = 0;
                break;
            }
        } else if (comparison > 0) {
            break;
        }
    }
    if (missing) {
        return 0;
    }
    removed = TQuestVmDownLoadServer__sub_803EEFC8(record, request);
    if (removed == 0) {
        return 0;
    }
    if (removed == -1) {
        size = (u16)(record[0] + (record[1] << 8));
        delta = -size;
        shift_removed_record_tail(record + size, end + 2, delta);
    } else {
        size = (u16)(record[0] + (record[1] << 8));
        shift_compacted_record_tail(record + size + removed, end + 2, -removed);
    }
    TQuestVmDownLoadServer__sub_803E79AC();
    TQuestVmDownLoadServer::set_active();
    return 3;
}

s32 TQuestVmDownLoadServer__sub_803EF538(Msg_803E9190 *msg) {
    u8 *end;
    u8 *page;
    u8 *p;
    s32 is_new = 1;
    u8 n;
    s32 c;
    s32 len;
    s32 size;
    char buf[0x50];
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (lbl_805D78F8 == 0x8000) {
        return -6;
    }
    strncpy(buf, msg->name, msg->len);
    buf[msg->len] = 0;
    page = get_cached_page__22TQuestVmDownLoadServerFi(find_name_index__22TQuestVmDownLoadServerFv(buf));
    for (end = page; (size = (u16)(end[0] + (end[1] << 8))) != 0; end += size) {
    }
    for (p = page; p < end; p += (u16)(p[0] + (p[1] << 8))) {
        n = p[2];
        c = strncmp((const char *)(p + 3), buf, (s16)n);
        if (c == 0) {
            if ((s16)n == msg->len) {
                is_new = 0;
                break;
            }
        } else if (c > 0) {
            break;
        }
    }
    len = is_new ? ((TQuestVmDownLoadServer *)msg)->calc_message_length() : ((TQuestVmDownLoadServer *)msg)->calc_text_length();
    if (end > page + 0x3FE - len) {
        return -5;
    }
    if (is_new) {
        shift_tail_bytes(p, end + 2, len);
        build_message_packet__22TQuestVmDownLoadServerFPviPvUc(p, len, msg, 0);
        if (msg->len <= 2) {
            TQuestVmDownLoadServer__sub_803E7F9C((u8 *)buf, msg->len);
        }
    } else {
        shift_tail_bytes(p + (u16)(p[0] + (p[1] << 8)), end + 2, len);
        append_message_text__22TQuestVmDownLoadServerFPviPvUc(p, len, msg, max_entry_index(p) + 1);
    }
    TQuestVmDownLoadServer__sub_803E79AC();
    TQuestVmDownLoadServer::set_active();
    return 3;
}

#pragma pop

void TQuestVmDownLoadServer__sub_803EF8E0(u8 *p) {
    u8 *end = p + (u16)(p[0] + (p[1] << 8));
    p = p + 3 + p[2];
    while (p < end) {
        p[1] = 0;
        p += 2;
        if (*p <= 0xB) {
            p++;
        }
        for (; p < end; p += 2) {
            if (*p <= 0x38) {
                break;
            }
        }
    }
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

s32 TQuestVmDownLoadServer__sub_803EF958(u32 id, u16 key, s32 *ids, s32 n) {
    s32 page;
    u8 *base;
    u8 *p;
    u16 off;
    if (lbl_805D7900 == 0) {
        return 3;
    }
    if (lbl_805D7904 == -1) {
        return -3;
    }
    if (id == 0xFFFFFFFF && key <= 3) {
        lbl_805D78FC = key;
        release_index_entries(ids, n);
        TQuestVmDownLoadServer::set_slot_values_for_indices(ids, n, 0);
        return 3;
    }
    {
        s32 a;
        s32 b;
        s32 v;
        page = TQuestVmDownLoadServer__sub_803E779C(id, &a, &b, &v);
        if (page == -1) {
            return 0;
        }
        off = key;
        if (key & 0x8000) {
            if (b == -1) {
                return 0;
            }
            base = TQuestVmDownLoadServer::get_buffer_ptr(b);
        } else {
            if (a == -1) {
                return 0;
            }
            base = get_cached_page__22TQuestVmDownLoadServerFi(page) + a;
        }
        v = ((TQuestVmDownLoadServer *)ids)->get_max_size_of_indices(n);
        p = base + (off & ~0x8000) + 1;
        if (*p != 0 && *p == v) {
            if (key & 0x8000) {
                TQuestVmDownLoadServer__sub_803E8924(b);
                TQuestVmDownLoadServer__sub_803E8918();
            }
            return 3;
        }
        if (++v == 0xFF) {
            release_index_entries(ids, n);
            v = 1;
        }
        *p = v;
        if (key & 0x8000) {
            TQuestVmDownLoadServer__sub_803E8924(b);
            TQuestVmDownLoadServer__sub_803E8918();
        } else {
            TQuestVmDownLoadServer::set_active();
        }
        TQuestVmDownLoadServer::set_slot_values_for_indices(ids, n, v);
        return 3;
    }
}

#pragma pop

u8 *TQuestVmDownLoadServer::find_insert_position(s32 key, s32 n, s32 len) {
    u8 *p = (u8 *)this;
    u8 *end = p + len;
    u8 *s;
    u8 *d;
    while (p < end) {
        if (*(u16 *)(p + 2) < key) {
            break;
        }
        p += 5;
        while (*p++ != 0) {
        }
        if ((u32)p & 1) {
            p++;
        }
    }
    if (p < end) {
        for (s = end - 1; s >= p; s--) {
            s[n] = *s;
        }
    }
    return p;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

void TQuestVmDownLoadServer__sub_803EFCB4(u8 *data, s32 key, s32 sub_key, s32 *cnt, s32 *total, u8 *buf, s32 flags) {
    u8 *p;
    u8 *end;
    u8 *rec;
    s32 size;
    u8 *text;
    Src_803EBD38 *out;
    s32 sub;
    s32 value;
    u8 unused[8];
    end = data + (u16)(data[0] + (data[1] << 8));
    p = data + 3 + data[2];
    while (p < end) {
        rec = p;
        value = p[1];
        p += 2;
        if (*p <= 0xB) {
            sub = *p;
            p++;
        } else {
            sub = 0;
        }
        if (key == rec[0] && sub_key == sub) {
            size = TQuestVmDownLoadServer::count_entries_until_terminator(p, end) + 6;
            if (size & 1) {
                size++;
            }
            out = (Src_803EBD38 *)((TQuestVmDownLoadServer *)buf)->find_insert_position(value, size, *total);
            out->x0 = flags | (rec - data);
            text = rec + 2;
            out->x2 = rec[1];
            out->x4 = 0;
            if (rec[2] <= 0xB) {
                text++;
            }
            TQuestVmDownLoadServer::unescape_copy_string(out->text, text, end);
            *total += size;
            (*cnt)++;
        }
        p = skip_entry_text(p, end);
    }
}

#pragma pop

s32 TQuestVmDownLoadServer::read_quest_chunk(u32 id, u8 a1, u8 a2, u8 *buf, s32 *out) {
    s32 a;
    s32 b;
    s32 cnt;
    s32 total;
    s32 r;
    s32 v;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    r = TQuestVmDownLoadServer__sub_803E779C(id, &a, &b, &cnt);
    if (r == -1) {
        return 0;
    }
    cnt = 0;
    total = 0;
    if (a != -1) {
        TQuestVmDownLoadServer__sub_803EFCB4(get_cached_page__22TQuestVmDownLoadServerFi(r) + a, a1, a2, &cnt, &total, buf, 0);
    }
    if (b != -1) {
        TQuestVmDownLoadServer__sub_803EFCB4(TQuestVmDownLoadServer::get_buffer_ptr(b), a1, a2, &cnt, &total, buf, 0x8000);
    }
    v = cnt;
    *out = v;
    if (v == 0) {
        return 0;
    }
    return 1;
}

void TQuestVmDownLoadServer__sub_803EFF20(u8 *data, s32 key, s32 sub_key, s32 *best, u8 *dst, s32 flags) {
    u8 *p;
    u8 *rec;
    u8 *end;
    u8 *found;
    u8 *text;
    Src_803EBD38 *out;
    u8 unused[8];
    s32 start_best;
    s32 sub;
    s32 value;
    start_best = *best;
    end = data + (u16)(data[0] + (data[1] << 8));
    p = data + 3 + data[2];
    while (p < end) {
        rec = p;
        value = p[1];
        p += 2;
        if (*p <= 0xB) {
            sub = *p;
            p++;
        } else {
            sub = 0;
        }
        if (key == rec[0] && sub_key == sub && value > *best) {
            found = rec;
            *best = value;
        }
        for (; p < end; p += 2) {
            if (*p <= 0x38) {
                break;
            }
        }
    }
    if (*best > start_best) {
        out = (Src_803EBD38 *)dst;
        out->x0 = flags | (found - data);
        text = found + 2;
        out->x2 = found[1];
        out->x4 = 0;
        if (found[2] <= 0xB) {
            text++;
        }
        TQuestVmDownLoadServer::unescape_copy_string(out->text, text, end);
    }
}

s32 TQuestVmDownLoadServer__sub_803F0048(s32 id, u8 a1, u8 a2, void *dst) {
    s32 a;
    s32 b;
    s32 c;
    s32 best;
    s32 page;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    page = TQuestVmDownLoadServer__sub_803E779C(id, &a, &b, &c);
    if (page == -1) {
        return 0;
    }
    best = -1;
    if (a != -1) {
        TQuestVmDownLoadServer__sub_803EFF20(get_cached_page__22TQuestVmDownLoadServerFi(page) + a, a1, a2, &best, (u8 *)dst, 0);
    }
    if (b != -1) {
        TQuestVmDownLoadServer__sub_803EFF20(TQuestVmDownLoadServer::get_buffer_ptr(b), a1, a2, &best, (u8 *)dst, 0x8000);
    }
    if (best == -1) {
        return 0;
    }
    return 1;
}

s32 find_symbol_entry__22TQuestVmDownLoadServerFPvsPv(const char *name, s16 len, Info_803F0138 *out) {
    u8 n;
    u8 *base;
    u8 *p;
    s32 id;
    s32 c;
    if (len <= 2 && ((TQuestVmDownLoadServer *)name)->is_char_allowed(len) != 0) {
        out->off = -1;
        return 0;
    }
    id = find_name_index__22TQuestVmDownLoadServerFv((const char *)name);
    {
        u8 *get_cached_page__22TQuestVmDownLoadServerFi(void);
        base = get_cached_page__22TQuestVmDownLoadServerFi();
    }
    p = base;
    while ((u16)(p[0] + (p[1] << 8)) != 0) {
        n = p[2];
        c = strncmp((const char *)(p + 3), name, (s16)n);
        if (c == 0) {
            if ((s16)n == len) {
                break;
            }
        } else if (c > 0) {
            out->off = -1;
            return 0;
        }
        p += (u16)(p[0] + (p[1] << 8));
    }
    if ((u16)(p[0] + (p[1] << 8)) == 0) {
        out->off = -1;
        return 0;
    }
    out->id = id;
    out->off = p - base;
    out->p = p;
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803F0268(const char *name, s16 len, Out_803F0268 *out) {
    char buf[0x50];
    Info_803F0138 i1;
    Out_803E8B1C i2;
    s32 max;
    s32 r1;
    s32 r2;
    u32 r;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, name, len);
    buf[len] = 0;
    r1 = find_symbol_entry__22TQuestVmDownLoadServerFPvsPv(buf, len, &i1);
    r2 = lookup_name_entry__22TQuestVmDownLoadServerFPvsPv((char *)(buf), len, &i2);
    if (r1 == 0 && r2 == 0) {
        return 0;
    }
    out->len = len;
    out->len2 = len;
    out->xa = 1;
    out->count = 0;
    max = 0;
    if (r1 == 1) {
        out->count = TQuestVmDownLoadServer__sub_803F03B4(i1.p, out->entries, 0, &max);
    }
    if (r2 == 1) {
        out->count = TQuestVmDownLoadServer__sub_803F03B4(i2.ent, out->entries, out->count, &max);
    }
    out->x4 = r = TQuestVmDownLoadServer::acquire_slot_entry(i1.id, i1.off, i2.id, max);
    if (r == 0xFFFFFFFF) {
        return 0;
    }
    return 1;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

s32 TQuestVmDownLoadServer__sub_803F03B4(u8 *cursor, Ent_803F03B4 *ents, s32 n, s32 *max) {
    Ent_803F03B4 *base = ents;
    u8 *end = cursor + (u16)(cursor[0] + (cursor[1] << 8));
    cursor = cursor + cursor[2] + 3;
    ents += n;
    while (cursor < end) {
        u8 keyb;
        ents->a = cursor[0];
        keyb = cursor[1];
        cursor += 2;
        ents->key = keyb;
        if ((u16)keyb > *max) {
            *max = ents->key;
        }
        if (*cursor <= 11) {
            ents->b = *cursor;
            cursor += 1;
        } else {
            ents->b = 0;
        }
        ents->c = 0;
        if (merge_duplicate_download_entry(base, ents) == 0) {
            n += 1;
            ents += 1;
            if (n >= 32) {
                break;
            }
        }
        cursor = skip_entry_text(cursor, end);
    }
    return n;
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803F0500(u8 *name, s16 len, Out_803E8C2C *out) {
    s16 blen;
    s16 cnt;
    s16 pre;
    s32 idx;
    s32 first;
    u8 *page;
    u8 *p;
    u8 *found;
    u8 n;
    first = 1;
    out->pre = 0;
    out->len = 0;
    idx = find_name_index__22TQuestVmDownLoadServerFv((const char *)name);
    if (((TQuestVmDownLoadServer *)idx)->has_name_mismatch(name) == 0) {
        return 2;
    }
    pre = 0;
    for (;;) {
        page = get_cached_page__22TQuestVmDownLoadServerFi(idx);
        p = page;
        cnt = TQuestVmDownLoadServer::count_matching_name_prefix(idx, name);
        blen = 0;
        for (; (u16)(p[0] + (p[1] << 8)) != 0; p += (u16)(p[0] + (p[1] << 8))) {
            s16 m;
            s32 r;
            u8 *e = p;
            n = e[2];
            m = TQuestVmDownLoadServer::match_prefix_length(e + 3, name, (s16)n);
            if (m >= pre) {
                pre = m + 1;
            }
            r = strncmp((const char *)(e + 3), (char *)name, (s16)n);
            if (r == 0) {
                if ((s16)n == len && first) {
                    return 2;
                }
                blen = n;
                found = p;
            } else if (r > 0) {
                if (strncmp((const char *)(e + 3), (char *)name, len) == 0 && first) {
                    return 2;
                }
                break;
            }
        }
        if (blen > 0) {
            break;
        }
        if (cnt <= 1) {
            out->id = -1;
            return 0;
        }
        len = cnt - 1;
        name[len] = 0;
        idx = find_name_index__22TQuestVmDownLoadServerFv((const char *)name);
        first = 0;
    }
    out->a = idx;
    out->id = found - page;
    out->len = blen;
    out->pre = pre;
    out->ent = found;
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803F06B8(const char *name, s16 len, Out_803F0268 *out) {
    char buf[0x50];
    Out_803E8C2C o1;
    Out_803E8C2C o2;
    s32 max;
    s32 r1;
    s32 r2;
    s32 n;
    u32 r;
    if (lbl_805D7904 == -1) {
        return -3;
    }
    strncpy(buf, name, len);
    buf[len] = 0;
    r1 = TQuestVmDownLoadServer__sub_803F0500((u8 *)buf, len, &o1);
    if (r1 == 2) {
        return 2;
    }
    strncpy(buf, name, len);
    buf[len] = 0;
    r2 = TQuestVmDownLoadServer__sub_803E8C2C(buf, len, &o2);
    if (r2 == 2) {
        return 2;
    }
    if (r1 == 0 && r2 == 0) {
        return 0;
    }
    out->xa = 1;
    max = 0;
    out->len2 = o1.pre > o2.pre ? o1.pre : o2.pre;
    if (o1.len > o2.len) {
        out->len = o1.len;
        out->count = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o1.ent, out->entries, 0, &max);
        o2.id = -1;
    } else if (o1.len < o2.len) {
        out->len = o2.len;
        out->count = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o2.ent, out->entries, 0, &max);
        o1.id = -1;
    } else {
        out->len = o1.len;
        n = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o1.ent, out->entries, 0, &max);
        out->count = TQuestVmDownLoadServer__sub_803F03B4((u8 *)o2.ent, out->entries, n, &max);
    }
    out->x4 = r = TQuestVmDownLoadServer::acquire_slot_entry(o1.a, o1.id, o2.id, max);
    if (r == 0xFFFFFFFF) {
        return 0;
    }
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803F0890(void) {
    if ((s32) lbl_805D7904 == -1) {
        return -3;
    }
    TQuestVmDownLoadServer__sub_803E8150();
    TQuestVmDownLoadServer__sub_803E9764();
    TQuestVmDownLoadServer::retry_seek_active_entries();
    if (TQuestVmDownLoadServer__sub_803E86C8() == -1) {
        return -2;
    }
    return 3;
}

s32 TQuestVmDownLoadServer__sub_803F08E4(s8 *quest_vm_down_load_server) {
    s32 r;

    if (lbl_805D7904 != -1) {
        return -4;
    }
    if (*quest_vm_down_load_server == 0) {
        return -1;
    }
    ((TQuestVmDownLoadServer *)quest_vm_down_load_server)->set_file_info_name();
    r = TQuestVmDownLoadServer::find_file_info_index();
    if (r != 0) {
        if (r == -1) {
            return -7;
        }
        return -8;
    }
    if (TQuestVmDownLoadServer::read_ask_header() == -1) {
        TQuestVmDownLoadServer__sub_803E86C8();
        return -2;
    }
    if (TQuestVmDownLoadServer__sub_803E8084() == -1) {
        TQuestVmDownLoadServer__sub_803E86C8();
        return -2;
    }
    TQuestVmDownLoadServer::init_page_cache();
    __VIRetraceHandler();
    if (lbl_805D78F8 == 0x8000) {
        return -6;
    }
    return 3;
}

s32 TQuestVmDownLoadServer__sub_803F09A4(void) {
    s32 var_r3;
    lbl_805D7834 = 0;
    quest_download_initialized = 1;
    lbl_805D7908 = 0;
    lbl_805D790C = 0;
    var_r3 = dispatch_request_0x20__19TWindowKeyBoardSoftFll(&lbl_805E10D8, &lbl_805E10E0);
    if (var_r3 == 0) {
        var_r3 = dispatch_request_0x1c__19TWindowKeyBoardSoftFv();
    }
    if (var_r3 > 0) {
        var_r3 = -1;
    }
    return var_r3;
}

s32 TQuestVmDownLoadServer__sub_803F09FC(void *arg0, int arg1, int arg2) {
    s32 r;
    switch (arg2) {
    case 0:
        if (arg1 < 0) {
            return -1;
        }
        lbl_805D7914.remain = lbl_805D7910 - arg1;
        lbl_805D7914.pos = arg1;
        break;
    case 1:
        r = lbl_805D7914.remain - arg1;
        if (r < 0 || (u32)r > lbl_805D7910) {
            return -1;
        }
        lbl_805D7914.remain = r;
        lbl_805D7914.pos += arg1;
        break;
    case 2:
        if (arg1 > 0) {
            return -1;
        }
        lbl_805D7914.remain = -arg1;
        arg1 = lbl_805D7910 + arg1;
        lbl_805D7914.pos = arg1 - 1;
        break;
    }
    return lbl_805D7914.pos;
}

u32 TQuestVmDownLoadServer::aram_dma_read(void *h, void *dst, int size) {
    u32 n;
    u32 len;
    u32 start;
    u8 *base;
    base = quest_download_aram_dma_buffer;
    n = lbl_805D7914.remain;
    if ((u32)lbl_805D7914.remain >= (u32)size) {
        n = size;
    }
    len = n;
    if (n & 3) {
        len = (n | 3) + 1;
    }
    DCInvalidateRange(base + 0x40, 0x2000);
    (*(u32 *)&quest_download_aram_dma_pending) = 1;
    ARQPostRequest(base + 0x2040, lbl_805D7924, 1, lbl_805D7920, lbl_805D792C + lbl_805D7914.pos,
                   (u32)(base + 0x40), len, TQuestVmDownLoadServer__sub_803F0BE8);
    start = OSGetTick();
    for (;;) {
        if ((*(u32 *)&quest_download_aram_dma_pending) == 0) {
            memcpy(dst, base + 0x40, n);
            break;
        }
        if (OSGetTick() - start > lbl_805D791C) {
            (*(u32 *)&quest_download_aram_dma_pending) = 0;
            ARQRemoveRequest(base + 0x2040);
            OSReport(aram_dma_timeout_message);
            return -1;
        }
    }
    lbl_805D7914.remain -= n;
    lbl_805D7914.pos += n;
    return n;
}

s32 TQuestVmDownLoadServer__sub_803F0BD8(void * _w0) {
    return 0;
}

s32 TQuestVmDownLoadServer__sub_803F0BE0(void * _w0, void * _w1) {
    return 1;
}

void TQuestVmDownLoadServer__sub_803F0BE8(u8 *arg0) {
    if ((u32) *(u32 *)((s8 *)arg0 + 4) == (u32) lbl_805D7924) {
        quest_download_aram_dma_pending = 0;
    }
}

void TQuestVmDownLoadServer__sub_803F0C04(u32 aram_addr, s32 size, u32 owner, u32 priority, u32 timeout_ms) {
    lbl_805D792C = aram_addr;
    lbl_805D7914.remain = size;
    lbl_805D7914.pos = 0;
    lbl_805D7924 = owner;
    lbl_805D7910 = lbl_805D7914.remain;
    lbl_805D7920 = priority;
    lbl_805D791C = timeout_ms * (__OSBusClock / 4 / 1000);
}

u16 lbl_805A02A8[0x4C];
u16 lbl_805A0340[0x98];
RecoveredGlobal_803E6ACC_lbl_805A0470 lbl_805A0470;
QuestDownloadInputEntry quest_download_entry_table[39];
RecoveredGlobal_803E6ACC_lbl_805A05D0 lbl_805A05D0;
QuestDownloadRequestStorage lbl_805A0698;
u8 quest_download_aram_dma_buffer[0x2060];

}
