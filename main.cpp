#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h> 

#include "opcodes.h"
#include "rom.h"
#include "bus.h"
#include "cpu.h"

//using namespace std;
//if only i could

//clock speed is 1.79 MHz
const int CLOCK_SPEED = 1790000;

Bus bus;
CPU cpu;

void initCPU(){
    cpu.bus = &bus;
    //these are for testing the properties of pointers, they're temporary. i'm only keeping them for now so i remember how to do it
    //*bus.SQ1_HI = 'a';
    //std::cout << cpu.bus->SQ1_HI << std::endl;
}

int main(){
    initCPU();
    std::cout << bus.loadROM("Super Mario Bros..nes") << std::endl;
    std::cout << bus.memory[0x8000] << std::endl;
    return 0;
}

