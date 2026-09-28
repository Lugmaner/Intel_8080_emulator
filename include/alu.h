#ifndef ALU_H
#define ALU_H

typedef struct alu alu_t;

typedef enum {
    ALU_OK
} alu_err_t;

alu_err_t create_new_alu(alu_t** out_new_alu);
alu_err_t destroy_alu(alu_t** alu);

#endif