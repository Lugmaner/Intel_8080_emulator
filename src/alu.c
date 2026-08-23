#include "alu.h"
#include "types.h"

int full_adder_job(full_adder_t* adder){
    if(!adder){
        return -1;
    }

    adder->C_out = (adder->A & adder->B) | (adder->C_in & (adder->A ^ adder->B));
    adder->S = adder->A ^ adder->C_in ^ adder->B;

    return 0;
}

alu_result_t alu_add8(byte_t A, byte_t B, uint8_t C_in){
    alu_result_t alu_result = {
        .result = 0u,
        .C_out = 0u,
        .aux_carry = 0u,
        .parity_flag = 1u,
        .err = 0u
    };

    full_adder_t full_adder = {
        .A = 0u,
        .B = 0u,
        .C_out = 0u,
        .C_in = C_in,
        .S = 0u
    };

    for(uint8_t i = 0u; i < 8u; i++){
        full_adder.A = (A >> i) & 1u;
        full_adder.B = (B >> i) & 1u;
        
        if(full_adder_job(&full_adder) != 0){
            alu_result.err = 1u;
        }
        
        // flip Parity for each 1
        if(full_adder.S == 1u){
            alu_result.parity_flag ^= 1u;
        }

        // check for Auxiliary carry
        if (i == 3u) {
            if (full_adder.C_out){
                alu_result.aux_carry = 1u;
            }
            else{
                alu_result.aux_carry = 0u;
            }
        }

        // add full adder result
        alu_result.result = (byte_t)((alu_result.result & ~(1u << i)) | (full_adder.S << i));

        full_adder.C_in = full_adder.C_out;
    }

    alu_result.C_out = full_adder.C_out;

    return alu_result;
}