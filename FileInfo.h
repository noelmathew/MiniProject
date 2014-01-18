#ifndef FILEINFO_H
#define FILEINFO_H
#include "headers.h"

int opMode;
class FILEINFO
	{
	protected:
		TCHAR fileName[MAX_PATH];
		TCHAR outputDir[MAX_PATH];
		int numParts;
		long fileSize;
		long partsSize;
	public:
		void setODir(TCHAR *oDir);
		TCHAR *getODir();
		void setfName(TCHAR *fName);
		TCHAR *getfName();
		void nParts(int n);
		int nParts();
		void fSize(long fSize);
		long fSize();
		void pSize(long ps);
	};



class OPSPLIT: public FILEINFO
	{
	public:
	void doSplitFile();
	int createSplitJoiner();
	int createBatchFile();
	void getRealFileName(TCHAR *szRet);
	};

class OPJOIN:  public FILEINFO
	{
	public:
	void doJoinFile();
	void getRealFileName(TCHAR *szRet);
	};

class RSA
{
  protected:
	TCHAR fileName[MAX_PATH];
	TCHAR outputDir[MAX_PATH];
	int p, q, M, N;
	int D, E;
  public:
	long calcD(void);
	long GCD(int, int);
	long xTimesyModz(unsigned long,unsigned  long,  int);
	long xToyModz(unsigned long,  int,  int);
	RSA();
	void setODir(TCHAR *oDir);
	TCHAR* getoDir();
	void setfName(TCHAR *fName);
	TCHAR* getfName();
	void getRealFileName(TCHAR *szRet);
};

class OPENCRYPT: public RSA
{
  public:
	void RSAencrypt();
	
};

class OPDECRYPT: public RSA
{
  public:
	void RSAdecrypt();
	
};




	BOOL CALLBACK MainProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int doINITDIALOG( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int doCOMMAND( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int msgbox( HWND wnd, TCHAR *tMsg, TCHAR *tTitle );
	int doOpenFile( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int doMenuPopup( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	long getfileSize( TCHAR *wStr );
	void getFormatSize( long double fSize, TCHAR *tRet );
	double partsSize( long double lFileSize, int iParts );
	int doEditParts( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	void setFileInfoView( HWND hwnd );
	int doVSCROLL( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int doGetOutputDir( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int _ERROR( int iErr );
	void doUIProgress( int iMode, int iProgress );
	void toAnsi( TCHAR *szStr );
	void isOperating( bool bYes );
	void setFont( HWND wnd, TCHAR *font, int size );
	 bool Run(int nCmdShow);
	void SplitFile();
	void JoinFile();
		void EFile();
		void DFile();
		
	HWND motherHwnd,hwnd;
	DWORD sId, jId,eId,dId;
	HINSTANCE hInstance;
	OPJOIN objoin;
	OPSPLIT obsplit;
	
	OPENCRYPT obencrypt;
	OPDECRYPT obdecrypt;
	PROGRESSBAR pBar;
	
	bool stopAction	= false;


#endif