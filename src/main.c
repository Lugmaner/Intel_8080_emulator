#include "cpu.h"
#include <stdio.h>





int main(void){

    cpu_t* new_cpu;
    cpu_err_t cpu_err = CPU_OK;
    alu_err_t alu_err = ALU_OK;
    cpu_err = create_cpu(&new_cpu, &alu_err);
    if(cpu_err != CPU_OK){
        print_cpu_err(cpu_err);
        return cpu_err;
    }

    print_cpu(new_cpu);

    cpu_err = destroy_cpu(&new_cpu, &alu_err);
    if(cpu_err != CPU_OK){
        print_cpu_err(cpu_err);
        return cpu_err;
    }

    return 0;
}