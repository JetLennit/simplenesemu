#include "rom.h"

ROM readROM(std::string romname) {
    ROM rom;

    //open rom file (not using the std namespace because you hate me)
    std::ifstream romf;

    romf.open(romname.c_str(), std::ios::in|std::ios::binary);

    romf.seekg(0, std::ios::beg);

    //read header
    rom.header = (unsigned char*)calloc(1, 16);
    romf.read((char*)rom.header,16);
    
    //only works with certain mappers, figure out later
    rom.mirror = (rom.header[6]&0b00000001);

    rom.mapper = ((rom.header[6] & 0b11110000) >> 4) | (rom.header[7] & 0b11110000);

    //check for trainer and ines2.0
    rom.hasTrainer = (rom.header[6]&4) != 0 ? true : false; 
    rom.isines2 = (rom.header[7]&0x0C) == 8 ? true : false;

    //if there is a trainer read and go past that (for the most part we don't need to worry about the trainer)
    //http://wiki.nesdev.com/w/index.php/INES#Trainer
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
