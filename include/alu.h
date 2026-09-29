#ifndef ALU_H
#define ALU_H

#include <stdlib.h>
#include <stdbool.h>
#include "types.h"


typedef struct alu alu_t;

typedef enum {
    ALU_OK,
    ALU_ERR_NULL_ARGUMENT,
    ALU_ERR_ALREADY_INITIATED,
    ALU_ERR_MEM_ALLOCATION
} alu_err_t;

alu_err_t create_alu(alu_t** out_new_alu);
alu_err_t destroy_alu(alu_t** alu);

#endif