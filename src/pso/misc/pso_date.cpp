#include "pso/system/ModelDrawCallback.h"
#include "pso/misc/pso_date.h"
#include "pso/misc/TCameraCtrl_803D6538.h"
#include "pso/system/date.h"
#include "dolphin/os/OSTime.h"

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

struct CalendarMonthStarts {
    s32 days[12];
};

extern "C" {
extern const CalendarMonthStarts date_month_start_days = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}
};
extern const CalendarMonthStarts lbl_80449700 = {
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}
};
void prepare_ginja_model(void);
}
void end_ginja_model_draw();

// Preserve the original division sequence and separate raw/normalized days.
#pragma push
#pragma opt_propagation off
extern "C" void fn_801E283C(u32 seconds, DateStamp *date) {
    CalendarMonthStarts months = lbl_80449700;
    u32 second;
    u32 minute;
    u32 hour;
    u32 day_of_year;
    u32 day;
    u32 leap_days;
    u32 year;
    second = seconds % 60;
    minute = seconds / 60 % 60;
    hour = seconds / 3600 % 24;
    year = seconds / 31536000;
    day_of_year = seconds / 86400 % 365;
    leap_days = (year + 1) / 4;
    date->second = second;
    date->minute = minute;
    date->hour = hour;

    if (leap_days <= day_of_year) {
        date->year = year + 2000;
        day = day_of_year - leap_days;
    } else {
        day = 365 - leap_days;
        date->year = year + 1999;
        day = day_of_year + day;
        if (date->year % 4 == 0) {
            ++day;
        }
    }

    s32 month = 1;
    if (date->year % 4 == 0) {
        if (day >= months.days[1]) {
            for (month = 2; month < 12; ++month) {
                if (day < months.days[month] + 1) {
                    break;
                }
            }
        }
    } else {
        for (month = 1; month < 12; ++month) {
            if (day < months.days[month]) {
                break;
            }
        }
    }
    date->month = month;
    date->day = day - months.days[month - 1] + 1;
    if (date->year % 4 == 0 && date->month > 2) {
        --date->day;
    }
    date->weekday = fn_801E2AC8(date->year, date->month, date->day);
    date->_pad = calc_day_in_cycle(date);
}

#pragma pop
u8 calc_day_in_cycle(DateStamp *date) {
    int seconds;
    u32 cycle_offset;
    DateToSeconds(date, &seconds);
    u32 elapsed = seconds;
    if (elapsed >= 0x5CB417D1U) {
        cycle_offset = elapsed - 0x5CB417D1U;
        cycle_offset = cycle_offset % 0x26EE7FU;
    } else {
        cycle_offset = 0x5CB417D1U - elapsed;
        cycle_offset = cycle_offset % 0x26EE7FU;
        cycle_offset = 0x26EE7FU - cycle_offset;
    }
    return (u8) (cycle_offset / 86400U);
}

u8 fn_801E2AC8(u16 year, u8 month, u8 day) {
    if (month <= 2) {
        year--;
        month += 12;
    }
    return (year + (year >> 2) - 15 + (13 * month + 8) / 5 + day) % 7;
}

#pragma push
#pragma opt_propagation off
void DateToSeconds(DateStamp *ds, int *out) {
    CalendarMonthStarts months = date_month_start_days;
    s32 y = ds->year - 0x7D0;
    u32 t = y + 2;
    s32 d = (t >> 2) + y * 0x16D;
    if ((t & 3) == 0 && ds->month <= 2) {
        d -= 1;
    }
    d += months.days[ds->month - 1];
    d += ds->day - 1;
    *out = ds->second + ((ds->minute + ((ds->hour + d * 0x18) * 0x3C))) * 0x3C;
}
#pragma pop

int getDateStamp(DateStamp* out) {
    OSCalendarTime cal;
    OSTicksToCalendarTime(OSGetTime(), &cal);
    out->year = cal.year;
    out->month = cal.mon + 1;
    out->day = cal.mday;
    out->hour = cal.hour;
    out->minute = cal.min;
    out->second = cal.sec;
    out->weekday = cal.wday;
    out->_pad = 0;
    return 1;
}

#include "pso/player/TObjPlayer.h"

extern "C" {

int OSResetSystem(int, int, int);
int VIWaitForRetrace(void);
int VIFlush(void);
int VISetBlack(int);

void fn_801E2C50(void) {  }
}
void reset_system(void) { VISetBlack(1); VIFlush(); VIWaitForRetrace(); OSResetSystem(1, 0, 0); }
void system_reset(void) { VISetBlack(1); VIFlush(); VIWaitForRetrace(); OSResetSystem(1, 0, 1); }
void draw_ginja_motion_link(NJS_OBJECT *model, NJS_MOTION_LINK *link, f32 frame) {
    bind_motion_blend_channels(link, frame);
    ModelDrawContext *g = model_draw_context;
    g->draw = draw_ginja_model_lists;
    prepare_ginja_model();
    TObjPlayer::render_model_tree(model);
    end_ginja_model_draw();
}
