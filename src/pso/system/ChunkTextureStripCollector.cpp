#include "pso/system/ChunkTextureStripCollector.h"

extern "C" {
StripReference *plist_strip_write_ptr;
s16 *plist_strip_uv_write_ptr;
s32 plist_texture_matches_filter;

void collect_model_strips_by_texture(StripBufferPair *ctx, NJS_OBJECT *node, s32 texture) {
    do {
        if (node->model != 0 && ((NJS_CNK_MODEL *)node->model)->polygon_list != 0) {
            collect_plist_strips_by_texture(ctx, ((NJS_CNK_MODEL *)node->model)->polygon_list, texture);
        }
        if (node->child != 0) {
            collect_model_strips_by_texture(ctx, node->child, texture);
        }
        node = node->sibling;
    } while (node != 0);
}
}

void collect_plist_strips_by_texture(StripBufferPair *ctx, s16 *p, s32 tex) {
    s16 c;
    s16 type;
    u32 n;
    u32 i;
    s16 len;
    s32 k;
    while ((c = *p++) != 0xFF) {
        if ((c & 0xFF) < 8) {
            continue;
        }
        type = c & 0xFF;
        if (type < 0x10) {
            if ((*p++ & 0x1FFF) == tex) {
                plist_texture_matches_filter = 1;
            } else {
                plist_texture_matches_filter = 0;
            }
        } else if (type < 0x40) {
            s32 skip = *(u16 *) p;
            p++;
            p += skip;
        } else {
            s32 skip = *(u16 *) p;
            p++;
            if (plist_texture_matches_filter != 0 && type == 0x41) {
                plist_strip_write_ptr->strip = p;
                plist_strip_write_ptr->uv = plist_strip_uv_write_ptr;
                plist_strip_write_ptr++;
                n = *p++ & 0x3FFF;
                for (i = 0; i < n; i++) {
                    len = *p++;
                    if (len < 0) {
                        len = -len;
                    }
                    for (k = 0; k < len; k++) {
                        *plist_strip_uv_write_ptr++ = p[1];
                        *plist_strip_uv_write_ptr++ = p[2];
                        p += 3;
                    }
                }
            } else {
                p += skip;
            }
        }
    }
}

void count_model_strips_by_texture(StripBufferPair *ctx, NJS_OBJECT *node, s32 texture) {
    do {
        if (node->model != 0 && ((NJS_CNK_MODEL *)node->model)->polygon_list != 0) {
            count_plist_strips_by_texture(ctx, ((NJS_CNK_MODEL *)node->model)->polygon_list, texture);
        }
        if (node->child != 0) {
            count_model_strips_by_texture(ctx, node->child, texture);
        }
        node = node->sibling;
    } while (node != 0);
}
void count_plist_strips_by_texture(StripBufferPair *cnt, s16 *p, s32 texture) {
    s16 c;
    s32 skip;
    u32 n;
    u32 i;
    s16 len;
    while ((c = *p++) != 0xFF) {
        if ((c & 0xFF) < 8) {
            continue;
        }
        c = c & 0xFF;
        if (c < 0x10) {
            if ((*p++ & 0x1FFF) == texture) {
                plist_texture_matches_filter = 1;
            } else {
                plist_texture_matches_filter = 0;
            }
        } else if (c < 0x40) {
            skip = *(u16 *) p;
            p++;
            p += skip;
        } else {
            s32 size = *(u16 *) p;
            p++;
            if (plist_texture_matches_filter != 0 && c == 0x41) {
                cnt->strip_count++;
                n = *p++ & 0x3FFF;
                for (i = 0; i < n; i++) {
                    len = *p++;
                    if (len < 0) {
                        len = -len;
                    }
                    cnt->uv_count += len;
                    p += len * 3;
                }
            } else {
                p += size;
            }
        }
    }
}
