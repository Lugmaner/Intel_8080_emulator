#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

//arithmetical, logical
int ADD();
int ADC();
int SUB();
int SBC();
int RSB();
int RSC();
int MUL();
int MLA();

int AND();
int ORR();
int EOR();
int BIC();

int MOV();
int MVN();

//comparings
int CMP();
int CMN();
int TST();
int TEQ();

//jumps
int B();
int BL();

//Barrel-Shifter
int LSL();
int LSR();
int ASR();
int ROR();
int RRX();

#endif