#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

extern size_t cit_place[2];

void
citOr (cit_ptr get, cit_ptr foo, cit_ptr bar, bit_index start, bit_index end)
{
  EqualCheck(get, foo);
  EqualCheck(get, bar);
  IndexCheck(foo, end);
  if (start > end) {
    cit_die("citCopy: start index is bigger than end index!");
  } else;
  
  size_t i;
  cit_unit_ptr now = get->_cit_limb;
  cit_unit_ptr fst = foo->_cit_limb;
  cit_unit_ptr sec = bar->_cit_limb;
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
  
  now += NumOfUnita;
  fst += NumOfUnita;
  sec += NumOfUnita;

  if (UnitDif > 0) {
    for (i = NumOfBitsa; i < UNITBITS; i++) {
      if ((cit_unit_get(fst, i) == ONE) ||
	  (cit_unit_get(sec, i) == ONE)) {
	cit_unit_set(now, i, ONE);
      } else {
	cit_unit_set(now, i, ZERO);
      }
    }

    now++;
    fst++;
    sec++;

    if (UnitDif >= 2) {
      cit_or_dec(fst, sec, 0, UnitDif - 2, now);
    } else;

    now += UnitDif - 1;
    fst += UnitDif - 1;
    sec += UnitDif - 1;

    for (i = 0; i <= NumOfBitsb; i++) {
      if ((cit_unit_get(fst, i) == ONE) ||
	  (cit_unit_get(sec, i) == ONE)) {
	cit_unit_set(now, i, ONE);
      } else {
	cit_unit_set(now, i, ZERO);
      }
    }
  } else {
    for (i = NumOfBitsa; i <= NumOfBitsb; i++) {
     if ((cit_unit_get(fst, i) == ONE) ||
	 (cit_unit_get(sec, i) == ONE)) {
	cit_unit_set(now, i, ONE);
      } else {
	cit_unit_set(now, i, ZERO);
      }
    }
  }

}
