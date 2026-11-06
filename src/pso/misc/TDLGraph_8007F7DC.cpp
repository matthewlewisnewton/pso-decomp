#include "types.h"
#include "pso/misc/TDLGraph_8007F7DC.h"
#include "pso/misc/TDLGraph.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern const f32 lbl_805D9298;
extern s32 __vt__8TDLGraph[];
extern void *TDLGraph__class_name;
extern void * TDLGraph__graph_object;

void *TDLGraph__ct(TDLGraph *dl_graph) {
    __ct__7TObjectFP7TObject(dl_graph);
    *(s32 **)((s8 *)dl_graph + 0x18) = __vt__8TDLGraph;
    *(void * *)&dl_graph->m_name = TDLGraph__class_name;
    *(f32 *)((s8 *)dl_graph + 0x1C) = lbl_805D9298;
    dl_graph->m_24 = 0;
    dl_graph->m_28 = -1;
    dl_graph->m_2c = -1;
    dl_graph->m_30 = -1;
    dl_graph->sub_8007F644();
    dl_graph->init_dl_graph_entries();
    dl_graph->m_20 = 3;
    TDLGraph__graph_object = dl_graph;
    return dl_graph;
}

}
