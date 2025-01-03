#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include "emulator_shell.h"

int Disassemble8080Op(unsigned char *codebuffer, int pc) {    
    unsigned char *code = &codebuffer[pc];    
    int opbytes = 1;    
    printf ("%04x ", pc);    
    switch (*code) {    
        case 0x00: printf("NOP"); break;    
        case 0x01: printf("LXI    B,#$%02x%02x", code[2], code[1]); opbytes=3; break;    
        case 0x02: printf("STAX   B"); break;    
        case 0x03: printf("INX    B"); break;    
        case 0x04: printf("INR    B"); break;    
        case 0x05: printf("DCR    B"); break;    
        case 0x06: printf("MVI    B,#$%02x", code[1]); opbytes=2; break;    
        case 0x07: printf("RLC"); break;    
        case 0x08: printf("NOP"); break;    
        
        case 0x09: printf("DAD    B");break;
        case 0x0a: printf("LDAX   B");break;	
        case 0x0b: printf("DCX    B");break;
        case 0x0c: printf("INR    C");break;
        case 0x0d: printf("DCR    C");break;
        case 0x0e: printf("MVI    C,#$%02x", code[1]); opbytes=2;break;
        case 0x0f: printf("RRC");break;
        case 0x10:	printf("NOP"); break;	

        case 0x11:	printf("LXI    D,#$%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x12:	printf("STAX   D"); break;
        case 0x13:	printf("INX    D"); break;
        case 0x14:	printf("INR    D"); break;
        case 0x15:	printf("DCR    D"); break;
        case 0x16:	printf("MVI    D,#$%02x", code[1]); opbytes=2; break;
        case 0x17:	printf("RAL"); break;
        case 0x18:	printf("NOP"); break;

        case 0x19:	printf("DAD    D"); break;
        case 0x1a:	printf("LDAX   D"); break;
        case 0x1b:	printf("DCX    D"); break;
        case 0x1c:	printf("INR    E"); break;
        case 0x1d:	printf("DCR    E"); break;
        case 0x1e:	printf("MVI    E,#$%02x", code[1]); opbytes=2; break;
        case 0x1f:	printf("RAR"); break;
        case 0x20:	printf("RIM"); break;
        case 0x21:	printf("LXI    H,#$%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x22:	printf("SHLD   $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x23:	printf("INX    H"); break;
        case 0x24:	printf("INR    H"); break;
        case 0x25:	printf("DCR    H"); break;
        case 0x26:	printf("MVI    H,#$%02x", code[1]); opbytes=2; break;
        case 0x27:	printf("DAA"); break;
        case 0x28:	printf("NOP"); break;

        case 0x29:	printf("DAD    H"); break;
        case 0x2a:	printf("LHLD   $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x2b:	printf("DCX    H"); break;
        case 0x2c:	printf("INR    L"); break;
        case 0x2d:	printf("DCR    L"); break;
        case 0x2e:	printf("MVI    L,#$%02x", code[1]); opbytes=2; break;
        case 0x2f:	printf("CMA"); break;
        case 0x30:	printf("SIM"); break;
        case 0x31:	printf("LXI    SP,#$%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x32:	printf("STA    $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x33:	printf("INX    SP"); break;
        case 0x34:	printf("INR    M"); break;
        case 0x35:	printf("DCR    M"); break;
        case 0x36:	printf("MVI    M,#$%02x", code[1]); opbytes=2; break;
        case 0x37:	printf("STC"); break;
        case 0x38:	printf("NOP"); break;

        case 0x39:	printf("DAD    SP"); break;
        case 0x3a:	printf("LDA    $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x3b:	printf("DCX    SP"); break;
        case 0x3c:	printf("INR    A"); break;
        case 0x3d:	printf("DCR    A"); break;
        case 0x3e:	printf("MVI    A,#$%02x", code[1]); opbytes=2; break;
        case 0x3f:	printf("CMC"); break;

        case 0x40:	printf("MOV    B,B"); break;
        case 0x41:	printf("MOV    B,C"); break;
        case 0x42:	printf("MOV    B,D"); break;
        case 0x43:	printf("MOV    B,E"); break;
        case 0x44:	printf("MOV    B,H"); break;
        case 0x45:	printf("MOV    B,L"); break;
        case 0x46:	printf("MOV    B,M"); break;
        case 0x47:	printf("MOV    B,A"); break;
        case 0x48:	printf("MOV    C,B"); break;
        case 0x49:	printf("MOV    C,C"); break;
        case 0x4a:	printf("MOV    C,D"); break;
        case 0x4b:	printf("MOV    C,E"); break;
        case 0x4c:	printf("MOV    C,H"); break;
        case 0x4d:	printf("MOV    C,L"); break;
        case 0x4e:	printf("MOV    C,M"); break;
        case 0x4f:	printf("MOV    C,A"); break;
        case 0x50:	printf("MOV    D,B"); break;
        case 0x51:	printf("MOV    D,C"); break;
        case 0x52:	printf("MOV    D,D"); break;
        case 0x53:	printf("MOV    D,E"); break;
        case 0x54:	printf("MOV    D,H"); break;
        case 0x55:	printf("MOV    D,L"); break;
        case 0x56:	printf("MOV    D,M"); break;
        case 0x57:	printf("MOV    D,A"); break;
        case 0x58:	printf("MOV    E,B"); break;
        case 0x59:	printf("MOV    E,C"); break;
        case 0x5a:	printf("MOV    E,D"); break;
        case 0x5b:	printf("MOV    E,E"); break;
        case 0x5c:	printf("MOV    E,H"); break;
        case 0x5d:	printf("MOV    E,L"); break;
        case 0x5e:	printf("MOV    E,M"); break;
        case 0x5f:	printf("MOV    E,A"); break;
        case 0x60:	printf("MOV    H,B"); break;
        case 0x61:	printf("MOV    H,C"); break;
        case 0x62:	printf("MOV    H,D"); break;
        case 0x63:	printf("MOV    H,E"); break;
        case 0x64:	printf("MOV    H,H"); break;
        case 0x65:	printf("MOV    H,L"); break;
        case 0x66:	printf("MOV    H,M"); break;
        case 0x67:	printf("MOV    H,A"); break;
        case 0x68:	printf("MOV    L,B"); break;
        case 0x69:	printf("MOV    L,C"); break;
        case 0x6a:	printf("MOV    L,D"); break;
        case 0x6b:	printf("MOV    L,E"); break;
        case 0x6c:	printf("MOV    L,H"); break;
        case 0x6d:	printf("MOV    L,L"); break;
        case 0x6e:	printf("MOV    L,M"); break;
        case 0x6f:	printf("MOV    L,A"); break;
        case 0x70:	printf("MOV    M,B"); break;
        case 0x71:	printf("MOV    M,C"); break;
        case 0x72:	printf("MOV    M,D"); break;
        case 0x73:	printf("MOV    M,E"); break;
        case 0x74:	printf("MOV    M,H"); break;
        case 0x75:	printf("MOV    M,L"); break;
        case 0x76:	printf("HLT"); break;
        case 0x77:	printf("MOV    M,A"); break;
        case 0x78:	printf("MOV    A,B"); break;
        case 0x79:	printf("MOV    A,C"); break;
        case 0x7a:	printf("MOV    A,D"); break;
        case 0x7b:	printf("MOV    A,E"); break;
        case 0x7c:	printf("MOV    A,H"); break;
        case 0x7d:	printf("MOV    A,L"); break;
        case 0x7e:	printf("MOV    A,M"); break;
        case 0x7f:	printf("MOV    A,A"); break;

        case 0x80:	printf("ADD    B"); break;
        case 0x81:	printf("ADD    C"); break;
        case 0x82:	printf("ADD    D"); break;
        case 0x83:	printf("ADD    E"); break;
        case 0x84:	printf("ADD    H"); break;
        case 0x85:	printf("ADD    L"); break;
        case 0x86:	printf("ADD    M"); break;
        case 0x87:	printf("ADD    A"); break;
        case 0x88:	printf("ADC    B"); break;
        case 0x89:	printf("ADC    C"); break;
        case 0x8a:	printf("ADC    D"); break;
        case 0x8b:	printf("ADC    E"); break;
        case 0x8c:	printf("ADC    H"); break;
        case 0x8d:	printf("ADC    L"); break;
        case 0x8e:	printf("ADC    M"); break;
        case 0x8f:	printf("ADC    A"); break;

        case 0x90:	printf("SUB    B"); break;
        case 0x91:	printf("SUB    C"); break;
        case 0x92:	printf("SUB    D"); break;
        case 0x93:	printf("SUB    E"); break;
        case 0x94:	printf("SUB    H"); break;
        case 0x95:	printf("SUB    L"); break;
        case 0x96:	printf("SUB    M"); break;
        case 0x97:	printf("SUB    A"); break;
        case 0x98:	printf("SBB    B"); break;
        case 0x99:	printf("SBB    C"); break;
        case 0x9a:	printf("SBB    D"); break;
        case 0x9b:	printf("SBB    E"); break;
        case 0x9c:	printf("SBB    H"); break;
        case 0x9d:	printf("SBB    L"); break;
        case 0x9e:	printf("SBB    M"); break;
        case 0x9f:	printf("SBB    A"); break;

        case 0xa0:	printf("ANA    B"); break;
        case 0xa1:	printf("ANA    C"); break;
        case 0xa2:	printf("ANA    D"); break;
        case 0xa3:	printf("ANA    E"); break;
        case 0xa4:	printf("ANA    H"); break;
        case 0xa5:	printf("ANA    L"); break;
        case 0xa6:	printf("ANA    M"); break;
        case 0xa7:	printf("ANA    A"); break;

        case 0xa8:	printf("XRA    B"); break;
        case 0xa9:	printf("XRA    C"); break;
        case 0xaa:	printf("XRA    D"); break;
        case 0xab:	printf("XRA    E"); break;
        case 0xac:	printf("XRA    H"); break;
        case 0xad:	printf("XRA    L"); break;
        case 0xae:	printf("XRA    M"); break;
        case 0xaf:	printf("XRA    A"); break;

        case 0xb0:	printf("ORA    B"); break;
        case 0xb1:	printf("ORA    C"); break;
        case 0xb2:	printf("ORA    D"); break;
        case 0xb3:	printf("ORA    E"); break;
        case 0xb4:	printf("ORA    H"); break;
        case 0xb5:	printf("ORA    L"); break;
        case 0xb6:	printf("ORA    M"); break;
        case 0xb7:	printf("ORA    A"); break;

        case 0xb8:	printf("CMP    B"); break;
        case 0xb9:	printf("CMP    C"); break;
        case 0xba:	printf("CMP    D"); break;
        case 0xbb:	printf("CMP    E"); break;
        case 0xbc:	printf("CMP    H"); break;
        case 0xbd:	printf("CMP    L"); break;
        case 0xbe:	printf("CMP    M"); break;
        case 0xbf:	printf("CMP    A"); break;

        case 0xc0: printf("RNZ"); break;
        case 0xc1: printf("POP    B"); break;
        case 0xc2: printf("JNZ    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xc3: printf("JMP    $%02x%02x",code[2],code[1]); opbytes = 3; break;    
        case 0xc4: printf("CNZ    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xc5: printf("PUSH   B"); break;
        case 0xc6: printf("ADI    #$%02x",code[1]); opbytes = 2; break;
        case 0xc7: printf("RST    0"); break;
        case 0xc8: printf("RZ"); break;
        case 0xc9: printf("RET"); break;
        case 0xca: printf("JZ     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xcb: printf("NOP"); break;

        case 0xcc: printf("CZ     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xcd: printf("CALL   $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xce: printf("ACI    #$%02x",code[1]); opbytes = 2; break;
        case 0xcf: printf("RST    1"); break;
        case 0xd0: printf("RNC"); break;
        case 0xd1: printf("POP    D"); break;
        case 0xd2: printf("JNC    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xd3: printf("OUT    #$%02x",code[1]); opbytes = 2; break;
        case 0xd4: printf("CNC    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xd5: printf("PUSH   D"); break;
        case 0xd6: printf("SUI    #$%02x",code[1]); opbytes = 2; break;
        case 0xd7: printf("RST    2"); break;
        case 0xd8: printf("RC"); break;
        case 0xd9: printf("NOP"); break;

        case 0xda: printf("JC     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xdb: printf("IN     #$%02x",code[1]); opbytes = 2; break;
        case 0xdc: printf("CC     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xdd: printf("NOP"); break;

        case 0xde: printf("SBI    #$%02x",code[1]); opbytes = 2; break;
        case 0xdf: printf("RST    3"); break;
        case 0xe0: printf("RPO"); break;
        case 0xe1: printf("POP    H"); break;
        case 0xe2: printf("JPO    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xe3: printf("XTHL"); break;
        case 0xe4: printf("CPO    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xe5: printf("PUSH   H"); break;
        case 0xe6: printf("ANI    #$%02x",code[1]); opbytes = 2; break;
        case 0xe7: printf("RST    4"); break;
        case 0xe8: printf("RPE"); break;
        case 0xe9: printf("PCHL"); break;
        case 0xea: printf("JPE    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xeb: printf("XCHG"); break;
        case 0xec: printf("CPE    $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xed: printf("NOP"); break;

        case 0xee: printf("XRI    #$%02x",code[1]); opbytes = 2; break;
        case 0xef: printf("RST    5"); break;
        case 0xf0: printf("RP"); break;
        case 0xf1: printf("POP    PSW"); break;
        case 0xf2: printf("JP     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xf3: printf("DI"); break;
        case 0xf4: printf("CP     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xf5: printf("PUSH   PSW"); break;
        case 0xf6: printf("ORI    #$%02x",code[1]); opbytes = 2; break;
        case 0xf7: printf("RST    6"); break;
        case 0xf8: printf("RM"); break;
        case 0xf9: printf("SPHL"); break;
        case 0xfa: printf("JM     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xfb: printf("EI"); break;
        case 0xfc: printf("CM     $%02x%02x",code[2],code[1]); opbytes = 3; break;
        case 0xfd: printf("NOP"); break;

        case 0xfe: printf("CPI    #$%02x",code[1]); opbytes = 2; break;
        case 0xff: printf("RST    7"); break;

    }    
    printf("\n");    
    return opbytes;    
}   

static int parity(int x, int size)
{
	int i;
	int p = 0;
	x = (x & ((1<<size)-1));
	for (i=0; i<size; i++)
	{
		if (x & 0x1) p++;
		x = x >> 1;
	}
	return (0 == (p & 0x1));
}

static void cc4(State8080* state, uint16_t ans) {
    state->cc.z = ((ans&0xff)==0);
    state->cc.s = ((ans&0x80)!=0);
    state->cc.cy = (ans>0xff);
    state->cc.p = parity(ans&0xff,8);
}

static void cc3(State8080* state, uint16_t ans) {
    state->cc.z = ((ans&0xff)==0);
    state->cc.s = ((ans&0x80)!=0);
    state->cc.p = parity(ans&0xff,8);
}

static void UnimplementedInstruction(State8080* state) {        
    printf ("Error: Unimplemented instruction\n"); 
    state->pc--;
	Disassemble8080Op(state->memory, state->pc);
	printf("\n");   
    exit(1);    
}

static void ADD(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a + (uint16_t) x;
    cc4(state,ans);
    state->a = ans&0xff;
}

static void ADC(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a + (uint16_t) x + (uint16_t) state->cc.cy;
    cc4(state,ans);
    state->a = ans&0xff;
}

static void SUB(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a - (uint16_t) x;
    cc4(state,ans);
    state->a = ans&0xff;
}

static void SBB(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a - (uint16_t) x - (uint16_t) state->cc.cy;
    cc4(state,ans);
    state->a = ans&0xff;
}

static void DAD(State8080* state, uint8_t x, uint8_t y) {
    uint32_t pair1 = (state->h<<8) | (state->l);
    uint32_t pair2 = (x<<8) | y;
    uint32_t ans = pair1 + pair2;
    state->h = (ans >> 8) & 0xFF;
    state->l = ans & 0xFF;
    state->cc.cy = (ans > 0xFFFF);
}

static void ANA(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a & (uint16_t) x;
    cc3(state,ans);
    state->cc.cy = 0;
    state->a = ans&0xff;
}

static void XRA(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a ^ (uint16_t) x;
    cc3(state,ans);
    state->cc.cy = 0;
    state->a = ans&0xff;
}

static void ORA(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a | (uint16_t) x;
    cc3(state,ans);
    state->cc.cy = 0;
    state->a = ans&0xff;
}

static void CMP(State8080* state, uint8_t x) {
    uint16_t ans = (uint16_t) state->a - (uint16_t) x;
    cc4(state,ans);
}

int Emulate8080Op(State8080* state) {    
    int cycles = 4;
	unsigned char *opcode = &state->memory[state->pc];

    Disassemble8080Op(state->memory, state->pc);

    state->pc+=1;

    switch(*opcode) {    
        case 0x00: break; //NOP
        case 0x01: //LXI B
        {
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2;
            break;    
        }
        case 0x02:  //STAX B
        {
            uint16_t pair = (state->b<<8) | (state->c);
            state->memory[pair] = state->a;
            break;
        }    
        case 0x03: //INX B
        {
            uint16_t pair = (state->b<<8) | (state->c);
            uint16_t ans = pair+1;
            state->b = (ans&0xff00)>>8 ;
            state->c = (ans&0xff);
            break;
        }
        case 0x04: //INR B
        {
            uint8_t ans = state->b+1;
            cc3(state,ans);
            state->b = ans&0xff;
            break;
        }
        case 0x05: //DCR B
        {
            uint8_t ans = state->b-1;
            cc3(state,ans);
            state->b = ans&0xff;
            break;
        }
        case 0x06:  //MVI B
        {
            state->b = opcode[1];
            state->pc++;
            break;
        }
        case 0x07:  //RLC
        {
            uint8_t x = state->a;
            state-> a = ((x << 1) | (x & 0x80) >> 7);
            state->cc.cy = ((x & 0x80) == 0x80);
            break;
        }  

        case 0x09: //DAD B
        {
            DAD(state, state->b, state->c);
            break;
        }
        case 0x0a:  //LDAX B
        {
            uint16_t pair = (state->b<<8) | (state->c);
            state->a = state->memory[pair];
            break;
        }
        case 0x0b: //DCX B
        {
            uint16_t pair = (state->b<<8) | (state->c);
            uint16_t ans = pair - 1;
            state->b = (ans&0xff00)>>8;
            state->c = (ans&0xff);
            break;
        }   
        case 0x0c: //INR C
        {
            uint8_t ans = (uint16_t) state->c + 1;
            cc3(state,ans);
            state->c = ans&0xff;
            break;
        } 
        case 0x0d: //DCR C
        {
            uint8_t ans = (uint16_t) state->c - 1;
            cc3(state,ans);
            state->c = ans&0xff;
            break;
        }
        case 0x0e:  //MVI C
        {
            state->c = opcode[1];
            state->pc++;
            break;
        }
        case 0x0f:  //RRC
        {
            uint8_t x = state->a;
            state-> a = ((x >> 1) | (x & 1) << 7);
            state->cc.cy = ((x & 1) == 1);
            break;
        }

        case 0x11: //LXI D
        {
            state->e = opcode[1];
            state->d = opcode[2];
            state->pc += 2;
            break;    
        }
        case 0x12:  //STAX D
        {
            uint16_t pair = (state->d<<8) | (state->e);
            state->memory[pair] = state->a;
            break;
        }
        case 0x13: //INX D
        {
            uint16_t pair = (state->d<<8) | (state->e);
            uint16_t ans = pair + 1;
            state->d = (ans&0xff00)>>8 ;
            state->e = (ans&0xff);
            break;
        }    
        case 0x14: //INR D
        {
            uint8_t ans = (uint16_t) state->d + 1;
            cc3(state,ans);
            state->b = ans&0xff;
            break;
        }    
        case 0x15: //DCR D
        {
            uint16_t ans = (uint16_t) state->d - 1;
            cc3(state,ans);
            state->b = ans&0xff;
            break;
        }
        case 0x16:  //MVI D
        {
            state->d = opcode[1];
            state->pc++;
            break;
        }
        case 0x17:  //RAL
        {
            uint8_t x = state->a;
            state->a = ((x<<1) | (state->cc.cy));
            state->cc.cy = ((x&0x80) == 0x80);
            break;
        }

        case 0x19:	//DAD D
        {
            DAD(state, state->d, state->e);
            break;
        }
        case 0x1a:  //LDAX D
        {
            uint16_t pair = (state->d<<8) | (state->e);
            state->a = state->memory[pair];
            break;
        }
        case 0x1b: //DCX D
        {
            uint16_t pair = (state->d<<8) | (state->e);
            uint16_t ans = pair - 1;
            state->d = (ans&0xff00)>>8;
            state->e = (ans&0xff);
            break;
        }   
        case 0x1c: //INR E
        {
            uint8_t ans = (uint16_t) state->e + 1;
            cc3(state,ans);
            state->c = ans&0xff;
            break;
        } 
        case 0x1d: //DCR E
        {
            uint8_t ans = (uint16_t) state->e - 1;
            cc3(state,ans);
            state->c = ans&0xff;
            break;
        }
        case 0x1e:  //MVI E
        {
            state->e = opcode[1];
            state->pc++;
            break;
        }
        case 0x1f:  //RAR
        {
            uint8_t x = state->a;
            state->a = ((x>>1) | (state->cc.cy<<7));
            state->cc.cy = ((x&1)==1);
        }
        case 0x21: //LXI H
        {
            state->l = opcode[1];
            state->h = opcode[2];
            state->pc += 2;
            break;    
        }
        case 0x22:  //SHLD adr
        {
            uint16_t adr = (opcode[2]<<8) | (opcode[1]);
            state->memory[adr+1] = state->h;
            state->memory[adr] = state->l;
            state->pc += 2;
            break;
        }
        case 0x23: //INX H
        {
            uint16_t pair = (state->h<<8) | (state->l);
            uint16_t ans = pair + 1;
            state->h = (ans&0xff00)>>8 ;
            state->l = (ans&0xff);
            break;
        }    
        case 0x24: //INR H
        {
            uint8_t ans = (uint16_t) state->h + 1;
            cc3(state,ans);
            break;
        }    
        case 0x25: //DCR H
        {
            uint16_t ans = (uint16_t) state->h - 1;
            cc3(state,ans);
            break;
        }
        case 0x26:  //MVI H
        {
            state->h = opcode[1];
            state->pc++;
            break;
        }
        case 0x27:	UnimplementedInstruction(state); break;

        case 0x29:	//DAD H
        {
            DAD(state, state->h, state->l);
            break;
        }
        case 0x2a:  //LHLD adr
        {
            uint16_t adr = (opcode[2]<<8) | (opcode[1]);
            state->h = state->memory[adr+1];
            state->l = state->memory[adr];
            state->pc += 2;
            break;
        }
        case 0x2b:	//DCX H
        {
            uint16_t pair = (state->h<<8) | (state->l);
            uint16_t ans = pair - 1;
            state->h = (ans&0xff00)>>8;
            state->l = (ans&0xff);
            break;
        }  
        case 0x2c:	//INR L
        { 
            uint8_t ans = (uint16_t) state->l + 1;
            cc3(state,ans);
            state->b = ans&0xff;
            break;
        }
        case 0x2d:	//DCR L
        {
            uint8_t ans = (uint16_t) state->l - 1;
            cc3(state,ans);
            state->b = ans&0xff;
            break;
        }
        case 0x2e:  //MVI L
        {
            state->l = opcode[1];
            state->pc++;
            break;
        }
        case 0x2f:  //CMA
        {
            state->a = ~state->a;
        }
        case 0x31: //LXI SP
        {
            state->sp = (opcode[2]<<8) | (opcode[1]);
            state->pc += 2;
            break;    
        }
        case 0x32:  //STA adr
        {
            uint16_t adr = (opcode[2]<<8) | (opcode[1]);
            state->memory[adr] = state->a;
            state->pc += 2;
            break;
        }
        case 0x33:  //INX SP
        {
            state->sp++;
            break;
        }
        case 0x34:	//INR HL
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t ans = state->memory[offset] + 1;
            cc3(state,ans);
            state->memory[offset] = ans&0xff;
            break;
        }
        case 0x35:	//DCR HL
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t ans = state->memory[offset] - 1;
            cc3(state,ans);
            state->memory[offset] = ans&0xff;
            break;
        }
        case 0x36:  //MVI M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = opcode[1];
            state->pc++;
            break;
        }
        case 0x37:  //STC
        {
            state->cc.cy = 1;
        }

        case 0x39:  //DAD SP
        {
            uint32_t pair = (state->h<<8) | (state->l);
            pair = pair + (uint32_t)state->sp;
            state->cc.cy = (pair > 0xff);
            state->h = (pair & 0xff00) >> 8;
            state->l = pair & 0xff;
            break;
        }
        case 0x3a:  //LDA adr
        {
            uint16_t adr = (opcode[2]<<8) | (opcode[1]);
            state->a = state->memory[adr];
            state->pc += 2;
            break;
        }
        case 0x3b:  //DCX SP
        {
            state->sp--;
            break;
        }
        case 0x3c:	//INR A
        {
            uint8_t ans = (uint16_t) state->a + 1;
            cc3(state,ans);
            break;
        }
        case 0x3d:  //DCR A
        {
            uint8_t ans = (uint16_t) state->a - 1;
            cc3(state,ans);
            break;
        }
        case 0x3e:  //MVI A
        {
            state->a = opcode[1];
            state->pc++;
            break;
        }
        case 0x3f:  //CMC
        {
            state->cc.cy = ~state->cc.cy;
        }

        case 0x40:  //MOV B,B
        {
            state->b = state->b;
            break;
        }
        case 0x41:  //MOV B,C
        {
            state->b = state->c;
            break;
        }
        case 0x42:  //MOV B,D
        {
            state->b = state->d;
            break;
        }
        case 0x43:  //MOV B,E
        {
            state->b = state->e;
            break;
        }
        case 0x44:  //MOV B,H
        {
            state->b = state->h;
            break;
        }
        case 0x45:  //MOV B,L
        {
            state->b = state->l;
            break;
        }
        case 0x46:  //MOV B,M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->b = state->memory[offset];
            break;
        }
        case 0x47:  //MOV B,A
        {
            state->b = state->a;
            break;
        }
        case 0x48:  //MOV C,B
        {
            state->c = state->b;
            break;
        }
        case 0x49:  //MOV C,C
        {
            state->c = state->c;
            break;
        }
        case 0x4a:  //MOV C,D
        {
            state->c = state->d;
            break;
        }
        case 0x4b:  //MOV C,E
        {
            state->c = state->e;
            break;
        }
        case 0x4c:  //MOV C,H
        {
            state->c = state->h;
            break;
        }
        case 0x4d:  //MOV C,L
        {
            state->c = state->l;
            break;
        }
        case 0x4e:  //MOV C,M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->c = state->memory[offset];
            break;
        }
        case 0x4f:  //MOV C,A
        {
            state->c = state->a;
            break;
        }
        case 0x50:  //MOV D,B
        {
            state->d = state->b;
            break;
        }
        case 0x51:  //MOV D,C
        {
            state->d = state->c;
            break;
        }
        case 0x52:  //MOV D,D
        {
            state->d = state->d;
            break;
        }
        case 0x53:  //MOV D,E
        {
            state->d = state->e;
            break;
        }
        case 0x54:  //MOV D,H
        {
            state->d = state->h;
            break;
        }
        case 0x55:  //MOV D,L
        {
            state->d = state->l;
            break;
        }
        case 0x56:  //MOV D,M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->d = state->memory[offset];
            break;
        }
        case 0x57:  //MOV D,A
        {
            state->d = state->a;
            break;
        }
        case 0x58:  //MOV E,B
        {
            state->e = state->b;
            break;
        }
        case 0x59:  //MOV E,C
        {
            state->e = state->c;
            break;
        }
        case 0x5a:  //MOV E,D
        {
            state->e = state->d;
            break;
        }
        case 0x5b:  //MOV E,E
        {
            state->e = state->e;
            break;
        }
        case 0x5c:  //MOV E,H
        {
            state->e = state->h;
            break;
        }
        case 0x5d:  //MOV E,L
        {
            state->e = state->l;
            break;
        }
        case 0x5e:  //MOV E,M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->e = state->memory[offset];
            break;
        }
        case 0x5f:  //MOV E,A
        {
            state->e = state->a;
            break;
        }
        case 0x60:  //MOV H,B
        {
            state->h = state->b;
            break;
        }
        case 0x61:  //MOV H,C
        {
            state->h = state->c;
            break;
        }
        case 0x62:  //MOV H,D
        {
            state->h = state->d;
            break;
        }
        case 0x63:  //MOV H,E
        {
            state->h = state->e;
            break;
        }
        case 0x64:  //MOV H,H
        {
            state->h = state->h;
            break;
        }
        case 0x65:  //MOV H,L
        {
            state->h = state->l;
            break;
        }
        case 0x66:  //MOV H,M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->h = state->memory[offset];
            break;
        }
        case 0x67:  //MOV H,A
        {
            state->h = state->a;
            break;
        }
        case 0x68:  //MOV L,B
        {
            state->l = state->b;
            break;
        }
        case 0x69:  //MOV L,C
        {
            state->l = state->c;
            break;
        }
        case 0x6a:  //MOV L,D
        {
            state->l = state->d;
            break;
        }
        case 0x6b:  //MOV L,E
        {
            state->l = state->e;
            break;
        }
        case 0x6c:  //MOV L,H
        {
            state->l = state->h;
            break;
        }
        case 0x6d:  //MOV L,L
        {
            state->l = state->l;
            break;
        }
        case 0x6e:  //MOV L,M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->l = state->memory[offset];
            break;
        }
        case 0x6f:  //MOV L,A
        {
            state->l = state->a;
            break;
        }
        case 0x70:  //MOV M,B
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = state->b;
            break;
        }
        case 0x71:  //MOV M,C
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = state->c;
            break;
        }
        case 0x72:  //MOV M,D
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = state->d;
            break;
        }
        case 0x73:  //MOV M,E
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = state->e;
            break;
        }
        case 0x74:  //MOV M,H
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = state->h;
            break;
        }
        case 0x75:  //MOV M,L
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = state->l;
            break;
        }
        case 0x76:  //HLT
        {
            exit(0);
        }
        case 0x77:  //MOV M,A
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->memory[offset] = state->a;
            break;
        }
        case 0x78:  //MOV A,B
        {
            state->a = state->b;
            break;
        }
        case 0x79:  //MOV A,C
        {
            state->a = state->c;
            break;
        }
        case 0x7a:  //MOV A,D
        {
            state->a = state->d;
            break;
        }
        case 0x7b:  //MOV A,E
        {
            state->a = state->e;
            break;
        }
        case 0x7c:  //MOV A,H
        {
            state->a = state->h;
            break;
        }
        case 0x7d:  //MOV A,L
        {
            state->a = state->l;
            break;
        }
        case 0x7e:  //MOV A,M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            state->a = state->memory[offset];
            break;
        }
        case 0x7f:  //MOV A,A
        {
            state->a = state->a;
            break;
        }

        case 0x80: //ADD B
        {
            ADD(state,state->b);
            break;
        }
        case 0x81:	//ADD C
        {
            ADD(state,state->c);
            break;
        }
        case 0x82:	//ADD D
        {
            ADD(state,state->d);
            break;
        }
        case 0x83:	//ADD E
        {
            ADD(state,state->e);
            break;
        }
        case 0x84:	//ADD H
        {
            ADD(state,state->h);
            break;
        }
        case 0x85:	//ADD L
        {
            ADD(state,state->l);
            break;
        }
        case 0x86:	//ADD HL
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t ans = (uint16_t) state->a + state->memory[offset];
            cc4(state,ans);
            state->a = ans&0xff;
            break;
        }
        case 0x87:	//ADD A
        {
            ADD(state,state->a);
            break;
        }
        case 0x88:	//ADC B
        {
            ADC(state,state->b);
            break;
        }
        case 0x89:	//ADC C
        {
            ADC(state,state->c);
            break;
        }
        case 0x8a:	//ADC D
        {
            ADC(state,state->d);
            break;
        }
        case 0x8b:	//ADC E
        {
            ADC(state,state->e);
            break;
        }
        case 0x8c:	//ADC H
        {
            ADC(state,state->h);
            break;
        }
        case 0x8d:	//ADC L
        {
            ADC(state,state->l);
            break;
        }
        case 0x8e:	//ADC HL
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t ans = (uint16_t) state->a + state->memory[offset] + (uint16_t) state->cc.cy;
            cc4(state,ans);
            state->a = ans&0xff;
            break;
        }
        case 0x8f:  //ADC A
        {
            ADC(state,state->a);
            break;
        }

        case 0x90:	//SUB B
        {
            SUB(state, state->b);
            break;
        }
        case 0x91:	//SUB C
        {
            SUB(state, state->c);
            break;
        }
        case 0x92:	//SUB D
        {
            SUB(state, state->d);
            break;
        }
        case 0x93:	//SUB E
        {
            SUB(state, state->e);
            break;
        }
        case 0x94:	//SUB H
        {
            SUB(state, state->h);
            break;
        }
        case 0x95:	//SUB L
        {
            SUB(state, state->l);
            break;
        }
        case 0x96:	//SUB HL
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t ans = (uint16_t) state->a - state->memory[offset];
            cc4(state,ans);
            state->a = ans&0xff;
            break;
        }
        case 0x97:	//SUB A
        {
            SUB(state, state->a);
            break;
        }
        case 0x98:	//SBB B
        {
            SBB(state,state->b);
            break;
        }
        case 0x99:	//SBB C
        {
            SBB(state,state->c);
            break;
        }
        case 0x9a:	//SBB D
        {
            SBB(state,state->d);
            break;
        }
        case 0x9b:	//SBB E
        {
            SBB(state,state->e);
            break;
        }
        case 0x9c:	//SBB H
        {
            SBB(state,state->h);
            break;
        }
        case 0x9d:	//SBB L
        {
            SBB(state,state->l);
            break;
        }
        case 0x9e:	//SBB HL
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t ans = (uint16_t) state->a - state->memory[offset] - (uint16_t) state->cc.cy;
            cc4(state,ans);
            state->a = ans&0xff;
            break;
        }
        case 0x9f:  //SBB A
        {
            SBB(state,state->a);
            break;
        }

        case 0xa0:  //ANA B
        {
            ANA(state,state->b);
            break;
        }
        case 0xa1:  //ANA C
        {
            ANA(state,state->c);
            break;
        }
        case 0xa2:  //ANA D
        {
            ANA(state,state->d);
            break;
        }
        case 0xa3:  //ANA E
        {
            ANA(state,state->e);
            break;
        }
        case 0xa4:  //ANA H
        {
            ANA(state,state->h);
            break;
        }
        case 0xa5:  //ANA L
        {
            ANA(state,state->l);
            break;
        }
        case 0xa6:  //ANA M
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t ans = (uint16_t) state->a & state->memory[offset];
            cc4(state,ans);
            state->a = ans&0xff;
            break;
        }
        case 0xa7:  //ANA A
        {
            ANA(state,state->a);
            break;
        }

        case 0xa8:  //XRA B
        {
            XRA(state,state->b);
            break;
        }
        case 0xa9:  //XRA C
        {
            XRA(state,state->c);
            break;
        }
        case 0xaa:  //XRA D
        {
            XRA(state,state->d);
            break;
        }
        case 0xab:  //XRA E
        {
            XRA(state,state->e);
            break;
        }
        case 0xac:  //XRA H
        {
            XRA(state,state->h);
            break;
        }
        case 0xad:  //XRA L
        {
            XRA(state,state->l);
            break;
        }
        case 0xae:  //XRA HL
        {
            uint16_t offset = (state->h<<8) | (state->l); 
            uint16_t ans = (uint16_t)state->a & state->memory[offset];
            cc3(state,ans);
            state->cc.cy = 0;
            break;
        }
        case 0xaf:  //XRA A
        {
            XRA(state,state->a);
            break;
        }

        case 0xb0:  //ORA B
        {
            ORA(state,state->b);
            break;
        }
        case 0xb1:  //ORA C
        {
            ORA(state,state->c);
            break;
        }
        case 0xb2:  //ORA D
        {
            ORA(state,state->d);
            break;
        }
        case 0xb3:  //ORA E
        {
            ORA(state,state->e);
            break;
        }
        case 0xb4:  //ORA H
        {
            ORA(state,state->h);
            break;
        }
        case 0xb5:  //ORA L
        {
            ORA(state,state->l);
            break;
        }
        case 0xb6:  //ORA HL
        {
            uint16_t offset = (state->h<<8) | (state->l); 
            uint16_t ans = (uint16_t)state->a | state->memory[offset];
            cc3(state,ans);
            state->cc.cy = 0;
            break;
        }
        case 0xb7:  //ORA A
        {
            XRA(state,state->a);
            break;
        }

        case 0xb8:  //CMP B
        {
            CMP(state,state->b);
            break;
        }
        case 0xb9:  //CMP C
        {
            CMP(state,state->c);
            break;
        }
        case 0xba:  //CMP D
        {
            CMP(state,state->d);
            break;
        }
        case 0xbb:  //CMP E
        {
            CMP(state,state->e);
            break;
        }
        case 0xbc:  //CMP H
        {
            CMP(state,state->h);
            break;
        }
        case 0xbd:  //CMP L
        {
            CMP(state,state->l);
            break;
        }
        case 0xbe:  //CMP HL
        {
            uint16_t offset = (state->h<<8) | state->l;
            uint16_t ans = (uint16_t) state->a - state->memory[offset];
            cc4(state,ans); 
            break;
        }
        case 0xbf:  //CMP A
        {
            CMP(state,state->a);
            break;
        }

        case 0xc0:  //RNZ
        if(state->cc.z==0) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;
        }break;
        case 0xc1:  //POP B
        {
            state->c = state->memory[state->sp];
            state->b = state->memory[state->sp+1];
            state->sp += 2;
            break;
        }
        case 0xc2:  //JNZ
        {
            state->pc = (state->cc.z == 0)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        } 
        case 0xc3:  //JMP
        {
            state->pc = (opcode[2]<<8) | opcode[1];
            break;
        }    
        case 0xc4:  //CNZ
        {  
            if(state->cc.z==0) {
                uint16_t ret = state->pc+2;    
                state->memory[state->sp-1] = (ret >> 8) & 0xff;    
                state->memory[state->sp-2] = (ret & 0xff);    
                state->sp = state->sp - 2;    
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else state->pc+=2; 
            break;   
        } 
        case 0xc5:  //PUSH B
        {
            state->memory[state->sp-1] = state->b; 
            state->memory[state->sp-2] = state->c;
            state->sp -= 2;
            break;
        }
        case 0xc6:  //ADI D8
        {
            uint16_t ans = (uint16_t)state->a + (uint16_t)opcode[1];
            cc4(state, ans);
            state->a = (ans&0xff);
            state->pc++;
            break;
        }
        case 0xc7:  //RST 0
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp -= 2;
            state->pc = 0x0;
            break;
        }
        case 0xc8:  //RZ
        if(state->cc.z==1) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;    
        }break;
        case 0xc9:  //RET
        {
            state->pc = (state->memory[state->sp]) | (state->memory[state->sp+1] << 8);
            state->sp += 2;
            break;
        }
        case 0xca:  //JZ
        {
            state->pc = (state->cc.z == 1)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        }

        case 0xcc:  //CZ
        {  
            if(state->cc.z!=1) {
                state->pc+=2; 
                break;
            }     
        }
        case 0xcd:// CALL adr    
        #ifdef FOR_CPUDIAG
            if (5 == ((opcode[2] << 8) | opcode[1])) {
                if (state->c == 9) {
                    uint16_t offset = (state->d<<8) | (state->e);
                    char *str = &state->memory[offset+3]; // skipping prefix
                    while (*str != '$')
                        printf("%c", *str++);
                    printf("\n");
                } else if (state->c == 2) {
                    printf("Print char: %c\n", state->e);
                }
            } else if (0 == ((opcode[2] << 8) | opcode[1])) {
                exit(0);  // Exit for CPUDIAG end of program
            }
        #endif
            {    
            uint16_t ret = state->pc+2;    
            state->memory[state->sp-1] = (ret >> 8) & 0xff;    
            state->memory[state->sp-2] = (ret & 0xff);    
            state->sp = state->sp - 2;    
            state->pc = (opcode[2] << 8) | opcode[1];    
            }    
            break;     
        case 0xce:  //ACI D8
        {
            uint16_t ans = (uint16_t) state->a | (uint16_t) opcode[1] | state->cc.cy;
            cc4(state, ans);
            state->a = (ans&0xff);
            state->pc++;
            break;
        }
        case 0xcf:  //RST 1
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp-=2;
            state->pc = 0x8;
            break;
        }
        case 0xd0:  //RNC
        if(state->cc.cy==0) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;
        }break;
        case 0xd1:  //POP D
        {
            state->e = state->memory[state->sp];
            state->d = state->memory[state->sp+1];
            state->sp += 2;
            break;
        }
        case 0xd2:  //JNC 
        {
            state->pc = (state->cc.cy == 0)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        }
        case 0xd3:  //OUT D8
        {
            state->pc++;
            break;
        }
        case 0xd4:  //CNC
        {  
            if(state->cc.cy==0) {
                uint16_t ret = state->pc+2;    
                state->memory[state->sp-1] = (ret >> 8) & 0xff;    
                state->memory[state->sp-2] = (ret & 0xff);    
                state->sp = state->sp - 2;    
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else state->pc+=2; 
            break;   
        }
        case 0xd5:  //PUSH D
        {
            state->memory[state->sp-1] = state->d;
            state->memory[state->sp-2] = state->e;
            state->sp -= 2;
            break;
        }
        case 0xd6:  //SUI D8
        {
            uint16_t ans = (uint16_t) state->a - (uint16_t) opcode[1];
            cc4(state, ans);
            state->a = (ans&0xff);
            state->pc++;
            break;
        }
        case 0xd7:  //RST 2
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp-=2;
            state->pc = 0x10;
            break;
        }
        case 0xd8:  //RC
        if(state->cc.cy==1) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;
        }break;

        case 0xda:  //JC
        {
            state->pc = (state->cc.cy == 1)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        }
        case 0xdb:  //IN D8
        {
            state->pc++;
            break;
        }
        case 0xdc:  //CC
        {  
            if(state->cc.z==1) {
                uint16_t ret = state->pc+2;    
                state->memory[state->sp-1] = (ret >> 8) & 0xff;    
                state->memory[state->sp-2] = (ret & 0xff);    
                state->sp = state->sp - 2;    
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else state->pc+=2; 
            break;   
        }

        case 0xde:  //SBI D8
        {
            uint16_t ans = (uint16_t) state->a - (uint16_t) opcode[1] - state->cc.cy;
            cc4(state, ans);
            state->a = (ans&0xff);
            state->pc++;
            break;
        }
        case 0xdf:  //RST 3
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp-=2;
            state->pc = 0x18;
            break;
        }
        case 0xe0:  //RPO
        if(state->cc.p==0) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;    
        }break;
        case 0xe1:  //POP H
        {
            state->l = state->memory[state->sp];
            state->h = state->memory[state->sp+1];
            state->sp += 2;
            break;
        }
        case 0xe2:  //JPO
        {
            state->pc = (state->cc.p == 0)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        }
        case 0xe3:  //XTHL
        {
            uint8_t swp = state->l;
            state->l = state->memory[state->sp];
            state->memory[state->sp] = swp;
            swp = state->h;
            state->h = state->memory[state->sp+1];
            state->memory[state->sp+1] = swp;
            break;
        }
        case 0xe4:  //CPO
        {  
            if(state->cc.p==0) {
                uint16_t ret = state->pc+2;    
                state->memory[state->sp-1] = (ret >> 8) & 0xff;    
                state->memory[state->sp-2] = (ret & 0xff);    
                state->sp = state->sp - 2;    
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else state->pc+=2; 
            break;   
        }
        case 0xe5:  //PUSH H
        {
            state->memory[state->sp-1] = state->h;
            state->memory[state->sp-2] = state->l;
            state->sp -= 2;
            break;
        }
        case 0xe6:  //ANI
        {
            uint16_t ans = (uint16_t) state->a & opcode[1];
            cc3(state,ans);
            state->cc.cy = 0;
            state->a = ans;
            state->pc++;
            break;
        }
        case 0xe7:  //RST 4
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp-=2;
            state->pc = 0x20;
            break;
        }
        case 0xe8:  //RPE
        if(state->cc.p==1) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;    
        }break;
        case 0xe9:  //PCHL
        {
            state->pc = (state->h<<8) | state->l; break;
        }
        case 0xea:  //JPE
        {
            state->pc = (state->cc.p == 1)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        }
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
        {  
            if(state->cc.p==1) {
                uint16_t ret = state->pc+2;    
                state->memory[state->sp-1] = (ret >> 8) & 0xff;    
                state->memory[state->sp-2] = (ret & 0xff);    
                state->sp = state->sp - 2;    
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else state->pc+=2; 
            break;   
        }

        case 0xee:  //XRI
        {
            uint16_t ans = (uint16_t) state->a ^ opcode[1];
            cc3(state,ans);
            state->cc.cy = 0;
            state->a = ans;
            state->pc++;
            break;
        }
        case 0xef:  //RST 5
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp-=2;
            state->pc = 0x28;
            break;
        }
        case 0xf0:  //RP
        if(state->cc.s==0) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;    
        }break;
        case 0xf1:  //POP PSW
        {
            uint8_t psw = state->memory[state->sp];
            state->cc.z = ((psw&0x01) == 0x01);
            state->cc.s = ((psw&0x02) == 0x02);
            state->cc.p = ((psw&0x04) == 0x04);
            state->cc.cy = ((psw&0x08) == 0x08);
            state->cc.ac = ((psw&0x10) == 0x10);
            state->a = state->memory[state->sp+1];
            state->sp += 2;
            break;
        }
        case 0xf2:  //JP
        {
            state->pc = (state->cc.s == 0)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        }
        case 0xf3:  //DI
        {
            state->int_enable = 0;
            break;
        }
        case 0xf4:  //CP
        {  
            if(state->cc.s==0) {
                uint16_t ret = state->pc+2;    
                state->memory[state->sp-1] = (ret >> 8) & 0xff;    
                state->memory[state->sp-2] = (ret & 0xff);    
                state->sp = state->sp - 2;    
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else state->pc+=2; 
            break;   
        }
        case 0xf5:  //PUSH PSW
        {
            state->memory[state->sp-1] = state->a;
            state->memory[state->sp-2] = (state->cc.z | state->cc.s<<1 | state->cc.p<<2 | state->cc.cy<<3 | state->cc.ac<<4) ;
            state->sp -= 2;
            break;
        }
        case 0xf6:  //ORI
        {
            uint16_t ans = (uint16_t) state->a | opcode[1];
            cc3(state,ans);
            state->cc.cy = 0;
            state->a = ans;
            state->pc++;
            break;
        }
        case 0xf7:  //RST 6
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp-=2;
            state->pc = 0x30;
            break;
        }
        case 0xf8:  //RM
        if(state->cc.s==1) {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);    
            state->sp += 2;    
        }break;
        case 0xf9:  //SPHL
        {
            state->sp = (state->h<<8) | (state->l);
            break;
        }
        case 0xfa:  //JM
        {
            state->pc = (state->cc.s == 1)? ((opcode[2]<<8) | opcode[1]):(state->pc+2);
            break;
        }
        case 0xfb:  //EI
        {
            state->int_enable = 1;
            break;
        }
        case 0xfc:  //CM
        {  
            if(state->cc.s==1) {
                uint16_t ret = state->pc+2;    
                state->memory[state->sp-1] = (ret >> 8) & 0xff;    
                state->memory[state->sp-2] = (ret & 0xff);    
                state->sp = state->sp - 2;    
                state->pc = (opcode[2] << 8) | opcode[1];
            }
            else state->pc+=2; 
            break;   
        }

        case 0xfe:  //CPI
        {
            uint16_t ans = (uint16_t) state->a - opcode[1];
            cc4(state,ans);
            state->pc++;
            break;
        }
        case 0xff:  //RST 7
        {
            uint16_t ret = state->pc + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp-=2;
            state->pc = 0x38;
            break;
        }
    }    

    /* print out processor state */    
    printf("\tC=%d,P=%d,S=%d,Z=%d\n", state->cc.cy, state->cc.p,    
    state->cc.s, state->cc.z);    
    printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x SP %04x\n",    
    state->a, state->b, state->c, state->d, state->e, state->h, state->l, state->sp);    

	return 0;
}

void ReadFileIntoMemoryAt(State8080* state, char* filename, uint32_t offset)
{   
    //Fix the first instruction to be JMP 0x100  
    state->memory[0]=0xc3;    
    state->memory[1]=0;    
    state->memory[2]=0x01; 

    //Fix the stack pointer from 0x6ad to 0x7ad    
    // this 0x06 byte 112 in the code, which is    
    // byte 112 + 0x100 = 368 in memory    
    state->memory[368] = 0x7;    

    //Skip DAA test    
    state->memory[0x59c] = 0xc3; //JMP    
    state->memory[0x59d] = 0xc2;    
    state->memory[0x59e] = 0x05; 
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
	State8080* state = calloc(1,sizeof(State8080));
	state->memory = malloc(0x10000);  //16K
	return state;
}


int main (int argc, char**argv)
{
	int done = 0;
	int vblankcycles = 0;
	State8080* state = Init8080();
	
	ReadFileIntoMemoryAt(state,"C:/Users/Jeffery/Desktop/Folder/Downloads/cpudiag.bin", 0x100);
	
	while (done == 0)
	{
		done = Emulate8080Op(state);
	}
	return 0;
}