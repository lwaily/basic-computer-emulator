/**
 * Name:  Ali Alwaily
 * Date:  16 August 2026
 * About: This file sets up the structure of the cpu class, with an inner class
 * 			called the reg class that takes care of initializing all 16
 * 			registers.
 * 			There is also an instance variable within the cpu class called the
 * 				CPSR, which handles branching mostly. It is a register that
 * 				exists outside of the other registers and is here represented
 * 				as a double, which is to have 4 bits of room for the flags
 * 				(outlined below) AND allow up to 16 nested if-statements and
 * 				for-loops.
 * 			Furthermore, there is the instr class, which handles the processing
 * 				of instructions that the user inputs. These instructions will
 * 				later be pushed back into the program[] vector.
 * 			There are two enums that define the values for Condition Codes and
 * 				Operation (Op) Codes.
 */

#ifndef MC_H
#define MC_H

#include <vector>	// loads vector data structure

#define SIZE_KB 32000

int machine_code_emulator();

/**
 *
 */
class program {
	private:
		/**
		 *
		 */
		char max_program_size[SIZE_KB];
	public:
		//setter for max_program_size
		//getter for max_program_size


		/**
		 * Instructions Class
		 *		This class is used to parse through every 32-bit input and break it up
		 *		into 6 categories:
		 *			Condition:			[See Enum Defined Below]
		 *			Operation Code:		[See Enum Defined Below]
		 *			Immediate Bit:		For any instruction other than branching:
		 * 								If 0, operand 2 will be treated as a register,
		 *								If 1, operand 2 will be treated as an immediate.
		 *								For Branching,
		 *								If 0, branch will not link,
		 *								If 1, this will represent branching and linking.
		 *			Destination Reg:	//
		 *			Oper1:				//
		 *			Oper2:				//
		 */
		class instr {
			public:
				/**
				 * 0b_COND_OPCD_I001_DEST_OPR1_OPER_2REG_IMME
				 */
				unsigned int condition;			// COND
				unsigned int opcode;			// OPCD
				unsigned int immediate_bit;		// I
				unsigned int dest_reg;			// DEST
				unsigned int oper1_reg;			// OPR1
				unsigned int oper2;				// OPER_2REG_IMME

				/**
				 * Constructor
				 * @param value
				 */
				instr(unsigned int value){
					condition		= (value & 0xf0000000) >> 28;
					opcode			= (value & 0x0f000000) >> 24;
					immediate_bit	= (value & 0x00800000) >> 23;
					dest_reg		= (value & 0x000f0000) >> 16;
					oper1_reg		= (value & 0x0000f000) >> 12;
					oper2			= (value & 0x00000fff);
				}
		};	// end of instr class
		/**
		 * A global vector that holds the instructions for a program.
		 */
		std::vector<instr> program_instructions;
};

/**
 * Condition Enum that represents the value of every condition
 */
enum cond {
	EQ = 0,		// == equal to
	NE = 1,		// != not equal to
	LT = 2,		// <  less than
	LE = 3,		// <= less than or equal to
	GT = 4,		// >  greater than
	GE = 5,		// >= greater than or equal to
	AL = 14,	// ALWAYS
};

/**
 * Op_code Enum that represents the value of every operation code
 */
enum op_code {
	// Logical Operations
	HLT = 0, 	// EOP signal
	AND = 1,	// &
	ORR = 2,	// |
	XOR = 3,	// ^
	BIC = 4,	// a & ~b
	LSR = 5,	// a >> n (zero extend)
	ASR = 6,	// a >> n (sign extend)
	LSL = 7,	// a << n (zero extend)
	// Arithmetic Operations
	ADD = 8,	// a + b
	SUB = 9,	// a - b
	MOV = 10,	// a = b
	MVN = 11,	// a = ~b
	// Data Transfer Operations
	LDR = 12,	//
	STR = 13,	//
	// Control Flow Operations
	CMP = 14,	//
	B	= 15,	//
};

#endif
