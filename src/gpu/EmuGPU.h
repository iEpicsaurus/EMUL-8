#ifndef EMU_GPU_H
#define EMU_GPU_H

#include <cstdint>

/**
 * @brief Implements the GPU of the CHIP-8 emulator
 * 
 * Implementation of the GPU class which deals drawing and reading the 
 * pixels and clearing the screen.
 *
 * @author Aleksandar Kostic
 * @author Sean Maas
 *
 */
class EmuGPU {
    
    public:
		bool drawPixel(int x, int y);
		void clear();
		uint8_t getPixel(int x, int y);
		
    private:
		uint8_t display[64 * 32] = {};
    
};

#endif // EMU_GPU_H

