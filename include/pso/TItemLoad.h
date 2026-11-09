#ifndef PSO_TITEMLOAD_H
#define PSO_TITEMLOAD_H
#include "pso/TObject.h"
#include "types.h"

class TItemLoad : public TObject {
public:
    virtual ~TItemLoad();
    virtual void run_task();
public:
    void clear_slots();
    static void update_all();
    static void free_all_models();
    static s32 decompress_buffer(u32 arg0);
    static void free_boss4_rock();
    static void alloc_work_buffer();
    static s32 has_resource_id(s32 id);
    static void get_data_entry(s32 arg0, s32 *arg1);
    static void lookup_item_data(s32 arg0, s32 *arg1);
    static void get_item_params(s32 *arg0, s32 *arg1, s32 *arg2);
    static void get_model_ids(u8 arg0, s32 *arg1, s32 *arg2);
    static void *find_node_by_id(s32 id);
    static void release_resource_by_id(s32 id);
    static void update();
    static void free_all();
    static void init_resources();
    static void create();
};

#endif
