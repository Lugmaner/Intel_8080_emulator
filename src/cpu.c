#include "cpu.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define GPR_NUM 13u

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
    alu_t* alu;
};

cpu_err_t create_cpu(cpu_t** out_cpu, alu_err_t* out_alu_err){
    if(!out_cpu){
        return CPU_ERR_NULL_ARGUMENT;
    }

    if(*out_cpu){
        return CPU_ERR_ALREADY_INITIATED;
    }

    *out_cpu = NULL;

    alu_t* new_alu = NULL;
    alu_err_t err = create_alu(&new_alu);
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

    new_cpu->alu = new_alu;

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
}

void print_cpu_err(cpu_err_t in_err){
    switch (in_err)
    {
    case CPU_OK:
        printf("CPU OK\n");
        break;
    case CPU_ERR_NULL_ARGUMENT:
        printf("CPU ERR (NULL ARGUMENT)\n");
        break;
    case CPU_ERR_ALREADY_INITIATED:
        printf("CPU ERR (ALREADY INITIATED)\n");
        break;
    case CPU_ERR_MEM_ALLOCATION:
        printf("CPU ERR (FAILED TO ALLOCATE MEMMORY)\n");
        break;
    case CPU_ERR_ALU_CREATION:
        printf("CPU ERR (ALU ERR, PLS CHECK ALU ERR CODE)\n");
        break;
    case CPU_ERR_ALU_DESTROY:
        printf("CPU ERR (ALU ERR, PLS CHECK ALU ERR CODE)\n");
        break;
    default:
        break;
    }
}