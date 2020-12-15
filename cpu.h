/*
Handles the CPU (and, honestly, tons of other stuff because the CPU is also in charge of most other things)
*/

class CPU {
    public:
        Bus *bus;
        //http://wiki.nesdev.com/w/index.php/CPU_registers
        unsigned char A = 0;
        unsigned char X = 0;
        unsigned char Y = 0;
        unsigned short PC = 0;
        unsigned char S = 0xFD;
        unsigned char P = 0x34;

        void runOpcode(unsigned char op){
            //check get instruction from opcode (will be removed later when i order opcodes)
            OPCODE opcode;
            for(int o = 0; o < (sizeof(opcode)/sizeof(opcode[0])); o++){
                if(op == opcode[o].opcode){
                    opln = opcode[o];
                    break;
                }
            }

            std::string inst = opcode.instruction;
        }
};

