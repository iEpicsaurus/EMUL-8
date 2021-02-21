#include "EmuFrame.h"
#include "EmuApp.h"

/** 
 * @brief Initialize the rendering area and toolbars
 * @param app Sets the frame's running app to this
 * 
 * Creates the file menu (for opening roms), the menu bar (for changing options), and the window display (for emulated display output)
 */
EmuFrame::EmuFrame(EmuApp *app): wxFrame(NULL, wxID_ANY, "EMUL-8", wxPoint(50, 50), wxSize(64 * 4, 32 * 4)), app(app)
{
	/// Sets up the file menu
	wxMenu *fileMenu = new wxMenu();
	fileMenu->Append(0, "&Open ROM");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT);
	
	/// Sets up the menu bar
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	SetMenuBar(menuBar);
	
	/// Preventing resizing smaller than the CHIP-8 resolution (multiplied by 2)
	SetClientSize(wxSize(64 * 4, 32 * 4));
	SetMinSize(GetSize());
	
	Centre();
	Show(true);
}

/**
 * @brief Runs the emulator
 *
 * Concurrently updates the display while the application is also running
 */
void EmuFrame::run()
{
    /// Continuously run the emulator core
    while (running)
        app->getCore()->runFrame();
}

/** 
 * @brief Initialize the rendering area and toolbars
 *
 * Opens a dialogue for the user to select a rom - only allows valid (.ch8) files to be opened, then creates the core
 * It will also stop any running emulation processes if any are running and replace them with the new Emulation core
 *
 * @param event A WxWidget defined event that signals that a file dialogue should be opened
 *
 */
void EmuFrame::openRom(wxCommandEvent &event)
{
    /// The file picker
    wxFileDialog romSelect(this, "Open ROM File", "", "", "CHIP-8 ROM files (*.ch8)|*.ch8", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (romSelect.ShowModal() == wxID_CANCEL)
        return;

    /// Get the ROM filename
    char path[1024];
    strncpy(path, (const char*)romSelect.GetPath().mb_str(wxConvUTF8), 1023);

    /// Stop the emulator thread if it was running
    if (thread)
    {
        running = false;
        thread->join();
        delete thread;
    }

    /// Create a new emulator core with the ROM
    if (app->getCore()) delete app->getCore();
    app->setCore(new EmuCore(path));


    /// Start the emulator thread
    running = true;
    thread = new std::thread(&EmuFrame::run, this);
}

/**
 * @brief Exits
 *
 * Offloads the shutdown process to WxWidgets to delete its objects
 *
 * @param event A WxWidget defined event that signals that a the application should be closed
 */
void EmuFrame::exit(wxCommandEvent &event)
{
    Close(true);
}
