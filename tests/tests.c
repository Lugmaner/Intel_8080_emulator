#include <assert.h>
#include <stdio.h>

#include "types.h"
#include "init.h"
#include "instructions.h"
#include "flags_makros.h"

static unsigned int expected_even_parity(byte_t reg){
    unsigned int ones_count = 0u;

    for (unsigned int i = 0u; i < 8u; i++) {
        if (((reg >> i) & 1u) != 0u) {
            ones_count++;
        }
    }

    return (ones_count % 2u) == 0u;
}

static void assert_zsp_flags(const cpu_t *cpu)
{
    assert(R_Z_FLAG(cpu->flags) == (cpu->A == 0u));
    assert(R_S_FLAG(cpu->flags) == ((cpu->A & 0x80u) != 0u));
    assert(R_P_FLAG(cpu->flags) == expected_even_parity(cpu->A));
}

static void test_ADD_basic(void){
    cpu_t cpu;

    /* init_registers */
    assert(init_registers(&cpu) == 0);

    /* simple addition */
    assert(ADD(&cpu, 5) == 0);
    assert(cpu.A == (byte_t)5u);

    for (unsigned int a = 0u; a <= 255u; a++){
        for (unsigned int b = 0u; b <= 255u; b++){
            cpu.A = (byte_t)a;

            assert(ADD(&cpu, (byte_t)b) == 0);
            unsigned int expected = a + b;

            /* result */
            assert(cpu.A == (byte_t)expected);

            /* carry */
            assert(R_C_FLAG(cpu.flags) == (expected > 255u));

            /* auxiliary carry*/
            unsigned int expected_ac = ((a & 0x0Fu) + (b & 0x0Fu)) > 0x0Fu;
            assert(R_AC_FLAG(cpu.flags) == expected_ac);

            /* zero, sign, parity */
            assert_zsp_flags(&cpu);
        }
    }
}

static void test_SUB_basic(void){
    cpu_t cpu;

    /* init_registers */
    assert(init_registers(&cpu) == 0);

    cpu.A = 10u;
    /* simple subtraction */
    assert(SUB(&cpu, 5) == 0);
    assert(cpu.A == (byte_t)5u);

    for (unsigned int a = 0u; a <= 255u; a++) {
        for (unsigned int b = 0u; b <= 255u; b++) {
            cpu.A = (byte_t)a;

            assert(SUB(&cpu, (byte_t)b) == 0);

            byte_t expected = (byte_t)(a - b);

            /* result */
            assert(cpu.A == expected);

            /* carry */
            assert(R_C_FLAG(cpu.flags) == (a < b));

            /* auxiliary carry*/
            unsigned int expected_ac = (a & 0x0Fu) >= (b & 0x0Fu);
            assert(R_AC_FLAG(cpu.flags) == expected_ac);

            /* zero, sign, parity */
            assert_zsp_flags(&cpu);
        }
    }
}


int main(void){
    
    test_ADD_basic();
    test_SUB_basic();

    printf("All tests passed!\n");

    return 0;
}