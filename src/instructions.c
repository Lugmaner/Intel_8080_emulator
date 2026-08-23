#include "instructions.h"
#include "flags_makros.h"
#include "alu.h"

static int update_CZS_flags(cpu_t* cpu, uint8_t C_out);
static int ADD_internal(cpu_t *cpu, byte_t B, uint8_t carry_in);

static int update_CZS_flags(cpu_t* cpu, uint8_t C_out){
    if(!cpu) {
        return -1;
    }

    // check and set carry
    if(C_out == 1u){
        S_C_FLAG(cpu->flags);
    }
    else{
        DEL_C_FLAG(cpu->flags);
    }

    // check and set zero
    if(cpu->A == 0u){
        S_Z_FLAG(cpu->flags);
    }
    else{
        DEL_Z_FLAG(cpu->flags);
    }

    // check and set sign
    if(cpu->A & (1u << 7u)){
        S_S_FLAG(cpu->flags);
    }
    else{
        DEL_S_FLAG(cpu->flags);
    }

    return 0;
}

static int ADD_internal(cpu_t *cpu, byte_t B, uint8_t carry_in){
    alu_result_t alu_res = alu_add8(cpu->A, B, carry_in);
    if(alu_res.err == 1u){
        return -1;
    }

    cpu->A = alu_res.result;

    if(update_CZS_flags(cpu, alu_res.C_out) != 0){
        return -1;
    }

    if(alu_res.parity_flag == 1u){
        S_P_FLAG(cpu->flags);
    }
    else{
        DEL_P_FLAG(cpu->flags);
    }

    if(alu_res.aux_carry == 1u){
        S_AC_FLAG(cpu->flags);
    }
    else{
        DEL_AC_FLAG(cpu->flags);
    }

    return 0;
}

static int SUB_internal(cpu_t *cpu, byte_t B, uint8_t carry_in){
    if(!cpu){
        return -1;
    }

    alu_result_t alu_res = alu_add8(cpu->A, (byte_t)(~B), carry_in);
    if(alu_res.err == 1u){
        return -1;
    }

    cpu->A = alu_res.result;

    if(update_CZS_flags(cpu, !alu_res.C_out) != 0){
        return -1;
    }

    if(alu_res.parity_flag == 1u){
        S_P_FLAG(cpu->flags);
    }
    else{
        DEL_P_FLAG(cpu->flags);
    }

    if(alu_res.aux_carry == 1u){
        S_AC_FLAG(cpu->flags);
    }
    else{
        DEL_AC_FLAG(cpu->flags);
    }

    return 0;
}

int ADDC(cpu_t* cpu, byte_t B){
    if (!cpu) {
        return -1;
    }

    return ADD_internal(cpu, B, R_C_FLAG(cpu->flags));
}

int ADD(cpu_t* cpu, byte_t B){
    if (!cpu) {
        return -1;
    }

    return ADD_internal(cpu, B, 0u);
}

int SUB(cpu_t* cpu, byte_t B){
    if (!cpu) {
        return -1;
    }

    return SUB_internal(cpu, B, 1u);
}

int SBB(cpu_t *cpu, byte_t B){
    uint8_t borrow = R_C_FLAG(cpu->flags);

    return SUB_internal(cpu, B, !borrow);
}