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

Bus bus;
APU apu;
CPU cpu;
PPU ppu;

void initSys(){
    bus.ppu = &ppu;
    apu.bus = &bus;
    cpu.bus = &bus;
    cpu.init("Burgertime.nes");
    ppu.bus = &bus;
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

