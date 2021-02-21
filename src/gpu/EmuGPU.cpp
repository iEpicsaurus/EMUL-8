#include "EmuGPU.h"
#include <cstring>

/**
 * Turns the specified pixel (x, y) on or off.
 * 
 * @param x representing the x coordinate of the pixel
 * @param y representing the y coordinate of the pixel
 * @returns bool indicating whether the pixel was turned on or off
 */
bool EmuGPU::drawPixel(int x, int y)
{	

    display[y * 64 + x] ^= 255;
    return display[y * 64 + x];	
}

/**
 * Clears the display
 */
void EmuGPU::clear()
{

    memset(display, 0, sizeof(display));	
}

/**
 * Reads a pixel, specified by (x, y), from the display
 * @param x representing the x coordinate of the pixel
 * @param y representing the y coordinate of the pixel
 * @return uint8_t representing a pixel
 */
uint8_t EmuGPU::getPixel(int x, int y)
{

    return display[y * 64 + x];
}
