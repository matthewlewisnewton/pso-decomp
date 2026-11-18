#include "pso/misc/TechniqueParams.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/object/TObjMotion.h"

extern "C" {
static __declspec(section ".rodata") const char lbl_8044CDF8[] ATTRIBUTE_ALIGN(4) = "eff_f_bartaturara.gj";
static __declspec(section ".rodata") const char lbl_8044CE10[] ATTRIBUTE_ALIGN(4) = "eff_f_gibarta_01.gj";
static __declspec(section ".rodata") const char lbl_8044CE24[] ATTRIBUTE_ALIGN(4) = "eff_f_gibartalv1.gj";
static __declspec(section ".rodata") const char lbl_8044CE38[] ATTRIBUTE_ALIGN(4) = "eff_f_gibartalv4.gj";
static __declspec(section ".rodata") const char lbl_8044CE4C[] ATTRIBUTE_ALIGN(4) = "eff_f_gibartalv6.gj";
static __declspec(section ".rodata") const char lbl_8044CE60[] ATTRIBUTE_ALIGN(4) = "eff_f_ice_piece.gj";
static __declspec(section ".rodata") const char lbl_8044CE74[] ATTRIBUTE_ALIGN(4) = "eff_f_rabarta.gj";
static __declspec(section ".rodata") const char lbl_8044CE88[] ATTRIBUTE_ALIGN(4) = "eff_f_rabarta_02.gj";
static __declspec(section ".rodata") const char lbl_8044CE9C[] ATTRIBUTE_ALIGN(4) = "eff_f_rabarta_03.gj";
static __declspec(section ".rodata") const char lbl_8044CEB0[] ATTRIBUTE_ALIGN(4) = "eff_f_rafoie_shushku.gj";
static __declspec(section ".rodata") const char lbl_8044CEC8[] ATTRIBUTE_ALIGN(4) = "eff_f_ringwave.gj";
static __declspec(section ".rodata") const char lbl_8044CEDC[] ATTRIBUTE_ALIGN(4) = "eff_rafoie.gj";
static __declspec(section ".rodata") const char lbl_8044CEEC[] ATTRIBUTE_ALIGN(4) = "eff_f_bartaturara.njm";
static __declspec(section ".rodata") const char lbl_8044CF04[] ATTRIBUTE_ALIGN(4) = "eff_f_gibarta_01.njm";
static __declspec(section ".rodata") const char lbl_8044CF1C[] ATTRIBUTE_ALIGN(4) = "eff_f_rabarta.njm";
static __declspec(section ".rodata") const char lbl_8044CF30[] ATTRIBUTE_ALIGN(4) = "eff_f_rabarta_02.njm";
static __declspec(section ".rodata") const char lbl_8044CF48[] ATTRIBUTE_ALIGN(4) = "eff_f_rabarta_03.njm";
static __declspec(section ".rodata") const char lbl_8044CF60[] ATTRIBUTE_ALIGN(4) = "bm_technic.bml";
static __declspec(section ".rodata") const char lbl_8044CF70[] ATTRIBUTE_ALIGN(4) = "TTecCtrl";

extern const NJS_ARGB technique_charge_light_color = {1.0f, 1.0f, 0.5f, 0.0f};
extern const Vec lbl_8044CF8C = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB technique_charge_light_params = {1.0f, 1.0f, 0.5f, 0.0f};
extern const Vec lbl_8044CFA8 = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB lbl_8044CFB4 = {1.0f, 1.0f, 1.0f, 1.0f};
extern const Vec lbl_8044CFC4 = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB rabarta_charge_light_color = {1.0f, 0.3f, 0.7f, 1.0f};
extern const Vec lbl_8044CFE0 = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB zonde_charge_light_color = {1.0f, 1.0f, 1.0f, 0.3f};
extern const Vec lbl_8044CFFC = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB resta_charge_light_color = {1.0f, 1.0f, 1.0f, 1.0f};
extern const Vec lbl_8044D018 = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB ryuker_charge_light_color = {1.0f, 0.3f, 0.9f, 1.0f};
extern const Vec lbl_8044D034 = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB shifta_charge_light_color = {1.0f, 0.9f, 0.3f, 1.0f};
extern const Vec lbl_8044D050 = {0.0f, -1.0f, 0.0f};
extern const NJS_ARGB megid_charge_light_color = {1.0f, 0.6f, 0.2f, 0.7f};
extern const Vec lbl_8044D06C = {0.0f, -1.0f, 0.0f};

const char *bm_technic_model_names[13] = {
    lbl_8044CDF8, lbl_8044CE10, lbl_8044CE24, lbl_8044CE38,
    lbl_8044CE4C, lbl_8044CE60, lbl_8044CE74, lbl_8044CE88,
    lbl_8044CE9C, lbl_8044CEB0, lbl_8044CEC8, lbl_8044CEDC,
    NULL,
};
const char *bm_technic_motion_names[6] = {
    lbl_8044CEEC, lbl_8044CF04, lbl_8044CF1C, lbl_8044CF30,
    lbl_8044CF48,
    NULL,
};
BmlResourceDescriptor technique_resource_descriptor = {lbl_8044CF60, bm_technic_model_names, bm_technic_motion_names, 12, 5};

TechniqueParams technique_param_table[19] = {
    {110.0f, 3.0f, 100.0f, 0.0f, 5, 5, 40, 1, 5461, 7281, 15, 1, 130, 50, 10, 20, 30},
    {260.0f, 8.0f, 50.0f, 0.0f, 20, 7, 100, 1, 65536, 0, 20, 10, 70, 26, 5, 25, 0},
    {350.0f, 0.0f, 100.0f, 10.0f, 30, 13, 133, 1, 7281, 0, 25, 10, 25, 22, 10, 28, 40},
    {50.0f, 3.0f, 90.0f, 0.0f, 4, 5, 35, 2, 9102, 0, 15, 1, 120, 50, 30, 25, 50},
    {230.0f, 0.0f, 100.0f, 0.0f, 25, 7, 100, 2, 20024, 0, 40, 10, 50, 24, 10, 24, 120},
    {400.0f, 0.0f, 40.0f, 0.0f, 35, 13, 106, 2, 65536, 0, 25, 10, 20, 19, 2, 30, 0},
    {80.0f, 0.0f, 110.0f, 10.0f, 6, 5, 44, 3, 32768, 16384, 15, 1, 110, 50, 10, 24, 0},
    {200.0f, 0.0f, 80.0f, 0.0f, 25, 7, 100, 3, 16384, 16384, 20, 10, 60, 22, 20, 25, 0},
    {450.0f, 0.0f, 50.0f, 0.0f, 35, 13, 134, 3, 65536, 16384, 25, 10, 30, 16, 20, 30, 0},
    {1180.0f, 0.0f, 150.0f, 10.0f, 45, 15, 160, 3, 32768, 16384, 35, 1, 110, 75, 30, 30, 0},
    {0.0f, 0.0f, 60.0f, 0.0f, 10, 5, 60, 10, 32768, 16384, 30, 10, 100, 1, 25, 17, 0},
    {0.0f, 0.0f, 50.0f, 0.0f, 10, 5, 60, 11, 32768, 16384, 15, 10, 50, 1, 4, 28, 0},
    {0.0f, 0.0f, 50.0f, 0.0f, 10, 5, 60, 12, 32768, 16384, 15, 10, 50, 1, 4, 28, 0},
    {0.0f, 0.0f, 60.0f, 0.0f, 10, 5, 60, 9, 32768, 16384, 30, 10, 100, 1, 25, 28, 0},
    {0.0f, 0.0f, 10.0f, 0.0f, 10, 20, 150, 14, 0, 0, 20, 0, 50, 0, 0, 0, 0},
    {50.0f, 0.0f, 60.0f, 0.0f, 15, 7, 50, 6, 0, 0, 20, 10, 120, 5, 25, 30, 0},
    {0.0f, 0.0f, 60.0f, 0.0f, 10, 7, 85, 7, 0, 0, 20, 10, 50, 0, 25, 26, 0},
    {0.0f, 0.0f, 100.0f, 0.0f, 20, 10, 150, 8, 0, 0, 30, 1, 0, 0, 0, 0, 0},
    {27.0f, 2.0f, 100.0f, 0.0f, 30, 15, 160, 5, 7281, 7281, 35, 1, 105, 3, 20, 28, 10},
};

const char *TTecCtrl__name = lbl_8044CF70;
}
