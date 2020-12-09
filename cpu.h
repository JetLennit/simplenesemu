/*
Handles the CPU (and, honestly, tons of other stuff because the CPU is also in charge of most other things)
*/

class CPU {
    public:
        Bus *bus;
        //http://wiki.nesdev.com/w/index.php/CPU_registers
        unsigned char A;
        unsigned char X;
        unsigned char Y;
        unsigned short PC;
        unsigned char S = 0xFD;
        unsigned char P = 0x34;
};

