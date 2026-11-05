#ifndef PSO_SYSTEM_DATE_H
#define PSO_SYSTEM_DATE_H

#include "types.h"

struct DateStamp {
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 minute;
    u8 second;
    u8 weekday;
    u8 _pad; // fn_801E283C stores calc_day_in_cycle here.
};

int getDateStamp(DateStamp *out);
void DateToSeconds(DateStamp *date, int *seconds);

u8 calc_day_in_cycle(DateStamp *date);
extern "C" {
void fn_801E283C(u32 seconds, DateStamp *date);
u8 fn_801E2AC8(u16 year, u8 month, u8 day);
}

#endif
