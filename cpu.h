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
        unsigned char V = 0b01000000;
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
            
            //for instructions that interact with memory
            unsigned char tmp = 0;

            if(currop.addressmode == 0x7)
                acc = true;
            else
                address = getAddress(arg, currop.addressmode);

            std::string inst = currop.instruction;
            if(inst == "ADC"){
                //add later
            }
            else if(inst == "AND"){
                A = A & bus->getCPUMem(address);
                ZF(A);
                NF(A);
            }
            else if(inst == "ASL"){
                if(acc){
                    CF(A & 0b10000000);
                    A = A << 1;
                }
                else{
                    tmp = bus->getCPUMem(address);
                    CF(tmp & 0b10000000);
                    bus->storeCPUMem(address, tmp << 1);
                }
                ZF(A);
                NF(A);
            }
            else if(inst == "BCC"){
                //add later
            }
            else if(inst == "BCS"){
                //add later
            }
            else if(inst == "BEQ"){
                //add later
            }
            else if(inst == "BIT"){
                tmp = bus->getCPUMem(address) & A;
                ZF(tmp);
                NF(tmp);
                VF(tmp);
            }
            else if(inst == "BMI"){
                //add later
            }
            else if(inst == "BNE"){
                //add later
            }
            else if(inst == "BPL"){
                //add later
            }
            else if(inst == "BRK"){
                //add later
            }
            else if(inst == "BVC"){
                //add later
            }
            else if(inst == "BRS"){
                //add later
            }
            else if(inst == "CLC"){
                CF(false);
            }
            else if(inst == "CLD"){
                //unused by the nes
            }
            else if(inst == "CLI"){
                IF(false);
            }
            else if(inst == "CLV"){
                IF(false);
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
        
        //sets carry flag based on bytes (gonna be doing this a lot)
        void CF(bool in){
            if(in)
                P = P | C;
            else
                P = P & ~C;
        }

         //sets carry flag based on bytes (gonna be doing this a lot)
        void IF(bool in){
            if(in)
                P = P | I;
            else
                P = P & ~I;
        }

        //sets zero flag (gonna be doing this a lot)
        void ZF(unsigned char in){
            if(in == 0)
                P = P | Z;
            else
                P = P & ~Z;
        }

        //sets negative flag (gonna be doing this a lot)
        void NF(unsigned char in){
            if(in & N)
                P = P | N;
            else
                P = P & ~N;
        }

        //sets overflow flag (gonna be doing this a lot)
        void VF(unsigned char in){
            if(in & V)
                P = P | V;
            else
                P = P & ~V;
        }
};

