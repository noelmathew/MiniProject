	#include"progressbar.h"

	PROGRESSBAR::PROGRESSBAR()
	{
		maxSize = 100;
	}

	int PROGRESSBAR::create(HWND parentWindow,int topW, int leftW,int heightW,int widthW,int ID,DWORD styleW)
	{
		parentHwnd	=parentWindow;
		top			=topW;
		left		=leftW;
		height		=heightW;
		width		=widthW;
		resourceID	=ID;

		hwnd = CreateWindow( PROGRESS_CLASS,NULL,styleW,left,top,width,height,parentHwnd,(HMENU)resourceID,(HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE),NULL);
		
		if( hwnd == NULL )
			return 0;

		return 1;
	}

	void PROGRESSBAR::setRange( int min, int max )
	{
		maxSize		= max;
		maxSizeDone = 0;

		SendMessage( hwnd, PBM_SETRANGE, 0, MAKELPARAM( min, 100 ) ); 
	}

	int PROGRESSBAR::add( int iAmount )
	{
		maxSizeDone		+= iAmount;
		double iPercent	= ( ( maxSizeDone / maxSize ) * ( 100 ) );
		double curAdd	= iPercent;
		SendMessage( hwnd, PBM_SETPOS, (WPARAM)curAdd ,(LPARAM)0 );
		return (int)iPercent;
	}

	void PROGRESSBAR::minus( int iAmount )
	{
		SendMessage( hwnd, PBM_SETSTEP, (WPARAM)1 ,(LPARAM)0 );
	}

	void PROGRESSBAR::reset()
	{
		SendMessage( hwnd, PBM_SETPOS, (WPARAM)0, (LPARAM)0 );
		maxSizeDone = 0;
	}

