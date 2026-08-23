#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef uint8_t byte_t;
typedef uint16_t word_t;

typedef struct
{
    byte_t A;
    byte_t B,C,D,E,H,L;   //can switch between 8-bit and 16-bit mode

    word_t PC; //program counter
    word_t SP; //stack pointer
    
    byte_t flags; // 	S 	Z 	0 	AC 	0 	P 	1 	C 	Flags
} cpu_t;


#endif