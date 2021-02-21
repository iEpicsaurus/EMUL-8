#ifndef EMU_CORE_H
#define EMU_CORE_H

#include <cstdint>
#include <string>

#include "controller/EmuController.h"
#include "cpu/EmuCPU.h"
#include "gpu/EmuGPU.h"
#include "memory/EmuMemory.h"
#include "timer/EmuTimer.h"

/**
 * @brief Core class integrating all other hardware classes
 * 
 * This class is the core of the CHIP-8 emulator, which integrates the 
 * CPU, GPU, timer, and the controller classes
 *
 * @author Aleksandar Kostic
 * @author Sean Maas
 * 
 */
class EmuCore
{
    public:
        EmuCore(std::string filename):
            cpu(&controller, &gpu, &memory, &delayTimer),
            memory(filename) {}
        ~EmuCore() {} ///< Do nothing

        void runFrame();
        uint8_t getPixel(int x, int y);
        void pressKey(int key);
        void releaseKey(int key);

    private:
        EmuController controller;
        EmuCPU cpu;
        EmuGPU gpu;
        EmuMemory memory;
        EmuTimer delayTimer;
};

#endif // EMU_CORE_H
