/**
 * Name:  Ali Alwaily
 * Date:  15 August 2026
 * About: This file acts as the ``entry point" into the program. It defines the
 * 			incr_pr() function, initializes variables, asks for user input and
 * 			processes that, then begins "executing" those instructions.
 * 			Finally, it will return the values of all the registers and frees
 * 				up any dynamically-allocated memory.
 */

#include "comp-emu.hpp"		//
#include "mach-code.hpp"	//

#include <iostream>			//
#include <string>			//
#include <bitset>			//

/**
 * Main Function
 */
int machine_code_emulator(){
	program new_program;

	// Local Variables
	std::string  input_str;
	unsigned int inst = 4294967295;
	
	// Prompt User Input
	std::cout << "Each instruction should be represented as:" << std::endl
			<< "0b_<COND>_<OPCD>_<I>001_<DEST>_<OPR1>_<OPER_2REG_IMME>" << std::endl
			<< "Input Instructions:            v" << std::endl;
	
	// Recieve User Input until Op-Code is "0000," which means HALT
	while (std::cin >> input_str && input_str.substr(4,4) != "0000") {
		if(input_str.size() == 32){
			// This converts the string of 1s and 0s into a 32-bit unsigned int
			std::bitset<32> bits(input_str);
			inst = static_cast<unsigned int>(bits.to_ulong());
			// Create new instr object and push pack into program[] vector
			program::instr my_instr(inst);
			new_program.program_instructions.push_back(my_instr);
		} else {
			/**
			 * Currently, there will be no additional checks to see if the
			 * 	instruction provided by the user is valid or not.
			 */
			std::cout << "Invalid Input (Must be 32-bits long)" << std::endl;
		}
	}

	// Creates a reg object
	COMP::cpu::reg my_reg;

/*	
	// TEST
	std::cout << "----  TEST  ----" << std::endl;
	for(unsigned int i = 0; i < program.size(); ++i){
		std::cout <<
				program[i].condition		<< " " <<
				program[i].opcode			<< " " <<
				program[i].immediate_bit	<< " " <<
				program[i].dest_reg			<< " " <<
				program[i].oper1_reg		<< " " <<
				program[i].oper2			<< " " 
				<< std::endl;
	}
	std::cout << "----------------" << std::endl;
*/
	// Parse the instructions and ``execute" them
	unsigned int n = new_program.program_instructions.size();
	for(unsigned int i = 0; i < n; ++i){
		/**
		 *
		 */
		if(new_program.program_instructions[i].opcode == AND){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int rn = (int)new_program.program_instructions[i].oper1_reg;
				int op = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] & my_reg.reg_arr[op];
			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd  = (int)new_program.program_instructions[i].dest_reg;
				int rn  = (int)new_program.program_instructions[i].oper1_reg;
				int imm = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] & imm;
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == ORR){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int rn = (int)new_program.program_instructions[i].oper1_reg;
				int op = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] | my_reg.reg_arr[op];
			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd  = (int)new_program.program_instructions[i].dest_reg;
				int rn  = (int)new_program.program_instructions[i].oper1_reg;
				int imm = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] | imm;
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == XOR){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int rn = (int)new_program.program_instructions[i].oper1_reg;
				int op = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] ^ my_reg.reg_arr[op];
			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd  = (int)new_program.program_instructions[i].dest_reg;
				int rn  = (int)new_program.program_instructions[i].oper1_reg;
				int imm = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] ^ imm;
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == BIC){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int rn  = (int)new_program.program_instructions[i].oper1_reg;
				int op = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] & ~(my_reg.reg_arr[op]);

				std::cout << rd << std::endl
						<< rn << std::endl
						<< op << std::endl
						<< my_reg.reg_arr[rd] << std::endl
						<< my_reg.reg_arr[rn] << std::endl
						<< ~(my_reg.reg_arr[op]) << std::endl;

			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd  = (int)new_program.program_instructions[i].dest_reg;
				int rn  = (int)new_program.program_instructions[i].oper1_reg;
				int imm = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] & ~(imm);
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == LSR){
			//
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == ASR){
			//
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == LSL){
			//
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == ADD){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int rn = (int)new_program.program_instructions[i].oper1_reg;
				int op = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] + my_reg.reg_arr[op];
			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd  = (int)new_program.program_instructions[i].dest_reg;
				int rn  = (int)new_program.program_instructions[i].oper1_reg;
				int imm = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] + imm;
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == SUB){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int rn = (int)new_program.program_instructions[i].oper1_reg;
				int op = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] - my_reg.reg_arr[op];
			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int rn  = (int)new_program.program_instructions[i].oper1_reg;
				int imm = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[rn] - imm;
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == MOV){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int value = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = my_reg.reg_arr[value];
			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd = (int)new_program.program_instructions[i].dest_reg;
				int value = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = value;
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == MVN){
			if(new_program.program_instructions[i].immediate_bit == 0){
				int rd      = (int)new_program.program_instructions[i].dest_reg;
				int reg_val = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = ~(my_reg.reg_arr[reg_val]) + 1;
			} else if(new_program.program_instructions[i].immediate_bit == 1){
				int rd    = (int)new_program.program_instructions[i].dest_reg;
				int value = (int)new_program.program_instructions[i].oper2;
				my_reg.reg_arr[rd] = ~(value) + 1;
			}
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == LDR){
			//
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == STR){
			//
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == CMP){
			/**
			 * cmp a, b
			 * \where a is rd and b is oper2
			 */
			/*
			if(program[i].immediate_bit == 0){
				int rd_value = my_reg.reg_arr[(int)program[i].dest_reg];
				int op_value = (int)program[i].oper2;
			} else if(program[i].immediate_bit == 1){
				int rd_value  = my_reg.reg_arr[(int)program[i].dest_reg];
				int imm_vaule = (int)program[i].oper2;
				//
			}
			*/
		}
		/**
		 *
		 */
		else if(new_program.program_instructions[i].opcode == B){
			//
		}
		/**
		 *
		 */
		my_reg.incr_pc();
	}

	/**
	 *
	 */
	std::cout << "-=-=-=- FINAL REGISTER VALUES -=-=-=-" << std::endl;
	for(int j = 0; j < 16; ++j){
		std::cout << "\tr" << j << "\t" << my_reg.reg_arr[j] << std::endl;
	}
	std::cout << "    Total Lines of Code: " << my_reg.reg_arr[15] / 4 << std::endl;

	/**
	 *
	 */
	// TODO free memory

	return 0;
}
