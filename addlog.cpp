
#include <windows.h>
#include "addlog.h"
#include "resource.h"
 
addlog::addlog()
{
}
 
addlog::~addlog()
{
}
 
// Function: Run
// Returns: Result of the DialogBox
int addlog::Run(HINSTANCE hInstance, HWND hParent)
{
    int retval = DialogBox(
        hInstance,
        MAKEINTRESOURCE(fs_logbar), // Dialog template
        hParent, // Pointer to parent hwnd
        DialogProc);
 
	return retval;
}
 
// Function: DialogProc
// Handles the messages for the About dialog
BOOL CALLBACK
    addlog::DialogProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int retVal = false;
    switch(msg)
    {
    case WM_INITDIALOG:
        retVal = true;
        break;
    case WM_COMMAND:
        if(LOWORD(wParam)== IDOK)
            EndDialog(hwnd, TRUE);
        break;
    case WM_CLOSE:
        EndDialog(hwnd, TRUE);
        break;
    }
    return retVal;
}


