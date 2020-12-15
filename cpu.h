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

        //http://wiki.nesdev.com/w/index.php/Status_flags
        unsigned char C = 0b00000001;
        unsigned char Z = 0b00000010;
        unsigned char I = 0b00000100;
        unsigned char B = 0b00110000;
        unsigned char O = 0b01000000;
        unsigned char N = 0b10000000;

        void runOpcode(unsigned char op, unsigned short arg){
            OPCODE currop;
            //check get instruction from opcode (will be removed later when i order opcodes)
            for(int o = 0; o < (sizeof(opcode)/sizeof(opcode[0])); o++){
                if(op == opcode[o].opcode){
                    currop = opcode[o];
                    break;
                }
            }
            
            bool acc = false;
            unsigned short address = 0;

            if(currop.addressmode != 0x7)
                address = getAddress(arg, currop.addressmode);
            else
                acc = true;

            std::string inst = currop.instruction;
            if(inst == "ADC"){
                //add later
            }
            else if(inst == "AND"){
                A = A & bus->getCPUMem(address);
                ZF();
                NF();
            }
            else if(inst == "ASL"){
                if(acc){
                    P = P | (A & 0b1);
                    A = A << 1;
                }
                ZF();
                NF();
            }
            
        }

    private:
        unsigned short getAddress(unsigned short input, unsigned char mode){
            switch(mode){
                //add modes later
                default: 
                    return 0;
                    break;
            }
        }

        //sets zero flag (gonna be doing this a lot)
        void ZF(){
            if(A == 0)
                P = P | Z;
            else
                P = P & ~Z;
        }

        //sets negative flag (gonna be doing this a lot)
        void NF(){
            if(A & 0b10000000)
                P = P | N;
            else
                P = P & ~N;
        }
};

