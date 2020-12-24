#ifndef PPU_H
#define PPU_H
#include "macros.h"

class Bus;

class PPU {
    public:
        Bus *bus;

        unsigned short PPUADDRstr = 0;
        unsigned short PPUSCROLLstr = 0;
        unsigned short PPUCYCLES = 0;
        unsigned short PPUSCANLINES = 0;
        bool nmi_occured = false;

        PPU(Bus* bus);
        
        bool step();

        bool storePPUReg(unsigned short location, unsigned char stored);
        // I Will need to take another look at wiki
        unsigned char getPPUReg(unsigned short location);
        bool OAMDMA(unsigned short stored);

        // Getting the status also clears the 7th bit
        // Wiki also says "will clear...the address latch used by PPUSCROLL and PPUADDR"?
        unsigned char getPPUStatus();
};
#endif