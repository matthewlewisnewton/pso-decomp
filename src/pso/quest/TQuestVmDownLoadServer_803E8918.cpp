#include "types.h"
#include "pso/quest/TQuestVmDownLoadServer_803E6970.h"
#include "pso/quest/TQuestVmDownLoadServer.h"
#include "pso/quest/QuestDownloadServer.h"

#pragma dont_inline off
#pragma inline_depth(2)

extern "C" {
NameCache_80591EC8 lbl_80591EC8;
QuestDownloadCachedNameIndex lbl_80593EC8;
u8 lbl_805D7868;
u8 *lbl_805D786C;
u8 *lbl_805D7870;
s32 lbl_805D7874;
QuestDownloadCachedNameNode *lbl_805D7878;
void TQuestVmDownLoadServer__sub_803E8918(void) {
    lbl_805D7868 = 1;
}

void TQuestVmDownLoadServer__sub_803E95BC(void);

inline int Hash_80591EC8(char *s) {
    int h;
    u8 c = s[0];
    if (c >= 0xA0 && c < 0xF0) {
        h = c - 0xA0;
    } else {
        h = 0;
    }
    return h;
}
inline s32 IsSjisLead(u8 c) {
    if ((c >= 0x80 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) {
        return 1;
    }
    return 0;
}

inline QuestDownloadCachedNameNode *FindName_80591EC8(char *buf, s16 len, QuestDownloadCachedNameNode ***plink) {
    QuestDownloadCachedNameNode *n;
    QuestDownloadCachedNameNode *prev = NULL;
    s32 h;
    h = Hash_80591EC8(buf);
    for (n = lbl_80593EC8.heads[h]; n != NULL; n = n->next) {
        s32 r;
        u8 elen = n->encodedRecord[2];
        r = strncmp((char *)(n->encodedRecord + 3), buf, (s16)elen);
        if (r == 0) {
            if (len == (s16)elen) {
                break;
            }
        } else if (r > 0) {
            break;
        }
        prev = n;
    }
    *plink = prev == NULL ? &lbl_80593EC8.heads[h] : &prev->next;
    return n;
}

void TQuestVmDownLoadServer__sub_803E8924(s32 id) {
    char buf[0x50];
    s32 unused[3];
    s16 page;
    int page_wide;
    u8 *p;
    s16 len;
    u8 *dst;
    s16 elen;
    QuestDownloadCachedNameNode *n;
    s32 size;
    s32 h;
    s32 r;
    u8 c;
    page = (s16)(page_wide = id >> 12);
    if (lbl_805D7874 == page) {
        return;
    }
    p = &lbl_80591EC8.pages[page][(s16)(id & 0xFFF)];
    u8 *lo = &p[(lbl_805D7874 == page) * 0];
    size = *lo + (p[1] << 8);
    size &= 0xFFFF;
    u8 *rec = p;
    if (lbl_805D7870 > lbl_805D786C - size - 2) {
        TQuestVmDownLoadServer__sub_803E95BC();
    }
    dst = lbl_805D7870;
    lbl_805D7870 += size;
    lbl_805D7870[0] = 0;
    lbl_805D7870[1] = 0;
    if (page == lbl_805D7874) {
        return;
    }
    len = p[2];
    strncpy(buf, (const char *)p + 3, len);
    buf[len] = 0;
    c = buf[0];
    if (c >= 0xA0 && c < 0xF0) {
        h = c - 0xA0;
    } else {
        h = 0;
    }
    n = lbl_80593EC8.heads[h];
    while (n != NULL) {
        elen = n->encodedRecord[2];
        r = strncmp((char *)(n->encodedRecord + 3), buf, elen);
        if (r == 0) {
            if (len == elen) {
                break;
            }
        } else if (r > 0) {
            break;
        }
        n = n->next;
    }

    if (n->encodedRecord != p) {
        return;
    }
    n->encodedRecord = dst;
    while (size != 0) {
        *dst++ = *p++;
        size--;
    }

    rec[2] = 0;
    TQuestVmDownLoadServer::invalidate_entries_by_id(id);
}

// Id of a name-cache record: its 0x400-byte page in bits 12 and up, its offset in the page below.
inline s32 NameRecordId_80591EC8(NameCache_80591EC8 *cache, void *rec) {
    s32 off = (u8 *)rec - (u8 *)cache;
    return ((off / 1024) << 12) | (off % 1024);
}

s32 TQuestVmDownLoadServer::lookup_name_entry(s16 name_len, Out_803E8C2C *out) {
    QuestDownloadCachedNameNode *n;
    s32 r;
    u8 len;
    u8 *e;
    for (n = lbl_80593EC8.heads[Hash_80591EC8(((char *)this))]; n != NULL; n = n->next) {
        e = n->encodedRecord;
        len = e[2];
        r = strncmp((char *)(e + 3), ((char *)this), (s16)len);
        if (r == 0) {
            if ((s16)len == name_len) {
                break;
            }
        } else if (r > 0) {
            out->id = -1;
            return 0;
        }
    }
    if (n == NULL) {
        out->id = -1;
        return 0;
    }
    out->a = 0;
    out->id = NameRecordId_80591EC8(&lbl_80591EC8, e);
    out->encodedRecord = e;
    return 1;
}

s32 TQuestVmDownLoadServer__sub_803E8C2C(char *name, s16 name_len, Out_803E8C2C *out) {
    QuestDownloadCachedNameNode *n;
    u8 *e;
    s16 len;
    u8 *found;
    s16 pre;
    s16 blen;
    s32 r;
    s16 m;
    blen = 0;
    pre = 0;
    out->pre = 0;
    out->len = 0;
    for (n = lbl_80593EC8.heads[Hash_80591EC8(name)]; n != NULL; n = n->next) {
        e = n->encodedRecord;
        len = e[2];
        m = TQuestVmDownLoadServer::match_prefix_length(e + 3, (u8 *)name, (s16)len);
        if (m >= pre) {
            pre = m + 1;
        }
        r = strncmp((char *)(e + 3), name, (s16)len);
        if (r == 0) {
            if ((s16)len == name_len) {
                return 2;
            }
            blen = len;
            found = e;
        } else if (r > 0) {
            if (strncmp((char *)(e + 3), name, name_len) == 0) {
                return 2;
            }
            break;
        }
    }
    if (blen == 0) {
        out->id = -1;
        return 0;
    }
    out->a = 0;
    out->id = NameRecordId_80591EC8(&lbl_80591EC8, found);
    out->len = blen;
    out->pre = pre;
    out->encodedRecord = found;
    return 1;
}

inline s32 RecordSize_803E8DA0(Req_803EEF2C *req) {
    s32 extra;
    if (req->x8 != 0 || req->x7 >= 0x2D) {
        extra = 3;
    } else {
        extra = 2;
    }
    return 3 + req->len + extra + TQuestVmDownLoadServer::calc_sjis_string_width(req->text);
}
inline void WriteRecord_803E8DA0(u8 *p, s32 size, Req_803EEF2C *req, u8 attr) {
    *p++ = size % 256;
    *p++ = size / 256;
    *p++ = req->len;
    strncpy((char *)p, req->name, req->len);
    p += req->len;
    *p++ = req->x7;
    *p++ = attr;
    if (req->x8 != 0 || req->x7 >= 0x2D) {
        *p++ = req->x8;
    }
    TQuestVmDownLoadServer::copy_sjis_string(req->text, p);
}
inline u8 *AllocRecord_80591EC8(s32 size) {
    u8 *p;
    if (lbl_805D7870 > lbl_805D786C - size - 2) {
        TQuestVmDownLoadServer__sub_803E95BC();
    }
    p = lbl_805D7870;
    lbl_805D7870 += size;
    lbl_805D7870[0] = 0;
    lbl_805D7870[1] = 0;
    return p;
}
s32 TQuestVmDownLoadServer__sub_803E8DA0(char *name, Req_803EEF2C *req, s32 attr) {
    NameCache_80591EC8 *cache;
    QuestDownloadCachedNameNode *n;
    QuestDownloadCachedNameNode *node;
    QuestDownloadCachedNameNode **link;
    u8 *e;
    s32 size;
    u8 *rec;
    lbl_805D7868 = 1;
    cache = &lbl_80591EC8;
    n = FindName_80591EC8(name, req->len, &link);
    e = n->encodedRecord;
    if (e[2] == req->len && strncmp(name, (char *)(e + 3), req->len) == 0) {
        e[2] = 0;
        *link = n->next;
        TQuestVmDownLoadServer::invalidate_entries_by_id(NameRecordId_80591EC8(cache, n->encodedRecord));
        n->next = lbl_805D7878;
        lbl_805D7878 = n;
    }
    if (lbl_805D7878 == NULL) {
        TQuestVmDownLoadServer__sub_803E95BC();
    }
    node = lbl_805D7878;
    lbl_805D7878 = node->next;
    size = RecordSize_803E8DA0(req);
    rec = AllocRecord_80591EC8(size);
    WriteRecord_803E8DA0(rec, size, req, attr);
    n = FindName_80591EC8(name, req->len, &link);
    node->encodedRecord = rec;
    node->next = n;
    *link = node;
    return 0;
}

void TQuestVmDownLoadServer::append_message_text(s32 size, Req_803EEF2C *msg, u8 attr) {
    u16 cur;
    s32 v;
    u8 *p;
    u8 *s;
    cur = ((u8 *)this)[0];
    cur += ((u8 *)this)[1] << 8;
    v = size + cur;
    ((u8 *)this)[0] = v % 256;
    ((u8 *)this)[1] = v / 256;
    p = ((u8 *)this) + cur;
    *p++ = msg->x7;
    *p++ = attr;
    if (msg->x8 != 0 || msg->x7 >= 0x2D) {
        *p++ = msg->x8;
    }
    s = msg->text;
    while (*s != 0) {
        if (IsSjisLead(*s)) {
            *p++ = *s++;
        } else {
            *p++ = 0xFF;
        }
        *p++ = *s++;
    }
}

inline void CopyText_803E9190(u8 *s, u8 *p) {
    while (*s != 0) {
        if (IsSjisLead(*s)) {
            *p++ = *s++;
        } else {
            *p++ = 0xFF;
        }
        *p++ = *s++;
    }
}
void build_message_packet__22TQuestVmDownLoadServerFPviPvUc(u8 *p, s32 size, Req_803EEF2C *msg, u8 attr) {
    u8 unused[8];
    *p++ = size % 256;
    *p++ = size / 256;
    *p++ = msg->len;
    strncpy((char *)p, msg->name, msg->len);
    p += msg->len;
    *p++ = msg->x7;
    *p++ = attr;
    if (msg->x8 != 0 || msg->x7 >= 0x2D) {
        *p++ = msg->x8;
    }
    CopyText_803E9190(msg->text, p);
}

s32 TQuestVmDownLoadServer::calc_text_length() {
    Req_803EEF2C *msg = (Req_803EEF2C *)this;
    s32 n;
    u8 *p;
    s32 extra;
    if (msg->x8 != 0 || msg->x7 >= 0x2D) {
        extra = 3;
    } else {
        extra = 2;
    }
    p = msg->text;
    n = 0;
    while (*p != 0) {
        if (IsSjisLead(*p)) {
            p += 2;
        } else {
            p += 1;
        }
        n += 2;
    }
    return extra + n;
}

s32 TQuestVmDownLoadServer::calc_message_length() {
    Req_803EEF2C *msg = (Req_803EEF2C *)this;
    s32 n;
    u8 *p;
    s32 extra;
    if (msg->x8 != 0 || msg->x7 >= 0x2D) {
        extra = 3;
    } else {
        extra = 2;
    }
    p = msg->text;
    n = 0;
    while (*p != 0) {
        if (IsSjisLead(*p)) {
            p += 2;
        } else {
            p += 1;
        }
        n += 2;
    }
    extra = msg->len + extra;
    n = extra + n;
    return n + 3;
}

#pragma push
#pragma opt_common_subs off
s32 TQuestVmDownLoadServer__sub_803E93DC(void) {
    u8 buf[0x50];
    QuestDownloadCachedNameNode *pc[2];
    NameCacheArea_80591EC8 *area = (NameCacheArea_80591EC8 *)&lbl_80591EC8;
    u8 *slot;
    u8 *p;
    s32 i;
    s16 len;
    s16 clen;
    u8 kind;
    s32 idx;
    s32 cmp;
    s16 unused;
    QuestDownloadCachedNameNode *n;
    QuestDownloadCachedNameNode **link;
    if (TQuestVmDownLoadServer::seek_or_reopen(0x1400) == -1) {
        return -1;
    }
    if (((TQuestVmDownLoadServer *)quest_download_file_handle)->aram_read_thunk((u32)lbl_80591EC8.pages, 0x2000) != 0x2000) {
        return -1;
    }
    slot = lbl_80591EC8.pages[0];
    for (i = 0; i < 8; i++) {
        for (p = slot; (u16)(p[0] + (p[1] << 8)) != 0; p += (u16)(p[0] + (p[1] << 8))) {
            len = (s16)p[2];
            if (len != 0) {
                strncpy((char *)buf, (char *)(p + 3), len);
                buf[len] = 0;
                pc[1] = NULL;
                kind = buf[0];
                if (kind >= 0xA0 && kind < 0xF0) {
                    idx = kind - 0xA0;
                } else {
                    idx = 0;
                }
                pc[0] = ((QuestDownloadCachedNameNode **)area->names.heads)[idx];
                while (pc[0] != NULL) {
                    clen = (s16)(pc[0]->encodedRecord[2] & 0xFFFFu);
                    cmp = strncmp((char *)(pc[0]->encodedRecord + 3), (char *)buf, clen);
                    if (cmp == 0) {
                        if (len == clen) {
                            break;
                        }
                    } else if (cmp > 0) {
                        break;
                    }
                    pc[1] = pc[0];
                    pc[0] = pc[0]->next;
                }

                if (pc[1] == NULL) {
                    QuestDownloadCachedNameNode **table = area->names.heads;
                    link = &table[idx];
                } else {
                    link = &pc[1]->next;
                }
                if (lbl_805D7878 == NULL) {
                    TQuestVmDownLoadServer__sub_803E95BC();
                }
                n = lbl_805D7878;
                lbl_805D7878 = n->next;
                n->encodedRecord = p;
                n->next = pc[0];
                *link = n;
            }
        }

        if (lbl_805D7874 == i) {
            lbl_805D7870 = p;
            lbl_805D786C = slot + 0x400;
        }
        slot += 0x400;
    }

    return 0;
}

#pragma pop

u8 *TQuestVmDownLoadServer::get_buffer_ptr(s32 id) {
    return &lbl_80591EC8.pages[(s16)(id >> 12)][(s16)(id & 0xFFF)];
}

#pragma push
#pragma opt_common_subs off
void TQuestVmDownLoadServer__sub_803E95BC(void) {
    u8 buf[0x50];
    NameCacheArea_80591EC8 *area = (NameCacheArea_80591EC8 *)&lbl_80591EC8;
    u8 *p;
    u8 len;
    u8 elen;
    s32 h;
    s32 r;
    QuestDownloadCachedNameNode *pc[2];
    QuestDownloadCachedNameNode **link;
    *lbl_805D7870++ = 0;
    *lbl_805D7870++ = 0;
    lbl_805D7874 = (lbl_805D7874 + 1) % 8;
    lbl_805D7870 = area->cache.pages[lbl_805D7874];
    lbl_805D786C = lbl_805D7870 + 0x400;
    p = lbl_805D7870;
    while ((u16)(p[0] + (p[1] << 8)) != 0) {
        len = p[2];
        if ((s16)len != 0) {
            strncpy((char *)buf, (char *)p + 3, (s16)len);
            buf[(s16)len] = 0;
            pc[1] = NULL;
            if (buf[0] >= 0xA0 && buf[0] < 0xF0) {
                h = buf[0] - 0xA0;
            } else {
                h = 0;
            }
            pc[0] = ((QuestDownloadCachedNameNode **)area->names.heads)[h];
            while (pc[0] != NULL) {
                elen = pc[pc[0]->encodedRecord[2] * 0]->encodedRecord[2];
                r = strncmp((char *)(pc[0]->encodedRecord + 3), (char *)buf, (s16)elen);
                if (r == 0) {
                    if ((s16)len == (s16)elen) {
                        break;
                    }
                } else if (r > 0) {
                    break;
                }
                pc[1] = pc[0];
                pc[0] = pc[0]->next;
            }

            if (pc[1] == NULL) {
                link = (QuestDownloadCachedNameNode **)area->names.heads + h;
            } else {
                link = &pc[1]->next;
            }
            if (pc[0]->encodedRecord == p) {
                *link = pc[0]->next;
                pc[0]->next = lbl_805D7878;
                lbl_805D7878 = pc[0];
            }
        }
        p += (u16)(p[0] + (p[1] << 8));
    }

    TQuestVmDownLoadServer::clear_entries_by_id(lbl_805D7874);
}

#pragma pop

void TQuestVmDownLoadServer__sub_803E9764(void) {
    if (lbl_805D7868 != 0) {
        if (TQuestVmDownLoadServer::seek_or_reopen(0x1400) != -1) {
            TQuestVmDownLoadServer__sub_803E8788(quest_download_file_handle, lbl_80591EC8.pages, 0x2000);
        }
    }
}

void __VIRetraceHandler(void) {
    NameCacheArea_80591EC8 *area = (NameCacheArea_80591EC8 *)&lbl_80591EC8;
    QuestDownloadCachedNameNode *n = area->names.nodes;
    QuestDownloadCachedNameNode *end = &area->names.nodes[0x1FF];
    s32 unused[6];

    while (n < end) {
        n->next = n + 1;
        n++;
    }
    n->next = NULL;
    lbl_805D7878 = area->names.nodes;
    area->names.heads[0] = NULL;
    area->names.heads[1] = NULL;
    area->names.heads[2] = NULL;
    area->names.heads[3] = NULL;
    area->names.heads[4] = NULL;
    area->names.heads[5] = NULL;
    area->names.heads[6] = NULL;
    area->names.heads[7] = NULL;
    area->names.heads[8] = NULL;
    area->names.heads[9] = NULL;
    area->names.heads[10] = NULL;
    area->names.heads[11] = NULL;
    area->names.heads[12] = NULL;
    area->names.heads[13] = NULL;
    area->names.heads[14] = NULL;
    area->names.heads[15] = NULL;
    area->names.heads[16] = NULL;
    area->names.heads[17] = NULL;
    area->names.heads[18] = NULL;
    area->names.heads[19] = NULL;
    area->names.heads[20] = NULL;
    area->names.heads[21] = NULL;
    area->names.heads[22] = NULL;
    area->names.heads[23] = NULL;
    area->names.heads[24] = NULL;
    area->names.heads[25] = NULL;
    area->names.heads[26] = NULL;
    area->names.heads[27] = NULL;
    area->names.heads[28] = NULL;
    area->names.heads[29] = NULL;
    area->names.heads[30] = NULL;
    area->names.heads[31] = NULL;
    area->names.heads[32] = NULL;
    area->names.heads[33] = NULL;
    area->names.heads[34] = NULL;
    area->names.heads[35] = NULL;
    area->names.heads[36] = NULL;
    area->names.heads[37] = NULL;
    area->names.heads[38] = NULL;
    area->names.heads[39] = NULL;
    area->names.heads[40] = NULL;
    area->names.heads[41] = NULL;
    area->names.heads[42] = NULL;
    area->names.heads[43] = NULL;
    area->names.heads[44] = NULL;
    area->names.heads[45] = NULL;
    area->names.heads[46] = NULL;
    area->names.heads[47] = NULL;
    area->names.heads[48] = NULL;
    area->names.heads[49] = NULL;
    area->names.heads[50] = NULL;
    area->names.heads[51] = NULL;
    area->names.heads[52] = NULL;
    area->names.heads[53] = NULL;
    area->names.heads[54] = NULL;
    area->names.heads[55] = NULL;
    area->names.heads[56] = NULL;
    area->names.heads[57] = NULL;
    area->names.heads[58] = NULL;
    area->names.heads[59] = NULL;
    area->names.heads[60] = NULL;
    area->names.heads[61] = NULL;
    area->names.heads[62] = NULL;
    area->names.heads[63] = NULL;
    area->names.heads[64] = NULL;
    area->names.heads[65] = NULL;
    area->names.heads[66] = NULL;
    area->names.heads[67] = NULL;
    area->names.heads[68] = NULL;
    area->names.heads[69] = NULL;
    area->names.heads[70] = NULL;
    area->names.heads[71] = NULL;
    area->names.heads[72] = NULL;
    area->names.heads[73] = NULL;
    area->names.heads[74] = NULL;
    area->names.heads[75] = NULL;
    area->names.heads[76] = NULL;
    area->names.heads[77] = NULL;
    area->names.heads[78] = NULL;
    area->names.heads[79] = NULL;

    if (TQuestVmDownLoadServer__sub_803E93DC() == -1) {
        u8 *page1 = area->cache.pages[1];
        area->cache.pages[0][1] = 0;
        area->cache.pages[0][0] = 0;
        page1[1] = 0;
        page1[0] = 0;
        area->cache.pages[2][1] = 0;
        area->cache.pages[2][0] = 0;
        area->cache.pages[3][1] = 0;
        area->cache.pages[3][0] = 0;
        area->cache.pages[4][1] = 0;
        area->cache.pages[4][0] = 0;
        area->cache.pages[5][1] = 0;
        area->cache.pages[5][0] = 0;
        area->cache.pages[6][1] = 0;
        area->cache.pages[6][0] = 0;
        area->cache.pages[7][1] = 0;
        area->cache.pages[7][0] = 0;
        lbl_805D7874 = 0;
        lbl_805D7870 = area->cache.pages[0];
        lbl_805D786C = page1;
    }
    lbl_805D7868 = 0;
}

}
