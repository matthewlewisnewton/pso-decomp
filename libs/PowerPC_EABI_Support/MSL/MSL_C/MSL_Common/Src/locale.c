#include "MSL_C/locale.h"
#include "limits.h"

/* The C locale pool contains the decimal point, the empty string and its name. */
#define C_LOCALE_STRINGS ".\0\0C"
#define C_LOCALE_EMPTY (C_LOCALE_STRINGS + sizeof("."))

struct lconv __lconv = {
    C_LOCALE_STRINGS, /* decimal_point */
    C_LOCALE_EMPTY, /* thousands_sep */
    C_LOCALE_EMPTY, /* grouping */
    C_LOCALE_EMPTY, /* mon_decimal_point */
    C_LOCALE_EMPTY, /* mon_thousands_sep */
    C_LOCALE_EMPTY, /* mon_grouping */
    C_LOCALE_EMPTY, /* positive_sign */
    C_LOCALE_EMPTY, /* negative_sign */
    C_LOCALE_EMPTY, /* currency_symbol */
    SCHAR_MAX, /* frac_digits */
    SCHAR_MAX, /* p_cs_precedes */
    SCHAR_MAX, /* n_cs_precedes */
    SCHAR_MAX, /* p_sep_by_space */
    SCHAR_MAX, /* n_sep_by_space */
    SCHAR_MAX, /* p_sign_posn */
    SCHAR_MAX, /* n_sign_posn */
    C_LOCALE_EMPTY, /* int_curr_symbol */
    SCHAR_MAX, /* int_frac_digits */
    SCHAR_MAX, /* int_p_cs_precedes */
    SCHAR_MAX, /* int_n_cs_precedes */
    SCHAR_MAX, /* int_p_sep_by_space */
    SCHAR_MAX, /* int_n_sep_by_space */
    SCHAR_MAX, /* int_p_sign_posn */
    SCHAR_MAX  /* int_n_sign_posn */
};
