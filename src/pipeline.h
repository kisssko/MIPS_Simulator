#ifndef PIPELINE_H
#define PIPELINE_H

#include "Instructions.h"
#include "mu-mips.h"

// project types
typedef enum 
{
	DEFAULT_CONTROL_TYPE = 0,
	LOAD_TYPE, 
	STORE_TYPE, 
	REGISTER_TYPE,
	SPECIAL_REGISTER_TYPE,
	BRANCH_TYPE
} CONTROL_TYPE;

typedef enum 
{
	DEFAULT_DATA_SIZE = 0,
	BYTE = 1, 
	HALF_WORD = 2, 
	WORD = 4,
} DATA_SIZE;

typedef struct CPU_Pipeline_Reg_Struct{
	uint32_t PC;
	uint32_t IR;   // Machine language instruction
	uint32_t A;    // ALU input
	uint32_t B;    // ALU input
	int32_t IMMED;
	uint32_t ALUOutput;
    uint32_t ALUOutput2;    // Used for Multiply and Divide instrs
	uint32_t LMD;
	mips_instr_t instr_data;
	CONTROL_TYPE Control;
	DATA_SIZE num_bytes;	// For store/load specify 1, 2, or 4 bytes. Ex() changes this value and MEM() and WB() should use this
	uint32_t FORWARDA;
	uint32_t FORWARDB;
	uint8_t flush;
} CPU_Pipeline_Reg;


/***************************************************************/
/* Pipeline Registers.                                         */
/***************************************************************/
CPU_Pipeline_Reg IF_ID;
CPU_Pipeline_Reg ID_EX;
CPU_Pipeline_Reg EX_MEM;
CPU_Pipeline_Reg MEM_WB;


// function declarations
void handle_pipeline();
void WB();
void MEM();
void EX();
void ID();
void IF();
void show_pipeline();
void print_program();

uint8_t checkDataHazard();
uint8_t checkControlHazard();
uint8_t checkForward();
uint8_t CheckInCache(uint32_t address);
uint32_t GetCacheValue(uint32_t address);
void SetCacheValue(uint32_t address, uint32_t value);
void LoadCache(uint32_t address);
void HandleLoadCache();
void HandleStoreCache();
#endif
