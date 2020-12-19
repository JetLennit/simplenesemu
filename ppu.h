#include "bus.h"

class PPU {
    public:
        Bus *bus;

        unsigned short PPUADDRstr = 0;
        unsigned short PPUSCROLLstr = 0;

        PPU(Bus* bus) {
            this->bus = bus;
        }
        
        bool step(){
            //switch ppustatus back and forth (not accurate)
            if(*bus->PPUSTATUS == 0x00) *bus->PPUSTATUS = 0x80;
            else *bus->PPUSTATUS = 0x00;

            return true;
        }

        bool storePPUReg(unsigned short location, unsigned char stored){
            switch(location){
                case 0:
                    *bus->PPUCTRL = stored;
                    break;
                case 3:
                    *bus->OAMADDR = stored;
                    break;
                default:
                    return false;
                    break;
            }
            return true;
        }

        unsigned char getPPUReg(unsigned short location){
            return 0;
        }

        bool OAMDMA(unsigned short stored){
            return true;
        }
};