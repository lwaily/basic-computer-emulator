/**
 * Name:  Ali Alwaily
 * Date:  4 July 2026
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

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

#define MAX_REG		16

/**
 * TODO CREATE 4 KB of MEMORY to ACT as THE COMPUTER MEMORY as if you're
 * 	working with a 4 KB COMPUTER.
 */

/**
 * CPU Class
 */
class cpu {
	public:
		/**
		 * Register Class
		 *		Registers here are represented as integer data types, which are 32-bits
		 *		 long, or 4 bytes. I have mostly followed ARM architure in the way I set
		 *		 up registers. Every register is accessed through the reg_arr[] array.
		 */
		class reg {
			public:
				/**
				* Structure of the Register array reg_arr[]
				*/
				int reg_arr[MAX_REG];
				/**
				* Constructor that initializes the registers.
				*/
				reg(){
					/**
					* ----------  SCHEME  -------------------------------------
					* REG_0  = General Purpose, Argument, Return Value
					* 											[Not Preserved]
					* REG_1  = General Purpose, Argument 		[Not Preserved]
					* REG_2  = General Purpose, Argument 		[Not Preserved]
					* REG_3  = General Purpose, Argument 		[Not Preserved]
					* REG_4  = General Purpose					[Preserved]
					* REG_5  = General Purpose 					[Preserved]
					* REG_6  = General Purpose 					[Preserved]
					* REG_7  = General Purpose 					[Preserved]
					* REG_8  = General Purpose 					[Preserved]
					* REG_9  = General Purpose 					[Preserved]
					* REG_10 = General Purpose 					[Preserved]
					* REG_11 = Frame Pointer 					[Preserved]
					* REG_12 = Instra Procedure Call 			[Not Preserved]
					* REG_13 = Stack Pointer  					[Preserved]
					* REG_14 = Link Register 					[Preserved]
					* REG_15 = Program Counter 					[Not Preserved]
					*/
					for(int i = 0; i < 11; ++i) { reg_arr[i] = 0; }
					reg_arr[11] = 0;
					reg_arr[12] = 0;
					reg_arr[13] = 0;
					reg_arr[14] = 0;
					reg_arr[15] = 4;
				}
				/**
				 *
				 */
				void incr_pc();
		};	// end of reg class
		/**
		 * aka: Current Program Status Register
		 */
		double CPSR;
		//
		/**
		 * Constructor that initializes the CPU
		 */
		cpu(){
			/**
			 * ----------  STRUCTURE  OF  THE  CPSR  --------------------------
			 * 	Based off of how it works in ARM.
			 * "Conditions which are used to construct conditional loops and
			 * 		other branching are based on condition flags, sometimes
			 * 		referred to as the ALU flags stored in PSTATE, which are in
			 * 		the global condition flag register, NZCV (shown in my ARM64
			 * 		Register Architecture diagram)."
			 * 	Reference:
			 * https://eclecticlight.co/2021/06/23/code-in-arm-assembly-controlling-flow/
			 * ----------------------------------
			 * The CPSR variable is 8 bytes, which is perfect for what I what I
			 * 	want to do, which is to have 4 bits of room for the flags
			 * 	outlined below AND allow up to 16 nested if-statements and for-
			 * 	loops.
			 * I really don't get how the CPU really does this, but this is
			 * 	the best I've come up with to simulate the behaivor.
			 * ----------  FLAGS  ---------------------------------------------
			 * N - Negative condition code flag;
			 * 			1: negative; 0 otherwise
			 * Z - Zero condition code flag
			 *			1: result is 0; 0 otherwise
			 * C - Carry condition code flag
			 * 			1: carry produced; 0 otherwise
			 * V - oVerflow condition code flag
			 * 			1: overflow produced; 0 otherwise
			 */
			CPSR = 0;
		}
};	// end of cpu class

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

/**
 * A global vector that holds the instructions for a program.
 */
std::vector<instr> program;

#endif 
