/**
 * Name:  Ali Alwaily
 * Date:  15 August 2026
 * About: This header file sets up virtual computer components
 */

#ifndef CE_H
#define CE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#define SIZE_MB 32000000
#define MAX_REG 16

/**
 * Class that represents entire computer
 */
class COMP {
    public:
        /**
         * storage
         */
        class storage {
            private:
                /**
                 * TODO figure out best data type for MAX_STORAGE
                 */
                std::vector<char> MAX_STORAGE;
            public:
                /**
                 * Constructor
                 * Zero out MAX_STORAGE when no parameter passed in
                 */
                storage() : MAX_STORAGE(SIZE_MB, 0) {}
                /**
                 * Load in from file when parameter passed in
                 */
                storage(std::fstream & file) : MAX_STORAGE(SIZE_MB, 0) {
                    std::cout << "LOADED\n";
                }
                //setter
                //getter
        };
        /**
        * cpu
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
                        int32_t reg_arr[MAX_REG];
                        /**
                         * Constructor that initializes the registers.
                         */
                        reg(){
                            /**
                             * ----------  SCHEME  --------------------------------
                             * REG_0  = General Purpose, Argument, Return Value
                             * 										[Not Preserved]
                             * REG_1  = General Purpose, Argument 	[Not Preserved]
                             * REG_2  = General Purpose, Argument 	[Not Preserved]
                             * REG_3  = General Purpose, Argument 	[Not Preserved]
                             * REG_4  = General Purpose				[Preserved]
                             * REG_5  = General Purpose 			[Preserved]
                             * REG_6  = General Purpose 			[Preserved]
                             * REG_7  = General Purpose 			[Preserved]
                             * REG_8  = General Purpose 			[Preserved]
                             * REG_9  = General Purpose 			[Preserved]
                             * REG_10 = General Purpose 			[Preserved]
                             * REG_11 = Frame Pointer 				[Preserved]
                             * REG_12 = Instra Procedure Call 		[Not Preserved]
                             * REG_13 = Stack Pointer  				[Preserved]
                             * REG_14 = Link Register 				[Preserved]
                             * REG_15 = Program Counter 			[Not Preserved]
                             */
                            reg_arr[0]  = 0;
                            reg_arr[1]  = 0;
                            reg_arr[2]  = 0;
                            reg_arr[3]  = 0;
                            reg_arr[4]  = 0;
                            reg_arr[5]  = 0;
                            reg_arr[6]  = 0;
                            reg_arr[7]  = 0;
                            reg_arr[8]  = 0;
                            reg_arr[9]  = 0;
                            reg_arr[10] = 0;
                            reg_arr[11] = 0;
                            reg_arr[12] = 0;
                            reg_arr[13] = 0;
                            reg_arr[14] = 0;
                            reg_arr[15] = 4;
                        }
                        /**
                         * The Increment-PC function.
                         */
                        void incr_pc(){
                            reg_arr[15] += 4;
                        }
            };	// end of reg class
            /**
             * Current Program Status Register
             */
            uint64_t CPSR;
            //
            /**
             * Constructor that initializes the CPU
             */
            cpu(){
                /**
                 * ----------  STRUCTURE  OF  THE  CPSR  --------------------------
                 * 	Based off of how it works in ARM.
                 * ``Conditions which are used to construct conditional loops and
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

        // COMP specific functions
        /**
         * boots up computer
         */
        void start_up();

        /**
         * displays menu options
         * @param result
         */
        void menu_options(char & result);

        /**
         * view programs stored in "hard drive" file
         */
        void view_programs();

        /**
         * sets up new coding environment
         */
        void new_program();

        /**
         * if program was run with no arguments
         */
        void NO_ARG();

        /**
         * if program was run with one argument
         */
        void ONE_ARG();

        /**
         * if program was run with 2 arguments
         */
        void TWO_ARG();

};  // end of COMP class

#endif
