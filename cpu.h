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
        unsigned short PC = 0xFFFC;
        unsigned char S = 0xFD;
        unsigned char P = 0x34;

        //http://wiki.nesdev.com/w/index.php/Status_flags
        unsigned char C = 0b00000001;
        unsigned char Z = 0b00000010;
        unsigned char I = 0b00000100;
        unsigned char B = 0b00110000;
        unsigned char V = 0b01000000;
        unsigned char N = 0b10000000;
        
        bool step(){
            unsigned char ophex = bus->getCPUMem(PC);
            if(ophex != 0x22){
                OPCODE currop;
                //check get instruction from opcode (will be removed later when i order opcodes)
                for(int o = 0; o < (sizeof(opcode)/sizeof(opcode[0])); o++){
                    if(ophex == opcode[o].opcode){
                        currop = opcode[o];
                        break;
                    }
                }
            
                unsigned short arg = 0;

                if(currop.bytes = 2)
                    arg = bus->getCPUMem(PC + 1);
                else if(currop.bytes = 3)
                    arg = bus->getCPUMem(PC + 1) & (bus->getCPUMem(PC + 2)<<3);

                PC++;
                runOpcode(currop, arg);

                return true;
            }
            return false;
        }

        void runOpcode(OPCODE op, unsigned short arg){
            //for instructions that interact with memory
            unsigned char M = 0;

            bool acc = false;
            unsigned short address = 0;

            if(op.addressmode == 0x7)
                acc = true;
            else
                address = getAddress(arg, op.addressmode);

            std::string inst = op.instruction;
            if(inst == "ADC"){
                //add later
            }
            else if(inst == "AND"){
                A = A & bus->getCPUMem(address);
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "ASL"){
                if(acc){
                    CF(A & C);
                    A = A << 1;
                ZF(A == 0);
                NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & C);
                    M = M << 1;
                    bus->storeCPUMem(address, M);
                    ZF(M == 0);
                    NF(M & N);
                }
            }
            else if(inst == "BCC"){
                if(!(P & C))
                    PC = PC + (signed short)address;
            }
            else if(inst == "BCS"){
                if(P & C)
                    PC = PC + (signed short)address;
            }
            else if(inst == "BEQ"){
                if(P & Z)
                    PC = PC + (signed short)address;
            }
            else if(inst == "BIT"){
                M = bus->getCPUMem(address) & A;
                ZF(M == 0);
                NF(M & N);
                VF(M & V);
            }
            else if(inst == "BMI"){
                if(P & N)
                    PC = PC + (signed short)address;
            }
            else if(inst == "BNE"){
                if(!(P & Z))
                    PC = PC + (signed short)address;
            }
            else if(inst == "BPL"){
                if(!(P & N))
                    PC = PC + (signed short)address;
            }
            else if(inst == "BRK"){
                P = P | B;
            }
            else if(inst == "BVC"){
                if(!(P & V))
                    PC = PC + (signed short)address;
            }
            else if(inst == "BVS"){
                if(P & V)
                    PC = PC + (signed short)address;
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
                VF(false);
            }
            else if(inst == "CMP"){
                M = bus->getCPUMem(address);
                CF(A >= M);
                ZF(A == M);
            }
            else if(inst == "CPX"){
                M = bus->getCPUMem(address);
                CF(X >= M);
                ZF(X == M);
            }
            else if(inst == "CPY"){
                M = bus->getCPUMem(address);
                CF(Y >= M);
                ZF(Y == M);
            }
            else if(inst == "DEC"){
                M = bus->getCPUMem(address);
                bus->storeCPUMem(M - 1, address);
            }
            else if(inst == "DEX"){
                X--;
            }
            else if(inst == "DEY"){
                Y--;
            }
            else if(inst == "EOR"){
                A = A ^ bus->getCPUMem(address);
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "INC"){
                M = bus->getCPUMem(address);
                bus->storeCPUMem(M + 1, address);
            }
            else if(inst == "INX"){
                X++;
            }
            else if(inst == "INY"){
                Y++;
            }
            else if(inst == "JMP"){
                PC = address;
            }
            else if(inst == "JSR"){
                PC = address - 1;
            }
            else if(inst == "LDA"){
                A = bus->getCPUMem(address);
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "LDX"){
                X = bus->getCPUMem(address);
                ZF(X == 0);
                NF(X & N);
            }
            else if(inst == "LDY"){
                Y = bus->getCPUMem(address);
                ZF(Y == 0);
                NF(Y & N);
            }
            else if(inst == "LSR"){
                if(acc){
                    CF(A & C);
                    A = A >> 1;
                    ZF(A == 0);
                    NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & C);
                    M = M >> 1;
                    bus->storeCPUMem(address, M);
                    ZF(M == 0);
                    NF(M & N);
                }
            }
            else if(inst == "NOP");
            else if(inst == "ORA"){
                M = bus->getCPUMem(address);
                A = A | M;
            }
            else if(inst == "PHA"){
                S = A - 1;
            }
            else if(inst == "PHP"){
                S = P - 1;
            }
            else if(inst == "PLA"){
                A = S;
                S--;
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "PLP"){
                P = S;
                S--;
            }
            else if(inst == "ROL"){
                bool ctmp = P & C;
                if(acc){
                    CF(A & C);
                    A = (A << 1) | ctmp;
                    ZF(A == 0);
                    NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & C);
                    M = (M << 1) | ctmp;
                    bus->storeCPUMem(address, M);
                    ZF(M == 0);
                    NF(M & N);
                }
            }
            else if(inst == "ROR"){
                bool ctmp = P & C;
                if(acc){
                    CF(A & C);
                    A = (A >> 1) | (A << 7);
                    ZF(A == 0);
                    NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & C);
                    M = (M >> 1) | (ctmp << 7);
                    bus->storeCPUMem(address, M);
                    ZF(M == 0);
                    NF(M & N);
                }
            }
            else if(inst == "RTI"){
                //add later
            }
            else if(inst == "RTS"){
                PC = S - 1;
            }
            else if(inst == "SBC"){
                //add later
            }
            else if(inst == "SEC"){
                P = P & C;
            }
            else if(inst == "STA"){
                bus->storeCPUMem(A, address);
            }
            else if(inst == "STX"){
                bus->storeCPUMem(X, address);
            }
            else if(inst == "STY"){
                bus->storeCPUMem(Y, address);
            }
            else if(inst == "TAX"){
                X = A;
                ZF(X == 0);
                NF(X & N);
            }
            else if(inst == "TAY"){
                Y = A;
                ZF(Y == 0);
                NF(Y & N);
            }
            else if(inst == "TSX"){
                X = S;
                ZF(X == 0);
                NF(X & N);
            }
            else if(inst == "TXA"){
                A = X;
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "TXS"){
                S = X;
            }
            else if(inst == "TYA"){
                A = Y;
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "DOP");
            else if(inst == "TOP");

            //illegal opcodes (very few games use them, may add support later)
            else if(inst == "AAC");
            else if(inst == "AAX");
            else if(inst == "ARR");
            else if(inst == "ASR");
            else if(inst == "ATX");
            else if(inst == "AXA");
            else if(inst == "AXS");
            else if(inst == "DCP");
            else if(inst == "ISC");
            else if(inst == "KIL");
            else if(inst == "LAR");
            else if(inst == "LAX");
            else if(inst == "RLA");
            else if(inst == "RRA");
            else if(inst == "SLO");
            else if(inst == "SRE");
            else if(inst == "SXA");
            else if(inst == "SYA");
            else if(inst == "XAA");
            else if(inst == "XAS");
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
        void ZF(bool in){
            if(in)
                P = P | Z;
            else
                P = P & ~Z;
        }

        //sets negative flag (gonna be doing this a lot)
        void NF(bool in){
            if(in)
                P = P | N;
            else
                P = P & ~N;
        }

        //sets overflow flag (gonna be doing this a lot)
        void VF(bool in){
            if(in)
                P = P | V;
            else
                P = P & ~V;
        }
};

