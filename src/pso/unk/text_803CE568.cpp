#include "types.h"
#include "pso/unk/text_803CE568.h"
#include "pso/misc/TLobby.h"

struct Ent_803CF958 { u32 a; char name[12]; };

struct CvFsDevVtbl {
    u8 pad0[8];
    s32 (*get_file_size)(char *);
    u8 padC[4];
    void *(*open)(char *, s32, s32);
    void (*close)(void *);
    u8 pad18[0x5C - 0x18];
    s32 (*get_file_size_ex)(char *, s32);
    s32 (*query)(s32, s32, s32, s32);
};

struct CvFsHandle {
    CvFsDevVtbl *vtbl;
    void *fd;
};

struct Drv_803CFD2C {
    u8 pad[0x14];
    void (*close)(s32);
};
struct Slot_803CFD2C {
    Drv_803CFD2C *drv;
    s32 handle;
};
struct Rec_803CFD2C {
    u8 pad0[4];
    s8 used;
    u8 pad5[0xB];
};

struct V_803CEF60 { void (*fn)(); };

extern "C" {
s32 strncmp(void *, void *, int);
void *memcpy(void *, void *, u32);
u32 strlen(void *);
extern s8 fs_default_device_name[];
extern Ent_803CF958 cvfs_entry_table[];
void *memset(void *, s32, u32);
extern s32 lbl_805D7600;
extern u32 lbl_80581A30[75];
extern CvFsHandle si_type_info_table[40];
char *strcpy(char *, const char *);
int sprintf(char *, const char *, ...);
// CVFS/GC version and diagnostic catalog. The inactive API diagnostics
// remain data; they do not require invented implementations of stripped routines.
static const char cvfs_version[] = "\nCVFS/GC Ver.2.24 Build:Jun 13 2002 19:00:27\n";
static const char cvfs_set_def_vol_error_1[] = "cvFsSetDefVol #1:illegal device name";
static const char cvfs_set_def_vol_error_2[] = "cvFsSetDefVol #2:illegal volume name";
static const char cvfs_set_def_vol_error_3[] = "cvFsSetDefVol #3:device not found";
static const char cvfs_get_volume_info_error_1[] = "cvFsGetVolumeInfo #1:illegal device name";
static const char cvfs_get_volume_info_error_2[] = "cvFsGetVolumeInfo #2:illegal volume name";
static const char cvfs_get_volume_info_error_3[] = "cvFsGetVolumeInfo #3:device not found";
static const char cvfs_del_volume_error_1[] = "cvFsDelVolume #1:illegal device name";
static const char cvfs_del_volume_error_2[] = "cvFsDelVolume #2:illegal volume name";
static const char cvfs_del_volume_error_3[] = "cvFsDelVolume #3:device not found";
static const char cvfs_add_volume_error_1[] = "cvFsAddVolume #1:illegal device name";
static const char cvfs_add_volume_error_2[] = "cvFsAddVolume #2:illegal volume name";
static const char cvfs_add_volume_error_3[] = "cvFsAddVolume #3:illegal image handle";
static const char cvfs_add_volume_error_3_device_not_found[] = "cvFsAddVolume #3:device not found";
static const char cvfs_set_cur_volume_error_1[] = "cvFsSetCurVolume #1:illegal device name";
static const char cvfs_set_cur_volume_error_2[] = "cvFsSetCurVolume #2:illegal image handle";
static const char cvfs_set_cur_volume_error_3[] = "cvFsSetCurVolume #3:device not found";
static const char cvfs_opt_fn2_error_1[] = "cvFsOptFn2 #1:handle error";
static const char cvfs_opt_fn2_error_2[] = "cvFsOptFn2 #2:vtbl error";
static const char cvfs_opt_fn1_error_1[] = "cvFsOptFn1 #1:handle error";
static const char cvfs_opt_fn1_error_2[] = "cvFsOptFn1 #2:vtbl error";
static const char cvfs_get_dev_name_error_1[] = "cvFsGetDevName #1:vtbl error";
static const char cvfs_delete_file_error_1[] = "cvFsDeleteFile #1:illegal file name";
static const char cvfs_delete_file_error_2[] = "cvFsDeleteFile #2:illegal device name";
static const char cvfs_delete_file_error_3[] = "cvFsDeleteFile #3:device not found";
static const char cvfs_delete_file_error_4[] = "cvFsDeleteFile #4:vtbl error";
static const char cvfs_remove_dir_error_1[] = "cvFsRemoveDir #1:illegal directory name";
static const char cvfs_remove_dir_error_2[] = "cvFsRemoveDir #2:illegal device name";
static const char cvfs_remove_dir_error_3[] = "cvFsRemoveDir #3:device not found";
static const char cvfs_remove_dir_error_4[] = "cvFsRemoveDir #4:vtbl error";
static const char cvfs_make_dir_error_1[] = "cvFsMakeDir #1:illegal directory name";
static const char cvfs_make_dir_error_2[] = "cvFsMakeDir #2:illegal device name";
static const char cvfs_make_dir_error_3[] = "cvFsMakeDir #3:device not found";
static const char cvfs_make_dir_error_4[] = "cvFsMakeDir #4:vtbl error";
static const char cvfs_get_max_byte_rate_error_1[] = "cvFsGetMaxByteRate #1:handle error";
static const char cvfs_get_max_byte_rate_error_2[] = "cvFsGetMaxByteRate #2:vtbl error";
static const char cvfs_is_exist_file_error_2[] = "cvFsIsExistFile #2:illegal device name";
static const char cvfs_is_exist_file_error_1[] = "cvFsIsExistFile #1:illegal file name";
static const char cvfs_is_exist_file_error_3[] = "cvFsIsExistFile #3:device not found";
static const char cvfs_is_exist_file_error_4[] = "cvFsIsExistFile #4:vtbl error";
static const char cvfs_change_dir_error_1[] = "cvFsChangeDir #1:illegal directory name";
static const char cvfs_change_dir_error_2[] = "cvFsChangeDir #2:illegal device name";
static const char cvfs_change_dir_error_3[] = "cvFsChangeDir #3:device not found";
static const char cvfs_change_dir_error_4[] = "cvFsChangeDir #4:vtbl error";
static const char cvfs_get_num_tr_error_1[] = "cvFsGetNumTr #1:handle error";
static const char cvfs_get_num_tr_error_2[] = "cvFsGetNumTr #2:vtbl error";
static const char cvfs_set_sct_len_error_3[] = "cvFsSetSctLen #3:handle error";
static const char cvfs_set_sct_len_error_4[] = "cvFsSetSctLen #4:vtbl error";
static const char cvfs_get_sct_len_error_1[] = "cvFsGetSctLen #1:handle error";
static const char cvfs_get_sct_len_error_2[] = "cvFsGetSctLen #2:vtbl error";
static const char cvfs_get_free_size_error_5[] = "cvFsGetFreeSize #5:device not found";
static const char cvfs_get_free_size_error_6[] = "cvFsGetFreeSize #6:vtbl error";
static const char cvfs_get_file_size_ex_error_1[] = "cvFsGetFileSizeEx #1:illegal file name";
static const char cvfs_get_file_size_ex_error_2[] = "cvFsGetFileSizeEx #2:illegal device name";
static const char cvfs_get_file_size_ex_error_3[] = "cvFsGetFileSizeEx #3:device not found";
static const char cvfs_get_file_size_ex_error_4[] = "cvFsGetFileSizeEx #4:vtbl error";
static const char cvfs_get_file_size_error_1[] = "cvFsGetFileSize #1:illegal file name";
static const char cvfs_get_file_size_error_2[] = "cvFsGetFileSize #2:illegal device name";
static const char cvfs_get_file_size_error_3[] = "cvFsGetFileSize #3:device not found";
static const char cvfs_get_file_size_error_4[] = "cvFsGetFileSize #4:vtbl error";
static const char cvfs_get_stat_error_1[] = "cvFsGetStat #1:handle error";
static const char cvfs_get_stat_error_2[] = "cvFsGetStat #2:vtbl error";
static const char cvfs_stop_tr_error_1[] = "cvFsStopTr #1:handle error";
static const char cvfs_stop_tr_error_2[] = "cvFsStopTr #2:vtbl error";
static const char cvfs_req_wr_error_1[] = "cvFsReqWr #1:handle error";
static const char cvfs_req_wr_error_2[] = "cvFsReqWr #2:vtbl error";
static const char cvfs_req_rd_error_1[] = "cvFsReqRd #1:handle error";
static const char cvfs_req_rd_error_2[] = "cvFsReqRd #2:vtbl error";
static const char cvfs_seek_error_1[] = "cvFsSeek #1:handle error";
static const char cvfs_seek_error_2[] = "cvFsSeek #2:vtbl error";
static const char cvfs_tell_error_1[] = "cvFsTell #1:handle error";
static const char cvfs_tell_error_2[] = "cvFsTell #2:vtbl error";
static const char cvfs_close_error_1[] = "cvFsClose #1:handle error";
static const char cvfs_close_error_2[] = "cvFsClose #2:vtbl error";
static const char cvfs_open_error_1[] = "cvFsOpen #1:illegal file name";
static const char cvfs_open_error_3[] = "cvFsOpen #3:failed handle alloced";
static const char cvfs_open_error_2[] = "cvFsOpen #2:illegal device name";
static const char cvfs_open_error_4[] = "cvFsOpen #4:device not found";
static const char cvfs_open_error_5[] = "cvFsOpen #5:vtbl error";
static const char cvfs_open_error_6[] = "cvFsOpen #6:open failed";
static const char cvfs_set_def_dev_error_1[] = "cvFsSetDefDev #1:illegal device name";
static const char cvfs_set_def_dev_error_2[] = "cvFsSetDefDev #2:unknown device name";
static const char cvfs_del_dev_error_1[] = "cvFsDelDev #1:illegal device name";
static const char cvfs_add_dev_error_1[] = "cvFsAddDev #1:illegal device name";
static const char cvfs_add_dev_error_2[] = "cvFsAddDev #2:illegal I/F func name";
static const char cvfs_add_dev_error_3[] = "cvFsAddDev #3:failed added a device";

const char *const volatile lbl_805E0DA0 = cvfs_version;
// The small-data slot stores this format and two null tail bytes.
const char lbl_805E0DA4[8] = "%s:%s";

u32 lbl_80581A30[75];
s8 fs_default_device_name[12];
Ent_803CF958 cvfs_entry_table[32];
CvFsHandle si_type_info_table[40];

#pragma dont_inline off
#pragma inline_depth(4)

inline void cvfs_error(const char *message) {
    if (cvfs_completion_callback != NULL) {
        cvfs_completion_callback(lbl_805D75FC, message, 0);
    }
}

// Path/device helpers and the three live file routines are adapted from
// zeroz41/pso-decomp ae797d392bb93d5bf7164341870f78f864da23b0.
inline void cvfs_split_path(char *dev, char *file, const char *path) {
    s32 i;
    s32 j;
    if (path == NULL) {
        return;
    }
    for (i = 0; i < 297; i++) {
        if (path[i] == ':' || path[i] == '\0') {
            break;
        }
        dev[i] = path[i];
    }
    if (path[i] == '\0') {
        dev[i] = '\0';
        memcpy(file, dev, strlen(dev) + 1);
        dev[0] = '\0';
    } else {
        u32 k;
        u32 n;
        dev[i] = '\0';
        i++;
        if (i == 2) {
            i = 0;
            dev[0] = '\0';
        }
        s32 end = i;
        for (j = i; j < 297; j++) {
            if (path[j] == '\0') {
                break;
            }
            file[end++ - i] = path[j];
        }
        file[end - i] = '\0';
        n = strlen(dev) + 1;
        for (k = 0; k < n; k++) {
            if (dev[k] >= 'a' && dev[k] <= 'z') {
                dev[k] -= 0x20;
            }
        }
    }
}

// Copies the default device name into dev and returns dev (like strcpy).
inline char *cvfs_get_default_device(char *dev) {
    s32 len = strlen(fs_default_device_name);
    if (fs_default_device_name[0] == '\0') {
        dev[0] = '\0';
    } else {
        memcpy(dev, fs_default_device_name, len + 1);
    }
    return dev;
}

inline CvFsDevVtbl *cvfs_lookup_device(char *name) {
    u32 i;
    s32 len = strlen(name);
    for (i = 0; i < 32; i++) {
        if (strncmp(name, cvfs_entry_table[i].name, len) == 0) {
            return (CvFsDevVtbl *)cvfs_entry_table[i].a;
        }
    }
    return NULL;
}

inline void cvfs_add_device_prefix(char *dev, char *file) {
    CvFsDevVtbl *vtbl;
    s32 need;
    if (dev == NULL) {
        dev = (char *)fs_default_device_name;
    }
    vtbl = cvfs_lookup_device(dev);
    if (vtbl == NULL) {
        need = 0;
    } else if (vtbl->query != NULL) {
        need = vtbl->query(0, 100, 0, 0);
    } else {
        need = 0;
    }
    if (need == 1) {
        strcpy((char *)lbl_80581A30, file);
        sprintf(file, lbl_805E0DA4, dev, (char *)lbl_80581A30);
    }
}

inline CvFsDevVtbl *cvfs_get_device(char *dev, char *file, const char *path) {
    CvFsDevVtbl *vtbl;
    if (dev[0] == '\0') {
        dev = cvfs_get_default_device(dev);
        if (dev[0] == '\0') {
            return NULL;
        }
    }
    cvfs_add_device_prefix(dev, file);
    vtbl = cvfs_lookup_device(dev);
    if (vtbl == NULL) {
        cvfs_get_default_device(dev);
        vtbl = cvfs_lookup_device(dev);
        if (vtbl == NULL) {
            return NULL;
        }
        strcpy(file, path);
    }
    return vtbl;
}

inline void *cvfs_alloc_handle(void) {
    s32 i;
    CvFsHandle *h;
    for (i = 0; i < 40; i++) {
        if (si_type_info_table[i].fd == NULL) {
            break;
        }
    }
    h = &si_type_info_table[i];
    if (i == 40) {
        h = NULL;
    }
    return h;
}

inline void cvfs_free_handle(CvFsHandle *h) {
    h->fd = NULL;
    h->vtbl = NULL;
}

s32 cvFsGetFileSizeEx(const char *path, s32 arg) {
    char dev[300];
    char file[300];
    CvFsDevVtbl *vtbl;

    if (path == NULL) {
        cvfs_error(cvfs_get_file_size_ex_error_1);
        return 0;
    }
    cvfs_split_path(dev, file, path);
    if (file[0] == '\0') {
        cvfs_error(cvfs_get_file_size_ex_error_1);
        return 0;
    }
    vtbl = cvfs_get_device(dev, file, path);
    if (dev == NULL) {
        cvfs_error(cvfs_get_file_size_ex_error_2);
    }
    if (vtbl == NULL) {
        cvfs_error(cvfs_get_file_size_ex_error_3);
    }
    if (vtbl->get_file_size_ex != NULL) {
        return vtbl->get_file_size_ex(file, arg);
    }
    cvfs_error(cvfs_get_file_size_ex_error_4);
    return 0;
}
s32 cvFsGetFileSize(const char *path) {
    char dev[300];
    char file[300];
    CvFsDevVtbl *vtbl;

    if (path == NULL) {
        cvfs_error(cvfs_get_file_size_error_1);
        return 0;
    }
    cvfs_split_path(dev, file, path);
    if (file[0] == '\0') {
        cvfs_error(cvfs_get_file_size_error_1);
        return 0;
    }
    vtbl = cvfs_get_device(dev, file, path);
    if (dev == NULL) {
        cvfs_error(cvfs_get_file_size_error_2);
    }
    if (vtbl == NULL) {
        cvfs_error(cvfs_get_file_size_error_3);
    }
    if (vtbl->get_file_size != NULL) {
        return vtbl->get_file_size(file);
    }
    cvfs_error(cvfs_get_file_size_error_4);
    return 0;
}

s32 TLobby::cv_fs_get_stat() {
    u8 *arg0 = (u8 *)this;
    s32 (*temp_r12)(s32);
    s32 var_r31;
    var_r31 = 3;
    if (arg0 == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_get_stat_error_1, 0);
        }
        return 3;
    }
    temp_r12 = *(s32 (**)(s32))((s8 *)(*(u8 * *)&this->m_name) + 0x2C);
    if (temp_r12 != NULL) {
        var_r31 = temp_r12(*(s32 *)&this->m_flags);
    } else if (cvfs_completion_callback != NULL) {
        cvfs_completion_callback(lbl_805D75FC, cvfs_get_stat_error_2, 0);
    }
    return var_r31;
}

void TLobby__sub_803CEF60(void) {
    s32 i;
    Ent_803CF958 *p;
    for (i = 0; i < 0x20; i++) {
        p = &cvfs_entry_table[i];
        if ((V_803CEF60 *)p->a != 0 && ((V_803CEF60 *)p->a)->fn != 0) {
            ((V_803CEF60 *)p->a)->fn();
        }
    }
}

void TLobby::cvfs_stop_tr() {
    u8 *arg0 = (u8 *)this;
    s32 (*temp_r12)(s32);
    if (arg0 == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_stop_tr_error_1, 0);
        }
    } else {
        temp_r12 = *(s32 (**)(s32))((s8 *)(*(u8 * *)&this->m_name) + 0x28);
        if (temp_r12 != NULL) {
            temp_r12(*(s32 *)&this->m_flags);
            return;
        }
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_stop_tr_error_2, 0);
        }
    }
}

s32 TLobby::cv_fs_req_rd(s32 error_context, s32 arg2) {
    u8 *arg0 = (u8 *)this;
    s32 (*temp_r12)(s32, s32, s32);
    s32 var_r31;
    if (arg0 == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_req_rd_error_1, 0);
        }
        return 0;
    }
    temp_r12 = *(s32 (**)(s32, s32, s32))((s8 *)(*(u8 * *)&this->m_name) + 0x20);
    if (temp_r12 != NULL) {
        var_r31 = temp_r12(*(s32 *)&this->m_flags, error_context, arg2);
    } else {
        var_r31 = 0;
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_req_rd_error_2, 0);
        }
    }
    return var_r31;
}

s32 TLobby::cv_fs_seek(s32 error_context, s32 arg2) {
    u8 *arg0 = (u8 *)this;
    s32 (*temp_r12)(s32, s32, s32);
    s32 var_r31;
    if (arg0 == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_seek_error_1, 0);
        }
        return 0;
    }
    temp_r12 = *(s32 (**)(s32, s32, s32))((s8 *)(*(u8 * *)&this->m_name) + 0x18);
    if (temp_r12 != NULL) {
        var_r31 = temp_r12(*(s32 *)&this->m_flags, error_context, arg2);
    } else {
        var_r31 = 0;
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_seek_error_2, 0);
        }
    }
    return var_r31;
}

s32 TLobby::cv_fs_tell() {
    u8 *arg0 = (u8 *)this;
    s32 (*temp_r12)(s32);
    s32 var_r31;
    if (arg0 == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_tell_error_1, 0);
        }
        return 0;
    }
    temp_r12 = *(s32 (**)(s32))((s8 *)(*(u8 * *)&this->m_name) + 0x1C);
    if (temp_r12 != NULL) {
        var_r31 = temp_r12(*(s32 *)&this->m_flags);
    } else {
        var_r31 = 0;
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_tell_error_2, 0);
        }
    }
    return var_r31;
}
void TLobby::cv_fs_close() {
    u8 *arg0 = (u8 *)this;
    s32 (*temp_r12)(s32);
    if (arg0 == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_close_error_1, 0);
        }
    } else {
        temp_r12 = *(s32 (**)(s32))((s8 *)(*(u8 * *)&this->m_name) + 0x14);
        if (temp_r12 != NULL) {
            temp_r12(*(s32 *)&this->m_flags);
            *(s32 *)&this->m_flags = 0;
            *(u8 * *)&this->m_name = NULL;
            return;
        }
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_close_error_2, 0);
        }
    }
}
CvFsHandle *cvFsOpen(const char *path, s32 mode, s32 arg) {
    char dev[300];
    char file[300];
    CvFsDevVtbl *vtbl;
    CvFsHandle *h;

    if (path == NULL) {
        cvfs_error(cvfs_open_error_1);
        return NULL;
    }
    cvfs_split_path(dev, file, path);
    if (file[0] == '\0') {
        cvfs_error(cvfs_open_error_1);
        return NULL;
    }
    h = (CvFsHandle *)cvfs_alloc_handle();
    if (h == NULL) {
        cvfs_error(cvfs_open_error_3);
        return NULL;
    }
    vtbl = cvfs_get_device(dev, file, path);
    h->vtbl = vtbl;
    if (dev == NULL) {
        cvfs_free_handle(h);
        cvfs_error(cvfs_open_error_2);
        return NULL;
    }
    if (h->vtbl == NULL) {
        cvfs_free_handle(h);
        cvfs_error(cvfs_open_error_4);
        return NULL;
    }
    if (h->vtbl->open != NULL) {
        h->fd = h->vtbl->open(file, mode, arg);
    } else {
        cvfs_free_handle(h);
        cvfs_error(cvfs_open_error_5);
        return NULL;
    }
    if (h->fd == NULL) {
        cvfs_free_handle(h);
        cvfs_error(cvfs_open_error_6);
        return NULL;
    }
    return h;
}

inline s32 find_803CF958(char *s, s32 len) {
    Ent_803CF958 *p;
    s32 i;
    for (p = cvfs_entry_table, i = 0; i < 32; i++, p++) {
        if (strncmp(s, p->name, len) == 0) {
            return 1;
        }
    }
    return 0;
}
void TLobby::cvFsSetDefDev() {
    char *arg0 = (char *)this;
    s32 len;
    u32 j;
    u32 n;
    if (arg0 == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_set_def_dev_error_1, 0);
        }
        return;
    }
    len = strlen(arg0);
    if (len == 0) {
        fs_default_device_name[0] = 0;
        return;
    }
    n = strlen(arg0) + 1;
    for (j = 0; j < n; j++) {
        if (arg0[j] >= 'a' && arg0[j] <= 'z') {
            arg0[j] -= 0x20;
        }
    }
    if (find_803CF958(arg0, len) == 1) {
        memcpy(fs_default_device_name, arg0, len + 1);
        return;
    }
    if (cvfs_completion_callback != NULL) {
        cvfs_completion_callback(lbl_805D75FC, cvfs_set_def_dev_error_2, 0);
    }
}

struct CvFsDevIf {
    u8 pad0[4];
    void (*set_callback)(CvFsErrorCallback, s32);
};

inline u32 cvfs_find_device_if(char *s, s32 len) {
    Ent_803CF958 *p;
    u32 i;
    for (p = cvfs_entry_table, i = 0; i < 32; i++, p++) {
        if (strncmp(s, p->name, len) == 0) {
            return cvfs_entry_table[i].a;
        }
    }
    return 0;
}
extern const char *const volatile lbl_805E0DA0;

inline CvFsDevIf *cvfs_add_device(char *name, CvFsDevIf *dev) {
    s32 k;
    if (cvfs_find_device_if(name, strlen(name)) != 0) {
        return dev;
    }
    for (k = 0; k < 32; k++) {
        if (cvfs_entry_table[k].name[0] == 0) {
            break;
        }
    }
    if (k == 32) {
        return NULL;
    }
    cvfs_entry_table[k].a = (u32)dev;
    memcpy(cvfs_entry_table[k].name, name, strlen(name) + 1);
    return dev;
}
void TLobby__sub_803CFAA8(char *name, CvFsDevIf *(*getif)(void), s32 arg) {
    CvFsDevIf *dev;
    u32 n;
    u32 i;
    lbl_805E0DA0;
    if (name == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_add_dev_error_1, 0);
        }
        return;
    }
    if (getif == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_add_dev_error_2, 0);
        }
        return;
    }
    n = strlen(name) + 1;
    for (i = 0; i < n; i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            name[i] -= 0x20;
        }
    }
    dev = cvfs_add_device(name, getif());
    if (dev == NULL) {
        if (cvfs_completion_callback != NULL) {
            cvfs_completion_callback(lbl_805D75FC, cvfs_add_dev_error_3, 0);
        }
        return;
    }
    if (dev->set_callback != NULL) {
        dev->set_callback(cvfs_forward_error, 0);
    }
}


void SIGetTypeAsync(void) {
    Slot_803CFD2C *s;
    Rec_803CFD2C *r;
    s32 i;

    if (--lbl_805D7600 == 0) {
        for (s = (Slot_803CFD2C *)si_type_info_table, i = 0; i < 40; i++, s++) {
            if (s->drv != NULL) {
                s->drv->close(s->handle);
            }
            s->drv = NULL;
            s->handle = 0;
        }
        for (i = 0; i < 32; i++) {
            ((Rec_803CFD2C *)cvfs_entry_table)[i].used = 0;
        }
        memset(fs_default_device_name, 0, 9);
        ((s8 *)fs_default_device_name)[0] = 0;
    }
}

}
