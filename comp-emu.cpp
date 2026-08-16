/**
 * Name:  Ali Alwaily
 * Date:  16 August 2026
 * About: This file ...
 */

#include "comp-emu.hpp"
#include "mach-code.hpp"

#include <filesystem>
#include <thread>
#include <chrono>

/**
 * boots up computer
 */
void COMP::start_up() {
    return;
}

/**
 * displays menu options
 * @param result
 */
void COMP::menu_options(char & result) {
    std::cout << "-----MENU---------" << std::endl;
    std::cout << "(0)  [VIEW]" << std::endl;
    std::cout << "(1)  [CREATE NEW]" << std::endl;
    std::cout << "(q)  [QUIT]" << std::endl;
    std::cin >> result;
    return;
}

/**
 * view programs stored in "hard drive" file
 */
void COMP::view_programs() {
    // new menu, list of programs and ...

    // this is a work in progress so always skip
    if(0) {
        //std::cout << "" << std::endl;
        return;
    } else {
        std::cout << "NO PROGRAMS FOUND" << std::endl;
        return;
    }
}

/**
 * sets up new coding environment
 */
void COMP::new_program() {
    // here, just run mach-code.cpp and add while loop

    // Wait two seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));

    char result = '-';
    machine_code_emulator();
    // While user does not input q (for quit)
    while(result != 'q'){

        if(result != 'q') {
            if(result == 's') {
                std::cout << "SAVING" << std::endl;
                result = '-';
            } else if(result == 'n') {
                machine_code_emulator();
                result = '-';
            } else {
                std::cout << "-----SUBMENU------" << std::endl;
                std::cout << "(s)  [SAVE]" << std::endl;
                std::cout << "(n)  [NEW PROJECT]" << std::endl;
                std::cout << "(q)  [QUIT]"<< std::endl;
                std::cin >> result;
            }
        }
    }
    return;
}

/**
 * if program was run with no arguments
 */
void COMP::NO_ARG(){
    std::cout << "No Program Found" << std::endl;
    std::cout << "Setting up New Coding Environment" << std::endl;
    new_program();
}

/**
 * if program was run with one argument
 */
void COMP::ONE_ARG(){
    std::fstream file("harddrive1.txt", std::ios::in | std::ios::out);
    // Check file for errors
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return;
    }

    // Call Constructor if
    if(std::filesystem::file_size("harddrive1.txt") < SIZE_MB) {
        std::cout << "BEFORE" << std::endl;
        COMP::storage storage(file);
        std::cout << "AFTER" << std::endl;
    } else {
        std::cerr << "Error: Harddrive Size Too Large" << std::endl;
        return;
    }
    char result = '-';
    // While user does not input q (for quit)
    while(result != 'q'){
        menu_options(result);

        if(result != 'q') {
            if(result == '0') {
                view_programs();
            } else if(result == '1') {
                new_program();
            } else {
                menu_options(result);
            }
        }
    }

    file.close();
    return;
}
/**
 * if program was run with 2 arguments
 */
void TWO_ARG(){
    return;
}
