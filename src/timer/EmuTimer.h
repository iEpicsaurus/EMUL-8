
#pragma once

/**
 * @brief Simulates CPU cycling
 *
 * Ticks the emulated CPU at a set speed and also holds the c urrent cycles that are being waited
 * such that registers can be initialized with this value.
 *
 */
class EmuTimer
{
    public:
        ///Cycle once
        void tick();

        ///Get the cycles in the current run
        int getTime();

        ///Set the cycles in the current run
        void setTime(int vewValue);

    private:
        ///Current cycles in this run
        int value = 0;
};
