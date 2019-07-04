#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

extern size_t cit_place[2];

void
citCopy (cit_ptr get, cit_ptr var, bit_index start, bit_index end)
{
  EqualCheck(get, var);
  IndexCheck(var, end);
  if (start > end) {
    cit_die("citCopy: start index is bigger than end index!");
  } else;
  
  size_t i;
  cit_unit_ptr fst = get->_cit_limb;
  cit_unit_ptr sec = var->_cit_limb;
  size_t NumOfUnita, NumOfUnitb;
  size_t NumOfBitsa, NumOfBitsb;
  size_t UnitDif;
  
  cit_tell(start);
  NumOfUnita = cit_place[0];
  NumOfBitsa = cit_place[1];

  cit_tell(end);
  NumOfUnitb = cit_place[0];
  NumOfBitsb = cit_place[1];

  UnitDif = NumOfUnitb - NumOfUnita;
  
  fst += NumOfUnita;
  sec += NumOfUnita;
  
  if (UnitDif > 0) {
    for (i = NumOfBitsa; i < UNITBITS; i++) {
      if (cit_unit_get(sec, i) == ONE) {
	cit_unit_set(fst, i, ONE);
      } else {
	cit_unit_set(fst, i ,ZERO);
      }
    }
  
    fst++;
    sec++;
    
    if (UnitDif >= 2) {
      cit_copy_dec(fst, sec, 0, UnitDif - 2);
    } else;
    
    fst += UnitDif - 1;
    sec += UnitDif - 1;

    for (i = 0; i <= NumOfBitsb; i++) {
      if (cit_unit_get(sec, i) == ONE) {
	cit_unit_set(fst, i, ONE);
      } else {
	cit_unit_set(fst, i ,ZERO);
      }
    }
  } else {
    for (i = NumOfBitsa; i <= NumOfBitsb; i++) {
      if (cit_unit_get(sec, i) == ONE) {
	cit_unit_set(fst, i, ONE);
      } else {
	cit_unit_set(fst, i ,ZERO);
      }
    }
  }
  
}
