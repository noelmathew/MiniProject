#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

	#include"headers.h"

	class PROGRESSBAR{

	public:

		PROGRESSBAR();
		int create(HWND parentWindow,int topW, int leftW,int heightW,int widthW,int ID,DWORD styleW);
		void setRange( int min, int max );
		int add( int iAmount );
		void minus( int iAmount );
		void reset();

		HWND hwnd, parentHwnd;
		HINSTANCE hinstance;
		int top,left;
		int width, height;
		int resourceID;
		double maxSize;
		double maxSizeDone;

	private:

	};

#endif