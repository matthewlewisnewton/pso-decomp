#ifndef PSO_UI_TWINDOWINPUTNUMBER_H
#define PSO_UI_TWINDOWINPUTNUMBER_H

#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowBase.h"

struct TWindowInputNumber : public TWindowBase {
    virtual ~TWindowInputNumber();
    s32 is_locked(s32);
    u8 test_input_flag();
    void refresh_digit_entries();
    void align_digits();
    void render();
    u16 inputFlags;
    s8 digitCount;
    s8 selectedDigit;
    s32 minimum;
    s32 maximum;
    s32 value;
    s32 unknown70;
    f32 scaleX;
    f32 scaleY;

    static void *operator new(unsigned long size) {
        return TObject::operator new(size);
    }
    TWindowInputNumber(void *position, s32 minimum, s32 maximum, s32 initial, s16 client);
    void mark_confirmed();
    void confirm_input();
    void update();
    void update_value();
    void handle_decrement();
    void move_cursor_next();
    void set_value(f32 farg0);
    int is_confirmed();
    void create(s32 arg1);
    void calc_digit_count();
    void run_task();
};

typedef char TWindowInputNumberSize[sizeof(TWindowInputNumber) == 0x7C ? 1 : -1];
typedef char NumberClientOffset[offsetof(TWindowInputNumber, m_20) == 0x20 ? 1 : -1];
typedef char NumberFlagsOffset[offsetof(TWindowInputNumber, inputFlags) == 0x60 ? 1 : -1];
typedef char NumberMinimumOffset[offsetof(TWindowInputNumber, minimum) == 0x64 ? 1 : -1];
typedef char NumberMaximumOffset[offsetof(TWindowInputNumber, maximum) == 0x68 ? 1 : -1];
typedef char NumberInitialOffset[offsetof(TWindowInputNumber, value) == 0x6C ? 1 : -1];
typedef char NumberScaleOffset[offsetof(TWindowInputNumber, scaleX) == 0x74 ? 1 : -1];

#endif
