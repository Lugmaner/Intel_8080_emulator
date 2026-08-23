#include "init.h"
#include "types.h"
#include "stdio.h"
#include "instructions.h"
#include "flags_makros.h"

void print_register(byte_t reg){
    for(uint8_t i = 0u; (i < sizeof(reg) || i < 8u); i++){
        uint8_t bit = (reg >> (7u - i)) & 1;
        printf("%u ", bit);
    }
    printf("\n");
}

void print_cpu(cpu_t cpu){
    printf("    A = ");
    print_register(cpu.A);

    printf("    B = ");
    print_register(cpu.B);

    printf("    C = ");
    print_register(cpu.C);

    printf("    D = ");
    print_register(cpu.D);

    printf("    E = ");
    print_register(cpu.E);

    printf("    H = ");
    print_register(cpu.H);

    printf("    L = ");
    print_register(cpu.L);
    printf("-------------------------------\n");
    printf("    FLAGS: S Z 0 H 0 P 1 C\n           ");
    print_register(cpu.flags);
    printf("-------------------------------\n");
    
    printf("    PC = ");
    print_register(cpu.PC);

    printf("    SP = ");
    print_register(cpu.SP);
}



int main(void){
    cpu_t cpu = {0u};

    printf("before init:\n");
    print_cpu(cpu);

    init_registers(&cpu);

    printf("after init:\n");
    print_cpu(cpu);

    ADD(&cpu, 5u);
    printf("after ADD:\n");
    print_cpu(cpu);

    S_C_FLAG(cpu.flags);
    printf("after setting C flag manually:\n");
    print_cpu(cpu);

    ADDC(&cpu, 249);
    printf("after ADDC:\n");
    print_cpu(cpu);

    return 0;
}