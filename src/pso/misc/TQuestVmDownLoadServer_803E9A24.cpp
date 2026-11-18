#include "pso/misc/QuestDownloadInternal.h"

// Native object layout: code, generated switch tables and owned storage.
// The boundaries preserve the original eight-byte table alignment.
extern "C" {

QuestDownloadPoolCell quest_download_block_pool[2000];

s32 TQuestVmDownLoadServer::is_download_cmd_allowed(u8 arg0) {
    if ((lbl_805D7888 - 1) <= 1U) {
        return 0;
    }
    switch (arg0) {
    case 0x9D:
    case 0xA1:
    case 0xA3:
    case 0xA5:
    case 0xA7:
    case 0xA9:
    case 0xC3:
    case 0xE3:
    case 0xE5:
    case 0xE7:
    case 0xEE:
    case 0xF2:
    case 0xF3:
        return 1;
    default:
        return 0;
    }
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)

QuestDownloadSegment *TQuestVmDownLoadServer__sub_803E9A74(s32 beg, s32 end, u8 a, u8 b) {
    const QuestDownloadMatchToken *t;
    QuestDownloadSegment *result;
    QuestDownloadSegment *seg;
    QuestDownloadSegment *sub;
    QuestDownloadSegment *walk;
    s32 off;

    result = NULL;
    if (beg >= end) {
        if (lbl_805D7888 < 3) {
            return NULL;
        }
        return QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED;
    }
    if ((t = quest_download_slot_chain_table[beg].tokens) == QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE) {
        return QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED;
    }
    if (t == NULL) {
        if (IsNameChar_803E9A74(lbl_805A0470.bytes[beg]) != 0) {
            if (a == 0 || TQuestVmDownLoadServer::is_valid_item_for_slot(a, b) != 0) {
                seg = (QuestDownloadSegment *)TQuestVmDownLoadServer__sub_803ECF0C();
                if (seg != NULL) {
                    seg->off = 1;
                    seg->a = 0xFF;
                    seg->reserved_2[0] = 0xFF;
                    seg->b = 0;
                    seg->reserved_2[1] = 0;
                    seg->next = NULL;
                }
                return seg;
            }
        }
    }
    while (t != NULL) {
        if (TQuestVmDownLoadServer::is_valid_item_for_slot(t->a, t->b) == 0) {
            goto advance;
        }
        if (a != 0) {
            if (TQuestVmDownLoadServer__sub_803E7390(a, b, t->a) == 0) {
                goto advance;
            }
        }
        off = lbl_8047F0F8[t->off];
        if (beg + off >= end || IsX_803E9FFC(lbl_805A0470.bytes[beg + off]) == 0) {
            seg = (QuestDownloadSegment *)TQuestVmDownLoadServer__sub_803ECF0C();
            if (seg != NULL) {
                seg->off = (s16)off;
                seg->reserved_2[0] = (seg->a = t->a);
                seg->reserved_2[1] = (seg->b = t->b);
                seg->next = result;
                result = seg;
            }
        }
advance:
        if ((s8)t->d == 0) {
            break;
        }
        t -= (s8)t->d;
    }
    t = quest_download_slot_chain_table[beg].tokens;
    while (t != NULL) {
        if (a != 0) {
            if (TQuestVmDownLoadServer__sub_803E7390(a, b, t->a) == 0) {
                goto advance2;
            }
        }
        off = lbl_8047F0F8[t->off];
        sub = TQuestVmDownLoadServer__sub_803E9A74(beg + off, end, t->a, t->b);
        if (sub == QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED) {
            TQuestVmDownLoadServer__sub_803ECE5C(result);
            return QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED;
        }
        if (sub != NULL) {
            for (walk = sub; ; walk = walk->next) {
                walk->off = walk->off + off;
                walk->reserved_2[0] = t->a;
                walk->reserved_2[1] = t->b;
                if (walk->next == NULL) {
                    break;
                }
            }
            walk->next = result;
            result = sub;
        }
advance2:
        if ((s8)t->d == 0) {
            break;
        }
        t -= (s8)t->d;
    }
    return result;
}

#pragma pop

const QuestDownloadMatchToken *find_longest_match_entry__22TQuestVmDownLoadServerFPviPv(u8 *arg0, s32 arg1, s32 *arg2) {
    u8 *s;
    u8 *a;
    s32 k;
    s32 rem;
    const QuestDownloadMatchToken *p;
    s32 m;
    s32 best = 1;
    u8 c = arg0[0];
    if (c < 0xA0) {
        *arg2 = 1;
        return NULL;
    }
    c -= 0xA0;
    for (p = &quest_download_lz_match_entry_table[quest_download_lz_match_index_table[c + 1]] - 1; p >= &quest_download_lz_match_entry_table[quest_download_lz_match_index_table[c]]; p--) {
        a = arg0 + 1;
        rem = arg1 - 1;
        s = &lbl_8047F0F8[p->off];
        m = 1;
        k = *s++ - 1;
        while (1) {
            if (k == 0) {
                if (m > best) {
                    best = m;
                }
                *arg2 = best;
                return p;
            }
            if (rem == 0) {
                if (lbl_805D7888 >= 3) {
                    return QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE;
                }
                break;
            }
            m++;
            if (*s != *a) {
                if (m > best) {
                    best = m;
                }
                break;
            }
            a++;
            s++;
            rem--;
            k--;
        }
    }
    *arg2 = best;
    return NULL;
}

void TQuestVmDownLoadServer::latch_slot_value(s32 arg0) {
    QuestDownloadSlot *slot = &quest_download_slot_chain_table[arg0];
    if (slot->x16 == 0 && slot->x14 != 0) {
        slot->x16 = slot->x15;
    }
}

s32 TQuestVmDownLoadServer__sub_803E9F54(s32 arg0) {
    QuestDownloadSlot *r;
    if (arg0 >= lbl_805D78C0) {
        return 0;
    }
    r = &quest_download_slot_chain_table[arg0];
    if (lbl_805D7848 == 2 && r->x14 == 0) {
        return 0;
    }
    return (s8)r->x15;
}

QuestDownloadEntryNode *insert_sorted_node__22TQuestVmDownLoadServerFPvPv(QuestDownloadEntryNode *arg0, QuestDownloadEntryNode *arg1) {
    QuestDownloadEntryNode *cur;
    QuestDownloadEntryNode *prev;
    s16 k = arg1->prefix.off;
    if (arg0 == NULL || arg0->prefix.off < k) {
        arg1->next = arg0;
        return arg1;
    }
    cur = arg0->next;
    prev = arg0;
    while (cur != NULL) {
        if (cur->prefix.off < k) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    prev->next = arg1;
    arg1->next = cur;
    return arg0;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)

void *TQuestVmDownLoadServer__sub_803E9FFC(s32 arg0, s32 arg1, QuestDownloadItemNode *t) {
    s32 off;
    QuestDownloadEntryNode *head;
    QuestDownloadEntryNode *tail;
    s32 pos;
    QuestDownloadSegment *s;
    QuestDownloadSegment *first;
    QuestDownloadEntryNode *o;
    off = t->off;
    head = NULL;
    tail = NULL;
    pos = arg0 + off;
    s = TQuestVmDownLoadServer__sub_803E9A74(pos, arg1, t->a, t->b);
    if (s == QUEST_DOWNLOAD_SEGMENT_SCAN_FAILED) {
        return QUEST_DOWNLOAD_ENTRY_LIST_FAILED;
    }
    for (first = s; s != NULL; s = s->next) {
        o = (QuestDownloadEntryNode *)TQuestVmDownLoadServer__sub_803ECF48();
        if (o == NULL) {
            break;
        }
        if (head == NULL) {
            head = o;
        }
        o->prefix.off = off + s->off;
        o->prefix.a = s->a;
        o->prefix.b = s->b;
        o->prefix.src = t;
        o->x8 = 0;
        o->xa = 0;
        o->next = NULL;
        if (tail != NULL) {
            tail->next = o;
        }
        tail = o;
    }
    TQuestVmDownLoadServer__sub_803ECE5C((QuestDownloadSegment *)first);
    if (off > 0 && TQuestVmDownLoadServer::is_valid_item_for_slot(t->a, t->b) != 0) {
        if (pos >= arg1 || IsX_803E9FFC(lbl_805A0470.bytes[pos]) == 0) {
            o = (QuestDownloadEntryNode *)TQuestVmDownLoadServer__sub_803ECF48();
            if (o != NULL) {
                if (head == NULL) {
                    head = o;
                }
                o->prefix.off = off;
                o->prefix.a = t->a;
                o->prefix.b = t->b;
                o->prefix.src = t;
                o->x8 = 0;
                o->xa = 0;
                o->next = NULL;
                if (tail != NULL) {
                    tail->next = o;
                }
            }
        }
    }
    return head;
}

#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_lifetimes off
#pragma opt_propagation off

s32 TQuestVmDownLoadServer__sub_803EA1A8(s32 index, s32 limit) {
    QuestDownloadSlot *slot;
    // A shared byte position keeps both borrows in the complete eighty-slot
    // representation. Valid caller indices select actual aligned Slot objects.
    s32 offset = index * sizeof(QuestDownloadSlot);
    slot = reinterpret_cast<QuestDownloadSlot *>(reinterpret_cast<u8 *>(&quest_download_slot_chain_table) + offset);
    QuestDownloadEntryNode *next;
    QuestDownloadItemNode *item;
    QuestDownloadEntryNode *entry;
    QuestDownloadEntryNode *result;
    QuestDownloadEntryNode *head;
    u8 *text;
    s32 pos;
    if (slot->items != QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE) {
        for (item = slot->items; item != NULL; item = item->next) {
            result = static_cast<QuestDownloadEntryNode *>(TQuestVmDownLoadServer__sub_803E9FFC(index, limit, item));
            if (result == QUEST_DOWNLOAD_ENTRY_LIST_FAILED) {
                if (slot->entryHead != NULL) {
                    TQuestVmDownLoadServer__sub_803ECD8C(slot->entryHead);
                    slot->entryHead = NULL;
                }
                return 0;
            }
            if (result != NULL) {
                head = slot->entryHead;
                for (entry = result; entry != NULL; entry = next) {
                    next = entry->next;
                    head = insert_sorted_node__22TQuestVmDownLoadServerFPvPv(head, entry);
                }
                slot->entryHead = head;
            }
        }
    }
    result = static_cast<QuestDownloadEntryNode *>(TQuestVmDownLoadServer__sub_803E9FFC(index, limit, &lbl_8047F8A8));
    if (result == QUEST_DOWNLOAD_ENTRY_LIST_FAILED) {
        if (slot->entryHead != NULL) {
            TQuestVmDownLoadServer__sub_803ECD8C(slot->entryHead);
            slot->entryHead = NULL;
        }
        return 0;
    }
    if (result != NULL) {
        // Borrow the real head lvalue after the generator has returned.
        // This fixed offset names the real pointer member; no node is retyped.
        u8 *member = reinterpret_cast<u8 *>(&quest_download_slot_chain_table) + offset;
        member += offsetof(QuestDownloadSlot, entryHead);
        QuestDownloadEntryNode **headp = reinterpret_cast<QuestDownloadEntryNode **>(member);
        head = *headp;
        for (entry = result; entry != NULL; entry = next) {
            next = entry->next;
            head = insert_sorted_node__22TQuestVmDownLoadServerFPvPv(head, entry);
        }
        *headp = head;
    }
    if (slot->entryHead == NULL) {
        entry = static_cast<QuestDownloadEntryNode *>(TQuestVmDownLoadServer__sub_803ECF48());
        if (entry == NULL) return -1;
        pos = index + 1;
        text = reinterpret_cast<u8 *>(&lbl_805A0470) + pos;
        for (; pos < limit; text++, pos++) {
            if (!TQuestVmDownLoadServer::is_download_cmd_allowed(*text)) break;
        }
        entry->prefix.off = pos - index;
        entry->prefix.a = 0x28;
        entry->prefix.b = 0;
        entry->prefix.src = NULL;
        entry->x8 = 0;
        entry->xa = 0;
        entry->next = NULL;
        slot->entryHead = entry;
        return 1;
    }
    return 1;
}

#pragma pop

QuestDownloadItemNode *build_item_list__22TQuestVmDownLoadServerFiPv(s32 arg0, Hdr_803EA384 *arg1) {
    s16 id;
    s32 x4;
    s32 n;
    Item_803EA384 *it;
    QuestDownloadItemNode *head;
    QuestDownloadItemNode *prev;
    QuestDownloadItemNode *node;
    u8 unused[8];
    it = arg1->entries;
    head = NULL;
    prev = NULL;
    id = arg1->len;
    x4 = arg1->x4;
    n = arg1->count;
    while (n-- != 0) {
        node = TQuestVmDownLoadServer__sub_803ECF84();
        if (node == NULL) {
            break;
        }
        if (head == NULL) {
            head = node;
        }
        node->off = id;
        node->a = it->a;
        node->b = it->b;
        node->x4 = x4;
        node->c = it->key;
        node->next = NULL;
        if (prev != NULL) {
            prev->next = node;
        }
        prev = node;
        it++;
    }
    return head;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)
#pragma opt_lifetimes off
#pragma opt_propagation off

s32 TQuestVmDownLoadServer__sub_803EA428(s32 start, s32 end) {
    size_t position;
    QuestDownloadSlot *slot;
    s32 stop;
    u32 candidateLength;
    u8 *text;
    QuestDownloadInputEntry *last;
    u8 runKind;
    u32 length;
    u8 kind;

    QuestDownloadWorkspaceAddress workspace(reinterpret_cast<size_t>(&lbl_80595008));
    length = end - start;
    if (length == 0) return 0;
    text = lbl_805A0470.bytes + start;
    // The native temporary holds the slot displacement on run-emission paths
    // and an input address inside either text scan. Each path initializes it
    // before use; keep addresses in size_t rather than inventing a pointer.
    position = start * sizeof(QuestDownloadSlot);
#ifdef __MWERKS__
    slot = reinterpret_cast<QuestDownloadSlot *>(workspace.address + sizeof(QuestDownloadWorkspace) + position);
#else
    slot = &quest_download_slot_chain_table[start];
#endif
    kind = 0;
    if (TQuestVmDownLoadServer__sub_803EDB58(*text)) {
        position = reinterpret_cast<size_t>(text + 1);
        kind = 0x1F;
        for (end = 1; end < length; end++, position++) {
            if (!TQuestVmDownLoadServer__sub_803EDB58(*reinterpret_cast<u8 *>(position))) break;
        }
        if (lbl_805D7888 >= 3 && end >= length) return 0;
    } else if (TQuestVmDownLoadServer__sub_803EDB3C(*text)) {
        position = reinterpret_cast<size_t>(text + 1);
        kind = 0x19;
        for (end = 1; end < length; end++, position++) {
            if (!TQuestVmDownLoadServer__sub_803EDB74(*reinterpret_cast<u8 *>(position))) break;
        }
        if (lbl_805D7888 >= 3 && end >= length) return 0;
    } else if (TQuestVmDownLoadServer__sub_803EDB20(*text)) {
        if (lbl_805D7888 >= 3 && length <= 1) return 0;
        candidateLength = 1; end = 1; kind = 0x19;
        goto candidates;
    } else if ((s8)*text != 0 && *text < 0xA0) {
        if (lbl_805D7888 >= 3 && length <= 1) return 0;
        candidateLength = 1; end = 1; kind = 0x29;
        goto candidates;
    } else if ((s8)*text == 0 && (quest_download_entry_table[start].ch & 0xFF00) == 0) {
        for (stop = start + 1; stop < end; stop++) {
            if ((quest_download_entry_table[stop].ch & 0xFF00) != 0) break;
        }
        runKind = 0x19;
        goto emit_run;
    } else if ((s8)*text == 0 && TQuestVmDownLoadServer::is_download_command(quest_download_entry_table[start].ch, 0)) {
        for (stop = start + 1; stop < end; stop++) {
            if (!TQuestVmDownLoadServer::is_download_command(quest_download_entry_table[stop].ch, 1)) break;
        }
        runKind = 0x19;
emit_run:
        if (lbl_805D7888 >= 3 && stop == end) return 0;
        QuestDownloadItemNode *item = TQuestVmDownLoadServer__sub_803ECF84();
        if (item != NULL) {
            item->off = stop - start;
            item->a = runKind;
            item->b = 0;
            item->x4 = -1;
            item->c = 0;
            item->next = NULL;
#ifdef __MWERKS__
            reinterpret_cast<s8 *>(workspace.address + sizeof(QuestDownloadWorkspace) +
                                   offsetof(QuestDownloadSlot, x17))[position] = stop - start + 1;
#else
            slot->x17 = stop - start + 1;
#endif
            append_candidate_items(item, &slot->items);
        }
        return 1;
    } else if ((s8)*text == 0) {
        for (stop = start + 1, text++; stop < end; stop++, text++) {
            if ((s8)*text != 0) break;
        }
        QuestDownloadInputEntry *table = quest_download_entry_table;
        last = table + stop;
        if (TQuestVmDownLoadServer__sub_803EC884((--last)->ch)) runKind = 0x28;
        else if (TQuestVmDownLoadServer::is_valid_sjis_code(last->ch)) runKind = 0x29;
        else runKind = 0x19;
        goto emit_run;
    } else {
        end = 1;
    }

lookup:
    {
        u8 *p = text;
        u32 remaining = length;
        candidateLength = 0;
        for (; candidateLength < remaining; candidateLength++) {
            if ((s8)*p++ == 0) break;
        }
        switch (TQuestVmDownLoadServer__sub_803F06B8((char *)text, candidateLength, (QUEST_WORKSPACE_RESULT(workspace.address)))) {
        case 2:
            if (lbl_805D7888 >= 3) return 0;
            break;
        case 1:
            if (kind != 0 && (QUEST_WORKSPACE_RESULT(workspace.address))->len <= end) {
                TQuestVmDownLoadServer__sub_803EED9C((QUEST_WORKSPACE_RESULT(workspace.address))->x4);
                candidateLength = end;
                slot->x17 = (QUEST_WORKSPACE_RESULT(workspace.address))->len2;
            } else {
                QuestDownloadItemNode *item = build_item_list__22TQuestVmDownLoadServerFiPv(start, (Hdr_803EA384 *)(QUEST_WORKSPACE_RESULT(workspace.address)));
                append_candidate_items(item, &slot->items);
                slot->x17 = (QUEST_WORKSPACE_RESULT(workspace.address))->len2;
                candidateLength = (QUEST_WORKSPACE_RESULT(workspace.address))->len - 1;
            }
            break;
        case 0:
        default:
            if (kind != 0) candidateLength = end;
            else { slot->items = QUEST_DOWNLOAD_ITEM_LIST_UNAVAILABLE; return -1; }
        }
    }
candidates:
    QuestDownloadItemNode **items = &slot->items;
    for (; candidateLength >= end; candidateLength--) {
        if (kind != 0 && candidateLength == end) {
            QuestDownloadItemNode *item = TQuestVmDownLoadServer__sub_803ECF84();
            if (item != NULL) {
                s8 maximum = end + 1;
                item->off = end;
                item->a = kind;
                item->b = 0;
                item->x4 = -1;
                item->c = 0;
                item->next = NULL;
                set_candidate_span(slot, maximum);
                append_candidate_items(item, items);
            }
        }
        if (TQuestVmDownLoadServer__sub_803F0268((char *)text, candidateLength, (QUEST_WORKSPACE_RESULT(workspace.address))) == 1) {
            if (slot->x17 == -1) slot->x17 = (QUEST_WORKSPACE_RESULT(workspace.address))->len2;
            QuestDownloadItemNode *item = build_item_list__22TQuestVmDownLoadServerFiPv(start, (Hdr_803EA384 *)(QUEST_WORKSPACE_RESULT(workspace.address)));
            append_candidate_items(item, items);
        }
    }
    return 1;
}

#pragma pop

s32 TQuestVmDownLoadServer::count_leading_entries(s32 i, s32 end) {
    QuestDownloadSlot *e = &quest_download_slot_chain_table[i];
    s32 n;
    s32 total = 0;
    while (i < end) {
        n = e->x15;
        if (n == 0) {
            return -1;
        }
        if (e->entryHead != NULL && (u32)e->entryHead != 0xFFFFFFFF && e->entryHead->prefix.a != 0x28) {
            break;
        }
        total += n;
        i += n;
        e += n;
    }
    if (total == 0 || i >= end) {
        return total;
    }
    return total + n;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(3)
#pragma opt_common_subs off
#pragma opt_lifetimes off
#pragma opt_propagation off

void TQuestVmDownLoadServer__sub_803EA9E8(s32 start, s32 inputEnd, s32 mode, s32 selectedLength) {
    s32 selectedEnd;
    u8 *text;
    QuestDownloadSlot *first;
    u8 *tokenText;
    s32 groupPos;
    s32 entryEnd;
    s32 remaining;
    QuestDownloadSlot *following;
    QuestDownloadSlot *slot;
    s32 pos;
    QuestDownloadEntryNode **link;
    s32 groupLength;
    size_t workspaceAddress;
    QuestDownloadSlot *walk;
    s32 next;
    const QuestDownloadMatchToken *tokens;
    s32 length;
    QuestDownloadEntryNode *entry;
    QuestDownloadEntryNode *prunedEntry;
    s32 covered;
    s32 limit = borrow_selection_limit(inputEnd);
    QuestDownloadEntryNode *allocated;
    s32 tokenLength;

    first = QUEST_WORKSPACE_SLOT(borrow_selection_address(workspaceAddress = selection_workspace_address(lbl_80595008)), start);
    text = lbl_805A0470.bytes + start;
    lbl_805D7888 = mode;
    slot = first;
    remaining = limit - start;
    while (remaining > 0) {
        if (slot->tokens == QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE) {

            tokenText = text;
            tokens = find_longest_match_entry__22TQuestVmDownLoadServerFPviPv(tokenText, remaining, &tokenLength);
            if (tokens == QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE) break;
            slot->x18 = tokenLength;
            slot->tokens = tokens;
        }
        text++; remaining--; slot++;
    }
    if (lbl_805D7888 == 3 && lbl_805D7880 != 0) return;
    pos = start;
    selectedEnd = start + selectedLength;
    while (pos < limit) {
        slot = QUEST_WORKSPACE_SLOT(workspaceAddress, pos);
        if (slot->x15 > 0) { pos += slot->x15; continue; }
        if (slot->items == NULL && TQuestVmDownLoadServer__sub_803EA428(pos, limit) == 0) break;
        if (slot->entryHead == NULL && TQuestVmDownLoadServer__sub_803EA1A8(pos, limit) == 0) break;
        entry = slot->entryHead;
        while (entry != NULL) {
            entryEnd = pos + entry->prefix.off;
            next = entryEnd;
            if (entryEnd >= limit) {
                if (lbl_805D7888 >= 3) {
                    if (entry->prefix.a != 0xFF) break;
                    lbl_805D7888 = 0;
                }
            } else {
                following = QUEST_WORKSPACE_SLOT(workspaceAddress, next);
                if (following->items == NULL && TQuestVmDownLoadServer__sub_803EA428(next, limit) == 0) break;
                if (following->entryHead == NULL && TQuestVmDownLoadServer__sub_803EA1A8(next, limit) == 0) break;
            }
            entry = entry->next;
        }

        if (pos == start) {
            if (lbl_805D7888 == 1) {
                TQuestVmDownLoadServer::select_best_slot_entry(pos, limit, selectedLength);
                first->x14 = 1;
                length = selectedLength;
                goto chosen_length;
            } else if (lbl_805D7888 == 2) {
                first->x14 = 1;
                length = selectedLength;
                goto chosen_length;
            }
        } else if (pos == selectedEnd && lbl_805D7888 == 2) {
            TQuestVmDownLoadServer::reset_slot_chain_timers(pos);
        }
        length = select_download_length(pos,limit);
        if (length == -1) break;
chosen_length:
        prunedEntry = slot->entryHead;
        link = &slot->entryHead;
        while (prunedEntry != NULL) {
            if (prunedEntry->prefix.off == length) link = &prunedEntry->next;
            else { *link = prunedEntry->next; push_download_entry__22TQuestVmDownLoadServerFPl(prunedEntry); }
            prunedEntry = *link;
        }
        TQuestVmDownLoadServer__sub_803EC460(pos, length);
        slot->x15 = length;
        pos += length;
    }
    for (groupPos = start; groupPos < limit; ) {
        slot = QUEST_WORKSPACE_SLOT(workspaceAddress, groupPos);
        walk = slot;
        covered = walk->x15;

        if (walk->x14 != 0) groupLength = covered;
        else {
            groupLength = TQuestVmDownLoadServer::count_leading_entries(groupPos, limit);
            if (groupLength < 0) return;
            if (groupLength == 0) groupLength = covered;
            if (groupLength == covered) walk->x14 = 1;
            else {
                while (covered < groupLength) {
                    if (walk->entryHead != QUEST_DOWNLOAD_ENTRY_LIST_FAILED) TQuestVmDownLoadServer__sub_803ECD8C(walk->entryHead);
                    walk->entryHead = NULL; walk->x15 = 0;
                    free_node_list__22TQuestVmDownLoadServerFv(walk->textHead); walk->textHead = NULL;
                    covered += (walk = QUEST_WORKSPACE_SLOT(workspaceAddress, groupPos + covered))->x15;
                }
                if (walk->entryHead != QUEST_DOWNLOAD_ENTRY_LIST_FAILED) TQuestVmDownLoadServer__sub_803ECD8C(walk->entryHead);
                walk->entryHead = NULL; walk->x15 = 0;
                free_node_list__22TQuestVmDownLoadServerFv(walk->textHead); walk->textHead = NULL;
                slot->x15 = groupLength;
                allocated = (QuestDownloadEntryNode *)TQuestVmDownLoadServer__sub_803ECF48();
                if (allocated != NULL) {
                    allocated->prefix.off = groupLength; allocated->prefix.a = 0x28; allocated->prefix.b = 0;
                    allocated->prefix.src = NULL; allocated->x8 = 0; allocated->xa = 0; allocated->next = NULL;
                    slot->entryHead = allocated; slot->x14 = 1;
                    TQuestVmDownLoadServer__sub_803EC460(groupPos, groupLength);
                }
            }
        }
        groupPos += groupLength;
    }
}

#pragma pop

void TQuestVmDownLoadServer__sub_803EADD4(QuestDownloadSlot *arg0, s32 arg1) {
    if (arg1 == 0) {
        arg0->tokens = QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE;
        arg0->x18 = -1;
        if ((u32)arg0->items != 0xFFFFFFFF) {
            release_node_chain__22TQuestVmDownLoadServerFPv((QuestDownloadItemNode *)(arg0->items));
        }
        arg0->items = NULL;
        arg0->x17 = -1;
        arg0->x19 = -1;
        arg0->x16 = 0;
    }
    if (arg0->entryHead != NULL && (u32)arg0->entryHead != 0xFFFFFFFF) {
        TQuestVmDownLoadServer__sub_803ECD8C(arg0->entryHead);
    }
    arg0->entryHead = NULL;
    if (arg0->textHead != NULL) {
        free_node_list__22TQuestVmDownLoadServerFv(arg0->textHead);
    }
    arg0->textHead = NULL;
    arg0->timer = 0;
    arg0->x14 = 0;
    arg0->x15 = 0;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

void TQuestVmDownLoadServer__sub_803EAE84(s32 arg0, s32 arg1, void *arg2) {
    QuestDownloadSlot *p;
    QuestDownloadSlot *end;
    end = &((QuestDownloadSlot *)quest_download_slot_chain_table)[arg1];
    p = &((QuestDownloadSlot *)quest_download_slot_chain_table)[arg0];
    for (; p < end; p++) {
        TQuestVmDownLoadServer__sub_803EADD4((QuestDownloadSlot *)(p), (s32)arg2);
    }
}

void TQuestVmDownLoadServer::init_entries() {
    QuestDownloadSlot *p;

    for (p = (QuestDownloadSlot *)quest_download_slot_chain_table; p < (QuestDownloadSlot *)quest_download_slot_chain_table + 80; p++) {
        p->tokens = QUEST_DOWNLOAD_MATCH_TOKENS_UNAVAILABLE;
        p->items = 0;
        p->entryHead = 0;
        p->textHead = 0;
        p->timer = 0;
        p->x14 = 0;
        p->x15 = 0;
        p->x16 = 0;
        p->x17 = -1;
        p->x18 = -1;
        p->x19 = -1;
    }
}

s32 TQuestVmDownLoadServer__sub_803EB0D8(s32 arg0, s32 arg1) {
    QuestDownloadTextNode *save = (*(QuestDownloadTextNode * *)&lbl_805D78A0);
    s32 cnt = lbl_805D789C;
    u8 unused[8];
    TQuestVmDownLoadServer__sub_803EC284(0, 0);
    if (save == (*(QuestDownloadTextNode * *)&lbl_805D78A0)) {
        if (arg1 == 0) {
            (*(QuestDownloadTextNode * *)&lbl_805D78A0) = save;
            lbl_805D789C = cnt;
            lbl_805D7898 = 0;
            return 0;
        }
        save = NULL;
    }
    for (;;) {
        if (Advance_803EB0D8((*(QuestDownloadTextNode * *)&lbl_805D78A0), lbl_805D789C) == save) {
            break;
        }
        (*(QuestDownloadTextNode * *)&lbl_805D78A0) = Advance_803EB0D8((*(QuestDownloadTextNode * *)&lbl_805D78A0), lbl_805D789C);
        Reload_803EB0D8();
    }
    if (arg0 == 1) {
        TQuestVmDownLoadServer__sub_803EB4D4();
    }
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803EB208(s32 mode, s32 force) {
    QuestDownloadTextNode *save = lbl_805D78A0;
    s32 count;
    lbl_805D78A0 = advance_entry_groups(save, lbl_805D789C);
    count = count_fitting_groups(lbl_805D78A0);
    if (count == 0) {
        if (force == 0) {
            lbl_805D78A0 = save;
            return 0;
        }
        TQuestVmDownLoadServer__sub_803EC284(0, 0);
    } else {
        lbl_805D789C = count;
    }
    lbl_805D7898 = 0;
    if (mode == 1) {
        TQuestVmDownLoadServer__sub_803EB4D4();
    }
    return 1;
}

s32 count_fitting_entries__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *arg0) {
    s32 n;
    s32 total;
    s32 lim;
    QuestDownloadTextNode *p;
    if (arg0 == NULL) {
        return 0;
    }
    p = arg0;
    total = 0;
    lim = lbl_805D78A4 - 9;
    n = 0;
    while (n < 9 && p != NULL) {
        total += Len_803EB328(p) + 3;
        if (total > lim) {
            break;
        }
        n++;
        p = Next_803EB328(p);
    }
    if (n == 0) {
        return 1;
    }
    return n;
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803EB420(s32 start, s32 count, QuestDownloadTextNode *arg2, u16 *buf) {
    s32 n;
    QuestDownloadTextNode *p;
    u8 unused[8];
    if (arg2 == NULL || (arg2->flags & 0x80)) {
        return TQuestVmDownLoadServer__sub_803E6970(start, count, buf, 0);
    }
    p = arg2;
    n = 0;
    for (;;) {
        n += TQuestVmDownLoadServer__sub_803EC95C(buf + n, reinterpret_cast<u8 *>(p) + 1, 6);
        if (!(p->flags & 1)) {
            break;
        }
        p = p->next;
    }
    buf += n;
    return n + TQuestVmDownLoadServer__sub_803E6970((s32)(start + arg2->payload.head.length), (s32)(count - arg2->payload.head.length), buf, 0);
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

void TQuestVmDownLoadServer__sub_803EB4D4(void) {
    u8 *digit;
    s32 index;
    QuestDownloadTextNode *node;
    s32 written;
    s32 count;
    s32 value;
    u16 *line;
    s32 n;
    u16 *pad;
    digit = reinterpret_cast<u8 *>(lbl_80596258.text) + 5;
    count = display_group_count(lbl_805D78A0);
    count -= lbl_805D7898;
    count -= 1;
    if (count < 0) count = 0;
    if ((value = count / 100) != 0) *digit++ = value + '0';
    else *digit++ = ' ';
    count %= 100;
    if ((value = count / 10) != 0 || (u32)digit[-1] != ' ') *digit++ = value + '0';
    else *digit++ = ' ';
    count %= 10;
    *digit = count + '0';
    TQuestVmDownLoadServer__sub_803EC95C(lbl_805A0340, reinterpret_cast<u8 *>(lbl_80596258.text), 0);
    node = lbl_805D78A0;
    written = 9;
    index = 0;
    while (index < lbl_805D789C) {
        line = lbl_805A0340 + written;
        lbl_805D7894[2] = index + '1';
        written += TQuestVmDownLoadServer__sub_803EC95C(line, lbl_805D7894, 0);
        line = lbl_805A0340 + written;
        n = display_convert_text(lbl_805D78F0, lbl_805D78EC, node, line);
        if (index == lbl_805D7898) TQuestVmDownLoadServer__sub_803ECA1C(line, n, 7);
        else TQuestVmDownLoadServer__sub_803ECA1C(line, n, 0);
        written += n;
        if ((node = display_next_group(node)) == NULL) break;
        index++;
    }
    pad = lbl_805A0340 + written;
    while (written < lbl_805D78A4) {
        TQuestVmDownLoadServer__sub_803EC95C(pad, lbl_805E10D0, 0);
        pad++;
        written++;
    }
}

#pragma pop

QuestDownloadTextNode *advance_nodes__22TQuestVmDownLoadServerFPvi(QuestDownloadTextNode *p, s32 n) {
    s32 i;
    for (i = 0; i != n; i++) {
        while (p->flags & 1) {
            p = p->next;
        }
        p = p->next;
    }
    return p;
}

s32 TQuestVmDownLoadServer__sub_803EB7C0(QuestDownloadTextNode *arg0) {
    s32 n;
    if (arg0->flags == 0x80) {
        return lbl_805D78EC * 2;
    }
    n = (lbl_805D78EC - arg0->payload.head.length) * 2;
    while (arg0->flags & 1) {
        n += strlen(reinterpret_cast<char *>(&arg0->payload));
        arg0 = arg0->next;
    }
    return n + strlen(reinterpret_cast<char *>(&arg0->payload));
}

s32 count_chain_nodes__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *p) {
    s32 n = 0;
    while (p != NULL) {
        while (p->flags & 1) {
            p = p->next;
        }
        p = p->next;
        n++;
    }
    return n;
}

QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EB878(QuestDownloadTextNode *p) {
    while (p->flags & 1) {
        p = p->next;
    }
    return p->next;
}

QuestDownloadTextNode *detach_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadTextNode *p) {
    QuestDownloadTextNode *next;
    while (p->flags & 1) {
        p = p->next;
    }
    next = p->next;
    p->next = NULL;
    return next;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

void append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(s32 start, QuestDownloadTextNode **headp, QuestDownloadTextNode **tailp, QuestDownloadTextNode *n) {
    s32 len;

    len = Conv_803EB8BC(start, lbl_805D78EC, n, lbl_805A0340);
    len = TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, (u8 *)lbl_805A02A8, len);
    if (Find_803EB8BC((u8 *)lbl_805A02A8, len)) {
        free_node_list__22TQuestVmDownLoadServerFv(n);
        return;
    }
    Add_803EB8BC((u8 *)lbl_805A02A8, len);
    if (*headp == NULL) {
        *tailp = n;
        *headp = n;
    } else {
        (*tailp)->next = n;
    }
    *tailp = Last_803EB8BC(n);
}

void TQuestVmDownLoadServer__sub_803EBA98(s32 start, QuestDownloadTextNode *arg1) {
    s32 n;
    s32 len;
    quest_download_text_write_ptr = quest_download_text_buffer;
    while (arg1 != NULL) {
        n = Conv_803EBA98(start, lbl_805D78EC, arg1, lbl_805A0340);
        len = TQuestVmDownLoadServer__sub_803EC71C(lbl_805A0340, quest_download_text_write_ptr + 1, n);
        *quest_download_text_write_ptr++ = len;
        quest_download_text_write_ptr += len;
        arg1 = Next_803EBA98(arg1);
    }
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
#pragma opt_dead_assignments off

QuestDownloadTextNode *get_next_node__22TQuestVmDownLoadServerFPv(QuestDownloadQueueNode *p) {
    QuestDownloadQueueNode *best = NULL;
    QuestDownloadTextNode *ret;
    u32 key;
    for (; p != NULL; p = p->next) {
        if (p->text != NULL && (best == NULL || p->score > key)) {
            best = p;
            key = p->score;
        }
    }
    if (best == NULL) {
        return NULL;
    }
    ret = best->text;
    best->text = Detach_803EBBBC(ret);
    best->score = best->text == NULL ? 0 : TQuestVmDownLoadServer__sub_803ED0B4((u8 *)best->entry, best->text->payload.head.attribute);
    return ret;
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

void TQuestVmDownLoadServer__sub_803EBC88(s32 mode) {
    QuestDownloadSlot *e = &quest_download_slot_chain_table[lbl_805D78F0];
    free_node_list__22TQuestVmDownLoadServerFv(e->textHead);
    e->textHead = build_entry_text(lbl_805D78F0, lbl_805D78EC, mode);
}

void *TQuestVmDownLoadServer::build_text_node_chain(void *sp, void *a1, s32 a2, void *hp, void *tp) {
    u8 *text;
    s32 rem;
    QuestDownloadTextNode *n;
    QuestDownloadTextNode *m;
    s32 c;
    text = ((Src_803EBD38 *)sp)->text;
    rem = strlen((const char *)text);
    n = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803ECED0();
    if (n == NULL) {
        return NULL;
    }
    n->flags = 0;
    c = Copy_803EBD38(reinterpret_cast<u8 *>(n->payload.head.text), text, 4);
    rem -= c;
    n->payload.head.length = a2;
    text += c;
    n->payload.head.kind = ((Src_803EBD38 *)sp)->x4;
    n->payload.head.source = (s32)a1;
    n->payload.head.id = ((Src_803EBD38 *)sp)->x0;
    n->payload.head.attribute = ((Src_803EBD38 *)sp)->x2;
    n->next = NULL;
    *((QuestDownloadTextNode **)hp) = n;
    while (rem > 0) {
        m = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803ECED0();
        if (m == NULL) {
            free_node_list__22TQuestVmDownLoadServerFv(*((QuestDownloadTextNode **)hp));
            return NULL;
        }
        n->flags |= 1;
        // Retain the two bytes that can later become a default head'((Src_803EBD38 *)sp)
        // attribute when this cell is recycled; do not create an uninitialized
        // character tail at those positions when changing the payload member.
        u8 *bytes = reinterpret_cast<u8 *>(m);
        const u8 attribute_high = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)];
        const u8 attribute_low = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1];
        new (&m->payload.continuation, quest_download_pool_storage) QuestDownloadTextContinuation;
        bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)] = attribute_high;
        bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1] = attribute_low;
        m->flags = 2;
        c = Copy_803EBD38(reinterpret_cast<u8 *>(m->payload.continuation.text), text, 14);
        rem -= c;
        text += c;
        m->next = NULL;
        n->next = m;
        n = m;
    }
    *((QuestDownloadTextNode **)tp) = n;
    return *((QuestDownloadTextNode **)hp);
}

QuestDownloadTextNode *TQuestVmDownLoadServer__sub_803EBEFC(QuestDownloadEntryPrefix *a) {
    s32 count;
    QuestDownloadTextNode *first;
    QuestDownloadTextNode *tl;
    s32 pad;
    QuestDownloadTextNode *head;
    u8 *base;
    QuestDownloadItemNode *t;
    QuestDownloadTextNode *tail;
    u8 *p;

    base = reinterpret_cast<u8 *>(lbl_80596258.text);
    t = a->src;
    if (t == NULL || t->off == 0) {
def:
        return Default_803EBEFC(a->off);
    }
    if ((u32)t->x4 == 0xFFFFFFFFU) {
        if (t->a != 0x1F) {
            goto def;
        }
        if (TQuestVmDownLoadServer__sub_803EEA48((s32)&lbl_805A0470 + lbl_805D78F0, t->off, QUEST_TEXT_SCRATCH(base), &count) > 0) {
            goto build;
        }
        goto def;
    } else {
        if (TQuestVmDownLoadServer::read_quest_chunk(t->x4, t->a, t->b, QUEST_TEXT_SCRATCH(base), &count) <= 0) {
            goto def;
        }
    }
build:
    p = QUEST_TEXT_SCRATCH(base);
    tail = NULL;
    head = NULL;
    while (count > 0) {
        if (TQuestVmDownLoadServer::build_text_node_chain(p, t, t->off, &first, &tl) == NULL) {
            free_node_list__22TQuestVmDownLoadServerFv(head);
            return NULL;
        }
        if (head == NULL) {
            head = first;
            tail = tl;
        } else {
            tail->next = first;
            tail = tl;
        }
        p += 5;
        while (*p++ != 0) {
        }
        if ((u32)p & 1) {
            p++;
        }
        count--;
    }
    return head;
}

void TQuestVmDownLoadServer__sub_803EC09C(void) {
    s32 idx;
    QuestDownloadSlot *e;
    QuestDownloadTextNode *tail;
    QuestDownloadTextNode *head;
    QuestDownloadEntryNode *o;
    QuestDownloadQueueNode *qh;
    QuestDownloadQueueNode *q;
    QuestDownloadQueueNode *qt;
    QuestDownloadTextNode *r;
    QuestDownloadTextNode *n;

    e = &quest_download_slot_chain_table[lbl_805D78F0];
    if ((u32)(o = e->entryHead) == 0xFFFFFFFFU) {
        return;
    }
    qh = NULL;
    qt = NULL;
    for (; o != NULL; o = o->next) {
        if (o->prefix.off != lbl_805D78EC) {
            continue;
        }
        q = TQuestVmDownLoadServer__sub_803ECE94();
        if (q == NULL) {
            for (; qh != NULL; qh = qh->next) {
                push_download_entry__22TQuestVmDownLoadServerFPl(qh->text);
            }
            qh = NULL;
            break;
        }
        q->text = r = (QuestDownloadTextNode *)TQuestVmDownLoadServer__sub_803EBEFC(&o->prefix);
        q->entry = o;
        q->score = (r == NULL) ? 0 : TQuestVmDownLoadServer__sub_803ED0B4((u8 *)o, r->payload.head.attribute);
        q->next = NULL;
        if (qh == NULL) {
            qh = qt = q;
        } else {
            qt->next = q;
            qt = q;
        }
    }
    e = &quest_download_slot_chain_table[idx = lbl_805D78F0];
    head = e->textHead;
    tail = Last_803EC09C(head);
    TQuestVmDownLoadServer__sub_803EBA98(idx, (QuestDownloadTextNode *)head);
    while ((n = get_next_node__22TQuestVmDownLoadServerFPv(qh)) != NULL) {
        append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(idx, (QuestDownloadTextNode **)&head, (QuestDownloadTextNode **)&tail, (QuestDownloadTextNode *)n);
    }
    if ((n = Default_803EC09C(lbl_805D78EC)) != NULL) {
        append_unique_node__22TQuestVmDownLoadServerFiPvPvPv(idx, (QuestDownloadTextNode **)&head, (QuestDownloadTextNode **)&tail, (QuestDownloadTextNode *)n);
    }
    e->textHead = head;
    TQuestVmDownLoadServer__sub_803ECD1C((QuestDownloadQueueNode *)qh);
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)

void TQuestVmDownLoadServer__sub_803EC284(s32 index, s32 mode) {
    QuestDownloadTextNode *head;
    s32 saved_mode = mode;
    if (saved_mode == 1) {
        TQuestVmDownLoadServer__sub_803EC09C();
    }
    head = quest_download_slot_chain_table[lbl_805D78F0].textHead;
    if (lbl_805D7834 > 0) {
        lbl_805D78A4 = 80;
    } else {
        lbl_805D78A4 = TQuestVmDownLoadServer::get_buffer_size();
    }
    mode = count_text_groups_that_fit(head);
    while (index >= mode) {
        index -= mode;
        advance_text_groups(head, mode);
        mode = count_text_groups_that_fit(head);
        if (mode == 0) {
            TQuestVmDownLoadServer__sub_803EC284(0, 0);
            goto finish;
        }
    }
    lbl_805D78A0 = head;
    lbl_805D7898 = index;
    lbl_805D789C = mode;
finish:
    if (saved_mode == 1 && lbl_805D7834 == 0) {
        TQuestVmDownLoadServer__sub_803EB4D4();
    }
}

void TQuestVmDownLoadServer__sub_803EC460(s32 pos, s32 x) {
    QuestDownloadTextNode *first;
    QuestDownloadTextNode *tl;
    QuestDownloadSlot *e;
    u8 *base;
    QuestDownloadEntryNode *o;
    QuestDownloadEntryNode *best;
    u16 bestv;
    u16 v;
    QuestDownloadItemNode *t;

    e = &quest_download_slot_chain_table[pos];
    base = reinterpret_cast<u8 *>(lbl_80596258.text);
    best = NULL;
    bestv = 0;
    if (e->textHead != NULL) {
        return;
    }
    if ((u32)(o = e->entryHead) == 0xFFFFFFFFU) {
def:
        e->textHead = Default_803EC460(x);
        return;
    }
    for (; o != NULL; o = o->next) {
        if (o->prefix.off != x) {
            continue;
        }
        v = (o->prefix.src == NULL) ? 0 : TQuestVmDownLoadServer__sub_803ED0B4((u8 *)o, o->prefix.src->c);
        if (v > bestv || best == NULL) {
            bestv = v;
            best = o;
        }
    }
    if (best == NULL || (t = best->prefix.src) == NULL || t->off == 0) {
        goto def;
    }
    if ((u32)t->x4 == 0xFFFFFFFFU) {
        if (t->a != 0x1F) {
            goto def;
        }
        if (TQuestVmDownLoadServer__sub_803EED0C((s32)&lbl_805A0470 + pos, t->off, (s32)(QUEST_TEXT_SCRATCH(base))) > 0) {
            goto build;
        }
        goto def;
    } else {
        if (TQuestVmDownLoadServer__sub_803F0048(t->x4, t->a, t->b, QUEST_TEXT_SCRATCH(base)) <= 0) {
            goto def;
        }
    }
build:
    e->textHead = (QuestDownloadTextNode *)TQuestVmDownLoadServer::build_text_node_chain(QUEST_TEXT_SCRATCH(base), t, t->off, &first, &tl);
}

#pragma pop

u16 TQuestVmDownLoadServer::jis_to_sjis(u16 arg0) {
    u8 lo;
    u8 hi;
    hi = arg0 >> 8;
    lo = arg0;
    if (arg0 < 0x2121 || arg0 > 0x7E7E) {
        return 0;
    }
    if (lo < 0x21 || lo >= 0x7F) {
        return 0;
    }
    lo += 0x1F;
    if (hi & 1) {
        hi >>= 1;
    } else {
        hi >>= 1;
        hi--;
        lo += 0x5E;
    }
    if (lo >= 0x7F) {
        lo++;
    }
    if (hi < 0x2F) {
        hi += 0x71;
    } else {
        hi += 0xB1;
    }
    return (hi << 8) | lo;
}

u16 TQuestVmDownLoadServer__sub_803EC69C(u16 code) {
    u32 lo = code & 0xff;
    u8 hi = ((u32)code >> 8) & 0xff;
    code = hi;
    u32 row;
    u8 outlo;
    if (lo < 0x40 || lo > 0xfc || lo == 0x7f) {
        return 0;
    }
    if (hi >= 0xe0) {
        code -= 0x40;
    }
    row = ((u8)code - 0x81) * 2 + 0x21;
    if ((u8)lo >= 0x9f) {
        row++;
        outlo = lo - 0x7e;
    } else if ((u8)lo >= 0x80) {
        outlo = lo - 0x20;
    } else {
        outlo = lo - 0x1f;
    }
    return ((row << 8) & 0xff00) | outlo;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(3)

s32 TQuestVmDownLoadServer__sub_803EC71C(u16 *text, u8 *out, s32 count) {
    s32 i;
    u8 *dst;
    u16 ch;
    s32 kind;
    u16 next;
    u16 pair;
    dst = out;
    i = 0;
    while (i < count) {
        ch = *text;
        kind = Kind_803EC71C(ch);
        if (kind == 0) {
            *dst = (s8)ch;
            text++;
            dst++;
            i++;
        } else if (kind & 1) {
            next = ReadNext_803EC71C(text);
            i++;
            // Narrowing to u16 retains only the first payload byte.
            pair = ch << 8;
            if (((next >> 8) & 0xf) == kind + 1) {
                pair |= next & 0xff;
                text++;
                i++;
                if (IsJis_803EC71C(pair)) {
                    pair = TQuestVmDownLoadServer::jis_to_sjis(pair);
                }
                dst[0] = (s8)(pair >> 8);
                dst[1] = (s8)pair;
                dst += 2;
            }
        }
    }
    *dst = 0;
    return dst - out;
}

#pragma pop

s32 TQuestVmDownLoadServer::is_valid_sjis_code(u16 arg0) {
    s32 var_r0;
    if ((arg0 >= 0x2120U) && (arg0 < 0x3020U)) {
        if ((s32) (arg0 & 0xFF00) == 0x2500) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            return 0;
        }
        return 1;
    }
    return 0;
}

s32 TQuestVmDownLoadServer__sub_803EC884(u16 arg0) {
    if (arg0 >= 0x3020U) {
        return 1;
    }
    return 0;
}

s32 TQuestVmDownLoadServer::is_download_command(u16 arg0, s32 arg1) {
    if ((arg1 != 0) && (arg0 == 0x213C)) {
        return 1;
    }
    if ((s32) (arg0 & 0xFF00) == 0x2500) {
        return 1;
    }
    return 0;
}

u8 TQuestVmDownLoadServer__sub_803EC8D8(u16 arg0) {
    s32 temp_r0;
    u8 var_r3;
    u16 var_r4;
    if ((arg0 > 0x20U) && (arg0 < 0x7FU)) {
        var_r3 = 0;
        return 0;
    }
    var_r4 = arg0;
    temp_r0 = arg0 & 0xFF00;
    switch (temp_r0) {
    case 0x2300:
        var_r3 = var_r4 & 0x7F;
        return var_r3;
    case 0x2400:
        var_r3 = (var_r4 & 0x7F) | 0x80;
        return var_r3;
    case 0x2500:
        var_r3 = 0;
        return 0;
    default:
        return TQuestVmDownLoadServer::lookup_value_by_key(arg0);
    }
}

s32 TQuestVmDownLoadServer__sub_803EC95C(u16 *out, u8 *text, int attr) {
    u16 *dst = out;
    u8 c;
    while ((c = *text) != 0) {
        if (c < 0x80 || (c >= 0xA0 && c < 0xE0)) {
            dst += TQuestVmDownLoadServer::encode_char_with_attr(dst, *text++, attr);
        } else {
            u16 ch = (c << 8) | text[1];
            dst += TQuestVmDownLoadServer::encode_char_with_attr(dst, ch, attr);
            text += 2;
        }
    }
    return dst - out;
}

void TQuestVmDownLoadServer__sub_803ECA1C(u16 *arg0, s32 arg1, s32 arg2) {
    u16 a = arg2 << 12;
    while (arg1-- != 0) {
        *arg0 = (*arg0 & 0xFFF) | a;
        arg0++;
    }
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)

s32 TQuestVmDownLoadServer::encode_char_with_attr(u16 *out, u16 ch, s32 attr) {
  s32 hi;
  u16 c;
  s32 lo;
  int new_var;
  u16 a;
  c = ch;
  a = (attr & 0xF) << 12;
  new_var = ch & 0xFF;
  hi = (ch >> 8) & 0xFF;
  lo = new_var;
  if (IsSjis_803ECAE8(new_var, hi))
  {
    if (Kind_803ECAE8(c, new_var) == 1)
    {
      a |= 0x300;
    }
    else
    {
      a |= 0x700;
    }
  }
  else
    if (IsJisPair_803ECAE8(new_var, hi))
  {
    a |= 0x500;
    if (ch == 0x2474)
    {
      ch = 0x2574;
    }
  }
  else
  {
    *out = a | lo;
    return 1;
  }
  *(out++) = a | (ch >> 8);
  *out = (a + 0x100) | (ch & 0xFF);
  return 2;
}

#pragma pop

s32 TQuestVmDownLoadServer__sub_803ECC7C(u16 arg0) {
    u8 hi = (arg0 >> 8) & 0xFF;
    u8 lo = arg0;
    s32 lead;
    if (hi < 0x81 || hi > 0xFC || (hi >= 0xA0 && hi < 0xE0)) {
        lead = 0;
    } else {
        lead = 1;
    }
    if (lead == 0) {
        return 0;
    }
    if (lo < 0x40 || lo > 0xFC || lo == 0x7F) {
        return 0;
    }
    return 1;
}

s32 TQuestVmDownLoadServer::is_sjis_lead_byte(u8 arg0) {
    if ((arg0 < 0x81U) || (arg0 > 0xFCU) || ((arg0 >= 0xA0U) && (arg0 < 0xE0U))) {
        return 0;
    }
    return 1;
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)

void TQuestVmDownLoadServer__sub_803ECD1C(QuestDownloadQueueNode *p) {
    while (p != NULL) {
        QuestDownloadQueueNode *next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}

void free_node_list__22TQuestVmDownLoadServerFv(QuestDownloadTextNode *p) {
    while (p != NULL) {
        QuestDownloadTextNode *next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}

void TQuestVmDownLoadServer__sub_803ECD8C(QuestDownloadEntryNode *p) {
    QuestDownloadEntryNode *next;
    while (p != NULL) {
        next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}

void release_node_chain__22TQuestVmDownLoadServerFPv(QuestDownloadItemNode *p) {
    u32 prev = 0xFFFFFFFF;
    QuestDownloadItemNode *next;
    while (p != NULL) {
        next = p->next;
        if ((prev == 0xFFFFFFFF || p->x4 != prev) && (u32)p->x4 != 0xFFFFFFFF) {
            TQuestVmDownLoadServer__sub_803EED9C(p->x4);
        }
        prev = p->x4;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}

void TQuestVmDownLoadServer__sub_803ECE5C(QuestDownloadSegment *p) {
    QuestDownloadSegment *next;
    while (p != NULL) {
        next = p->next;
        if (p != NULL) return_quest_pool_cell(p);
        p = next;
    }
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(1)

QuestDownloadQueueNode *TQuestVmDownLoadServer__sub_803ECE94(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->queue, quest_download_pool_storage) QuestDownloadQueueNode;
    return reinterpret_cast<QuestDownloadQueueNode *>(p);
}

void *TQuestVmDownLoadServer__sub_803ECED0(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    // Inspect the persistent cell representation before changing its active
    // member. Defaults retain these bytes, so initialize the new head's value
    // explicitly rather than reading an indeterminate u16 after construction.
    u8 *bytes = reinterpret_cast<u8 *>(reinterpret_cast<QuestDownloadPoolCell *>(p));
    const u8 attribute_high = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)];
    const u8 attribute_low = bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1];
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->text, quest_download_pool_storage) QuestDownloadTextNode;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->text.payload.head, quest_download_pool_storage) QuestDownloadTextHead;
    bytes[offsetof(QuestDownloadTextNode, payload.head.attribute)] = attribute_high;
    bytes[offsetof(QuestDownloadTextNode, payload.head.attribute) + 1] = attribute_low;
    return reinterpret_cast<QuestDownloadTextNode *>(p);
}

void *TQuestVmDownLoadServer__sub_803ECF0C(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->segment, quest_download_pool_storage) QuestDownloadSegment;
    return reinterpret_cast<QuestDownloadSegment *>(p);
}

void *TQuestVmDownLoadServer__sub_803ECF48(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->entry, quest_download_pool_storage) QuestDownloadEntryNode;
    return reinterpret_cast<QuestDownloadEntryNode *>(p);
}

QuestDownloadItemNode *TQuestVmDownLoadServer__sub_803ECF84(void) {
    QuestDownloadFreeLink *p = pop_free_block();
    if (p == NULL) return NULL;
    new (&reinterpret_cast<QuestDownloadPoolCell *>(p)->item, quest_download_pool_storage) QuestDownloadItemNode;
    return reinterpret_cast<QuestDownloadItemNode *>(p);
}

#pragma pop

#pragma push
#pragma dont_inline off
#pragma inline_depth(2)

void push_download_entry__22TQuestVmDownLoadServerFPl(void *arg0) {
    if (arg0 != NULL) return_quest_pool_cell(arg0);
}

void TQuestVmDownLoadServer::init_block_free_list() {
    QuestDownloadPoolCell *p;
    if (quest_download_free_list_ready_flag == 0 && lbl_805D78AC == 2000) return;
    lbl_805D78B0 = &quest_download_block_pool[0].free;
    for (p = quest_download_block_pool; p < &quest_download_block_pool[1999]; p++) {
        new (&p->free, quest_download_pool_storage) QuestDownloadFreeLink;
        p->free.next = &(p + 1)->free;
    }
    new (&p->free, quest_download_pool_storage) QuestDownloadFreeLink;
    p->free.next = 0;
    lbl_805D78AC = 2000;
    quest_download_free_list_ready_flag = 0;
}

#pragma pop

u16 TQuestVmDownLoadServer__sub_803ED0B4(u8 *arg0, u16 arg1) {
    if (arg1 != 0) {
        return arg1 + 0x3E8;
    }
    // All three native callers pass the complete live entry object.
    return reinterpret_cast<QuestDownloadEntryNode *>(arg0)->x8;
}

}
