#ifndef _CIT_LIMB_
  #define _CIT_LIMB_

void * cit_alloc_limb(size_t size);
void * cit_realloc_limb(cit_unit_ptr old, size_t size);
void cit_free_limb(void * p);

size_t cit_unit_get(cit_unit_ptr p, size_t index);
void cit_unit_set(cit_unit_ptr p, size_t index, int signal);
void cit_tell(bit_index index);

void cit_zerone_dec(cit_unit_ptr p, size_t start, size_t end, int signal);
void cit_zerone_inc(cit_unit_ptr p, size_t start, size_t end, int signal);
void cit_copy_dec(cit_unit_ptr d, cit_unit_ptr s, size_t start, size_t end);
void cit_copy_inc(cit_unit_ptr d, cit_unit_ptr s, size_t start, size_t end);
void cit_flip_dec(cit_unit_ptr d, cit_unit_ptr s, size_t start, size_t end);
void cit_flip_inc(cit_unit_ptr d, cit_unit_ptr s, size_t start, size_t end);
void cit_and_dec(cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get);
void cit_and_inc(cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get);
void cit_or_dec(cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get);
void cit_or_inc(cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get);
void cit_xor_dec(cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get);
void cit_xor_inc(cit_unit_ptr fst, cit_unit_ptr sec, size_t start, size_t end, cit_unit_ptr get);

#endif
