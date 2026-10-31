#ifndef PSO_MISC_TWINDOWDRAWCONTEXT_H
#define PSO_MISC_TWINDOWDRAWCONTEXT_H

// The draw-context layout remains opaque at the shared call boundary.
struct TWindowDrawContext;
extern "C" TWindowDrawContext *get_draw_context__11TWindowBaseFPv(void *window);

#endif
