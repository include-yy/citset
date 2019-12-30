#ifndef __CITDEF_H_
  #define __CITDEF_H_

#ifndef CIT_WORD_SIZE
  #define CIT_WORD_SIZE 4
#endif

#include<stdint.h>
#include<limits.h>
#include<stddef.h>

#ifndef CIT_WORD_SIZE
  #error Must define CIT_WORD_SIZE to be 1, 2, 4, 8

#elif (CIT_WORD_SIZE == 1)
  #define cit_unit               uint8_t
  #define CIT_UNIT_MSB           ((cit_unit)0x80)
  #define CIT_UNIT_MAX           ((cit_unit)0xFF)

#elif (CIT_WORD_SIZE == 2)
  #define cit_unit               uint16_t
  #define CIT_UNIT_MSB           ((cit_unit)0x8000)
  #define CIT_UNIT_MAX           ((cit_unit)0xFFFF)

#elif (CIT_WORD_SIZE == 4)
  #define cit_unit               uint32_t
  #define CIT_UNIT_MSB           ((cit_unit)0x80000000)
  #define CIT_UNIT_MAX           ((cit_unit)0xFFFFFFFF)

#elif (CIT_WORD_SIZE == 8)
  #define cit_unit               uint64_t
  #define CIT_UNIT_MSB           ((cit_unit)0x8000000000000000)
  #define CIT_UNIT_MAX           ((cit_unit)0xFFFFFFFFFFFFFFFF)

#endif

#ifndef cit_unit
  #error cit_unit must be defined to uint8_t, uint16_t, uint32_t, uint64_t
#endif

#define CHARUNIT_MAX             UINT32_MAX
#define UNITBITS (CIT_WORD_SIZE * CHAR_BIT)

typedef uint64_t bit_index;
typedef cit_unit * cit_unit_ptr;

#define ONE              0X1
#define ZERO             0X0

#define AND              0X0
#define OR               0X1
#define XOR              0X2

#define LEFT             0X0
#define RIGHT            0X1

void cit_die(char *);

#endif
