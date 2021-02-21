#ifndef EMUAPP_H
#define EMUAPP_H

#include <wx/wx.h>

#include "EmuFrame.h"
#include "EmuPanel.h"
#include "../EmuCore.h"

/**
 * @brief Links the core class of the emulator and wxWidgets.
 *
 * Links between the core class of the Emulator and WxWidgets.
 * Stores the Frame (Where the core renders to),
 * Stores the Panel (Where the OS can create the window),
 * and stores the Core (Where data is augmented and where the emulation of a single ROM occurs)
 *
 * @author Sean Maas
 *
 */
class EmuApp: public wxApp
{
    public:
    
        /** 
         * @brief Allows data access
         * 
         * Allows WxWidgets to access the core's data that is needed to render
         * @return Core The Emulator's core for a single ROM
         */
        EmuCore *getCore() { return core; }
        
        /** 
         * @brief Changes data on runtime
		 * 
         * Allows WxWidgets to change the core on runtime - allows multiple ROMs to be opened sequentially
         * @param core The new ROM core
         */
        void setCore(EmuCore *core) { this->core = core; }

    private:
        EmuFrame *frame; ///< Where the frames are drawn to
        EmuPanel *panel; ///< What contains the frame
        EmuCore *core; ///< What modifies the data that must be drawn

        /// Returns Success_Status True if initiation was finished correctly with no errors - error otherwise
        virtual bool OnInit();

        /// Updates the application
        void update(wxIdleEvent &event);
};

#endif // EMUAPP_H
