#include <wx/rawbmp.h>

#include "EmuPanel.h"
#include "EmuApp.h"

/**
 * @brief Panel Constructor
 *
 * Creates the Panel of which the Frame is contained within
 *
 * @param parent Specifies the frame in which the Panel resides in
 *
 * @param app The application that contains the core which has data to be outputted (ex. Pixel values)
 */
EmuPanel::EmuPanel(EmuApp *app, wxFrame *parent): wxPanel(parent), app(app)
{
    /// Set focus to allow inputs to be read
	SetFocus();
}

/**
 * @brief Resizes the window
 *
 * Resizes the window if the user drags the corners of the window or via the window sizing buttons given by the OS
 *
 * @param event A wxWidgets event from the event table for a resize event
 */
void EmuPanel::resize(wxSizeEvent &event)
{
    /// Scale the display to the size of the window
    wxSize size = GetSize();
    float ratio = 64.0f / 32;
    float window = (float)size.x / size.y;
    scale = ((ratio >= window) ? (float)size.x / (64 * 4) : (float)size.y / (32 * 4));

    /// Centre the display
    x = ((float)size.x / scale - (64 * 4)) / 2;
    y = ((float)size.y / scale - (32 * 4)) / 2;

    draw(true);
}

/**
 * @brief Passes key presses to the emulator
 *
 * Defines an event for when a key is pushed and sends it to the core emulator for user input
 *
 * @param event A wxWidgets event from the event table for a presskey event
 */
void EmuPanel::pressKey(wxKeyEvent &event)
{
    /// Only run when an instance of the core has been created
    if (!app->getCore()) return;

    /// Send a key press to the core
    for (int i = 0; i < 16; i++)
    {
        if (event.GetKeyCode() == keyMap[i])
            app->getCore()->pressKey(i);
    }
}

/**
 * @brief Passes key releases to the emulator
 *
 * Defines an event for when a key is released (after being pushed) and sends it to the core emulator for user input
 *
 * @param event A wxWidgets event from the event table for a release key event
 */
void EmuPanel::releaseKey(wxKeyEvent &event)
{
    /// Only run when an instance of the core has been created
    if (!app->getCore()) return;

    /// Send a key release to the core
    for (int i = 0; i < 16; i++)
    {
        if (event.GetKeyCode() == keyMap[i])
            app->getCore()->releaseKey(i);
    }
}

/**
 * @brief Draws the CHIP-8 emulated screen to the Panel and handles resizing
 *
 * Defines the size of the area (before resizing) where the Panel will draw to
 * The CHIP-8 has a screen size of 64 pixels by 32 pixels and using the default colour depth of 24 (if set below it, WxWidgets still defaults to 24)
 * Sets the RGB values of every pixel on the Panel to values given by the emulator - which will always be black and white
 * Then Pushes the created bitmap to the Wx renderer and scales it properly
 *
 * @param clear Clears the bitmap if true - stops all output
 */
void EmuPanel::draw(bool clear)
{
	wxBitmap bmp(64 * 4, 32 * 4, 24); ///< Create a 64x32 screen with colour depth of 24
	wxNativePixelData data(bmp);
	wxNativePixelData::Iterator iter(data);
	
	/// Copy the display to the bitmap
	for (int y = 0; y < 32 * 4; y++)
	{
		wxNativePixelData::Iterator pixel = iter;
		for (int x = 0; x < 64 * 4; x++, pixel++)
		{
            /// Set all the RGB values to the same value to produce a shade of grey
			uint8_t shade = app->getCore() ? app->getCore()->getPixel(x / 4, y / 4) : 0;
			pixel.Red()   = shade;
           	pixel.Green() = shade;
			pixel.Blue()  = shade;
		}
		iter.OffsetY(data, 1);
	}
	
	/// Display the bitmap
	wxClientDC dc(this);
	if (clear) dc.Clear();
	dc.SetUserScale(scale, scale);
	dc.DrawBitmap(bmp, wxPoint(x,y));
}
		
