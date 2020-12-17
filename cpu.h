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
        unsigned char P;

        //http://wiki.nesdev.com/w/index.php/Status_flags
        unsigned char C = 0b00000001;
        unsigned char Z = 0b00000010;
        unsigned char I = 0b00000100;
        unsigned char B = 0b00110000;
        unsigned char V = 0b01000000;
        unsigned char N = 0b10000000;
        
        void init(std::string rom){
            A = 0;
            X = 0;
            Y = 0;
            for(int i = 0; i < (sizeof(bus->cpu_memory)/sizeof(bus->cpu_memory[0])); i++)
                bus->cpu_memory[i] = 0;
                
            bus->loadROM(rom);
            PC = bus->getCPUMem(0xFFFC) + (bus->getCPUMem(0xFFFD)*256);
            pushS(0xFD);
            P = 0x34;
        }


        std::string step(){
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
                std::cout << "Instruction is " << currop.instruction << " " << std::hex << (int)currop.opcode << std::dec << std::endl;
                std::cout << "X is " << (int)X << std::endl;
                std::cout << "Y is " << (int)Y << std::endl;
                std::cout << "A is " << (int)A << std::endl;
                std::cout << "PC is " << (int)PC-0x8000 << std::endl;
            
                unsigned short arg = 0;

                if(currop.bytes == 2)
                    arg = bus->getCPUMem(PC + 1);
                else if(currop.bytes == 3)
                    arg = bus->getCPUMem(PC + 1) + (bus->getCPUMem(PC + 2)*256);

                std::cout << "Arg is " << (int)arg << std::endl;

                runOpcode(currop, arg);

                return currop.instruction;
            }
            return "rip";
        }

        void runOpcode(OPCODE op, unsigned short arg){
            //for instructions that interact with memory
            unsigned char M = 0;

            bool acc = false;
            bool imm = false;
            unsigned short address = 0;
            
            if(op.addressmode == 0x8)
                imm = true;

            if(op.addressmode == 0x7)
                acc = true;
            else
                address = getAddress(arg, op.addressmode);

            std::string inst = op.instruction;
            if(inst == "ADC"){
                //add later
            }
            else if(inst == "AND"){
                if(imm)
                    A = A & address;
                else
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
                    PC = PC + (signed char)address;
            }
            else if(inst == "BCS"){
                if(P & C)
                    PC = PC + (signed char)address;
            }
            else if(inst == "BEQ"){
                if(P & Z)
                    PC = PC + (signed char)address;
            }
            else if(inst == "BIT"){
                M = bus->getCPUMem(address) & A;
                ZF(M == 0);
                NF(M & N);
                VF(M & V);
            }
            else if(inst == "BMI"){
                if(P & N)
                    PC = PC + (signed char)address;
            }
            else if(inst == "BNE"){
                if(!(P & Z))
                    PC = PC + (signed char)address;
            }
            else if(inst == "BPL"){
                if(!(P & N))
                    PC = PC + (signed char)address;
            }
            else if(inst == "BRK"){
                pushS((unsigned char)(PC>>4));
                pushS((unsigned char)PC);
                pushS(P);
                P = P | B;
            }
            else if(inst == "BVC"){
                if(!(P & V))
                    PC = PC + (signed char)address;
            }
            else if(inst == "BVS"){
                if(P & V)
                    PC = PC + (signed char)address;
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
                if(imm)
                    M = address;
                else
                    M = bus->getCPUMem(address);
                CF(A >= M);
                ZF(A == M);
            }
            else if(inst == "CPX"){
                if(imm)
                    M = address;
                else
                    M = bus->getCPUMem(address);
                CF(X >= M);
                ZF(X == M);
            }
            else if(inst == "CPY"){
                if(imm)
                    M = address;
                else
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
                if(imm)
                    A = A ^ address;
                else
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
                pushS((unsigned char)(PC>>4));
                pushS((unsigned char)PC-1);
                PC = address;
            }
            else if(inst == "LDA"){
                if(imm)
                    A = address;
                else
                    A = bus->getCPUMem(address);
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "LDX"){
                if(imm)
                    X = address;
                else
                    X = bus->getCPUMem(address);
                ZF(X == 0);
                NF(X & N);
            }
            else if(inst == "LDY"){
                if(imm)
                    Y = address;
                else
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
                if(imm)
                    M = address;
                else
                    M = bus->getCPUMem(address);
                A = A | M;
            }
            else if(inst == "PHA"){
                pushS(A);
            }
            else if(inst == "PHP"){
                pushS(P);
            }
            else if(inst == "PLA"){
                A = pullS();
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "PLP"){
                P = pullS();
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
                    A = (A >> 1) | (A << 8);
                    ZF(A == 0);
                    NF(A & N);
                }
                else{
                    M = bus->getCPUMem(address);
                    CF(M & C);
                    M = (M >> 1) | (ctmp << 8);
                    bus->storeCPUMem(address, M);
                    ZF(M == 0);
                    NF(M & N);
                }
            }
            else if(inst == "RTI"){
                P = pullS();
                M = pullS();
                PC = M + (pullS()*256);
            }
            else if(inst == "RTS"){
                M = pullS();
                PC = M + (pullS()*256);
            }
            else if(inst == "SBC"){
                //add later
            }
            else if(inst == "SEC"){
                P = P | C;
            }
            else if(inst == "SED"){
                //unused by nes
            }
            else if(inst == "SEI"){
                P = P | I;
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
                X = pullS();
                ZF(X == 0);
                NF(X & N);
            }
            else if(inst == "TXA"){
                A = X;
                ZF(A == 0);
                NF(A & N);
            }
            else if(inst == "TXS"){
                pushS(X);
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

            PC = PC + op.bytes;
        }

    private:
        unsigned short getAddress(unsigned short input, unsigned char mode){
            unsigned short tmp;
            switch(mode){
                case 0x0:
                    return (input + X) % 0xFF;
                    break;
                case 0x1:
                    return (input + Y) % 0xFF;
                    break;
                case 0x2:
                    return input + X;
                    break;
                case 0x3:
                    return input + Y;
                    break;
                case 0x4:
                    return (bus->getCPUMem(input) + X) % 0xFF;
                    break;
                case 0x5:
                    return bus->getCPUMem(input) + Y;
                    break;
                case 0x6:
                    return 0;
                    break;
                case 0x7:
                    return 0;
                    break;
                case 0x8:
                    return input;
                    break;
                case 0x9:
                    return input;
                    break;
                case 0xA:
                    return input;
                    break;
                case 0xB:
                    return input;
                    break;
                case 0xC:
                    tmp = bus->getCPUMem(input) + (bus->getCPUMem(input+1)*256);
                    return tmp;
                    break;
                case 0xD:
                    return 0;
                    break;
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
        
        //pushes to stack
        bool pushS(unsigned char in){
            if(bus->cpu_memory[0x0100]){
                std::cerr << "Stack overflow error" << std::endl;
                return false;
            }
            for(int i = 1; i < 0x100; i++){
                bus->storeCPUMem(0x100+i, bus->getCPUMem(0x100 + i + 1));
            }
            return bus->storeCPUMem(0x1FF, in);
        }
        
        //pulls from stack
        unsigned char pullS(){
            unsigned char ret = bus->getCPUMem(0x1FF);
            for(int i = 0xFF; i >= 0; i--){
                bus->storeCPUMem(0x100+i, bus->getCPUMem(0x100 + i - 1));
            }
            return ret;
        }
};

