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

    private:
        unsigned short getAddressMode(OPCODE opcode){
            unsigned short addressmode = opcode.opcode & 0b00011100;
            unsigned short modifier = opcode.opcode & 0b00000011;
            if(modifier == 0b01){
                
            }
            else if(modifier == 0b10){

            }
            else if(modifier == 0b00){
                
            }
            else{
                std::cerr << "Nonexistant opcode modifier" << std::endl;
                return -1;
            }
            return -1;
        }
};

