#define B2(n) n,n+1,n+1,n+2
#define B4(n) B2(n),B2(n+1),B2(n+1),B2(n+2)
#define B6(n) B4(n),B4(n+1),B4(n+1),B4(n+2)

const unsigned char cit_bits_count[256] = {B6(0), B6(1), B6(1),B6(2)};

#undef B2
#undef B4
#undef B6
