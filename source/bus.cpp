#include "bus.h"
#include "ppu.h"
#include <iostream>

void Bus::dumpRAM(){
	std::cout << std::endl;
	for(int i = 0; i < 0x800; i++)
		if(ram[i])
			std::cout << "$" << std::hex << i << std::dec << ": " << std::hex << (int)ram[i] << std::dec << std::endl;
}

//here's where the rom is mapped to memory, it's also where we'll need to do a lot of work later to make other games work
bool Bus::loadROM(std::string romname){
	rom = readROM(romname);
	if(rom.mapper == 0){
		//this assumes the specific rom of smb, i'll fix it later to include other nrom games
		//load cartridge prg-rom into cpu memory
		if(rom.prglen == 32768){
			for(int i = 0; i < rom.prglen; i++) 
				cpu_memory[0x8000 + i] = rom.prg[i];
		}
		else if(rom.prglen == 16384){
			for(int i = 0; i < rom.prglen; i++){
				cpu_memory[0x8000 + i] = rom.prg[i];
				cpu_memory[0x8000 + i + 16384] = rom.prg[i];
			}
		}
		
		//load cartridge chr-rom into ppu memory
		for(int i = 0; i < rom.chrlen; i++)
			pattern_table[i] = rom.chr[i];

		return true;
	}
	else{
		std::cerr << "Mapper not recognized, stick to NROM until we have more implemented" << std::endl;
		return false;
	}
}

bool Bus::storeCPUMem(unsigned short location, unsigned char stored){
	//make sure that location is within memory
	if(location > 0xFFFF){
		std::cerr << "Trying to access memory out of range" << std::endl;
		return false;
	}
	if(location < 0x2000) 
		ram[location % 0x800] = stored;
	else if(location < 0x4000) 
		return ppu->storePPUReg(location % 0x8, stored);
	else if(location == 0x4014)
		return ppu->OAMDMA(stored);
	else 
		cpu_memory[location] = stored;

	return true;
}

unsigned char Bus::getCPUMem(unsigned short location){
	//make sure that location is within memory
	if(location > 0xFFFF){
		std::cerr << "Trying to access memory out of range" << std::endl;
		//return kil instruction, can't think of a better way to give error
		return 0x22;
	}

	if(location < 0x2000) 
		return ram[location % 0x800];
	else if(location < 0x4000)
		return ppu->getPPUReg(location % 0x8);
	else 
		return cpu_memory[location];

	return 0x22;
}   