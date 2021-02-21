#include <thread>
#include <chrono>

#include "EmuTimer.h"

using namespace std;

/**
 * Simulates one cycle of the CPU and waits
 *
 * @author Sean Aspinall
 * @author Sean Maas
 *
 */
void EmuTimer::tick()
{
    if (value != 0) value--;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}

/**
 * Returns the remaining cycles left the current run of the CPU
 * 
 * @return The remaining cycles in the current run
 */
int EmuTimer::getTime()
{
    return value;
}

/**
 * Updates the current number of cycles in the current run
 */
void EmuTimer::setTime(int newValue)
{
    value = newValue;
}
