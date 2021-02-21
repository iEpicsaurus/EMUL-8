#include "EmuCore.h"

/**
 * Core process the emulator runs, basically the CPU 
 * cycles and the timer. 
 */
void EmuCore::runFrame()
{
    /// Run the CPU and timers
    cpu.runCycle();
    delayTimer.tick();
}

/**
 * GPU process, outputs the graphics
 * 
 * @param x is an integer representing the x coordinate
 * @param y is an integer representing the y coordinate
 * @return an unsigned char representing the pixel
 */
uint8_t EmuCore::getPixel(int x, int y)
{
    /// Read a pixel from the GPU
    return gpu.getPixel(x, y);
}

/**
 * Gets key states and pass information to the system if key(s) is 
 * pressed
 * 
 * @param key is an integer representing a key that is pressed
 */
void EmuCore::pressKey(int key)
{
    /// Pass a key press to the controller
    controller.pressKey(key);
}

/**
 * Gets key states and pass information to the system if key(s) is 
 * not pressed
 * 
 * @param key is an integer representing a key that is released
 */
void EmuCore::releaseKey(int key)
{
    /// Pass a key release to the controller
    controller.releaseKey(key);
}
