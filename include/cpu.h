#ifndef CPU_H
#define CPU_H

#include "alu.h"
#include "types.h"

typedef enum {
    CPU_OK,
    CPU_ERR_NULL_ARGUMENT,
    CPU_ERR_ALREADY_INITIATED,
    CPU_ERR_MEM_ALLOCATION,
    CPU_ERR_ALU_CREATION,
    CPU_ERR_ALU_DESTROY
} cpu_err_t;

typedef struct cpu cpu_t;

cpu_err_t create_cpu(cpu_t** out_cpu, alu_err_t* out_alu_err);
cpu_err_t destroy_cpu(cpu_t** cpu, alu_err_t* out_alu_err);

void print_cpu(const cpu_t* in_cpu);
void print_cpu_err(cpu_err_t in_err);

#endif