#ifndef PSO_SYSTEM_ADXENCODER_H
#define PSO_SYSTEM_ADXENCODER_H

#include "types.h"

// CRI ADX encoder (AdxEncoder.cpp): encodes PCM read from SJ streams into an
// ADX stream; its contexts are pooled in adx_encoder_context_pool.

#include "pso/system/SjRingBuffer.h"
typedef struct S_803C6138 {
    u8 pad0[0x80];
    u8 *f80;
    u8 *f84;
} S_803C6138;

extern "C" {
// Defined in TLobby_803C4698.cpp: predictor coefficients for a high-pass cutoff at a sample rate.
void calc_adx_predictor_coeffs(s32 cutoff, s32 rate, s16 *k0, s16 *k1);
void TLobby__sub_803C5E78(void);
void adx_process_encoder_output(u8 *arg0p);
void TLobby__sub_803C60F0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void TLobby__sub_803C610C(u8 *arg0);
void TLobby__sub_803C6118(u8 *arg0);
void TLobby__sub_803C6138(S_803C6138 *arg0);
u8 *TLobby__sub_803C61C4(s32, SjRingBuffer **, SjRingBuffer *);
}

#endif
