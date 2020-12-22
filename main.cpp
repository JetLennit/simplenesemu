#include <iostream>
#include <fstream>
#include <cstdio>
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

//Future proofing
std::string rom_name = "Burgertime.nes";

Bus bus;
APU apu(&bus);
CPU cpu(rom_name, &bus);
PPU ppu(&bus);

void initSys() {
    bus.ppu = &ppu;
}

int main(){
    initSys();
    char cmd;
    while(cmd != 'q' && cmd != 'Q'){
        cpu.step();
        cmd = getchar();
    }
    bus.dumpRAM();
    return 0;
}