#ifndef PSO_UNK_TEXT_803CE568_H
#define PSO_UNK_TEXT_803CE568_H

#include "types.h"

struct CvFsHandle;
typedef void (*CvFsErrorCallback)(s32 context, const char *message, s32 handle);

extern "C" {
extern CvFsErrorCallback cvfs_completion_callback;
extern s32 lbl_805D75FC;

s32 cvFsGetFileSizeEx(const char *path, s32 mode);
s32 cvFsGetFileSize(const char *path);
CvFsHandle *cvFsOpen(const char *path, s32 mode, s32 extra);
void cvFsEntryErrFunc(CvFsErrorCallback callback, s32 context);
void cvfs_forward_error(s32 context, const char *message, s32 handle);

void SIGetTypeAsync(void);
void TLobby__sub_803CEF60(void);
s32 find_803CF958(char *s, s32 len);
}

#endif
