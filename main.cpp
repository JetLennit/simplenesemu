#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h> 

#include "opcodes.h"
#include "cpu.h"
#include "rom.h"

//using namespace std;
//if only i could

//clock speed is 1.79 MHz
const int CLOCK_SPEED = 1790000;

int main(){
    ROM rom = readRom("Super Mario Bros..nes");
    std::cout << rom.prglen;
    return 0;
}

