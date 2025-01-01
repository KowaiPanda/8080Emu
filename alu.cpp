#include <stdio.h>
#include <stdlib.h>
#include "emulator_shell.h"
#include "disassembler.h"

int parity(int x, int size) {
    int i, p = 0;
    x = (x & ((1 << size) - 1));
    for (i = 0; i < size; i++)
    {
        if (x & 0x1) p++;
        x = x >> 1;
    }
    return (0 == (p & 0x1));
}

void cc3(State8080* state, uint8_t ans) {
    state->cc.z = (ans == 0);
    state->cc.s = ((ans & 0x80) == 0x80);
    state->cc.p = parity(ans, 8);
}

void cc4(State8080* state, uint16_t ans) {
    state->cc.z = ((ans & 0xff) == 0);
    state->cc.s = ((ans & 0x80) == 0x80);
    state->cc.p = parity(ans & 0xff, 8);
    state->cc.cy = (ans > 0xff);
}

void writeMem(State8080* state, uint16_t address, uint8_t val) {
    if (address >= 0x2000) {
        uint16_t baseMemory = address % 0x2000;
        state->memory[baseMemory + 0x2000] = (val & 0xff);
        state->memory[baseMemory + 0x4000] = (val & 0xff);
    }
}

uint16_t formPair(uint8_t x, uint8_t y) {
    uint16_t offset = (x << 8) | (y);
    return offset;
}

uint16_t ReadWord(State8080* state, uint16_t pc) {
    return formPair(state->memory[pc + 1], state->memory[pc]);
}

uint16_t AdvanceWord(State8080* const state) {
    uint16_t result = ReadWord(state, state->pc);
    state->pc += 2;
    return result;
}

uint8_t ReadByte(State8080* state, uint16_t pc) {
    return state->memory[pc];
}

uint8_t AdvanceByte(State8080* const state) {
    uint8_t result = ReadByte(state, state->pc);
    state->pc += 1;
    return result;
}

uint8_t readHL(State8080* state) {
    return state->memory[formPair(state->h, state->l)];
}

void writeHL(State8080* state, uint8_t val) {
    writeMem(state, formPair(state->h, state->l), val);
}

void LXI(State8080* state, uint8_t* a, uint8_t* b) {
    uint16_t opcode = AdvanceWord(state);
    *a = (opcode >> 8) & 0xff;
    *b = opcode & 0xff;
}

void INX(State8080* state, uint8_t* a, uint8_t* b) {
    uint16_t result = ((*a << 8) | (*b & 0xFF)) + 1;
    *a = (result >> 8) & 0xff;
    *b = result & 0xff;
}

void DCX(State8080* state, uint8_t* a, uint8_t* b) {
    uint16_t result = ((*a << 8) | (*b & 0xFF)) - 1;
    *a = (result >> 8) & 0xff;
    *b = result & 0xff;
}

uint8_t INR(State8080* state, uint8_t registerVal) {
    uint8_t result = registerVal + 1;
    cc3(state, result);
    return result;
}

uint8_t DCR(State8080* state, uint8_t registerVal) {
    uint8_t result = registerVal - 1;
    cc3(state, result);
    return result;
}

void ADD(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a + x;
    cc4(state, ans);
    state->a = ans & 0xff;
}

void ADC(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a + x + (uint16_t)state->cc.cy;
    cc4(state, ans);
    state->a = ans & 0xff;
}

void SUB(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a - x;
    cc4(state, ans);
    state->a = ans & 0xff;
}

void SBB(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a - x - (uint16_t)state->cc.cy;
    cc4(state, ans);
    state->a = ans & 0xff;
}

void ANA(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a & x;
    cc3(state, ans);
    state->cc.cy = 0;
    state->a = ans & 0xff;
}

void ORA(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a | x;
    cc3(state, ans);
    state->cc.cy = 0;
    state->a = ans & 0xff;
}

void XRA(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a ^ x;
    cc3(state, ans);
    state->cc.cy = 0;
    state->a = ans & 0xff;
}

void CMP(State8080* state, uint16_t x) {
    uint16_t ans = (uint16_t)state->a - x;
    cc4(state, ans);
}

void JMP(State8080* state) {
    uint16_t address = AdvanceWord(state);
    state->pc = address;
}

void JNZ(State8080* state) {
    if (!state->cc.z) { JMP(state); }
    else { AdvanceWord(state); }
}

void JNC(State8080* state) {
    if (!state->cc.cy) { JMP(state); }
    else { AdvanceWord(state); }
}

void JPO(State8080* state) {
    if (!state->cc.p) { JMP(state); }
    else { AdvanceWord(state); }
}

void JP(State8080* state) {
    if (!state->cc.s) { JMP(state); }
    else { AdvanceWord(state); }
}

void JZ(State8080* state) {
    if (state->cc.z) { JMP(state); }
    else { AdvanceWord(state); }
}

void JC(State8080* state) {
    if (state->cc.cy) { JMP(state); }
    else { AdvanceWord(state); }
}

void JPE(State8080* state) {
    if (state->cc.p) { JMP(state); }
    else { AdvanceWord(state); }
}

void JM(State8080* state) {
    if (state->cc.s) { JMP(state); }
    else { AdvanceWord(state); }
}

void RET(State8080* state) {
    uint16_t result = formPair(state->memory[state->sp + 1], state->memory[state->sp] & 0xFF);
    state->pc = result;
    state->sp += 2;
}

void RNZ(State8080* state) {
    if (!state->cc.z) { RET(state); }
}

void RNC(State8080* state) {
    if (!state->cc.cy) { RET(state); }
}

void RPO(State8080* state) {
    if (!state->cc.p) { RET(state); }
}

void RP(State8080* state) {
    if (!state->cc.s) { RET(state); }
}

void RZ(State8080* state) {
    if (state->cc.z) { RET(state); }
}

void RC(State8080* state) {
    if (state->cc.cy) { RET(state); }
}

void RM(State8080* state) {
    if (state->cc.s) { RET(state); }
}

void CALL(State8080* state) {
    uint16_t nextAddress = state->pc + 2; 
    uint8_t HReg = (nextAddress >> 8) & 0xFF;
    uint8_t LReg = (nextAddress) & 0xFF;
    writeMem(state, state->sp - 1, HReg);
    writeMem(state, state->sp - 2, LReg);
    state->sp -= 2;
    state->pc = AdvanceWord(state);
}

void CNZ(State8080* state) {
    if (!state->cc.z) { CALL(state); }
    else { AdvanceWord(state); }
}

void CNC(State8080* state) {
    if (!state->cc.cy) { CALL(state); }
    else { AdvanceWord(state); }
}

void CPO(State8080* state) {
    if (!state->cc.p) { CALL(state); }
    else { AdvanceWord(state); }
}

void CP(State8080* state) {
    if (!state->cc.s) { CALL(state); }
    else { AdvanceWord(state); }
}

void CZ(State8080* state) {
    if (state->cc.z) { CALL(state); }
    else { AdvanceWord(state); }
}

void CC(State8080* state) {
    if (state->cc.cy) { CALL(state); }
    else { AdvanceWord(state); }
}

void CPE(State8080* state) {
    if (state->cc.p) { CALL(state); }
    else { AdvanceWord(state); }
}

void CM(State8080* state) {
    if (state->cc.s) { CALL(state); }
    else { AdvanceWord(state); }
}

void RST(State8080* state, uint8_t N) {
    uint8_t HReg = (state->pc >> 8) & 0xFF;
    uint8_t LReg = state->pc & 0xFF;
    writeMem(state, state->sp - 1, HReg);
    writeMem(state, state->sp - 2, LReg);
    state->sp = state->sp - 2;
    state->pc = N * 8;
}

void PUSH(State8080* state, uint8_t high, uint8_t low) {
    writeMem(state, state->sp - 1, high);
    writeMem(state, state->sp - 2, low);
    state->sp -= 2;
}

void POP(State8080* state, uint8_t* high, uint8_t* low) {
    *low = state->memory[state->sp];
    *high = state->memory[state->sp + 1];
    state->sp += 2;
}

void STA(State8080* state) {
    uint16_t address = AdvanceWord(state);
    writeMem(state, address, state->a);
}

void SHLD(State8080* state) {
    uint16_t address = AdvanceWord(state);
    writeMem(state, address, state->l);
    writeMem(state, address + 1, state->h);
}

void LHLD(State8080* state) {
    uint16_t address = AdvanceWord(state);
    state->l = state->memory[address];
    state->h = state->memory[address + 1];
}

void RLC(State8080* state) {
    uint16_t result = (state->a) << 1;
    result |= ((state->a & 0xFF) >> 7);
    state->cc.cy = result & 0x01;
    state->a = result & 0xFF;
}

void RAL(State8080* state) {
    uint16_t result = (state->a) << 1;
    result |= state->cc.cy;
    state->cc.cy = ((state->a & 0xFF) >> 7) & 0x01;
    state->a = result;
}

void RRC(State8080* state) {
    uint8_t x = state->a;
    state->a = ((x >> 1) | (x & 1) << 7);
    state->cc.cy = ((x & 1) == 1);
}

void RAR(State8080* state) {
    uint16_t result = (state->a) >> 1;
    result |= (state->cc.cy << 7);
    state->cc.cy = (state->a & 0x01);
    state->a = result & 0xff;
}

void DAD(State8080* state, uint8_t x, uint8_t y) {
    uint32_t hl = formPair(state->h, state->l);
    uint32_t pair = formPair(x, y);
    uint32_t ans = hl + pair;
    state->h = (ans & 0xff00) >> 8;
    state->l = ans & 0xff;
    state->cc.cy = (ans > 0xffff);
}

void DAA(State8080* state) {
    uint16_t result = state->a;
    if (((state->a & 0x0F) > 9) || state->cc.ac) {
        result += 6;
        state->cc.ac = 0;
    }

    if ((((result >> 4) & 0x0F) > 9) || state->cc.cy) {
        result += (6 << 4);
    }
    state->cc.cy = (result >> 8) & 0x01;
    cc3(state, state->a);
    state->a = result & 0xFF;
}

void MachineIn(State8080* state) {
    uint8_t portNum = state->memory[state->pc];
    state->pc++;
    state->a = state->IOPorts[portNum];
    switch (portNum) {
    case 3:
        state->a = (state->shiftRegister >> (8 - state->shiftOffset)) & 0xFF;
        break;
    }

}

void MachineOut(State8080* state) {
    uint8_t portNum = state->memory[state->pc];
    state->pc++;
    switch (portNum) {
    case 2:
        state->shiftOffset = state->a & 0x07;
        break;
    case 4:
        uint16_t mask = 0xFF00;
        uint16_t value = state->a << 8;
        state->shiftRegister &= ~(mask >> state->shiftOffset);
        state->shiftRegister |= value >> state->shiftOffset;
    }
}