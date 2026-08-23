#include "init.h"
#include "types.h"
#include "stdio.h"

void print_flags(byte_t flags){
    for(uint8_t i = 0u; (i < sizeof(flags) || i < 8); i++){
        uint8_t bit = (flags >> (7 - i)) & 1;
        printf("%u", bit);
    }
    printf("\n");
}

int main(void){
    cpu_t cpu = {0};

    print_flags(cpu.flags);

    init_status_register(&cpu.flags);

    print_flags(cpu.flags);

    return 0;
}