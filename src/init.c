#include "init.h"

int init_status_register(byte_t* flags){
    if(!flags){
        return -1;
    }

    *flags = 0u;

    *flags |= (1u << 1);

    return 0;
}

int init_registers(cpu_t* cpu){
    if(!cpu){
        return -1;
    }

    cpu->A = 0;
    cpu->B = 0;
    cpu->C = 0;
    cpu->D = 0;
    cpu->E = 0;
    cpu->H = 0;
    cpu->L = 0;

    cpu->PC = 0;
    cpu->SP = 0;

    if(init_status_register(&cpu->flags) != 0){
        return -1;
    }

    return 0;
}