/*
Handles the memory mostly
*/
#ifndef BUS_H
#define BUS_H
#include "rom.h"
class PPU;

class Bus {
    public:
        ROM rom;
        PPU *ppu;
        
        //CPU MEMORY
        //http://wiki.nesdev.com/w/index.php/CPU_memory_map
        unsigned char cpu_memory[0xFFFF] = {};

        //$0000 - $1FFF (ram)
        unsigned char *ram = cpu_memory;

        //$2000 - $2007 (PPU registers http://wiki.nesdev.com/w/index.php/PPU_registers)
        unsigned char *ppu_reg = cpu_memory + 0x2000;
        unsigned char *PPUCTRL = ppu_reg;
        unsigned char *PPUMASK = ppu_reg + 0x1;
        unsigned char *PPUSTATUS = ppu_reg + 0x2;
        unsigned char *OAMADDR = ppu_reg + 0x3;
        unsigned char *OAMDATA = ppu_reg + 0x4;
        unsigned char *PPUSCROLL = ppu_reg + 0x5;
        unsigned char *PPUADDR = ppu_reg + 0x6;
        unsigned char *PPUDATA = ppu_reg + 0x7;

        //$4000 - $4017 (2A03 registers)
        unsigned char *APUIORegisters = cpu_memory + 0x4000;
        unsigned char *SQ1_VOL = APUIORegisters;
        unsigned char *SQ1_SWEEP = APUIORegisters + 0x01;
        unsigned char *SQ1_LO = APUIORegisters + 0x02;
        unsigned char *SQ1_HI = APUIORegisters + 0x03;
        unsigned char *SQ2_VOL = APUIORegisters + 0x04;
        unsigned char *SQ2_SWEEP = APUIORegisters + 0x05;
        unsigned char *SQ2_LO = APUIORegisters + 0x06;
        unsigned char *SQ2_HI = APUIORegisters + 0x07;
        unsigned char *TRI_LINEAR = APUIORegisters + 0x08;
        unsigned char *TRI_LO = APUIORegisters + 0x0A;
        unsigned char *TRI_HI = APUIORegisters + 0x0B;
        unsigned char *NOISE_VOL = APUIORegisters + 0x0C;
        unsigned char *NOISE_LO = APUIORegisters + 0x0E;
        unsigned char *NOISE_HI = APUIORegisters + 0x0F;
        unsigned char *DMC_FREQ = APUIORegisters + 0x10;
        unsigned char *DMC_RAW = APUIORegisters + 0x11;
        unsigned char *DMC_START = APUIORegisters + 0x12;
        unsigned char *DMC_LEN = APUIORegisters + 0x13;
        unsigned char *OAMDMA = APUIORegisters + 0x14;
        unsigned char *SND_CHN = APUIORegisters + 0x15;
        unsigned char *JOY1 = APUIORegisters + 0x16;
        unsigned char *JOY2 = APUIORegisters + 0x17;
        //I'm not gonna deal with the CPU test mode registers, they don't really seem to matter
        //I'm also not sure if we need to put the data from the ROM into here, only time will tell

        //PPU MEMORY
        //Object Attribute Memory (https://wiki.nesdev.com/w/index.php/PPU_OAM)
        unsigned char OAM[0xFF] = {};

        //https://wiki.nesdev.com/w/index.php/PPU_memory_map
        unsigned char ppu_memory[0x3FFF] = {};

        //$0000 - $1FFF (full pattern table)
        unsigned char *pattern_table = ppu_memory;

        //$0000 - $1FFF (pattern tables 0-1) (not sure if this is neccessary yet)
        unsigned char *pattern_table1 = pattern_table;
        unsigned char *pattern_table2 = pattern_table1 + 0x1000;

        //$2000 - $2FFF (full name table)
        unsigned char *name_table = ppu_memory + 0x2000;

        //$2000 - $2FFF (name tables 0-3) (not sure if this is neccessary yet)
        unsigned char *name_table0 = name_table;
        unsigned char *name_table1 = name_table + 0x0400;
        unsigned char *name_table2 = name_table + 0x0800;
        unsigned char *name_table3 = name_table + 0x0C00;
        //this section is mirrored, resolve later

        //$3F00 - $3F1F (https://wiki.nesdev.com/w/index.php/PPU_palettes)
        unsigned char *palette_map = ppu_memory + 0x3F00;
        unsigned char *universal_background_color = palette_map;
        unsigned char *background_palette0 = palette_map + 0x01;
        unsigned char *background_palette1 = palette_map + 0x05;
        unsigned char *background_palette2 = palette_map + 0x09;
        unsigned char *background_palette3 = palette_map + 0x0D;
        unsigned char *sprite_palette0 = palette_map + 0x11;
        unsigned char *sprite_palette1 = palette_map + 0x15;
        unsigned char *sprite_palette2 = palette_map + 0x19;
        unsigned char *sprite_palette3 = palette_map + 0x1D;
        //this section is mirrored too, resolve later

        void dumpRAM();

        //here's where the rom is mapped to memory, it's also where we'll need to do a lot of work later to make other games work
        bool loadROM(std::string romname);

        bool storeCPUMem(unsigned short location, unsigned char stored);

        unsigned char getCPUMem(unsigned short location);
};
#endif