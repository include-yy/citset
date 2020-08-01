#ifndef CIT_UNIT_H
#define CIT_UNIT_H

#include <stdint.h>
#include <limits.h>
#include <stddef.h>

#define CIT_UINT8_MSB    0x80U
#define CIT_UINT16_MSB   0x8000U
#define CIT_UINT32_MSB   0x80000000UL
#define CIT_UINT64_MSB   0x8000000000000000ULL

#define CIT_UINT8_BIT    8
#define CIT_UINT16_BIT   16
#define CIT_UINT32_BIT   32
#define CIT_UINT64_BIT   64

#define CIT_SWAP(a, b)                                  \
    (((a) ^ (b)) && ((b) ^= (a) ^= (b), (a) ^= (b)))

#define cit_cit_get_bit(v, id, msb, bits)       \
    ((((v) << (id)) & (msb)) >> ((bits) - 1))
#define cit_get_bit_u8(v, id)                               \
    cit_cit_get_bit(v, id, CIT_UINT8_MSB, CIT_UINT8_BIT)
#define cit_get_bit_u16(v, id)                              \
    cit_cit_get_bit(v, id, CIT_UINT16_MSB, CIT_UINT16_BIT)
#define cit_get_bit_u32(v, id)                              \
    cit_cit_get_bit(v, id, CIT_UINT32_MSB, CIT_UINT32_BIT)
#define cit_get_bit_u64(v, id)                              \
    cit_cit_get_bit(v, id, CIT_UINT64_MSB, CIT_UINT64_BIT)

#define cit_cit_set_bit(v, id, b, msb)          \
    ((v) ^ ((-(b) ^ (v)) & ((msb) >> (id))))
#define cit_set_bit_u8(v, id, b)                \
    cit_cit_set_bit(v, id, b, CIT_UINT8_MSB)
#define cit_set_bit_u16(v, id, b)               \
    cit_cit_set_bit(v, id, b, CIT_UINT16_MSB)
#define cit_set_bit_u32(v, id, b)               \
    cit_cit_set_bit(v, id, b, CIT_UINT32_MSB)
#define cit_set_bit_u64(v, id, b)               \
    cit_cit_set_bit(v, id, b, CIT_UINT64_MSB)

#define cit_cit_flip_bit(v, id, msb)            \
    ((v) ^ ((msb) >> (id)))
#define cit_flip_bit_u8(v, id)                  \
    cit_cit_flip_bit(v, id, CIT_UINT8_MSB)
#define cit_flip_bit_u16(v, id)                 \
    cit_cit_flip_bit(v, id, CIT_UINT16_MSB)
#define cit_flip_bit_u32(v, id)                 \
    cit_cit_flip_bit(v, id, CIT_UINT32_MSB)
#define cit_flip_bit_u64(v, id)                 \
    cit_cit_flip_bit(v, id, CIT_UINT64_MSB)

#define cit_cit_get(v, st, ed, id, maxx, bits)                          \
    ((((v) & (((maxx) & ((maxx) << ((bits) - ((ed) - (st))))) >> (st))) << (st)) >> (id))
#define cit_get_u8(v, st, ed, id)                           \
    cit_cit_get(v, st, ed, id, UINT8_MAX, CIT_UINT8_BIT)
#define cit_get_u16(v, st, ed, id)                          \
    cit_cit_get(v, st, ed, id, UINT16_MAX, CIT_UINT16_BIT)
#define cit_get_u32(v, st, ed, id)                          \
    cit_cit_get(v, st, ed, id, UINT32_MAX, CIT_UINT32_BIT)
#define cit_get_u64(v, st, ed, id)                          \
    cit_cit_get(v, st, ed, id, UINT64_MAX, CIT_UINT64_BIT)

#define cit_cit_zerone(v, st, ed, b, maxx, bits)                        \
    ((v) ^ ((-(b) ^ (v)) & (((maxx) & ((maxx) << ((bits) - ((ed) - (st)))))) >> (st)))
#define cit_zerone_u8(v, st, ed, b)                         \
    cit_cit_zerone(v, st, ed, b, UINT8_MAX, CIT_UINT8_BIT)
#define cit_zerone_u16(v, st, ed, b)                            \
    cit_cit_zerone(v, st, ed, b, UINT16_MAX, CIT_UINT16_BIT)
#define cit_zerone_u32(v, st, ed, b)                            \
    cit_cit_zerone(v, st, ed, b, UINT32_MAX, CIT_UINT32_BIT)
#define cit_zerone_u64(v, st, ed, b)                            \
    cit_cit_zerone(v, st, ed, b, UINT64_MAX, CIT_UINT64_BIT)

#define cit_cit_flip_gen(name, type, maxx, bits)                        \
    static inline type name(type v, int st, int ed)  {                  \
        type mode = ((maxx) & ((maxx) << ((bits) - (ed - st)))) >> st;	\
        return (v & (~mode)) | (mode ^ (v & mode));                     \
    }
cit_cit_flip_gen(cit_flip_u8, uint8_t, UINT8_MAX, CIT_UINT8_BIT)
cit_cit_flip_gen(cit_flip_u16, uint16_t, UINT16_MAX, CIT_UINT16_BIT)
cit_cit_flip_gen(cit_flip_u32, uint32_t, UINT32_MAX, CIT_UINT32_BIT)
cit_cit_flip_gen(cit_flip_u64, uint64_t, UINT64_MAX, CIT_UINT64_BIT)

#define cit_cit_copy_gen(name, type, maxx)                              \
    static inline type name(type v, int get_index, int org_index, int len) { \
        type x = ((v << get_index) ^ (v << org_index)) & ((maxx) & (~((maxx) >> len))); \
        return v ^ (x >> get_index);                                    \
    }
cit_cit_copy_gen(cit_copy_u8, uint8_t, UINT8_MAX)
cit_cit_copy_gen(cit_copy_u16, uint16_t, UINT16_MAX)
cit_cit_copy_gen(cit_copy_u32, uint32_t, UINT32_MAX)
cit_cit_copy_gen(cit_copy_u64, uint64_t, UINT64_MAX)

#define cit_cit_swap_gen(name, type, maxx)                              \
    static inline type name(type v, int i, int j, int n) {              \
        type x = ((v << i) ^ (v << j)) & ((maxx) & (~((maxx) >> n)));   \
        return v ^ ((x >> i) | (x >> j));                               \
    }
cit_cit_swap_gen(cit_swap_u8, uint8_t, UINT8_MAX)
cit_cit_swap_gen(cit_swap_u16, uint16_t, UINT16_MAX)
cit_cit_swap_gen(cit_swap_u32, uint32_t, UINT32_MAX)
cit_cit_swap_gen(cit_swap_u64, uint64_t, UINT64_MAX)

#ifdef CIT_NOUSE_EXTERN_CNT
#define B2(n) n,n+1,n+1,n+2
#define B4(n) B2(n),B2(n+1),B2(n+1),B2(n+2)
#define B6(n) B4(n),B4(n+1),B4(n+1),B4(n+2)
static const unsigned char cit_bits_count[256] = {B6(0), B6(1), B6(1), B6(2)};
#undef B2
#undef B4
#undef B6
#else
extern const unsigned char cit_bits_count[256];
#endif

#define cit_count_u8(v)                         \
    (cit_bits_count[(v)])
#define cit_count_u16(v)                                    \
    (cit_bits_count[(v) & 0xff] + cit_bits_count[(v) >> 8])
#define cit_count_u32(v)                                                \
    (cit_bits_count[(v) & 0xff] + cit_bits_count[((v) >> 8) & 0xff] +	\
     cit_bits_count[((v) >> 16) & 0xff] + cit_bits_count[(v) >> 24])
#define cit_count_u64(v)                                                \
    (cit_bits_count[(v)         & 0xff] + cit_bits_count[((v) >>  8) & 0xff] + \
     cit_bits_count[((v) >> 16) & 0xff] + cit_bits_count[((v) >> 24) & 0xff] + \
     cit_bits_count[((v) >> 32) & 0xff] + cit_bits_count[((v) >> 40) & 0xff] + \
     cit_bits_count[((v) >> 48) & 0xff] + cit_bits_count[(v) >> 56         ])

#ifdef CIT_NOUSE_EXTERN_REV
#define R2(n) n,n+2*64,n+1*64,n+3*64
#define R4(n) R2(n),R2(n+2*16),R2(n+1*16),R2(n+3*16)
#define R6(n) R4(n),R4(n+2*4),R4(n+1*4),R4(n+3*4)
static const unsigned char cit_bits_reverse[256] = {R6(0), R6(2), R6(1), R6(3)};
#undef R2
#undef R4
#undef R6
#else
extern const unsigned char cit_bits_reverse[256];
#endif

#define cit_reverse_u8(v)                       \
    (cit_bits_reverse[(v)])
#define cit_reverse_u16(v)                         \
    (cit_bits_reverse[(v) & 0xff] << 8 |           \
     cit_bits_reverse[(v) >> 8])
#define cit_reverse_u32(v)                          \
    (cit_bits_reverse[(v) & 0xff] << 24 |           \
     cit_bits_reverse[((v) >> 8) & 0xff] << 16 |	\
     cit_bits_reverse[((v) >> 16) & 0xff] << 8 |	\
     cit_bits_reverse[(v) >> 24])
#define cit_reverse_u64(v)                                     \
    ((uint64_t)cit_bits_reverse[(v) & 0xff] << 56 |            \
     (uint64_t)cit_bits_reverse[((v) >> 8) & 0xff] << 48 |     \
     (uint64_t)cit_bits_reverse[((v) >> 16) & 0xff] << 40 |    \
     (uint64_t)cit_bits_reverse[((v) >> 24) & 0xff] << 32 |    \
     (uint64_t)cit_bits_reverse[((v) >> 32) & 0xff] << 24 |    \
     (uint64_t)cit_bits_reverse[((v) >> 40) & 0xff] << 16 |    \
     (uint64_t)cit_bits_reverse[((v) >> 48) & 0xff] <<  8 |    \
     (uint64_t)cit_bits_reverse[(v) >> 56])

#define cit_zerone_dec(p, st, ed, b) do {       \
        for (size_t i = ed - 1; i > st; i--) {	\
            p[i] = -b;                          \
        }                                       \
        p[st] = -b;                             \
    } while (0)
#define cit_zerone_inc(p, st, ed, b) do {       \
        for (size_t i = st; i < ed; i++) {		\
            p[i] = -b;                          \
        }                                       \
    } while (0)
#define cit_cit_bin_dec(get, org, st, ed, op) do {	\
        for (size_t i = ed - 1; i > st; i--) {      \
            get[i] = op org[i];                     \
        }                                           \
        get[st] = op org[st];                       \
    } while(0)
#define cit_cit_bin_inc(get, org, st, ed, op) do {  \
        for (size_t i = start; i < end; i++) {      \
            get[i] = op org[i];                     \
        }                                           \
    } while(0)

#define cit_copy_dec(get, org, st, ed)          \
    cit_cit_bin_dec(get, org, st, ed, )
#define cit_copy_inc(get, org, st, ed)          \
    cit_cit_bin_inc(get, org, st, ed, )

#define cit_flip_dec(get, org, st, ed)          \
    cit_cit_bin_dec(get, org, st, ed, ~)
#define cit_flip_inc(get, org, st, ed)          \
    cit_cit_bin_inc(get, org, st, ed, ~)

#define cit_cit_logic_dec(get, fst, sec, st, ed, op) do {	\
        for (size_t i = ed - 1; i > st; i--) {              \
            get[i] = fst[i] op sec[i];                      \
        }                                                   \
        get[st] = fst[st] op sec[st];                       \
    } while(0)

#define cit_cit_logic_inc(get, fst, sec, st, ed, op) do {	\
        for (size_t i = st; i < ed; i++) {                  \
            get[i] = fst[i] op sec[i];                      \
        }                                                   \
    }while(0)

#define cit_and_dec(get, fst, sec, st, ed)      \
    cit_cit_logic_dec(get, fst, sec, st, ed, &)
#define cit_and_inc(get, fst, sec, st, ed)      \
    cit_cit_logic_inc(get, fst, sec, st, ed, &)
#define cit_ior_dec(get, fst, sec, st, ed)      \
    cit_cit_logic_dec(get, fst, sec, st, ed, |)
#define cit_ior_inc(get, fst, sec, st, ed)      \
    cit_cit_logic_inc(get, fst, sec, st, ed, |)
#define cit_xor_dec(get, fst, sec, st, ed)      \
    cit_cit_logic_dec(get, fst, sec, st, ed, ^)
#define cit_xor_inc(get, fst, sec, st, ed)      \
    cit_cit_logic_inc(get, fst, sec, st, ed, ^)

#endif
