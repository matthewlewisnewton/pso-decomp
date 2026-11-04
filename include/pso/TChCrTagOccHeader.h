#ifndef PSO_TCHCRTAGOCCHEADER_H
#define PSO_TCHCRTAGOCCHEADER_H
#include "pso/TChCrTag.h"
#include "types.h"

class TChCrTagOccHeader : public TChCrTag {
public:
    virtual ~TChCrTagOccHeader();
    virtual void run_task();
    virtual void render();
};

void create_all_ch_cr_tag_headers(void);
void *create_ch_cr_tag_occ_header(void *arg0);

#endif
