#ifndef PSO_MISC_TWINDOWSHORTCUT_H
#define PSO_MISC_TWINDOWSHORTCUT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowShortCut : public TWindowBase {
    TWindowShortCut(void *position, s32 index, void *shortcut);
    virtual ~TWindowShortCut();
    virtual void render();
    virtual void run_task();
    void *m_60; // Owned opaque heading; legacy initializer/release protocol.
    TWindowBase *m_64; // Optional message window, released through close().
    TWindowBase *m_68; // Optional symbol window, released through close().
    s32 m_6c;
    void *m_70; // Borrowed shortcut record.
};

typedef char TWindowShortCut_size[sizeof(TWindowShortCut) == 0x74 ? 1 : -1];
typedef char ShortCut_heading[offsetof(TWindowShortCut, m_60) == 0x60 ? 1 : -1];
typedef char ShortCut_message[offsetof(TWindowShortCut, m_64) == 0x64 ? 1 : -1];
typedef char ShortCut_symbol[offsetof(TWindowShortCut, m_68) == 0x68 ? 1 : -1];
typedef char ShortCut_record[offsetof(TWindowShortCut, m_70) == 0x70 ? 1 : -1];

#endif
