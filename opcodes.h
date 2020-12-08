/*
Stores all the opcodes for the 6502 (hopefully)

TODO:
*/

class OPCODE
{
    public:
        unsigned char opcode;
        std::string instruction;
        unsigned char bytes;
};

//http://obelisk.me.uk/6502/reference.html
//http://nesdev.com/undocumented_opcodes.txt
OPCODE opcode[256] ={
    {0x69, "ADC", 2}, 
    {0x65, "ADC", 2}, 
    {0x75, "ADC", 2}, 
    {0x6D, "ADC", 3}, 
    {0x7D, "ADC", 3}, 
    {0x79, "ADC", 3}, 
    {0x61, "ADC", 2}, 
    {0x71, "ADC", 2}, 

    {0x29, "AND", 2}, 
    {0x25, "AND", 2}, 
    {0x35, "AND", 2}, 
    {0x2D, "AND", 3}, 
    {0x3D, "AND", 3}, 
    {0x39, "AND", 3}, 
    {0x21, "AND", 2}, 
    {0x31, "AND", 2}, 

    {0x0A, "ASL", 1}, 
    {0x06, "ASL", 2}, 
    {0x16, "ASL", 2},
    {0x0E, "ASL", 3},
    {0x1E, "ASL", 3},

    {0x90, "BCC", 2},

    {0xB0, "BCS", 2},

    {0xF0, "BEQ", 2},

    {0x24, "BIT", 2},
    {0x2C, "BIT", 3},

    {0x30, "BMI", 2},

    {0xD0, "BNE", 2},

    {0x10, "BPL", 2},

    {0x00, "BRK", 1},

    {0x50, "BVC", 2},

    {0x70, "BVS", 2},

    {0x18, "CLC", 1},

    {0xD8, "CLD", 1},

    {0x58, "CLI", 1},

    {0xB8, "CLV", 1},

    {0xC9, "CMP", 2},
    {0xC5, "CMP", 2},
    {0xD5, "CMP", 2},
    {0xCD, "CMP", 3},
    {0xDD, "CMP", 3},
    {0xD9, "CMP", 3},
    {0xC1, "CMP", 2},
    {0xD1, "CMP", 2},

    {0xE0, "CPX", 2},
    {0xE4, "CPX", 2},
    {0xEC, "CPX", 3},

    {0xC0, "CPY", 2},
    {0xC4, "CPY", 2},
    {0xCC, "CPY", 3},

    {0xC6, "DEC", 2},
    {0xD6, "DEC", 2},
    {0xCE, "DEC", 3},
    {0xDE, "DEC", 3},

    {0xCA, "DEX", 1},

    {0x88, "DEY", 1},

    {0x49, "EOR", 2},
    {0x45, "EOR", 2},
    {0x55, "EOR", 2},
    {0x4D, "EOR", 3},
    {0x5D, "EOR", 3},
    {0x59, "EOR", 3},
    {0x41, "EOR", 2},
    {0x51, "EOR", 2},

    {0xE6, "INC", 2},
    {0xF6, "INC", 2},
    {0xEE, "INC", 3},
    {0xFE, "INC", 3},

    {0xE8, "INX", 1},

    {0xC8, "INY", 1},

    {0x4C, "JMP", 3},
    {0x6C, "JMP", 3},

    {0x20, "JSR", 3},

    {0xA9, "LDA", 2},
    {0xA5, "LDA", 2},
    {0xB5, "LDA", 2},
    {0xAD, "LDA", 3},
    {0xBD, "LDA", 3},
    {0xB9, "LDA", 3},
    {0xA1, "LDA", 2},
    {0xB1, "LDA", 2},

    {0xA2, "LDX", 2},
    {0xA6, "LDX", 2},
    {0xB6, "LDX", 2},
    {0xAE, "LDX", 3},
    {0xBE, "LDX", 3},

    {0xA0, "LDY", 2},
    {0xA4, "LDY", 2},
    {0xB4, "LDY", 2},
    {0xAC, "LDY", 3},
    {0xBC, "LDY", 3},

    {0x4A, "LSR", 1}, 
    {0x46, "LSR", 2}, 
    {0x56, "LSR", 2},
    {0x4E, "LSR", 3},
    {0x5E, "LSR", 3},

    {0xEA, "NOP",1 },

    {0x09, "ORA", 2},
    {0x05, "ORA", 2},
    {0x15, "ORA", 2},
    {0x0D, "ORA", 3},
    {0x1D, "ORA", 3},
    {0x19, "ORA", 3},
    {0x01, "ORA", 2},
    {0x11, "ORA", 2},

    {0x48, "PHA", 1},

    {0x08, "PHP", 1},

    {0x68, "PLA", 1},

    {0x28, "PLP", 1},

    {0x2A, "ROL", 1},
    {0x26, "ROL", 2},
    {0x36, "ROL", 2},
    {0x2E, "ROL", 3},
    {0x3E, "ROL", 3},

    {0x6A, "ROR", 1},
    {0x66, "ROR", 2},
    {0x76, "ROR", 2},
    {0x6E, "ROR", 3},
    {0x7E, "ROR", 3},

    {0x40, "RTI", 1},

    {0x60, "RTS", 1},

    {0xE9, "SBC", 2},
    {0xE5, "SBC", 2},
    {0xF5, "SBC", 2},
    {0xED, "SBC", 3},
    {0xFD, "SBC", 3},
    {0xF9, "SBC", 3},
    {0xE1, "SBC", 2},
    {0xF1, "SBC", 2},

    {0x38, "SEC", 1},

    {0xF8, "SED", 1},

    {0x78, "SEI", 1},

    {0x85, "STA", 2},
    {0x95, "STA", 2},
    {0x8D, "STA", 3},
    {0x9D, "STA", 3},
    {0x99, "STA", 3},
    {0x81, "STA", 2},
    {0x91, "STA", 2},

    {0x8E, "STX", 2},
    {0x96, "STX", 3},
    {0x86, "STX", 3},

    {0x84, "STY", 2},
    {0x94, "STY", 3},
    {0x8C, "STY", 3},

    {0xAA, "TAX", 1},
    
    {0xA8, "TAY", 1},

    {0xBA, "TSX", 1},

    {0x8A, "TXA", 1},

    {0x9A, "TXS", 1},

    {0x98, "TXY", 1},

    //undocumented opcodes (real peeved these exist)
    {0x0B, "AAC", 2},
    {0x2B, "AAC", 2},

    {0x87, "AAX", 2},
    {0x97, "AAX", 2},
    {0x83, "AAX", 2},
    {0x8F, "AAX", 3},

    {0x6B, "AAR", 2},

    {0x4B, "ASR", 2},

    {0xAB, "ATX", 2},

    {0x9F, "AXA", 3},
    {0x93, "AXA", 2},

    {0xCB, "AXS", 2}, 

    {0xC7, "DCP", 2},
    {0xD7, "DCP", 2},
    {0xCF, "DCP", 3},
    {0xDF, "DCP", 3},
    {0xDB, "DCP", 3},
    {0xC3, "DCP", 2},
    {0xD3, "DCP", 2},

    {0x04, "DOP", 2},
    {0x14, "DOP", 2},
    {0x34, "DOP", 2},
    {0x44, "DOP", 2},
    {0x54, "DOP", 2},
    {0x64, "DOP", 2},
    {0x74, "DOP", 2},
    {0x80, "DOP", 2},
    {0x82, "DOP", 2},
    {0x89, "DOP", 2},
    {0xC2, "DOP", 2},
    {0xD4, "DOP", 2},
    {0xE2, "DOP", 2},
    {0xF4, "DOP", 2},

    {0xE7, "ISC", 2},
    {0xF7, "ISC", 2},
    {0xEF, "ISC", 3},
    {0xFF, "ISC", 3},
    {0xFB, "ISC", 3},
    {0xE3, "ISC", 2},
    {0xF3, "ISC", 2},

    {0x02, "KIL", 1},
    {0x12, "KIL", 1},
    {0x22, "KIL", 1},
    {0x32, "KIL", 1},
    {0x42, "KIL", 1},
    {0x52, "KIL", 1},
    {0x62, "KIL", 1},
    {0x72, "KIL", 1},
    {0x92, "KIL", 1},
    {0xB2, "KIL", 1},
    {0xD2, "KIL", 1},
    {0xF2, "KIL", 1},

    {0xBB, "LAR", 3},

    {0xA7, "LAX", 2},
    {0xB7, "LAX", 2},
    {0xAF, "LAX", 3},
    {0xBF, "LAX", 3},
    {0xA3, "LAX", 2},
    {0xB3, "LAX", 2},

    {0x1A, "NOP", 1},
    {0x3A, "NOP", 1},
    {0x5A, "NOP", 1},
    {0x7A, "NOP", 1},
    {0xDA, "NOP", 1},
    {0xFA, "NOP", 1},

    {0x27, "RLA", 2},
    {0x37, "RLA", 2},
    {0x2F, "RLA", 3},
    {0x3F, "RLA", 3},
    {0x3B, "RLA", 3},
    {0x23, "RLA", 2},
    {0x33, "RLA", 2},

    {0x67, "RRA", 2},
    {0x77, "RRA", 2},
    {0x6F, "RRA", 3},
    {0x7F, "RRA", 3},
    {0x7B, "RRA", 3},
    {0x63, "RRA", 2},
    {0x73, "RRA", 2},

    {0xEB, "SBC", 2},

    {0x07, "SLO", 2},
    {0x17, "SLO", 2},
    {0x0F, "SLO", 3},
    {0x1F, "SLO", 3},
    {0x1B, "SLO", 3},
    {0x03, "SLO", 2},
    {0x13, "SLO", 2},

    {0x47, "SRE", 2},
    {0x57, "SRE", 2},
    {0x4F, "SRE", 3},
    {0x5F, "SRE", 3},
    {0x5B, "SRE", 3},
    {0x43, "SRE", 2},
    {0x53, "SRE", 2},

    {0x9E, "SXA", 3},

    {0x9C, "SYA", 3},

    {0x0C, "TOP", 3},
    {0x1C, "TOP", 3},
    {0x3C, "TOP", 3},
    {0x5C, "TOP", 3},
    {0x7C, "TOP", 3},
    {0xDC, "TOP", 3},
    {0xFC, "TOP", 3},

    {0x8B, "XAA", 2},

    {0x9B, "XAS", 3},
};
//{0x, "", },

