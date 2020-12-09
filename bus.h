/*
Handles the memory mostly
*/

class Bus {
    public:
        //http://wiki.nesdev.com/w/index.php/CPU_memory_map
        unsigned char memory[0xFFFF] = {};

        //$0000 - $1FFF (ram)
        unsigned char *ram = memory;

        //$2000 - $2007 (PPU registers http://wiki.nesdev.com/w/index.php/PPU_registers)
        unsigned char *ppu_reg = memory + 0x2000;
        unsigned char *PPUCTRL = ppu_reg;
        unsigned char *PPUMASK = ppu_reg + 0x1;
        unsigned char *PPUSTATUS = ppu_reg + 0x2;
        unsigned char *OAMADDR = ppu_reg + 0x3;
        unsigned char *OAMDATA = ppu_reg + 0x4;
        unsigned char *PPUSCROLL = ppu_reg + 0x5;
        unsigned char *PPUADDR = ppu_reg + 0x6;
        unsigned char *PPUDATA = ppu_reg + 0x7;

        //$4000 - $4017 (2A03 registers)
        unsigned char *APUIORegisters = memory + 0x4000;
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

        int storeRAM(unsigned short location, unsigned char stored){
            //make sure that location is within ram or the mirrors of the ram
            if(location >= 0x2000){
                std::cerr << "Trying to access memory out of range" << std::endl;
                return -1;
            }
            //store byte at that ram location (taking into account the potential of using the mirrored locations)
            ram[location % 0x800] = stored;
            return 1;
        }

        unsigned char getRAM(unsigned short location){
            //make sure that location is within ram or the mirrors of the ram
            if(location >= 0x2000){
                std::cerr << "Trying to access memory out of range" << std::endl;
                return -1;
            }
            //return byte at that ram location (taking into account the potential of using the mirrored locations)
            return ram[location % 0x800];
        }

        //here's where the rom is mapped to memory, it's also where we'll need to do a lot of work later to make other games work
        int loadROM(std::string romname){
            ROM rom = readROM(romname);
            if(rom.mapper == 0){
                //this assumes the specific rom of smb, i'll fix it later to include other nrom games
                //load cartridge rom into memory
                std::cout << rom.chrlen + rom.prglen + 0x8000 << std::endl;
                for(int i = 0; i < rom.prglen; i++) memory[0x8000 + i] = rom.prg[i];
                for(int i = 0; i < rom.chrlen; i++) memory[0x8000 + rom.prglen + i] = rom.chr[i];
                return 1;
            }
            return -1;
        }
};