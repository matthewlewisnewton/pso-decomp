#include "musyx/runtime/musyx_runtime_b.h"

#define synthInfo_voiceNum (((u8 *)synthInfo)[0x210])
#define CLAMP(value, min, max) ((value) > (max) ? (max) : (value) < (min) ? (min) : (value))
#define CLAMP_INV(value, min, max) ((value) < (min) ? (min) : (value) > (max) ? (max) : (value))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define SLOTS_803BD694 (*(Slot_803BD694 **)&lbl_805D748C)
#define OSCachedToPhysical(caddr) ((u32)((u8 *)(caddr) - 0x80000000))
extern "C" {

#pragma push
#pragma dont_inline off
static inline void DLsetdelay(SoundReverbDelay * dl, s32 lag) {
    dl->readOffset = dl->writeOffset - (lag * 4);
    while (dl->readOffset < 0) {
        dl->readOffset += dl->byteLength;
    }
}

static inline void DLcreate(SoundReverbDelay * dl, s32 max_byteLength) {
    dl->byteLength = (max_byteLength * 4);
    dl->samples = salMalloc( max_byteLength << 2);
    memset(dl->samples, 0, max_byteLength << 2);
    dl->last = 0.0f;
    DLsetdelay(dl, max_byteLength >> 1);
    dl->writeOffset = 0;
    dl->readOffset = 0;
}

s32 ReverbHICreate(SoundReverb * rv, float coloration, float time, float mix, float damping, float preDelay, float crossTalk) {
    u8 i;
    u8 k;
    static s32 lens[] = {1789, 1999, 2333, 433, 149, 47, 73, 67};

    if ((coloration < 0.0f ) || (coloration > 1.0f )
     || (time       < 0.01f) || (time       > 10.0f)
     || (mix        < 0.0f ) || (mix        > 1.0f )
     || (crossTalk  < 0.0f ) || (crossTalk  > 1.0f )
     || (damping    < 0.0f ) || (damping    > 1.0f )
     || (preDelay   < 0.0f ) || (preDelay   > 0.1f )) {
        return 0;
    }
    memset(rv, 0, 0x1C4);
    for(k = 0; k < 3; k++) {
        for(i = 0; i < 3; i++) {
            DLcreate(&rv->comb[i + (k * 3)], lens[i] + 2);
            DLsetdelay(&rv->comb[i + (k * 3)], lens[i]);
            rv->feedback[i + (k * 3)] = powf(10.0f, (lens[i] * -3) / (32000.0f * time));
        }
        for(i = 0; i < 2; i++) {
            DLcreate(&rv->allPass[i + (k * 3)], lens[i + 3] + 2);
            DLsetdelay(&rv->allPass[i + (k * 3)], lens[i + 3]);
        }
        DLcreate(&rv->allPass[2 + (k * 3)], lens[k + 5] + 2);
        DLsetdelay(&rv->allPass[2 + (k * 3)], lens[k + 5]);
        rv->lowPassLast[k] = 0.0f;
    }
    rv->coloration = coloration;
    rv->mix = mix;
    rv->crossTalk = crossTalk;
    rv->damping = damping;
    if (rv->damping < 0.05f) {
        rv->damping = 0.05f;
    }
    rv->damping = (1.0f - (0.05f + (0.8f * rv->damping)));
    if (0.0f != preDelay) {
        rv->preDelayFrames = (32000.0f * preDelay);
        for(i = 0; i < 3; i++) {
            rv->preDelay[i] = salMalloc( rv->preDelayFrames * 4);
            memset(rv->preDelay[i], 0, rv->preDelayFrames * 4);
            rv->preDelayCurrent[i] = rv->preDelay[i];
        }
    } else {
        rv->preDelayFrames = 0;
        for(i = 0; i < 3; i++) {
            rv->preDelayCurrent[i] = 0;
            rv->preDelay[i] = 0;
        }
    }
    return 1;
}

#pragma pop

static const float value0_3 = 0.3f;
static const float value0_6 = 0.6f;
static const double i2fMagic = 4.503601774854144E15;

#ifdef __MWERKS__
asm void DoCrossTalk(void *a, void *b, f32 start, f32 end) {
#include "orig_asm/musyx/runtime/StdReverb/reverb/DoCrossTalk.inc"
}

asm void HandleReverb(void *sptr, void *rv, int k) {
#include "orig_asm/musyx/runtime/StdReverb/reverb/HandleReverb.inc"
}
#else
/* Scalar fallback for the MusyX high-quality reverb kernels. The GameCube
 * bodies stay the vendor paired-single assembly under __MWERKS__.
 * Cross-checked with
 * https://github.com/AxioDL/musyx/blob/717404d77c17a95dd101bbe737d0f9549ab600e6/src/musyx/runtime/StdReverb/reverb.c
 * and the AXFX equivalents in doldecomp/dolsdk2001 src/axfx/reverb_hi.c.
 * This binary is the MUSY_VERSION <= 2.0.0 schedule: DoCrossTalk scales the
 * (start, end) pair by value0_6 (`ps_muls0`) and converts with fctiw
 * (round-to-nearest-even). HandleReverb's predelay reloads preDelayCurrent
 * every sample and stores the advanced pointer with `stw r29, 0x1B8(r30)`,
 * where r30 is the delay-line base rather than the reverb object.
 */
static s32 fctiw_round(f32 x) {
    s32 neg = x < 0.0f;
    f32 ax = neg ? -x : x;
    s32 base = (s32)ax;
    f32 frac = ax - (f32)base;
    s32 rounded;
    if (frac > 0.5f) {
        rounded = base + 1;
    } else if (frac < 0.5f) {
        rounded = base;
    } else if ((base & 1) != 0) {
        rounded = base + 1;
    } else {
        rounded = base;
    }
    return neg ? -rounded : rounded;
}

void DoCrossTalk(void *a_in, void *b_in, f32 start, f32 end) {
    s32 *a = (s32 *)a_in;
    s32 *b = (s32 *)b_in;
    f32 start_scaled = start * value0_6;
    f32 end_scaled = end * value0_6;
    s32 i;

    for (i = 0; i < 160; i++) {
        f32 af = (f32)a[i];
        f32 bf = (f32)b[i];
        a[i] = fctiw_round(af * end + bf * start);
        b[i] = fctiw_round(af * start_scaled + bf * end_scaled);
    }
}

static void delay_write(SoundReverbDelay *dl, f32 sample) {
    dl->samples[dl->writeOffset / (s32)sizeof(f32)] = sample;
    dl->writeOffset += (s32)sizeof(f32);
    if (dl->writeOffset == dl->byteLength) {
        dl->writeOffset = 0;
    }
}

static f32 delay_read(SoundReverbDelay *dl) {
    f32 sample = dl->samples[dl->readOffset / (s32)sizeof(f32)];
    dl->readOffset += (s32)sizeof(f32);
    if (dl->readOffset == dl->byteLength) {
        dl->readOffset = 0;
    }
    dl->last = sample;
    return sample;
}

static f32 predelay_sample(SoundReverb *rv, s32 channel, f32 sample) {
    f32 *line;
    f32 *ptr;
    f32 delayed;

    if (rv->preDelayFrames == 0) {
        return sample;
    }
    line = rv->preDelay[channel];
    ptr = rv->preDelayCurrent[channel] + 1;
    delayed = ptr[-1];
    ptr[-1] = sample;
    if (ptr == line + (rv->preDelayFrames - 1)) {
        ptr = line;
    }
    memcpy((u8 *)line + 0x1B8, &ptr, sizeof(ptr));
    return delayed;
}

void HandleReverb(void *sptr_in, void *rv_in, int k) {
    s32 *sptr = (s32 *)sptr_in;
    SoundReverb *rv = (SoundReverb *)rv_in;
    f32 damp_wet = rv->mix * value0_6;
    f32 damp_dry = value0_6 - damp_wet;
    SoundReverbDelay *comb = &rv->comb[k * 3];
    SoundReverbDelay *ap = &rv->allPass[k * 3];
    s32 i;

    for (i = 0; i < 160; i++) {
        f32 sample = (f32)sptr[i];
        f32 delayed = predelay_sample(rv, k, sample);
        f32 comb_sum;
        f32 old_last;
        f32 ap_in;
        f32 low;
        f32 wet;

        delay_write(&comb[0], rv->feedback[k * 3] * comb[0].last + delayed);
        delay_write(&comb[1], rv->feedback[k * 3 + 1] * comb[1].last + delayed);
        delay_write(&comb[2], rv->feedback[k * 3 + 2] * comb[2].last + delayed);
        comb_sum = delay_read(&comb[0]) + delay_read(&comb[1]) + delay_read(&comb[2]);

        old_last = ap[0].last;
        ap_in = rv->coloration * old_last + comb_sum;
        delay_write(&ap[0], ap_in);
        low = old_last - rv->coloration * ap_in;
        delay_read(&ap[0]);

        old_last = ap[1].last;
        ap_in = rv->coloration * old_last + low;
        delay_write(&ap[1], ap_in);
        low = old_last - rv->coloration * ap_in;
        delay_read(&ap[1]);

        low = low * value0_3;
        rv->lowPassLast[k] = rv->damping * rv->lowPassLast[k] + low;

        old_last = ap[2].last;
        ap_in = rv->coloration * old_last + rv->lowPassLast[k];
        delay_write(&ap[2], ap_in);
        wet = old_last - rv->coloration * ap_in;
        delay_read(&ap[2]);

        sptr[i] = (s32)(damp_dry * sample + damp_wet * wet);
    }
}
#endif

#pragma push
#pragma peephole off
void ReverbHICallback(void *arg0, void *arg1, void *arg2, S_803BF408 *arg3) {
    u8 i;
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            if (0.0f != arg3->f1A8) {
                f32 t = 0.5f * arg3->f1A8;
                DoCrossTalk(arg0, arg1, t, 1.0f - t);
            }
            HandleReverb(arg0, arg3, 0);
            break;
        case 1:
            HandleReverb(arg1, arg3, 1);
            break;
        case 2:
            HandleReverb(arg2, arg3, 2);
            break;
        }
    }
}
#pragma pop

}
