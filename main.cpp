/**
 * Name:  Ali Alwaily
 * Date:  16 August 2026
 * About: This file is the ``entry point" into the program.
 */

#include "comp-emu.hpp"

/**
 * Main Function
 * @param argc
 * @param argv
 */
int main(int argc, char* argv[]){
    COMP comp;
    comp.start_up();
    /**
     * If program ran without additional argument
     */
    if(argc == 1) {
        if(1) {
            comp.NO_ARG();
        }
    }
    /**
     * If program ran with additional argument, which is a file
     * ![WORK IN PROGRESS]
     */
    else if(argc == 2) {
        comp.ONE_ARG();
    }
    /**
     * If program ran with 2 additional arguments, both of which are files
     * ![WORK IN PROGRESS]
     */
    else if(argc == 3) {
        //comp.TWO_ARG();
    }
    /**
     *
     */
    else {
        std::cout << "else" << std::endl;
    }

    return 0;   // EOP
}
