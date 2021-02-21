#include "EmuController.h"

/**
 * Sets the specific key passed into the function as a parameter as "1"
 * indicating the on state of the key.
 * 
 * @param key an integer representing the key
 */
void EmuController::pressKey(int key)
{	
	keys[key] = 1;
}

/**
 * Sets the specific key passed into the function as a parameter as "0"
 * indicating the off state of the key.
 * 
 * @param key an integer representing the key
 */
void EmuController::releaseKey(int key)
{
	keys[key] = 0;	
}

/**
 * Returns the state of the specified key passed as a parameter
 * 
 * @return state of the specified key
 */
bool EmuController::getKey(int key)
{	
    return keys[key];	
}

