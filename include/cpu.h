#ifndef CPU_H
#define CPU_H

#include "alu.h"

typedef struct cpu cpu_t;

cpu_err_t create_cpu(cpu_t** out_cpu, alu_err_t* out_alu_err);
cpu_err_t destroy_cpu(cpu_t** cpu, alu_err_t* out_alu_err);

void print_cpu(const cpu_t* in_cpu);

#endif