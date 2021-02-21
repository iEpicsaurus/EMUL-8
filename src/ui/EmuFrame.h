#ifndef EMUFRAME_H
#define EMUFRAME_H

#include <thread>
#include <wx/wx.h>

/// Forward declaration to prevent conflicts
class EmuApp;

/**
 * @brief Deals with the UI window
 *
 * Maintains the tool bar, window sizing, and file opening operations
 *
 * @author Zhen Wang
 * @author Sean Maas
 * @author Aleksandar Kostic
 *
 */
class EmuFrame: public wxFrame
{
    public:

        /// Initializes the application for the Frame
        EmuFrame(EmuApp *app);

    private:

        /// The Application that runs the core
        EmuApp *app;

        /// The currently running thread of the emulator
        std::thread *thread;

        /// Set to true while the emulator is running, set to false when the emulator is shutting down
        bool running;

        /// Runs the application
        void run();

        /// Defines a ROM opening event
        void openRom(wxCommandEvent &event);

        /// Defines an exiting event
        void exit(wxCommandEvent &event);

        /// Stores a static event table for this class
        wxDECLARE_EVENT_TABLE();
};

#endif // EMUFRAME_H
