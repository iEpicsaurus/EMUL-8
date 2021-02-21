#ifndef EMUPANEL_H
#define EMUPANEL_H

#include <wx/wx.h>

/// Forward declaration to prevent conflicts
class EmuApp;

/**
 * @brief Deals with providing controls to user
 *
 * Contains the window and provides controls for the user (such as pressing buttons) and updates the display
 *
 * @author Sean Aspinall
 * @author James Mitsumasu
 * @author Sean Maas
 *
 */
class EmuPanel: public wxPanel
{
    public:

        /// Default Panel Constructor that houses the app and links itself to the parent widget
        EmuPanel(EmuApp *app, wxFrame *parent);

        /// Clears the screen
        void draw(bool clear);

    private:
        /// The application that contains the core which has data to be outputted (ex. Pixel values)
        EmuApp *app;

        /// Refer to readme for information on the control map
        const char keyMap[16] = { 'X', '1', '2', '3',
                                  'Q', 'W', 'E', 'A',
                                  'S', 'D', 'Z', 'C',
                                  '4', 'R', 'F', 'V' };

        /// Stores the size of the window (x = width, y = height)
        int x, y;

        /// Stores the multiplicative scale of the current panel (ex. 2x scaled)
        float scale;

        ///Resizes the windows
        void resize(wxSizeEvent &event);

        /// Defines a pressed key event for the emulator
        void pressKey(wxKeyEvent &event);

        /// Defines a released key event for the emulator
        void releaseKey(wxKeyEvent &event);

        /// A Static table containing each defined event for this class
        wxDECLARE_EVENT_TABLE();
};

#endif // EMUPANEL_H
