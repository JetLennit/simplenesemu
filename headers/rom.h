/*
Handles the game ROM
*/
#ifndef ROM_H
#define ROM_H
#include <string>
#include <fstream>

class ROM {
    //http://wiki.nesdev.com/w/index.php/INES
    public:
        //we can worry about iNES2 later, most roms don't require the specific features and it's backwards compatibile with iNES
        //see http://wiki.nesdev.com/w/index.php/NES_2.0
        bool isines2;
        bool hasTrainer;
        bool mirror;
        int prglen;
        int chrlen;
        unsigned char mapper;
        unsigned char *header;
        unsigned char *trainer;
        unsigned char *prg;
        unsigned char *chr;
};

ROM readROM(std::string romname);
#endif