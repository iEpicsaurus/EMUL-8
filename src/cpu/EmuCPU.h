#ifndef EMU_CPU_H
#define EMU_CPU_H

#include <cstdint>
#include <stack>

/// Forward declarations to avoid conflicts
class EmuController;
class EmuGPU;
class EmuMemory;
class EmuTimer;

/** @brief Implements the CPU class to deal with opcodes
  *
  * This class interperets the CHIP-8 opcodes, allowing programs to be run in the emulator.
  * Opcodes are fetched from memory, decoded, and simulated using virtual registers.
  *
  * @author Sean Maas
  * @author Aleksandar Kostic
  * @author James Mitsumasu
  * @author Zhen Wang
  *
  */
class EmuCPU
{
    public:
        /// Create a CPU with access to a given controller, GPU, memory, and timer
        EmuCPU(EmuController *controller, EmuGPU *gpu, EmuMemory *memory, EmuTimer *delayTimer):
            controller(controller), gpu(gpu), memory(memory), delayTimer(delayTimer) {}

        ~EmuCPU() {} ///< Do nothing

        /** @brief Executes an opcode.
          *
          * This function runs a cycle of the CPU.
          * This involves fetching, decoding, and executing an opcode.
          */
        void runCycle();

    private:
        uint16_t programCounter = 0x200;
        uint16_t opcode = 0;
        uint8_t registerV[16] = {};
        uint16_t registerI = 0;

        std::stack<uint16_t> stack;

        EmuController *controller;
        EmuGPU *gpu;
        EmuMemory *memory;
        EmuTimer *delayTimer;

        /// Opcode 00E0: Clear the screen
        void clearScreen();

        /// Opcode 00EE: Return from subroutine
        void subroutineReturn();

        /// Opcode 2NNN: Call subroutine at address NNN
        void callRoutine();

        /// Opcode 1NNN: Jump to address NNN
        void jump();

        /// Opcode ANNN: Set I to NNN
        void setI();

        /// Opcode BNNN: Jump to address NNN plus V0
        void jumpPlus();

        /// Opcode CXNN: Set VX to a random number bitwise anded with NN
        void random();

        /// Opcode 3XNN: Skip an opcode if VX is equal to NN
        void skipequal();

        /// Opcode 4XNN: Skip an opcode if VX is not equal to NN
        void skipnotequal();

        /// Opcode 5XY0: Skip an opcode if VX is equal to VY
        void skipxequaly();

        /// Opcode 9XY0: Skip an opcode if VX is not equal to VY
        void skipxnotequaly();

        /// Opcode 6XNN: Set VX to NN
        void setRV();

        /// Opcode 7XNN: Add NN to VX
        void addRV();

        /// Opcode DXYN: Draw a sprite with a width of 8 and a height of N at VX,VY
        void drawSprite();

        /// Opcode EX9E: Skip an opcode if the key specified by VX is pressed
        void skipPress();

        /// Opcode EXA1: Skip an opcode if the key specified by VX is not pressed
        void skipRelease();

        /// Opcode FX07: Set VX to the value of the delay timer
        void readDelayTimer();

        /// Opcode FX0A: Wait until a key is pressed and store it in VX
        void keyWait();

        /// Opcode FX15: Set the value of the delay timer to VX
        void setDelayTimer();

        /// Opcode FX18: Set the value of the sound timer to VX
        void setSoundTimer();

        /// Opcode FX1E: Add VX to I
        void addVI();

        /// Opcode FX29: Set I to the address of the sprite for the character in VX
        void spriteLoc();

        /// Opcode FX33: Store the BCD representation of VX at address I
        void bcd();

        /// Opcode FX55: Store V0 to VX in memory starting at I
        void store();

        /// Opcode FX65: Fill V0 to VX with memory starting at I
        void fill();

        /// Opcode 8XY0: Set VX to the value of VY
        void setVx();

        /// Opcode 8XY1: Bitwise or VX with VY
        void orVx();

        /// Opcode 8XY2: Bitwise and VX with VY
        void andVx();

        /// Opcode 8XY7: Set VX to VY minus VX and set the carry flag in V15
        void setMinus();

        /// Opcode 8XY6: Shift VX left 1 and set the carry flag in V15
        void shiftLeft1();

        /// Opcode 8XY5: Subtract VY from VX and set the carry flag in V15
        void subyandx();

        /// Opcode 8XY6: Shift VX right 1 and set the carry flag in V15
        void shiftXRightStore();

        /// Opcode 8XY3: Bitwise exclusive or VX withz VY
        void exor();

        /// Opcode 8XY4: Add VY to VX and set the carry flag in V15
        void pluscarry();
};

#endif // EMU_CPU_H
