#include <stdio.h>
#include <stdint.h>

#include "Instructions.h"
#include "mu-mips.h"

mips_instr_t opcode_0x00_table[0x2A + 1] =
{
			// Name			type	OCode	FCode	Makeup			FPtr	SubTable
	[0x00] = { "SLL",		R_TYPE, 0x00,	0x00,	{RD, RT, SA},	&instr_handler_SLL,		NULL },
	[0x02] = { "SRL",		R_TYPE, 0x00,	0x02,	{RD, RT, SA},	&instr_handler_SRL,		NULL },
	[0x03] = { "SRA",		R_TYPE, 0x00,	0x03,	{RD, RT, SA},	&instr_handler_SRA,		NULL },
	[0x08] = { "JR",		R_TYPE, 0x00,	0x08,	{RS},			&instr_handler_JR,		NULL },
	[0x09] = { "JALR",		R_TYPE, 0x00,	0x09,	{RD, RS},		&instr_handler_JALR,	NULL },
	[0x0C] = { "SYSCALL",	R_TYPE, 0x00,	0x0C,	{INV},			NULL,	NULL },
	[0x10] = { "MFHI",		R_TYPE, 0x00,	0x10,	{RD},			NULL,	NULL },
	[0x11] = { "MTHI",		R_TYPE, 0x00,	0x11,	{RS},			NULL,	NULL },
	[0x12] = { "MFLO",		R_TYPE, 0x00,	0x12,	{RD},			NULL,	NULL },
	[0x13] = { "MTLO",		R_TYPE, 0x00,	0x13,	{RS},			NULL,	NULL },
	[0x18] = { "MULT",		R_TYPE, 0x00,	0x18,	{RS, RT},		NULL,	NULL },
	[0x19] = { "MULTU",		R_TYPE, 0x00,	0x19,	{RS, RT},		NULL,	NULL },
	[0x1A] = { "DIV",		R_TYPE, 0x00,	0x1A,	{RS, RT},		NULL,	NULL },
	[0x1B] = { "DIVU",		R_TYPE, 0x00,	0x1B,	{RS, RT},		NULL,	NULL },
	[0x20] = { "ADD",		R_TYPE,	0x00,	0x20,	{RD, RS, RT},	NULL,	NULL },
	[0x21] = { "ADDU",		R_TYPE, 0x00,	0x21,	{RD, RS,RT},	NULL,	NULL },
	[0x22] = { "SUB",		R_TYPE, 0x00,	0x22,	{RD, RS, RT},	NULL,	NULL },
	[0x23] = { "SUBU",		R_TYPE, 0x00,	0x23,	{RD, RS, RT},	NULL,	NULL },
	[0x24] = { "AND",		R_TYPE, 0x00,	0x24,	{RD, RS, RT},	NULL,	NULL },
	[0x25] = { "OR",		R_TYPE, 0x00,	0x25,	{RD, RS, RT},	NULL,	NULL },
	[0x26] = { "XOR",		R_TYPE, 0x00,	0x26,	{RD, RS, RT},	NULL,	NULL },
	[0x27] = { "NOR",		R_TYPE, 0x00,	0x27,	{RD, RS, RT},	NULL,	NULL },
	[0x2A] = { "SLT",		R_TYPE, 0x00,	0x2A,	{RD, RS, RT},	NULL,	NULL }
};

mips_instr_t opcode_0x01_table[2] =
{
			// Name			type	OCode	FCode	Makeup			FPtr	SubTable
	[0x00] = { "BLTZ",		I_TYPE,	0x01,	0x00,	{RS, IMMED},	NULL,	NULL },
	[0x01] = { "BGEZ",		I_TYPE, 0x01,	0x00,	{RS, IMMED},	NULL,	NULL }
};


mips_instr_t mips_instr_lookup[0x2B + 1] =
{
			//  Name		type	OCode	FCode	Makeup				FunctPtr			SubTable
	[0x00] = { "XXXX",		M_TYPE,	0x00,	0x00,	{},					NULL,				opcode_0x00_table },
	[0x01] = { "XXXX",		M_TYPE,	0x01,	0x00,	{},					NULL,				opcode_0x01_table },
	[0x02] = { "J",			J_TYPE,	0x02,	0x00,	{ADDRESS},			NULL,				NULL },
	[0x03] = { "JAL",		J_TYPE,	0x03,	0x00,	{ADDRESS},			NULL,				NULL },
	[0x04] = { "BEQ",		I_TYPE,	0x04,	0x00,	{RS, RT, IMMED},	NULL,				NULL },
	[0x05] = { "BNE",		I_TYPE,	0x05,	0x00,	{RS, RT, IMMED},	NULL,				NULL },
	[0x06] = { "BLEZ",		I_TYPE,	0x06,	0x00,	{RS, IMMED},		NULL,				NULL },
	[0x07] = { "BGTZ",		I_TYPE,	0x07,	0x00,	{RS, IMMED},		NULL,				NULL },
	[0x08] = { "ADDI",		I_TYPE,	0x08,	0x00,	{RT, RS, IMMED},	NULL,				NULL },
	[0x09] = { "ADDIU",		I_TYPE,	0x09,	0x00,	{RT, RS, IMMED},	NULL,				NULL },
	[0x0A] = { "SLTI",		I_TYPE,	0x0A,	0x00,	{RT, RS, IMMED},	NULL,				NULL },
	[0x0C] = { "ANDI",		I_TYPE,	0x0C,	0x00,	{RT, RS, IMMED},	NULL,				NULL },
	[0x0D] = { "ORI",		I_TYPE,	0x0D,	0x00,	{RT, RS, IMMED},	NULL,				NULL },
	[0x0E] = { "XORI",		I_TYPE,	0x0E,	0x00,	{RT, RS, IMMED},	NULL,				NULL },
	[0x0F] = { "LUI",		I_TYPE,	0x0F,	0x00,	{RT, IMMED},		&instr_handler_LUI,	NULL },
	[0x20] = { "LB",		I_TYPE,	0x20,	0x00,	{RT, IMMED, RS},	NULL,				NULL },
	[0x21] = { "LH",		I_TYPE,	0x21,	0x00,	{RT, IMMED, RS},	NULL,				NULL },
	[0x23] = { "LW",		I_TYPE,	0x23,	0x00,	{RT, IMMED, RS},	NULL,				NULL },
	[0x28] = { "SB",		I_TYPE,	0x28,	0x00,	{RT, IMMED, RS},	NULL,				NULL },
	[0x29] = { "SH",		I_TYPE,	0x29,	0x00,	{RT, IMMED, RS},	NULL,				NULL },
	[0x2B] = { "SW",		I_TYPE,	0x2B,	0x00,	{RT, IMMED, RS},	NULL,				NULL }
};

char mips_reg_names[][5] =
{
	[0] = "zero",
	[1] = "at",
	[2] = "v0",
	[3] = "v1",
	[4] = "a0",
	[5] = "a1",
	[6] = "a2",
	[7] = "a3",
	[8] = "t0",
	[9] = "t1",
	[10] = "t2",
	[11] = "t3",
	[12] = "t4",
	[13] = "t5",
	[14] = "t6",
	[15] = "t7",
	[16] = "s0",
	[17] = "s1",
	[18] = "s2",
	[19] = "s3",
	[20] = "s4",
	[21] = "s5",
	[22] = "s6",
	[23] = "s7",
	[24] = "t8",
	[25] = "t9",
	[26] = "k0",
	[27] = "k1",
	[28] = "gp",
	[29] = "sp",
	[30] = "fp",
	[31] = "ra"
};

mips_instr_t mips_instr_decode( uint32_t instr )
{
	uint8_t opcode;
	uint8_t funct_code;
	uint8_t rt;
	mips_instr_t instr_info;


	opcode = GET_OPCODE( instr );
	funct_code = -1;
	rt = -1;

	if( opcode == 0 )
	{
		funct_code = GET_FUNCTCODE( instr );
		instr_info = mips_instr_lookup[opcode].subtable[funct_code];
	}
	else if( opcode == 1 )
	{
		rt = GET_RT( instr );
		instr_info = mips_instr_lookup[opcode].subtable[rt];
	}
	else
	{
		instr_info = mips_instr_lookup[opcode];

	}

	return instr_info;
}

void instr_handler_LUI()
{
	printf( "LUI executed\n\n" );
}

void instr_handler_JALR()
{

}

void instr_handler_JR()
{
	uint32_t instr;
	int32_t rs_val;
	uint8_t rs;

	// Get instruction
	instr = mem_read_32(CURRENT_STATE.PC);

	rs = GET_RS(instr);
	rs_val = CURRENT_STATE.REGS[rs];

	// jump to specified address
	NEXT_STATE.PC = rs_val;
}

void instr_handler_SRA()
{
	uint32_t instr;
	int32_t rt_val;
	uint8_t rt, rd, sa;

	// Get instruction
	instr = mem_read_32(CURRENT_STATE.PC);

	rt = GET_RT(instr);
	rd = GET_RD(rd);
	sa = GET_SA(sa);
	rt_val = CURRENT_STATE.REGS[rt];

	// Shift right and sign extend
	rt_val >> sa;
	NEXT_STATE.REGS[rd] = rt_val;

	// Increment program counter
	NEXT_STATE.PC += 4;
}

void instr_handler_SLL()
{
	uint32_t instr;
	uint32_t rt_val;
	uint8_t rt, rd, sa;

	// Get instruction
	instr = mem_read_32(CURRENT_STATE.PC);

	rt = GET_RT(instr);
	rd = GET_RD(rd);
	sa = GET_SA(sa);
	rt_val = CURRENT_STATE.REGS[rt];

	// Shift left and zero extend
	rt_val << sa;
	NEXT_STATE.REGS[rd] = rt_val;

	// Increment program counter
	NEXT_STATE.PC += 4;
}

void instr_handler_SRL()
{
	uint32_t instr;
	uint32_t rt_val;
	uint8_t rt, rd, sa;

	// Get instruction
	instr = mem_read_32(CURRENT_STATE.PC);

	rt = GET_RT(instr);
	rd = GET_RD(rd);
	sa = GET_SA(sa);
	rt_val = CURRENT_STATE.REGS[rt];

	// Shift right and zero extend
	rt_val >> sa;
	NEXT_STATE.REGS[rd] = rt_val;

	// Increment program counter
	NEXT_STATE.PC += 4;
}

