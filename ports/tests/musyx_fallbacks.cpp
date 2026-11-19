#include "musyx/runtime/musyx_runtime_b.h"

static bool check_chorus(void (*resample)(void *), unsigned whole_step) {
    s32 output[162];
    s32 samples[] = {2, 5, 9, 20, 25, 30, 35};
    s32 old[] = {1000, 0, 0};
    s32 history[] = {old[0], old[1], old[2]};
    output[0] = 76543;
    output[161] = -76543;
    ChorusSrcInfo_803BFBF0 state = {output + 1, samples, old, 0, 2, 0x80000000, 0, 7, 2};
    resample(&state);

    // A half-step pitch alternates between coefficient indices 0 and 16.
    static const f32 banks[2][4] = {
        {0.097503662109f, 0.802215576172f, 0.101593017578f, -0.0009765625f},
        {0.08203125f, 0.800476074219f, 0.118927001953f, -0.001403808594f}
    };
    unsigned index = 2;
    for (unsigned i = 0; i < 160; ++i) {
        const f32 *coef = banks[i & 1];
        const f32 result = history[0] * coef[0] + history[1] * coef[1] +
            history[2] * coef[2] + samples[index] * coef[3];
        if (output[i + 1] != (s32)result) return false;
        for (unsigned n = 0; n < whole_step + (i & 1); ++n) {
            history[0] = history[1];
            history[1] = history[2];
            history[2] = samples[index];
            if (++index == 7) index = 2;
        }
    }
    return output[0] == 76543 && output[161] == -76543 && state.posLo == 0 &&
        state.posHi == index && old[0] == history[0] && old[1] == history[1] && old[2] == history[2];
}

static bool check_cross_talk() {
    s32 left[160], right[160];
    const s32 input[] = {1000, 1, 3, -3};
    const s32 expected_left[] = {500, 0, 2, -2};
    const s32 expected_right[] = {300, 0, 1, -1};
    for (int i = 0; i < 160; ++i) {
        left[i] = input[i % 4];
        right[i] = 0;
    }
    DoCrossTalk(left, right, .5f, .5f);
    for (int i = 0; i < 160; ++i) {
        if (left[i] != expected_left[i % 4] || right[i] != expected_right[i % 4]) return false;
    }
    return true;
}

static bool check_reverb(int frames, int channel, bool wet) {
    SoundReverb reverb = {};
    f32 cells[6] = {};
    f32 storage[115];
    f32 *line = storage + 1;
    for (int i = 0; i < 115; ++i) storage[i] = 12345;
    for (int i = 0; i < frames; ++i) line[i] = 0;
    reverb.preDelayFrames = frames;
    reverb.preDelay[channel] = reverb.preDelayCurrent[channel] = line;
    reverb.mix = wet ? 1 : 0;
    for (int tap = 0; tap < 3; ++tap) {
        SoundReverbDelay &all_pass = reverb.allPass[3 * channel + tap];
        SoundReverbDelay &comb = reverb.comb[3 * channel + tap];
        all_pass.byteLength = comb.byteLength = sizeof(f32);
        all_pass.samples = cells + tap;
        comb.samples = cells + 3 + tap;
    }
    s32 samples[162];
    samples[0] = 23456;
    samples[161] = -23456;
    for (int i = 0; i < 160; ++i) samples[i + 1] = wet ? (i == 0 ? 100 : 0) : i - 80;
    HandleReverb(samples + 1, &reverb, channel);
    for (int i = 0; i < 160; ++i) {
        // The impulse passes through three one-sample all-pass stages.
        s32 expected = wet ? (i == 3 ? 54 : 0) : (s32)((i - 80) * 0.6f);
        if (samples[i + 1] != expected) return false;
    }
    for (int i = frames + 1; i < 115; ++i) {
        if (storage[i] != 12345) return false;
    }
    if (frames && line[0] != 79) return false;
    if (frames > 110) {
        u32 cursor;
        memcpy(&cursor, line + 110, sizeof(cursor));
        if (cursor != (u32)(line + 1)) return false;
    }
    return storage[0] == 12345 && samples[0] == 23456 && samples[161] == -23456 &&
        reverb.preDelayCurrent[channel] == line;
}

int main() {
    if (!check_chorus(do_src1, 0)) return 1;
    if (!check_chorus(do_src2, 1)) return 2;
    if (!check_cross_talk()) return 3;
    const int frames[] = {0, 1, 2, 110, 111, 112};
    for (int channel = 0; channel < 3; ++channel) {
        for (unsigned i = 0; i < sizeof(frames) / sizeof(frames[0]); ++i) {
            if (!check_reverb(frames[i], channel, false)) return 4;
        }
        if (!check_reverb(0, channel, true)) return 5;
    }
    return 0;
}
