#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h> 

#include "opcodes.h"
#include "rom.h"
#include "bus.h"
#include "apu.h"
#include "cpu.h"
#include "ppu.h"

//using namespace std;
//if only i could

//clock speed is 1.79 MHz
const int CLOCK_SPEED = 1790000;

Bus bus;
APU apu;
CPU cpu;
PPU ppu;

void initSys(){
    apu.bus = &bus;
    cpu.bus = &bus;
    cpu.init();
    ppu.bus = &bus;
}

int main(){
    bus.loadROM("Super Mario Bros..nes");
    initSys();
    while(true){
        cpu.step();
        std::cout << "X is " << (int)cpu.X << std::endl;
        std::cout << "Y is " << (int)cpu.Y << std::endl;
        std::cout << "A is " << (int)cpu.A << std::endl;
        std::cout << "PC is " << (int)cpu.PC << std::endl;
        std::cout << "$0000 is " << (int)bus.getCPUMem(0) << std::endl;
        std::cin.get();
    }
    return 0;
}

