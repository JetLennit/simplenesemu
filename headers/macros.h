//Because I'm lazy
#ifndef MACROS_H
#define MACROS_H

#define BITSET(NUMBER, BIT)    ((NUMBER) |=  (1 << (BIT)))
#define BITCLEAR(NUMBER, BIT)  ((NUMBER) &= ~(1 << (BIT)))
#define BITTOGGLE(NUMBER, BIT) ((NUMBER) ^=  (1 << (BIT)))
#define BITCHECK(NUMBER, BIT)  ((NUMBER) &   (1 << (BIT)))

#define HEIGHT 240
#define WIDTH 256

#endif 