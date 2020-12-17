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
    cpu.init("Super Mario Bros..nes");
    ppu.bus = &bus;
}

int main(){
    initSys();
    while(true){
        cpu.step();
        std::cin.get();
    }
    return 0;
}

