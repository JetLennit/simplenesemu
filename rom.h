/*
Handles the game ROM
*/

class ROM {
    //http://wiki.nesdev.com/w/index.php/INES
    public:
        //we can worry about iNES2 later, most roms don't require the specific features and it's backwards compatibile with iNES
        //see http://wiki.nesdev.com/w/index.php/NES_2.0
        bool isines2;
        bool hasTrainer;
        int prglen;
        int chrlen;
        unsigned char mapper;
        unsigned char *header;
        unsigned char *trainer;
        unsigned char *prg;
        unsigned char *chr;
};

ROM readROM(std::string romname){
    ROM rom;

    //open rom file (not using the std namespace because you hate me)
    std::ifstream romf;

    romf.open(romname.c_str(), std::ios::in|std::ios::binary);

    romf.seekg(0, std::ios::beg);

    //read header
    rom.header = (unsigned char*)calloc(1, 16);
    romf.read((char*)rom.header,16);
    
    //check for trainer and ines2.0
    rom.hasTrainer = (rom.header[6]&4) != 0 ? true : false; 
    rom.isines2 = (rom.header[7]&0x0C) == 8 ? true : false;

    rom.mapper = ((rom.header[6] & 0b11110000) >> 4) | (rom.header[7] & 0b11110000);

    //if there is a trainer read and go past that (for the most part we don't need to worry about the trainer)
    //http://wiki.nesdev.com/w/index.php/INES#Trainer
    if(rom.hasTrainer){
        rom.trainer = (unsigned char*)calloc(1, 512);
        romf.read((char*)rom.trainer, 512);
    }

    //read prg rom
    rom.prglen = 16384*(rom.header[4]);
    rom.prg = (unsigned char*)calloc(1, rom.prglen);
    romf.read((char*)rom.prg, rom.prglen);

    //read chr rom
    rom.chrlen = 8192*(rom.header[5]);
    rom.chr = (unsigned char*)calloc(1, rom.chrlen);
    romf.read((char*)rom.chr, rom.chrlen);

    romf.close();

    return rom;
}