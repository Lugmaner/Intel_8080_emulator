#include "alu.h"

struct alu
{
    bool S2, S1, S0;    // 1=TRUE, 0=FALSE
    reg_t a, b;    // input regs
};


alu_err_t create_alu(alu_t** out_alu){
    if(!out_alu){
        return ALU_ERR_NULL_ARGUMENT;
    }

    if(*out_alu){
        return ALU_ERR_ALREADY_INITIATED;
    }

    *out_alu = NULL;

    alu_t* new_alu = calloc(1u, sizeof(*new_alu));
    if(!new_alu){
        return ALU_ERR_MEM_ALLOCATION;
    }

    *out_alu = new_alu;

    return ALU_OK;
}

alu_err_t destroy_alu(alu_t** alu){
    if(!alu){
        return ALU_ERR_NULL_ARGUMENT;
    }

    if(!*alu){
        return ALU_OK;
    }

    free(*alu);

    *alu = NULL;

    return ALU_OK;
}