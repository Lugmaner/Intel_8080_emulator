#include "init.h"
#include "types.h"
#include "stdio.h"
#include "instructions.h"
#include "flags_makros.h"

void print_8_bit_register(byte_t reg){
    for(uint8_t i = 0u; i < 8u; i++){
        uint8_t bit = (reg >> (7u - i)) & 1;
        printf("%u ", bit);
    }
    printf("\n");
}

void print_16_bit_register(word_t reg){
    for(uint8_t i = 0u; i < 16u; i++){
        uint8_t bit = (reg >> (15u - i)) & 1;
        printf("%u ", bit);
    }
    printf("\n");
}

void print_cpu(cpu_t cpu){
    printf("    A = ");
    print_8_bit_register(cpu.A);

    printf("    B = ");
    print_8_bit_register(cpu.B);

    printf("    C = ");
    print_8_bit_register(cpu.C);

    printf("    D = ");
    print_8_bit_register(cpu.D);

    printf("    E = ");
    print_8_bit_register(cpu.E);

    printf("    H = ");
    print_8_bit_register(cpu.H);

    printf("    L = ");
    print_8_bit_register(cpu.L);
    printf("-------------------------------\n");
    printf("    FLAGS: S Z 0 H 0 P 1 C\n           ");
    print_8_bit_register(cpu.flags);
    printf("-------------------------------\n");
    
    printf("    PC = ");
    print_16_bit_register(cpu.PC);

    printf("    SP = ");
    print_16_bit_register(cpu.SP);
}



int main(void){
    cpu_t cpu = {0u};

    printf("before init:\n");
    print_cpu(cpu);

    init_registers(&cpu);

    printf("after init:\n");
    print_cpu(cpu);

    ADD(&cpu, 5u);
    printf("after ADD 5:\n");
    print_cpu(cpu);

    S_C_FLAG(cpu.flags);
    printf("after setting C flag manually:\n");
    print_cpu(cpu);

    ADDC(&cpu, 2);
    printf("after ADDC 2 (carry makes result = 8):\n");
    print_cpu(cpu);

    SUB(&cpu, 8);
    printf("after SUB 8 (Z flag should be 1):\n");
    print_cpu(cpu);

    ADD(&cpu, 5u);
    printf("after ADD 5:\n");
    print_cpu(cpu);

    S_C_FLAG(cpu.flags);
    printf("after setting C flag manually again:\n");
    print_cpu(cpu);

    SBB(&cpu, 4);
    printf("after SBB 4 (carry makes result = 0):\n");
    print_cpu(cpu);


    return 0;
}