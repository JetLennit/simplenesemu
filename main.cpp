#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h> 

#include "opcodes.h"

//using namespace std;
//if only i could

//clock speed is 1.79 MHz
const int CLOCK_SPEED = 1790000;

class CPU {
    public:
        unsigned char ram[2048];
};

class ROM
{
    public:
        bool isines2;
        bool hasTrainer;
        int prglen;
        int chrlen;
        unsigned char *header;
        unsigned char *trainer;
        unsigned char *prg;
        unsigned char *chr;
};

ROM readRom(std::string romname){
    ROM rom;

    //open rom file (not using the std namespace because you hate me)
    std::ifstream romf;
    std::cout << romname << std::endl;

    romf.open(romname.c_str(), std::ios::in|std::ios::binary);

    romf.seekg(0, std::ios::beg);

    //read header
    rom.header = (unsigned char*)calloc(1, 16);
    romf.read((char*)rom.header,16);
    std::cout << romf.tellg() << std::endl;
    
    //check for trainer and ines2.0
    rom.hasTrainer = (rom.header[6]&4) != 0 ? true : false; 
    rom.isines2 = (rom.header[7]&0x0C) == 8 ? true : false;

    //if there is a trainer read and go past that
    if(rom.hasTrainer){
        rom.trainer = (unsigned char*)calloc(1, 512);
        romf.read((char*)rom.trainer, 512);
    }

    //read prg rom
    rom.prglen = 16384*(rom.header[4]);
    rom.prg = (unsigned char*)calloc(1, rom.prglen);
    romf.read((char*)rom.prg, rom.prglen);

    //read chr rom
    rom.chrlen = 8192*(rom.header[5]);
    rom.chr = (unsigned char*)calloc(1, rom.chrlen);
    romf.read((char*)rom.chr, rom.chrlen);

    romf.close();

    return rom;
}

int main(){
    ROM smb = readRom("Super Mario Bros..nes");
    std::cout << smb.prglen << std::endl;
    return 0;
}

