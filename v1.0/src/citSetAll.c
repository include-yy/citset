#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

extern size_t cit_place[2];

void
citSetAll (cit_ptr var, bit_index start, bit_index end, int symbol)
{
  IndexCheck(var, end);
  if (start > end) {
    cit_die("citCopy: start index is bigger than end index!");
  } else;
  
  size_t i;
  cit_unit_ptr nod = var->_cit_limb;
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

  nod += NumOfUnita;
  
  if (UnitDif > 0) {
    for (i = NumOfBitsa; i < UNITBITS; i++) {
      cit_unit_set(nod, i, symbol);
      }

    nod++;
    
    if (UnitDif >= 2) {
      cit_zerone_dec(nod, 0, UnitDif - 2, symbol);
    } else;

    nod += UnitDif - 1;

    for (i = 0; i <= NumOfBitsb; i++) {
      cit_unit_set(nod, i, symbol);
    }
  } else {
    for (i = NumOfBitsa; i <= NumOfBitsb; i++) {
      cit_unit_set(nod, i, symbol);
    }
  }
}
