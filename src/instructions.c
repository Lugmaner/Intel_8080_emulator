#include "instructions.h"
#include "flags_makros.h"

static int update_CZS_flags(cpu_t* cpu, uint8_t C_out){
    if(!cpu) {
        return -1;
    }

    // check for carry
    if(C_out == 1u){
        S_C_FLAG(cpu->flags);
    }
    else{
        DEL_C_FLAG(cpu->flags);
    }

    // check for zero
    if(cpu->A == 0u){
        S_Z_FLAG(cpu->flags);
    }
    else{
        DEL_Z_FLAG(cpu->flags);
    }

    // check sign
    if(cpu->A & (1u << 7u)){
        S_S_FLAG(cpu->flags);
    }
    else{
        DEL_S_FLAG(cpu->flags);
    }

    return 0;
}

typedef struct
{
    unsigned int A : 1;
    unsigned int B : 1;
    unsigned int C_in : 1;

    unsigned int C_out : 1;
    unsigned int S : 1;
} full_adder_t;

static int full_adder_job(full_adder_t* adder){
    if(!adder){
        return -1;
    }

    adder->C_out = (adder->A & adder->B) | (adder->C_in & (adder->A ^ adder->B));
    adder->S = adder->A ^ adder->C_in ^ adder->B;

    return 0;
}

int ADD(cpu_t* cpu, byte_t B){
    if (!cpu) {
        return -1;
    }
    
    full_adder_t full_adder = {
        .A = 0u,
        .B = 0u,
        .C_out = 0u,
        .C_in = 0u,
        .S = 0u
    };

    S_P_FLAG(cpu->flags);

    for(uint8_t i = 0u; i < 8u; i++){
        full_adder.A = (cpu->A >> i) & 1u;
        full_adder.B = (B >> i) & 1u;
        
        if(full_adder_job(&full_adder) != 0){
            return -1;
        }
        
        // flip Parity for each 1
        if(full_adder.S == 1u){
            F_P_FLAG(cpu->flags);
        }

        // check for Auxiliary carry
        if (i == 3u) {
            if (full_adder.C_out){
                S_AC_FLAG(cpu->flags);
            }
            else{
                DEL_AC_FLAG(cpu->flags);
            }
        }

        // add full adder result
        cpu->A = (byte_t)((cpu->A & ~(1u << i)) | (full_adder.S << i));

        full_adder.C_in = full_adder.C_out;
    }

    if(update_CZS_flags(cpu, full_adder.C_out) != 0){
        return -1;
    }

    return 0;
}