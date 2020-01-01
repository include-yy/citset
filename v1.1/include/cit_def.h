#ifndef CITDEF_H_
#define CITDEF_H_

#include "cit_unit.h"

#ifndef CIT_WORD_SIZE
#define CIT_WORD_SIZE 1
#endif

#ifndef CIT_WORD_SIZE
#error CIT_WORD_SIZE undefined

#elif (CIT_WORD_SIZE == 1)
#define cit_unit uint8_t
#define CIT_UNIT_MSB CIT_UINT8_MSB
#define CIT_UNIT_MAX CIT_UINT8_MAX
#define CIT_UNIT_BIT CIT_UINT8_BIT

#define cit_get_bit cit_get_bit_u8
#define cit_set_bit cit_set_bit_u8
#define cit_flip_bit cit_flip_bit_u8
#define cit_get cit_get_u8
#define cit_zerone cit_zerone_u8
#define cit_flip cit_flip_u8
#define cit_copy cit_copy_u8
#define cit_swap cit_swap_u8
#define cit_count cit_count_u8
#define cit_reverse cit_reverse_u8

#elif (CIT_WORD_SIZE == 2)
#define cit_unit uint16_t
#define CIT_UNIT_MSB CIT_UINT16_MSB
#define CIT_UNIT_MAX CIT_UINT16_MAX
#define CIT_UNIT_BIT CIT_UINT16_BIT

#define cit_get_bit cit_get_bit_u16
#define cit_set_bit cit_set_bit_u16
#define cit_flip_bit cit_flip_bit_u16
#define cit_get cit_get_u16
#define cit_zerone cit_zerone_u16
#define cit_flip cit_flip_u16
#define cit_copy cit_copy_u16
#define cit_swap cit_swap_u16
#define cit_count cit_count_u16
#define cit_reverse cit_reverse_u16

#elif (CIT_WORD_SIZE == 4)
#define cit_unit uint32_t
#define CIT_UNIT_MSB CIT_UINT32_MSB
#define CIT_UNIT_MAX CIT_UINT32_MAX
#define CIT_UNIT_BIT CIT_UINT32_BIT

#define cit_get_bit cit_get_bit_u32
#define cit_set_bit cit_set_bit_u32
#define cit_flip_bit cit_flip_bit_u32
#define cit_get cit_get_u32
#define cit_zerone cit_zerone_u32
#define cit_flip cit_flip_u32
#define cit_copy cit_copy_u32
#define cit_swap cit_swap_u32
#define cit_count cit_count_u32
#define cit_reverse cit_reverse_u32

#elif (CIT_WORD_SIZE == 8)
#define cit_unit uint64_t
#define CIT_UNIT_MSB CIT_UINT64_MSB
#define CIT_UNIT_MAX CIT_UINT64_MAX
#define CIT_UNIT_BIT CIT_UINT64_BIT

#define cit_get_bit cit_get_bit_u64
#define cit_set_bit cit_set_bit_u64
#define cit_flip_bit cit_flip_bit_u64
#define cit_get cit_get_u64
#define cit_zerone cit_zerone_u64
#define cit_flip cit_flip_u64
#define cit_copy cit_copy_u64
#define cit_swap cit_swap_u64
#define cit_count cit_count_u64
#define cit_reverse cit_reverse_u64

#endif

#define CIT_OUT_OFFSET(index) ((index) / CIT_UNIT_BIT)
#define CIT_IN_OFFSET(index) ((index) % CIT_UNIT_BIT)

#endif