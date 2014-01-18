
#include <windows.h>
#include "resource.h"
 
// Class: addlog
// Draws the About Dialog
class addlog
{
public:
    static BOOL CALLBACK DialogProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    int Run(HINSTANCE hInstance, HWND hParent);
 
private:
    HWND m_hwnd;
};


addlog dlg;