#include "bus.h"
#include "macros.h"

class PPU {
    public:
        Bus *bus;

        unsigned short PPUADDRstr = 0;
        unsigned short PPUSCROLLstr = 0;
        unsigned short PPUCYCLES = 0;
        unsigned short PPUSCANLINES = 0;
        bool nmi_occured = false;

        PPU(Bus* bus) {
            this->bus = bus;
        }
        
        bool step() {
            //switch ppustatus back and forth (not accurate)
            // if(*bus->PPUSTATUS == 0x00) *bus->PPUSTATUS = 0x80;
            // else *bus->PPUSTATUS = 0x00;
            // return true;

            PPUCYCLES++;
            if (PPUCYCLES > 340) {
                PPUCYCLES = 0;
                PPUSCANLINES++; 
            }

            if (PPUSCANLINES == 241 && PPUCYCLES == 1)
            {
                BITSET(*bus->PPUSTATUS, 7);
                nmi_occured = true;
                //Other drawing stuff
            }
            else if (PPUSCANLINES == 261 && PPUCYCLES == 1)
            {
                BITCLEAR(*bus->PPUSTATUS, 7);
                nmi_occured = false;
                PPUSCANLINES = 0;
            }
        }

        bool storePPUReg(unsigned short location, unsigned char stored) {
            switch(location) {
                case 0:
                    *bus->PPUCTRL = stored;
                    break;
                case 1:
                    *bus->PPUMASK = stored;
                    break;
                case 2:
                    *bus->PPUSTATUS = stored;
                    break;
                case 3:
                    *bus->OAMADDR = stored;
                    break;
                case 4:
                    *bus->OAMDATA = stored;
                    break;
                case 5:
                    *bus->PPUSCROLL = stored;
                    break;
                case 6:
                    *bus->PPUADDR = stored;
                    break;
                case 7:
                    *bus->PPUDATA = stored;
                    break;
                default:
                    return false;
                    break;
            }
            return true;
        }

        // I Will need to take another look at wiki
        unsigned char getPPUReg(unsigned short location) { 
            switch(location) {
                case 0:
                    return *bus->PPUCTRL;
                case 1:
                    return *bus->PPUMASK;
                case 2:
                    return *bus->PPUSTATUS;
                case 3:
                    return *bus->OAMADDR;
                case 4:
                    return *bus->OAMDATA;
                case 5:
                    return *bus->PPUSCROLL;
                case 6:
                    return *bus->PPUADDR;
                case 7:
                    return *bus->PPUDATA;
                default:
                    return -1;
            }
        }

        bool OAMDMA(unsigned short stored){
            *bus->OAMDMA = stored;
            return true;
        }

        // Getting the status also clears the 7th bit
        // Wiki also says "will clear...the address latch used by PPUSCROLL and PPUADDR"?
        unsigned char getPPUStatus()
        {
            unsigned char copy = *bus->PPUSTATUS;
            *bus->PPUSTATUS &= ~(1 << 7);
            return copy;
        }
};