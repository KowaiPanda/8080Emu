#ifndef ALU
#define ALU

#include "emulator_shell.h"

int parity(int x, int size);
void cc3(State8080* state, uint8_t ans);
void cc4(State8080* state, uint16_t ans);
void writeMem(State8080* state, uint16_t address, uint8_t val);
uint16_t formPair(uint8_t x, uint8_t y);
uint8_t readHL(State8080* state);
void writeHL(State8080* state, uint8_t val);
uint16_t ReadWord(State8080* state, uint16_t pc);
uint16_t AdvanceWord(State8080* const state);
uint8_t ReadByte(State8080* state, uint16_t pc);
uint8_t AdvanceByte(State8080* const state);

void LXI(State8080* state, uint8_t* a, uint8_t* b);
void INX(State8080* state, uint8_t* a, uint8_t* b);
void DCX(State8080* state, uint8_t* a, uint8_t* b);
uint8_t INR(State8080* state, uint8_t registerVal);
uint8_t DCR(State8080* state, uint8_t registerVal);
void ADD(State8080* state, uint16_t x);
void ADC(State8080* state, uint16_t x);
void SUB(State8080* state, uint16_t x);
void SBB(State8080* state, uint16_t x);
void DAD(State8080* state, uint8_t x, uint8_t y);

void ANA(State8080* state, uint16_t x);
void ORA(State8080* state, uint16_t x);
void XRA(State8080* state, uint16_t x);
void CMP(State8080* state, uint16_t x);

void JMP(State8080* state);
void JNZ(State8080* state);
void JNC(State8080* state);
void JPO(State8080* state);
void JP(State8080* state);
void JZ(State8080* state);
void JC(State8080* state);
void JPE(State8080* state);
void JM(State8080* state);

void RET(State8080* state);
void RNZ(State8080* state);
void RNC(State8080* state);
void RPO(State8080* state);
void RP(State8080* state);
void RZ(State8080* state);
void RC(State8080* state);
void RM(State8080* state);

void CALL(State8080* state);
void CNZ(State8080* state);
void CNC(State8080* state);
void CPO(State8080* state);
void CP(State8080* state);
void CZ(State8080* state);
void CC(State8080* state);
void CPE(State8080* state);
void CM(State8080* state);

void RST(State8080* state, uint8_t N);
void PUSH(State8080* state, uint8_t high, uint8_t low);
void POP(State8080* state, uint8_t* high, uint8_t* low);
void STA(State8080* state);
void SHLD(State8080* state);
void LHLD(State8080* state);

void RLC(State8080* state);
void RAL(State8080* state);
void RRC(State8080* state);
void RAR(State8080* state);
void DAA(State8080* state);

void MachineIn(State8080* state);
void MachineOut(State8080* state);

#endif