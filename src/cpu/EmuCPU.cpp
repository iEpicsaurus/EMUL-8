#include <cstdio>
#include <cstdlib>
#include <sstream>

#include "EmuCPU.h"
#include "../controller/EmuController.h"
#include "../gpu/EmuGPU.h"
#include "../logger/Logger.h"
#include "../memory/EmuMemory.h"
#include "../timer/EmuTimer.h"

void EmuCPU::runCycle()
{
    /// Read the 16-bit opcode from memory
    opcode = (memory->read(programCounter) << 8) | memory->read(programCounter + 1);

    /// Log debug information
    std::stringstream stream;
    stream << "Opcode 0x" << std::hex << opcode << " at address 0x" << std::hex << programCounter;
    Logger::getInstance() << stream.str();

    /// Decode the opcode
    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode)
            {
                case 0x00E0: clearScreen(); return;
                case 0x00EE: subroutineReturn(); return;
            }
            break;

        case 0x1000: jump(); return;
        case 0x2000: callRoutine(); return;
        case 0x3000: skipequal(); return;
        case 0x4000: skipnotequal(); return;
        case 0x5000: skipxequaly(); return;
        case 0x6000: setRV(); return;
        case 0x7000: addRV(); return;

        case 0x8000:
            switch (opcode & 0x000F)
            {
                case 0x0000: setVx(); return;
                case 0x0001: orVx(); return;
                case 0x0002: andVx(); return;
                case 0x0003: exor(); return;
                case 0x0004: pluscarry(); return;
                case 0x0005: subyandx(); return;
                case 0x0006: shiftXRightStore(); return;
                case 0x0007: setMinus(); return;
                case 0x000E: shiftLeft1(); return;
            }
            break;

        case 0x9000: skipxnotequaly(); return;
        case 0xA000: setI(); return;
        case 0xB000: jumpPlus(); return;
        case 0xC000: random(); return;
        case 0xD000: drawSprite(); return;

        case 0xE000:
            switch (opcode & 0x00FF)
            {
                case 0x009E: skipPress(); return;
                case 0x00A1: skipRelease(); return;
            }
            break;

        case 0xF000:
            switch (opcode & 0x00FF)
            {
                case 0x0007: readDelayTimer(); return;
                case 0x000A: keyWait(); return;
                case 0x0015: setDelayTimer(); return;
                case 0x0018: setSoundTimer(); return;
                case 0x001E: addVI(); return;
                case 0x0029: spriteLoc(); return;
                case 0x0033: bcd(); return;
                case 0x0055: store(); return;
                case 0x0065: fill(); return;
            }
            break;
    }

    /// If the program reaches here, it tried to run an unknown opcode
    printf("Unknown opcode: 0x%X\n", opcode);
    exit(1);
}

void EmuCPU::clearScreen()
{
    /// 00E0: Clear the screen
    gpu->clear();

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::subroutineReturn() {
    if (stack.size() > 0)
    {
        programCounter = stack.top() + 2;
        stack.pop();
    }
}

void EmuCPU::callRoutine() {
    if (stack.size() < 16)
    {
        stack.push(programCounter);
        programCounter = opcode & 0x0FFF;
    }
}

void EmuCPU::jump()
{
    /// 1NNN: Jump to address NNN
    programCounter = opcode & 0x0FFF;
}

void EmuCPU::setI()
{
    /// ANNN: Set I to NNN
    registerI = opcode & 0x0FFF;

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::jumpPlus()
{
    /// BNNN: Jump to address NNN plus V0
    programCounter = (opcode & 0x0FFF) + registerV[0];
}

void EmuCPU::random()
{
    /// CXNN: Set VX to the result of a random number and NN
    registerV[(opcode & 0x0F00) >> 8] = rand() & (opcode & 0x00FF);

    /// Move to the next opcode
    programCounter += 2;
}

/// Skip the next instruction if vx equal NN
void EmuCPU::skipequal()
{
    if(registerV[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
    {
    programCounter +=2;
    }
    programCounter +=2;    
}

/// Skip the next instruction if vx not equal to NN
void EmuCPU::skipnotequal()
{
    if(registerV[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
    {
    programCounter +=2;
    }
    programCounter +=2; 
}

/// Skip the next instruction if vx equals vy
void EmuCPU::skipxequaly()
{
    if(registerV[(opcode & 0x0F00) >> 8] == registerV[(opcode & 0x00f0) >> 4])
    {
        programCounter += 2;
    }
    programCounter +=2;
    
}

/// Skip the next instruction if vx doesn't equal vy
void EmuCPU::skipxnotequaly()
{
    if(registerV[(opcode & 0x0F00) >> 8] != registerV[(opcode & 0x00f0) >> 4])
    {
        programCounter += 2;
    }
    programCounter +=2;
    
}

/// Set VX to NN
void EmuCPU::setRV()
{
    registerV[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
    programCounter += 2;
    
}

/// Add NN to VX without setting VF
void EmuCPU::addRV()
{
    registerV[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
    programCounter += 2;
}

void EmuCPU::drawSprite()
{
    int x = registerV[(opcode & 0x0F00) >> 8];
    int y = registerV[(opcode & 0x00F0) >> 4];
    int h = (opcode & 0x000F);

    /// DXYN: Draw a sprite with a width of 8 pixels and a height of N pixels at VX,VY
	int yline, xline;
	for (yline = 0; yline < h; yline++)
    {
        uint8_t pixels = memory->read(registerI + yline);
		for (xline = 0; xline < 8; xline++)
		{
			if ((pixels & (0x80 >> xline)) != 0)
            {
                bool collision = gpu->drawPixel(x + xline, y + yline);
                registerV[15] = !collision;
			}
		}
	}

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::skipPress()
{
    /// EX9E: Skip the next opcode if the key specified by VX is pressed
    if (controller->getKey(registerV[(opcode & 0x0F00) >> 8]) == true)
        programCounter += 2;

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::skipRelease()
{
    /// EXA1: Skip the next opcode if the key specified by VX is not pressed
    if (controller->getKey(registerV[(opcode & 0x0F00) >> 8]) == false)
        programCounter += 2;

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::readDelayTimer()
{
    /// FX07: Set VX to the value of the delay timer
    registerV[(opcode & 0x0F00) >> 8] = delayTimer->getTime();

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::keyWait()
{
    /// FX0A: Wait until a key is pressed and store it in VX
    for (int i = 0; i < 16; i++)
    {
        if (controller->getKey(i) == true)
        {
            registerV[(opcode & 0x0F00) >> 8] = i;
            programCounter += 2;
            break;
        }
    }
}

void EmuCPU::setDelayTimer()
{
    /// FX15: Set the value of the delay timer to VX
    delayTimer->setTime(registerV[(opcode & 0x0F00) >> 8]);

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::setSoundTimer()
{
    /// FX18: Set the value of the sound timer to VX
    ///soundTimer->setTime(registerV[(opcode & 0x0F00) >> 8]);

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::addVI()
{
    /// FX1E: Add VX to I
    registerI += registerV[(opcode & 0x0F00) >> 8];

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::spriteLoc()
{
    /// FX29: Set I to the address of the sprite for the character in VX
    registerI = 0x050 + registerV[(opcode & 0x0F00) >> 8] * 5;

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::bcd()
{
    /// FX33: Store the BCD representation of VX at address I
    uint8_t number = registerV[(opcode & 0x0F00) >> 8];
    memory->write(registerI + 0, (number / 100));
    memory->write(registerI + 1, (number % 100) / 10);
    memory->write(registerI + 2, (number % 10));

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::store()
{
    /// FX55: Store V0 to VX in memory starting at I
    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++)
        memory->write(registerI + i, registerV[i]);

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::fill()
{
    /// FX65: Fill V0 to VX with memory starting at I
    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++)
        registerV[i] = memory->read(registerI + i);

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::setVx()
{
    uint8_t *RegX = &(registerV[(opcode & 0x0F00) >> 8]);
    uint8_t *RegY = &(registerV[(opcode & 0x00F0) >> 4]);
    *RegX = *RegY;

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::orVx()
{
    uint8_t *RegX = &(registerV[(opcode & 0x0F00) >> 8]);
    uint8_t *RegY = &(registerV[(opcode & 0x00F0) >> 4]);
    *RegX = *RegX | *RegY;

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::andVx()
{
    uint8_t *RegX = &(registerV[(opcode & 0x0F00) >> 8]);
    uint8_t *RegY = &(registerV[(opcode & 0x00F0) >> 4]);
    *RegX = *RegX & *RegY;

    /// Move to the next opcode
    programCounter += 2;
}

void EmuCPU::setMinus() {
    
    registerV[0xF] = (registerV[(opcode & 0x00F0) >> 4] >= registerV[(opcode & 0x0F00) >> 8]);
    registerV[(opcode & 0x0F00) >> 8] = registerV[(opcode & 0x00F0) >> 4] -
    registerV[(opcode & 0x0F00) >> 8];
    programCounter += 2;

}

void EmuCPU::shiftLeft1() {
    
    registerV[0xF] = registerV[(opcode & 0x0F00) >> 8] >> 7;
    registerV[(opcode & 0x0F00) >> 8] <<= 1;
    programCounter += 2;
    
}

void EmuCPU::subyandx()
{
  registerV[0xF] = (registerV[(opcode & 0x0F00) >> 8] >= registerV[(opcode & 0x00F0) >> 4]);

  registerV[(opcode & 0x0F00) >> 8] -= registerV[(opcode & 0x00F0) >> 4];

  programCounter +=2;
  
}

void EmuCPU::shiftXRightStore()
{
  registerV[0xF] = registerV[(opcode & 0x0F00) >> 8] & 0x01;
  registerV[(opcode & 0x0F00) >> 8] >>=1;
  programCounter +=2;
}

/// 8XY3-Sets VX to (VX XOR VY).
void EmuCPU::exor(){
    registerV[(opcode & 0x0F00) >> 8] ^= registerV[(opcode & 0x00F0) >> 4];//xor
    programCounter += 2;
}

/// 8XY4-dd VY to VX and set VF based on if there was a carry
void EmuCPU::pluscarry(){
    registerV[0xF] = (registerV[(opcode & 0x0F00) >> 8] + registerV[(opcode & 0x00F0) >> 4] > 0xFF);//boolean in bracket to decide 0 or 1(carry)
    registerV[(opcode & 0x0F00) >> 8] += registerV[(opcode & 0x00F0) >> 4];
    programCounter += 2;
}
