#include "EmuApp.h"

/** 
 * @brief Initialize member variables
 *
 * Initializes the frame, panel, and sets a default size and allows the window to be resizable
 * @return true if initialized
 */
bool EmuApp::OnInit()
{
    /// Set up the window
    frame = new EmuFrame(this);
    panel = new EmuPanel(this, frame);
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1, wxEXPAND);     
    frame->SetSizer(sizer);
    Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(EmuApp::update));
    return true;
}


/**
 * @brief Updates view
 *
 * Given an event, redraws the panel and queries for more events
 * @param event an event that is define in the WxWidgets
 */
void EmuApp::update(wxIdleEvent &event)
{
    panel->draw(false);
    event.RequestMore();
}
