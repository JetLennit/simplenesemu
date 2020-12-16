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
            unsigned char M = 0;

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
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "ASL"){
                if(acc){
                    CF(A & 0b10000000);
                    A = A << 1;
                ZF(A == 0);
                NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & 0b00000001);
                    M = M << 1;
                    bus->storeCPUMem(address, M);
                    ZF(M == 0);
                    NF(M & N);
                }
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
                M = bus->getCPUMem(address) & A;
                ZF(M == 0);
                NF(M & N);
                VF(M & V);
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
                //add later
            }
            else if(inst == "JSR"){
                //add later
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
                    CF(A & 0b00000001);
                    A = A >> 1;
                    ZF(A == 0);
                    NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & 0b00000001);
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
                //add later
            }
            else if(inst == "PHP"){
                //add later
            }
            else if(inst == "PLA"){
                //add later
            }
            else if(inst == "PLP"){
                //add later
            }
            else if(inst == "ROL"){
                bool ctmp = P & C;
                if(acc){
                    CF(A & 0b10000000);
                    A = (A << 1) | ctmp;
                    ZF(A == 0);
                    NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & 0b10000000);
                    M = (M << 1) | ctmp;
                    bus->storeCPUMem(address, M);
                    ZF(M == 0);
                    NF(M & N);
                }
            }
            else if(inst == "ROR"){
                bool ctmp = P & C;
                if(acc){
                    CF(A & 0b00000001);
                    A = (A >> 1) | (A << 7);
                    ZF(A == 0);
                    NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & 0b00000001);
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
                //add later
            }
            else if(inst == "SBC"){
                CF(true);
            }
            else if(inst == "SEC"){
                //unused on the nes
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

