// The GameCube encoder work structs and their layout checks are private to this unit.
#include "../../src/pso/audio/AdxEncoder.cpp"

int main() {
    const s16 samples[] = {0, -32768, 32767, -301, 177};
    const s32 peaks[] = {0, 32768, 32767, 301, 177};
    const s32 scales[] = {1, 4096, 4096, 43, 26};
    for (unsigned i = 0; i < sizeof(samples) / sizeof(samples[0]); ++i) {
        AdxEncoder encoder = {};
        AdxEncChannel channel = AdxEncChannel();
        AdxEncHistory history = {};
        encoder.channel[1] = &channel;
        channel.history = &history;
        encoder.pcm[1][1] = samples[i];
        encoder.block_samples = channel.block_samples = 2;
        if (fn_803C8020(&encoder, 1) != 0) return 1;
        if (channel.samples[1] != samples[i] || channel.peak != peaks[i]) return 2;
        if (channel.scale != scales[i]) return 3;
    }
    return 0;
}
