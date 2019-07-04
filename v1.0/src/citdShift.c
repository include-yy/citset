#include"cit_def.h"
#include"cit_limb.h"
#include"citset_in.h"

void
citdShift (cit get, cit var, bit_index length, int signal)
{
  EqualCheck(get, var);

  bit_index len = var->_cit_alloc;

  bit_index i;
  
  if (length >= len) {
    citdSetAll(get, ZERO);
  } else {
    if (signal == LEFT) {
      for (i = 0; i < len - length; i++) {
	if (citGet(var, i + length) == ONE) {
	  citSet(get, i, ONE);
	} else {
	  citSet(get, i, ZERO);
	}
      }
      for (i = len - length; i < len; i++) {
	citSet(get, i, ZERO);
      }
    } else if (signal == RIGHT) {
      for (i = len - 1; i >= length; i--) {
	if (citGet(var, i - length) == ONE) {
	  citSet(get, i, ONE);
	} else {
	  citSet(get, i, ZERO);
	}
      }
      for (i = 0; i < length; i++) {
	citSet(get, i, ZERO);
      }
    }
  }
  
}
      
    
