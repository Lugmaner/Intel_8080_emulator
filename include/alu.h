#ifndef ALU_H
#define ALU_H

#include "types.h"

typedef struct
{
    unsigned int A : 1;
    unsigned int B : 1;
    unsigned int C_in : 1;

    unsigned int C_out : 1;
    unsigned int S : 1;
} full_adder_t;

typedef struct {
    byte_t result;
    uint8_t C_out;
    uint8_t aux_carry;
    uint8_t parity_flag;
    uint8_t err; //1 if err
} alu_result_t;

int full_adder_job(full_adder_t *adder);

alu_result_t alu_add8(byte_t A, byte_t B, uint8_t C_in);

#endif