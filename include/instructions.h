#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"

int ADD(cpu_t* cpu, byte_t B);
int ADDC(cpu_t* cpu, byte_t B);

int SUB(cpu_t* cpu, byte_t B);
int SBB(cpu_t* cpu, byte_t B);

#endif