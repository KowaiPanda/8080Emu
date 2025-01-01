#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "emulator_shell.h"
//#include "disassembler.h"
#include "alu.h"

void Emulate8080Op(State8080* state) {
	unsigned char *opcode = &state->memory[state->pc];
    //Disassemble8080Op(state->memory, state->pc);
    state->pc++;

    switch (*opcode)
    {
        //NOP
        case 0x00:
        case 0x08:
        case 0x10:
        case 0x18:
        case 0x28:
        case 0x30:
        case 0x38:
            break;
        case 0x01:  //LXI B,D16
            LXI(state, &state->b, &state->c); break;
        case 0x02:  //STAX B
            state->memory[formPair(state->b, state->c)] = state->a; break;
        case 0x03:  //INX B
            INX(state, &state->b, &state->c); break;
        case 0x04: //INR B
            state->b = INR(state, state->b); break;
        case 0x05:  //DCR B
            state->b = DCR(state, state->b); break;
        case 0x06:  //MVI B,D8
            state->b = AdvanceByte(state); break;
        case 0x07:  //RLC
            RLC(state); break;
        case 0x09:  //DAD B
            DAD(state, state->b, state->c); break;
        case 0x0a:  //LDAX B
            state->a = state->memory[formPair(state->b, state->c)]; break;
        case 0x0b:  //DCX B
            DCX(state, &state->b, &state->c); break;
        case 0x0c:  //INR C
            state->c = INR(state, state->c); break;
        case 0x0d:  //DCR C
            state->c = DCR(state, state->c); break;
        case 0x0e:  //MVI C,D8
            state->c = AdvanceByte(state); break;
        case 0x0f:  //RRC
            RRC(state); break;
        case 0x11:  //LXI D,D16
            LXI(state, &state->d, &state->e); break;
        case 0x12:  //STAX D
            state->memory[formPair(state->d, state->e)] = state->a; break;
        case 0x13:  //INX D
            INX(state, &state->d, &state->e);  break;
        case 0x14: //INR D
            state->d = INR(state, state->d); break;
        case 0x15:  //DCR D
            state->d = DCR(state, state->d); break;
        case 0x16:  //MVI D
            state->d = AdvanceByte(state); break;
        case 0x17:  //RAL
            RAL(state); break;
        case 0x19:  //DAD D
            DAD(state, state->d, state->e); break;
        case 0x1a:  //LDAX D
            state->a = state->memory[formPair(state->d, state->e)]; break;
        case 0x1b:  //DCX D
            DCX(state, &state->d, &state->e); break;
        case 0x1c:  //INR E
            state->e = INR(state, state->e); break;
        case 0x1d:  //DCR E
            state->e = DCR(state, state->e); break;
        case 0x1e:  //MVI E
            state->e = AdvanceByte(state); break;
        case 0x1f:  //RAR
            RAR(state); break;
        case 0x21:  //LXI H,D16
            LXI(state, &state->h, &state->l); break;
        case 0x22:  //SHLD adr
            SHLD(state); break;
        case 0x23:  //INX H
            INX(state, &state->h, &state->l);  break;
        case 0x24:  //INR H
            state->h = INR(state, state->h); break;
        case 0x25:  //DCR H
            state->h = DCR(state, state->h); break;
        case 0x26:  //MVI H,D8
            state->h = AdvanceByte(state); break;
        case 0x27:  //DAA
            DAA(state); break;
        case 0x29:  //DAD H
            DAD(state, state->h, state->l); break;
        case 0x2a:  //LHLD adr
            LHLD(state); break;
        case 0x2b:	//DCX H
            DCX(state, &state->h, &state->l); break;
        case 0x2c:  //INR L
            state->l = INR(state, state->l); break;
        case 0x2d:  //DCR L
            state->l = DCR(state, state->l); break;
        case 0x2e:  //MVI L
            state->l = AdvanceByte(state); break;
        case 0x2f:  //CMA
            state->a = ~state->a; break;
        case 0x31:  //LXI SP,D16
            state->sp = AdvanceWord(state); break;
        case 0x32:  //STA adr
            STA(state); break;
        case 0x33:  //INX SP
            state->sp++; break;
        case 0x34:  //INR M
            state->memory[formPair(state->h, state->l)] = INR(state, state->memory[formPair(state->h, state->l)]); break;
        case 0x35:  //DCR M
            state->memory[formPair(state->h, state->l)] = DCR(state, state->memory[formPair(state->h, state->l)]); break;
        case 0x36:  //MVI M,D8
            state->memory[formPair(state->h, state->l)] = AdvanceByte(state);  break;
        case 0x37:  //STC
            state->cc.cy = 1; break;
        case 0x39:  //DAD SP
        {
            uint32_t pair = (state->h << 8) | (state->l);
            pair = pair + (uint32_t)state->sp;
            state->cc.cy = (pair > 0xff);
            state->h = (pair & 0xff00) >> 8;
            state->l = pair & 0xff;
            break;
        }
        case 0x3a:  //LDA adr
            state->a = state->memory[AdvanceWord(state)]; break;
        case 0x3b:  //DCX A
           state->sp--; break;
        case 0x3c:  //INR A
            state->a = INR(state, state->a); break;
        case 0x3d: //DCR A
            state->a = DCR(state, state->a); break;
        case 0x3e:  //MVI A,D8
            state->a = AdvanceByte(state); break;
        case 0x3f:  //CMC
            state->cc.cy = !state->cc.cy; break;
        case 0x40:  //MOV B,B
            state->b = state->b; break;
        case 0x41:  //MOV B,C
            state->b = state->c; break;
        case 0x42:  //MOV B,D
            state->b = state->d; break;
        case 0x43:  //MOV B,E
            state->b = state->e; break;
        case 0x44:  //MOV B,H
            state->b = state->h; break;
        case 0x45:  //MOV B,L
            state->b = state->l; break;
        case 0x46:  //MOV B,M
            state->b = state->memory[formPair(state->h, state->l)]; break;
        case 0x47:  //MOV B,A
            state->b = state->a; break;
        case 0x48:  //MOV C,B
            state->c = state->b; break;
        case 0x49:  //MOV C,C
            state->c = state->c; break;
        case 0x4a:  //MOV C,D
            state->c = state->d; break;
        case 0x4b:  //MOV C,E
            state->c = state->e; break;
        case 0x4c:  //MOV C,H
            state->c = state->h; break;
        case 0x4d:  //MOV C,L
            state->c = state->l; break;
        case 0x4e:  //MOV C,M
            state->c = state->memory[formPair(state->h, state->l)]; break;
        case 0x4f:  //MOV C,A
            state->c = state->a; break;
        case 0x50:  //MOV D,B
            state->d = state->b; break;
        case 0x51:  //MOV D,C
            state->d = state->c; break;
        case 0x52:  //MOV D,D
            state->d = state->d; break;
        case 0x53:  //MOV D,E
            state->d = state->e; break;
        case 0x54:  //MOV D,H
            state->d = state->h; break;
        case 0x55:  //MOV D,L
            state->d = state->l; break;
        case 0x56:  //MOV D,M
            state->d = state->memory[formPair(state->h, state->l)]; break;
        case 0x57:  //MOV D,A
            state->d = state->a; break;
        case 0x58:  //MOV E,B
            state->e = state->b; break;
        case 0x59:  //MOV E,C
            state->e = state->c; break;
        case 0x5a:  //MOV E,D
            state->e = state->d; break;
        case 0x5b:  //MOV E,E
            state->e = state->e; break;
        case 0x5c:  //MOV E,H
            state->e = state->h; break;
        case 0x5d:  //MOV E,L
            state->e = state->l; break;
        case 0x5e:  //MOV E,M
            state->e = state->memory[formPair(state->h, state->l)]; break;
        case 0x5f:  //MOV E,A
            state->e = state->a; break;
        case 0x60:  //MOV H,B
            state->h = state->b; break;
        case 0x61:  //MOV H,C
            state->h = state->c; break;
        case 0x62:  //MOV H,D
            state->h = state->d; break;
        case 0x63:  //MOV H,E
            state->h = state->e; break;
        case 0x64:  //MOV H,H
            state->h = state->h; break;
        case 0x65:  //MOV H,L
            state->h = state->l; break;
        case 0x66:  //MOV H,M
            state->h = state->memory[formPair(state->h, state->l)]; break;
        case 0x67:  //MOV H,A
            state->h = state->a; break;
        case 0x68:  //MOV L,B
            state->l = state->b; break;
        case 0x69:  //MOV L,C
            state->l = state->c; break;
        case 0x6a:  //MOV L,D
            state->l = state->d; break;
        case 0x6b:  //MOV L,E
            state->l = state->e; break;
        case 0x6c:  //MOV L,H
            state->l = state->h; break;
        case 0x6d:  //MOV L,L
            state->l = state->l; break;
        case 0x6e:  //MOV L,M
            state->l = state->memory[formPair(state->h, state->l)]; break;
        case 0x6f:  //MOV L,A 
            state->l = state->a; break;
        case 0x70:  //MOV M,B
            state->memory[formPair(state->h, state->l)] = state->b; break;
        case 0x71:  //MOV M,C
            state->memory[formPair(state->h, state->l)] = state->c; break;
        case 0x72:  //MOV M,D
            state->memory[formPair(state->h, state->l)] = state->d; break;
        case 0x73:  //MOV M,E
            state->memory[formPair(state->h, state->l)] = state->e; break;
        case 0x74:  //MOV M,H
            state->memory[formPair(state->h, state->l)] = state->h; break;
        case 0x75:  //MOV M,L
            state->memory[formPair(state->h, state->l)] = state->l; break;
        case 0x76:  //HLT
            exit(0);
        case 0x77:  //MOV M,A
            state->memory[formPair(state->h, state->l)] = state->a; break;
        case 0x78:  //MOV A,B
            state->a = state->b; break;
        case 0x79:  //MOV A,C
            state->a = state->c; break;
        case 0x7a:  //MOV A,D
            state->a = state->d; break;
        case 0x7b:  //MOV A,E
            state->a = state->e; break;
        case 0x7c:  //MOV A,H
            state->a = state->h; break;
        case 0x7d:  //MOV A,L
            state->a = state->l; break;
        case 0x7e:  //MOV A,M
            state->a = state->memory[formPair(state->h, state->l)]; break;
        case 0x7f:  //MOV A,A
            state->a = state->a; break;
        case 0x80: //ADD B
            ADD(state, state->b); break;
        case 0x81:	//ADD C
            ADD(state, state->c); break;
        case 0x82:	//ADD D
            ADD(state, state->d); break;
        case 0x83:	//ADD E
            ADD(state, state->e); break;
        case 0x84:	//ADD H
            ADD(state, state->h); break;
        case 0x85:	//ADD L
            ADD(state, state->l); break;
        case 0x86:	//ADD HL
            ADD(state, state->memory[formPair(state->h, state->l)]); break;
        case 0x87:	//ADD A
            ADD(state, state->a); break;
        case 0x88:	//ADC B
            ADC(state, state->b); break;
        case 0x89:	//ADC C
            ADC(state, state->c); break;
        case 0x8a:	//ADC D
            ADC(state, state->d); break;
        case 0x8b:	//ADC E
            ADC(state, state->e); break;
        case 0x8c:	//ADC H
            ADC(state, state->h); break;
        case 0x8d:	//ADC L
            ADC(state, state->l); break;
        case 0x8e:	//ADC HL
            ADC(state, state->memory[formPair(state->h, state->l)]); break;
        case 0x8f:  //ADC A
            ADC(state, state->a); break;
        case 0x90:	//SUB B
            SUB(state, state->b); break;
        case 0x91:	//SUB C
            SUB(state, state->c); break;
        case 0x92:	//SUB D
            SUB(state, state->d); break;
        case 0x93:	//SUB E
            SUB(state, state->e); break;
        case 0x94:	//SUB H
            SUB(state, state->h); break;
        case 0x95:	//SUB L
            SUB(state, state->l); break;
        case 0x96:	//SUB HL
            SUB(state, state->memory[formPair(state->h, state->l)]); break;
        case 0x97:	//SUB A
            SUB(state, state->a); break;
        case 0x98:	//SBB B
            SBB(state, state->b); break;
        case 0x99:	//SBB C
            SBB(state, state->c); break;
        case 0x9a:	//SBB D
            SBB(state, state->d); break;
        case 0x9b:	//SBB E
            SBB(state, state->e); break;
        case 0x9c:	//SBB H
            SBB(state, state->h); break;
        case 0x9d:	//SBB L
            SBB(state, state->l); break;
        case 0x9e:	//SBB HL
            SBB(state, state->memory[formPair(state->h, state->l)]); break;
        case 0x9f:  //SBB A
            SBB(state, state->a); break;
        case 0xa0:  //ANA B
            ANA(state, state->b); break;
        case 0xa1:  //ANA C
            ANA(state, state->c); break;
        case 0xa2:  //ANA D
            ANA(state, state->d); break;
        case 0xa3:  //ANA E
            ANA(state, state->e); break;
        case 0xa4:  //ANA H
            ANA(state, state->h); break;
        case 0xa5:  //ANA L
            ANA(state, state->l); break;
        case 0xa6:  //ANA M
            ANA(state, state->memory[formPair(state->h, state->l)]); break;
        case 0xa7:  //ANA A
            ANA(state, state->a); break;
        case 0xa8:  //XRA B
            XRA(state, state->b); break;
        case 0xa9:  //XRA C
            XRA(state, state->c); break;
        case 0xaa:  //XRA D
            XRA(state, state->d); break;
        case 0xab:  //XRA E
            XRA(state, state->e); break;
        case 0xac:  //XRA H
            XRA(state, state->h); break;
        case 0xad:  //XRA L
            XRA(state, state->l); break;
        case 0xae:  //XRA HL
            XRA(state, state->memory[formPair(state->h, state->l)]); break;
        case 0xaf:  //XRA A
            XRA(state, state->a); break;
        case 0xb0:  //ORA B
            ORA(state, state->b); break;
        case 0xb1:  //ORA C
            ORA(state, state->c); break;
        case 0xb2:  //ORA D
            ORA(state, state->d); break;
        case 0xb3:  //ORA E
            ORA(state, state->e); break;
        case 0xb4:  //ORA H
            ORA(state, state->h); break;
        case 0xb5:  //ORA L
            ORA(state, state->l); break;
        case 0xb6:  //ORA HL
            ORA(state, state->memory[formPair(state->h, state->l)]); break;
        case 0xb7:  //ORA A
            ORA(state, state->a); break;
        case 0xb8:  //CMP B
            CMP(state, state->b); break;
        case 0xb9:  //CMP C
            CMP(state, state->c); break;
        case 0xba:  //CMP D
            CMP(state, state->d); break;
        case 0xbb:  //CMP E
            CMP(state, state->e); break;
        case 0xbc:  //CMP H
            CMP(state, state->h); break;
        case 0xbd:  //CMP L
            CMP(state, state->l); break;
        case 0xbe:  //CMP HL
            CMP(state, state->memory[formPair(state->h, state->l)]); break;
        case 0xbf:  //CMP A
            CMP(state, state->a); break;
        case 0xc0:  //RNZ
            RNZ(state); break;
        case 0xc1:  //POP B
            POP(state, &state->b, &state->c); break;
        case 0xc2:  //JNZ adr
            JNZ(state); break;
        case 0xc3:  //JMP
            JMP(state); break;
        case 0xc4:  //CNZ
            CNZ(state); break;
        case 0xc5:  //PUSH B
            PUSH(state, state->b, state->c); break;
        case 0xc6:  //ADI D8
            ADD(state, AdvanceByte(state)); break;
        case 0xc7:  //RST 0
            RST(state, 0); break;
        case 0xc8:  //RZ
            RZ(state); break;
        case 0xc9:  //RET
            RET(state); break;
        case 0xca:  //JZ
            JZ(state); break;
        case 0xcc:  //CZ
            CZ(state); break;
        case 0xcd:  //CALL adr
            CALL(state); break;
        case 0xce:  //ACI D8
            ADC(state, AdvanceByte(state)); break;
        case 0xcf:  //RST 1
            RST(state, 1); break;
        case 0xd0:  //RNC
            RNC(state); break;
        case 0xd1:  //POP D
            POP(state, &state->d, &state->e); break;
        case 0xd2:  //JNC
            JNC(state); break;
        case 0xd3:  //OUT
            MachineOut(state); break;
        case 0xd4:  //CNC
            CNC(state); break;
        case 0xd5:  //PUSH D
            PUSH(state, state->d, state->e); break;
        case 0xd6:  //SUI D8
            SUB(state, AdvanceByte(state)); break;
        case 0xd7:  //RST 2
            RST(state, 2); break;
        case 0xd8:  //RC
            RC(state); break;
        case 0xda:  //JC
            JC(state); break;
        case 0xdb:  //IN
            MachineIn(state); break;
        case 0xdc:  //CC
            CC(state); break;
        case 0xde:  //SBI D8
            SBB(state, AdvanceByte(state)); break;
        case 0xdf:  //RST 3
            RST(state, 3); break;
        case 0xe0:  //RPO
            RPO(state); break;
        case 0xe1:  //POP H
            POP(state, &state->h, &state->l); break;
        case 0xe2:  //JPO
            JPO(state); break;
        case 0xe3:  //XTHL
        {
            uint8_t swp = state->l;
            state->l = state->memory[state->sp];
            state->memory[state->sp] = swp;
            swp = state->h;
            state->h = state->memory[state->sp + 1];
            state->memory[state->sp + 1] = swp;
            break;
        }
        case 0xe4:  //CPO
            CPO(state); break;
        case 0xe5:  //PUSH H
            PUSH(state, state->h, state->l); break;
        case 0xe6:  //ANI D8
            ANA(state, AdvanceByte(state)); break;
        case 0xe7:  //RST 4
            RST(state, 4); break;
        case 0xe8:  //RPE
            RP(state); break;
        case 0xe9:  //PCHL
            state->pc = formPair(state->h, state->l); break;
        case 0xea:  //JPE
            JPE(state); break;
        case 0xeb:  //XCHG
        {
            uint8_t tmp = state->h;
            state->h = state->d;
            state->d = tmp;
            tmp = state->l;
            state->l = state->e;
            state->e = tmp;
            break;
        }
        case 0xec:  //CPE
            CPE(state); break;
        case 0xee:  //XRI
            XRA(state, AdvanceByte(state)); break;
        case 0xef:  //RST 5
            RST(state, 5); break;
        case 0xf0:  //RP
            RP(state); break;
        case 0xf1:  //POP PSW
        {
            uint8_t psw = state->memory[state->sp];
            state->cc.z = ((psw&0x01) == 0x01);
            state->cc.s = ((psw&0x02) == 0x02);
            state->cc.p = ((psw&0x04) == 0x04);
            state->cc.cy = ((psw&0x08) == 0x08);
            state->cc.ac = ((psw&0x10) == 0x10);
            state->a = state->memory[state->sp+1];
            state->sp+=2;
            break;
        }
        case 0xf2:  //JP
            JP(state); break;
        case 0xf3:  //DI
            state->int_enable = 0; break;
        case 0xf4:  //CP
            CP(state); break;
        case 0xf5:  //PUSH PSW
        {
            state->memory[state->sp-1] = state->a;
            state->memory[state->sp-2] = (state->cc.z | state->cc.s<<1 | state->cc.p<<2 | state->cc.cy<<3 | state->cc.ac<<4) ;
            state->sp-=2;
            break;
        }
        case 0xf6:  //ORI
            ORA(state, AdvanceByte(state)); break;
        case 0xf7:  //RST 6
            RST(state, 6); break;
        case 0xf8:  //RM
            RM(state); break;
        case 0xf9:  //SPHL
            state->sp = formPair(state->h, state->l); break;
        case 0xfa:  //JM
            JM(state); break;
        case 0xfb:  //EI
            state->int_enable = 1; break;
        case 0xfc:  //CM
            CM(state); break;
        case 0xfe:  //CPI D8
            CMP(state, AdvanceByte(state)); break;
        case 0xff:  //RST 7
            RST(state, 7); break;
    }
    /*printf("\t");
	printf("%c", state->cc.z ? 'z' : '.');
	printf("%c", state->cc.s ? 's' : '.');
	printf("%c", state->cc.p ? 'p' : '.');
	printf("%c", state->cc.cy ? 'c' : '.');
	printf("%c  ", state->cc.ac ? 'ac' : '.');
    printf("A $%02x BC $%04x DE $%04x HL $%04x PC %04x SP %04x\n", state->a, formPair(state->b, state->c), 
        formPair(state->d, state->e), formPair(state->h, state->l), state->pc, state->sp);*/
    state->cyclesInterrupt += OPCODE_CYCLES[(uint8_t)opcode];
    state->cycles += OPCODE_CYCLES[(uint8_t)opcode];
}

void ReadFileIntoMemoryAt(State8080* state, const char* filename, uint32_t offset)
{
	FILE *f= fopen(filename, "rb");
	if (f==NULL)
	{
		printf("error: Couldn't open %s\n", filename);
		exit(1);
	}
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	uint8_t *buffer = &state->memory[offset];
	fread(buffer, fsize, 1, f);
	fclose(f);
}

State8080* Init8080(void)
{
	State8080* state = (State8080*)calloc(1,sizeof(State8080));
	state->memory = (uint8_t*)malloc(16*0x1000);
	return state;
}