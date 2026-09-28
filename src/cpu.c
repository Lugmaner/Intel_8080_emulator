#include "cpu.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define GPR_NUM 13u

typedef uint32_t reg_t;

typedef enum {
    CPU_OK,
    CPU_ERR_NULL_ARGUMENT,
    CPU_ERR_ALREADY_INITIATED,
    CPU_ERR_MEM_ALLOCATION,
    CPU_ERR_ALU_CREATION,
    CPU_ERR_ALU_DESTROY
} cpu_err_t;

struct cpu
{
    reg_t r[GPR_NUM];

    reg_t sp;   //stack pointer
    reg_t lr;   //link register
    reg_t pc;   //program counter

    reg_t cpsr; /* Bit 31: N,
                       30: Z,
                       29: C,
                       28: V,
                        7: I,
                        6: F,
                        4: M4,
                        3: M3,
                        2: M2,
                        1: M1,
                        0: M0
                */
    alu_t* const alu;
};

cpu_err_t create_cpu(cpu_t** out_cpu, alu_err_t* out_alu_err){
    if(!out_cpu){
        *out_cpu = NULL;
        return CPU_ERR_NULL_ARGUMENT;
    }

    if(*out_cpu){
        return CPU_ERR_ALREADY_INITIATED;
    }

    *out_cpu = NULL;

    alu_t* new_alu = NULL;
    alu_err_t err = create_new_alu(&new_alu);
    if(err != ALU_OK){
        *out_alu_err = err;
        return CPU_ERR_ALU_CREATION;
    }

    *out_alu_err = ALU_OK;

    cpu_t* new_cpu = calloc(1u, sizeof(*new_cpu));
    if(!new_cpu){
        destroy_alu(&new_alu);
        return CPU_ERR_MEM_ALLOCATION;
    }

    *out_cpu = new_cpu;

    return CPU_OK;
}

cpu_err_t destroy_cpu(cpu_t** cpu, alu_err_t* out_alu_err){
    if(!cpu){
        *cpu = NULL;
        return CPU_ERR_NULL_ARGUMENT;
    }

    if(!*cpu){
        return CPU_OK;
    }

    alu_err_t err = destroy_alu(&((*cpu)->alu));
    if(err != ALU_OK){
        *out_alu_err = err;
        return CPU_ERR_ALU_DESTROY;
    }

    *out_alu_err = ALU_OK;

    free(*cpu);

    *cpu = NULL;

    return CPU_OK;
}

void print_cpu(const cpu_t* in_cpu){
    for(uint8_t i = 0u; i < GPR_NUM; i++){
        printf("r%d: 0x%08" PRIX32 "\n", i, in_cpu->r[i]);
    }

    printf("sp: 0x%08" PRIX32 "\n", in_cpu->sp);
    printf("lr: 0x%08" PRIX32 "\n", in_cpu->lr);
    printf("pc: 0x%08" PRIX32 "\n", in_cpu->pc);

    printf("cpsr: 0x%08" PRIX32 "\n", in_cpu->cpsr);

    printf("alu is valid = %s", in_cpu->alu != NULL ? "true" : "false");

    return CPU_OK;
}