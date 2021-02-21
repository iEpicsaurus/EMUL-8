#ifndef EMU_CONTROLLER_H
#define EMU_CONTROLLER_H

/**
 * @brief Implements the controller
 * 
 * Implementation of the Controller class which deals with when keys are
 * in an active or inactive state.
 *
 * @author Zhen Wang
 * @author Sean Maas
 *
 */
class EmuController
{
    public:
        void pressKey(int key);
        void releaseKey(int key);
        bool getKey(int key);

    private:
        bool keys[16] = {};
};

#endif // EMU_CONTROLLER_H
