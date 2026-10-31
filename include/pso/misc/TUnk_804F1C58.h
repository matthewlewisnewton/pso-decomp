#ifndef PSO_MISC_TUNK_804F1C58_H
#define PSO_MISC_TUNK_804F1C58_H
#include "types.h"
#include "pso/TObject.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
struct NJS_MOTION;

class TUnk_804F1C58 : public TObject {
public:
    virtual ~TUnk_804F1C58();
    void *destroy(s16);
    NJS_OBJECT *root;
    NJS_MOTION *motion;
    f32 frame;
    void * m_28;
    s32 node_count;
    s32 m_30;
    ChunkModelNodeCallback draw_callback;
    ChunkModelNodeCallback capture_callback;
    void set_capture_callback(ChunkModelNodeCallback);
    void apply_with_callback(NJS_MOTION *, f32);
    void draw_node_tree(NJS_OBJECT *);
    void draw_node_tree_if_visible();
};
typedef char TUnk_804F1C58_size[sizeof(TUnk_804F1C58) == 0x3C ? 1 : -1];

#endif
