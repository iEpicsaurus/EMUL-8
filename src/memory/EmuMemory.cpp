#include <cstring>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "EmuMemory.h"

/**
* The constructor for the memory class used for the loading of a ROM and initializing the memory.
*
* @param filename is a string representation of the ROM file name.
*/
EmuMemory::EmuMemory(std::string filename)
{
	memset(ram, 0, sizeof(ram));

    /// Load the ROM and store it in memory
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    file.read((char*)&ram[0x200], size);

    /// Load the CHIP-8 font data into memory
    std::vector<uint8_t> font =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    write_bytes(0x50, font);
}

/**
* Check if address used is in the specified memory range from 0 to 0xFFF - 1 if not an error is thrown
* showing that the address is out of bounds.
*
* @param addr is an unsigned short representing a memory address to be checked.
*/
void EmuMemory::mem_check(uint16_t addr)
{
	if(addr < 0 || addr >= 4096)
	{
	throw std::out_of_range("Address location is not in memory space");
	}
}

/**
* Reads a byte into memory and checks that the address is within range.
*
* @param addr is an unsigned short representing a memory address to be read into memory.
* @return an unsigned char (byte) back to the program.
*/
uint8_t EmuMemory::read(uint16_t addr)
{
	mem_check(addr);
	
	uint8_t byte = ram[addr];
	
	return byte;
}

/**
* Reads one or more bytes into memory all while checking that the bytes are within the memory bounds.
*
* @param addr is an unsigned short representing the start memory address for bytes to be read from memory.
* @param amount is an unsigned short representing the amount of bytes to be read into the memory.
* @return a vector that contains elements of the type unsigned char (a byte).
*/
std::vector<uint8_t> EmuMemory::read_bytes(uint16_t addr, uint16_t amount)
{	
	std::vector<uint8_t> list_bytes;
	
	for(int i = 0; i < amount; i++)
	{
		 list_bytes.push_back(read(addr + i));
	}
	
	return list_bytes;
}

/**
* Writes a byte into memory and check that the address specified is within bounds.
*
* @param addr is an unsigned short representing the starting memory address for a byte to be written to memory.
* @param data is an unsigned char representing a byte of information going into memory.
*/
void EmuMemory::write(uint16_t addr, uint8_t data)
{
	/// Check that there is enough space to write that one byte in RAM
	mem_check(addr);
	
	/// Place data into memory array at the next available space
	ram[addr] = data;
	
	return;
}

/**
* Writes more than one byte into memory and checks that the address is within bound as it writes.
*
* @param addr is an unsigned short representing the starting memory address for the bytes to be written to memory.
* @param data is a vector of the type unsigned char containing the bytes of information going into memory.
*/
void EmuMemory::write_bytes(uint16_t addr, std::vector<uint8_t> data)
{	
	for(int i = 0; i < data.size(); i++)
	{
		 write(addr + i, data[i]);
	}
}

