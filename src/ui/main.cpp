#include <wx/wx.h>

#include "EmuApp.h"
#include "EmuFrame.h"
#include "EmuPanel.h"

/// wxWidgets sets up the main() function
wxIMPLEMENT_APP(EmuApp);

wxBEGIN_EVENT_TABLE(EmuFrame, wxFrame) ///< Initialize static event table for the Frame
EVT_MENU(0, EmuFrame::openRom) ///< Create a menu item event for opening roms
EVT_MENU(wxID_EXIT, EmuFrame::exit) ///< Create a menu item event for closing the application
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(EmuPanel, wxPanel) ///< Initialize a static event table for the Panel
EVT_SIZE(EmuPanel::resize) ///< Create a menu item event for resizing the panel
EVT_KEY_DOWN(EmuPanel::pressKey) ///< Create a menu item event for pushing a key down
EVT_KEY_UP(EmuPanel::releaseKey) ///< Create a menu item event for releasing a key (after pushing it down)
wxEND_EVENT_TABLE()
