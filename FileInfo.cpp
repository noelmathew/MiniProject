#include "FileInfo.h"
#include "headers.h"
#include "log.h"
#include "progressbar.h"
#include "addlog.h"

MYSQL *hnd=NULL;

int addlog::Run(HINSTANCE hInstance, HWND hParent)
{
    int r = DialogBox(hInstance,MAKEINTRESOURCE(fs_logbar),hParent,DialogProc);
 	return r;
}
 
BOOL CALLBACK addlog::DialogProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TCHAR file[100000];
	char temp[100000];
	FILE  *ptr;
	int i;
    int retVal = false;
	memset(file,0,100000);
	memset(temp,0,100000);
	const char *tbl;
	const char *sinf=NULL; // mysql server information 
	switch(msg)
    {
    case WM_INITDIALOG:
        retVal = true;
		 
	  
	hnd = mysql_init(NULL); // mysql connection handle


	
	if (mysql_real_connect(hnd,SERVER_NAME,DB_USER,DB_USERPASS,DB_NAME,0,NULL,0)==NULL) 
	{ 
		_ERROR(ERR_DBCONNECTION);
		
	} 
	else 
	{	 
		sinf = mysql_get_server_info(hnd); 
		if (sinf != NULL) 
		{ 
		fstream logfile;
		TCHAR file[100000];
		logfile.open("D:\\splitlog1.log",ios::out);
		logfile<<"No.\tMODE\t\tFILENAME\tSIZE\tPARTS\tPARTS_SIZE\tDAY\tTIME\n";


		MYSQL_RES *res=NULL; // result of querying for all rows in table 
		MYSQL_ROW row; // one row returned 
		char sql[1024], // sql statement used to get all rows 
		int i,y=0,numf=0; // number of fields returned from the query 


		sprintf(sql,"select * from %s",TABLE_OF_INTEREST); 
	
		if (!mysql_query(hnd,sql)) 
		{ 
		res = mysql_use_result(hnd); 
		if (res) 
		{ 
		numf = mysql_num_fields(res); 
		row = mysql_fetch_row(res);  
	
		while (row) 
		{ 
			
			for (i=0;i<numf;i++) 
			{ 	
				if (row[i] == NULL) 
				{ 
				} 
				else if (strlen(row[i]) >= 15) 
				{ 
					 logfile<<(char*)(row[i])<<"\t";
					 	
				} 
				else 
				{ 
					
					logfile<<(char*)(row[i])<<"\t"; 
		
				} 
				
			} 
			logfile<<endl; 
		

			row = mysql_fetch_row(res); 
		}  

			mysql_free_result(res); 
	} 
	else 
	{ 
		_ERROR(ERR_RSLTACQRFAILED);
		
	} 
	} 
else 
{ 
	ERROR(ERR_EXEQUERYFAILED);
	
	
} 

logfile.close();
			} 
		
		else 			
		{ 
			_ERROR(ERR_SISRETFAILED);
			
		} 

	mysql_close(hnd); 
		}

	if(ptr=fopen("D:\\splitlog1.log","rb"))
		{
			while(!feof(ptr))
			{
				temp[i++]=fgetc(ptr);
			}
			mbstowcs(file,temp,100000);
			SetWindowText( GetDlgItem( hwnd, fs_logtext ),file );
			fclose(ptr);
		}
		else
		{
			_ERROR( ERR_LOGNOTCREATED );
		}
		
        break;

	case WM_RBUTTONDOWN:

		break;
    
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    }
    return retVal;
}


RSA :: RSA()
{
	int g;

	p = 11;
	q = 23;
	N = p * q;
	M = (p - 1) * (q - 1);
	E = 10;

	do
	{
		E++;
		g = GCD(E, M);
	}while(g != 1);

	D = calcD();
}

long RSA :: GCD(int e, int n)
{
	if(n == 0)
		return e;
	else if(n > e)
		return(GCD(n, e));
	else
		return(GCD(n, (e % n)));
}

long RSA :: xTimesyModz(unsigned long  x,unsigned  long y,  int z)
{
	return (x * y) % z;
}

long RSA :: xToyModz(unsigned long x, int y,  int z)
{
	int ans = 1, idx = 1;
	for(idx = 1; idx <= y; idx++)
	{
		ans = xTimesyModz(ans, x, z);
	}
	return ans;
}

 long RSA :: calcD()
{
	unsigned long prodOne = M + 1;
	unsigned long tmp = prodOne % E;

	while(tmp != 0)
	{
		prodOne += M;
		tmp = prodOne % E;
	}

	return (prodOne / E);
}

void RSA::setODir(TCHAR *oDir){swprintf(outputDir,oDir);}
void RSA::setfName(TCHAR *fName){swprintf(fileName,fName);}
TCHAR* RSA::getfName(){ return fileName;}
TCHAR* RSA::getoDir(){return outputDir;}

void RSA::getRealFileName(TCHAR *szRet)
	{
		for( int iPos = wcslen( fileName ); iPos > 0; iPos-- )
		{
			if( fileName[iPos]==  '\\' )
			{
				swprintf( szRet, &fileName[iPos + 1] );
				break;
			}
		}
	}


void OPENCRYPT :: RSAencrypt()
{

	if( wcslen( fileName ) < 2 ){ _ERROR( ERR_NOFILE ); return; }
		if( wcslen( outputDir ) < 2 ){ _ERROR( ERR_EMTYDIR ); return; }
		if( opMode != ENCRYPT_MODE ){ _ERROR( ERR_ENCRYPT ); return; }

	isOperating( true );

	FILE *ptrread,*ptrwrite;
	TCHAR *mark=NULL;
	TCHAR *fileTitle		= new TCHAR[100];
	TCHAR *tmpFileTitle	= new TCHAR[100];
	char *contTmp= new char[MB + 1];
	unsigned long R;
	long chr;
	long tfSize=0;
	long curPos			= 0;
	long curBuffSize	= MB;
	long iBytesWriten	= 0;
	int i=0,iPos=0;
	
	tfSize=getfileSize(fileName);
	pBar.reset();
	pBar.setRange(0,tfSize);

	tfSize = getfileSize( fileName );
	ptrread=fileOpen(fileName,U("r"));

	if(!ptrread)
	{
		_ERROR(ERR_READINGFILE);
		goto cleanup;
	}
	for( iPos = wcslen( fileName ); iPos > 0; iPos-- )
		{
			if( fileName[iPos]==  '\\' )
			{
				swprintf( fileTitle, &fileName[iPos + 1] );
				break;
			}
		}
	swprintf( tmpFileTitle, U("%s\\%s.enc"), outputDir, fileTitle  );
	ptrwrite = fileOpen(tmpFileTitle,U("wb"));
	mark=U("AHNP");
	for(i = 0; i < 4; i++)
	{	
		chr=mark[i];
		R = xToyModz(chr, E, N);
		fputwc((TCHAR)R,ptrwrite);
	}
		fclose(ptrread);
		
	if(	ptrread=fileOpen(fileName,U("rb")))

	{	
		while(1)
			{
				curPos = ( tfSize - ftell( ptrread )  );
					if( curPos >= MB )
							curBuffSize	= MB;
					else
							curBuffSize = curPos;
				fread( contTmp, curBuffSize, 1, ptrread );
				for(long i=0;i<curBuffSize;i++)
				{
					R = xToyModz(contTmp[i], E, N);
					fputwc((R),ptrwrite);
					doUIProgress( ENCRYPT_MODE, pBar.add( 1 ) );
				}

			iBytesWriten += curBuffSize;

			if( stopAction )
				{
					isOperating( false );
					stopAction = false;
					_ERROR( ERR_ACTION_CANCELLED );
					goto cleanup;
				}
				
				if( iBytesWriten >= tfSize )
						{
								iBytesWriten = 0;
								fclose( ptrread );
								break;
						}

			
			}
		}
			getRealFileName(fileName);
			fileName[15]='\0';
			msgbox(motherHwnd,U("Encryption successfully done!!"),U("Success"));
		writelog(hnd,3,fileName);
	
cleanup:
	if(ptrread) fclose(ptrread);
	isOperating( false );
	fclose(ptrread);
	fclose(ptrwrite);
	pBar.reset();
	delete [] contTmp;
	return;
}

void OPDECRYPT :: RSAdecrypt()
{
		if( wcslen( fileName ) < 2 ){ _ERROR( ERR_NOFILE ); return; }
		if( wcslen( outputDir ) < 2 ){ _ERROR( ERR_EMTYDIR ); return; }
		if( opMode != DECRYPT_MODE ){ _ERROR( ERR_DECRYPT ); return; }

	isOperating( true );

	FILE *ptrread,*ptrwrite;
	TCHAR mark[4];
	TCHAR *fileTitle		= new TCHAR[100];
	TCHAR *tmpFileTitle	= new TCHAR[100];
	unsigned long R;
	long chr;
	long tfSize=0;
	long curPos			= 0;
	long curBuffSize	= MB;
	long iBytesWriten	= 0;
	int i=0,iPos=0,flag=0;
	TCHAR *contTmp	= new TCHAR[MB + 1];
	tfSize=getfileSize(fileName);
	pBar.reset();
	pBar.setRange(0,tfSize-8);
		
	tfSize = getfileSize( fileName );
    ptrread=fileOpen(fileName,U("rb"));
	
	if(!ptrread)
	{
		_ERROR(ERR_READINGFILE);
		goto cleanup;
		
	}
	
	for(iPos = wcslen(fileName); iPos > 0; iPos-- )
		{
			if( fileName[iPos]== '.' && flag==0 )
			{
				flag=1;
				fileName[iPos]='\0';
			}
			if( fileName[iPos]==  '\\' )
			{
				swprintf( fileTitle, &fileName[iPos + 1] );
				break;
			}
		}

	swprintf( tmpFileTitle, U("%s\\%s"), outputDir, fileTitle  );
	ptrwrite = fileOpen(tmpFileTitle,U("wb"));

	for(i = 0; i < 4; i++)
	{
		chr=fgetwc(ptrread);
		mark[i] = xToyModz(chr, D, N);
	}
	
	if(mark[0] == 'A' && mark[1] == 'H' && mark[2] == 'N' && mark[3]=='P')
	{
				
		while(1)
			{
				curPos = ( tfSize - ftell( ptrread )  );
					if( curPos >= MB )
							curBuffSize	= MB;
					else
							curBuffSize = curPos;
				fread( contTmp, curBuffSize, 1, ptrread );
				for(long i=0;i<(curBuffSize/2);i++)
				{
					R = xToyModz(contTmp[i], D, N);
					fputwc((R),ptrwrite);
					doUIProgress( ENCRYPT_MODE, pBar.add( 2 ) );

				}

				iBytesWriten += curBuffSize;
				if( stopAction )
				{
					isOperating( false );
					stopAction = false;
					_ERROR( ERR_ACTION_CANCELLED );
					goto cleanup;
				}
				
							if( iBytesWriten >= (tfSize/2) )
							{
								iBytesWriten = 0;
								fclose( ptrread );
								break;
							}

			
			}
		
			getRealFileName(fileName);
			fileName[15]='\0';
			msgbox(motherHwnd,U("Decryption successfully done!!"),U("Success"));
		writelog(hnd,4,fileName);
	

	}
	else
	{
		msgbox(motherHwnd,U("File Mismatch Error!!"),U("Abort"));
		_ERROR( ERR_FILEMISMATCH );
		return;
	}
cleanup:
	if(ptrread) fclose(ptrread);
	isOperating( false );
	fclose(ptrread);
	fclose(ptrwrite);
	pBar.reset();
	delete [] contTmp;
	return;
}



void OPJOIN::doJoinFile()
		{
		
		if( wcslen( fileName ) < 2 ){ _ERROR( ERR_NOFILE ); return; }
		if( wcslen( outputDir ) < 2 ){ _ERROR( ERR_EMTYDIR ); return; }
		if( opMode != JOIN_MODE ){ _ERROR( ERR_SPLITMODE ); return; }

		TCHAR filename1[100];
		TCHAR *cTmp			= new TCHAR[MAX_PATH];
		TCHAR *contTmp		= new TCHAR[MB + 1];
		TCHAR *jFileTitle	= new TCHAR[MAX_PATH];
		TCHAR *jFileName	= new TCHAR[MAX_PATH];
		TCHAR *curFileName	= new TCHAR[MAX_PATH];
		TCHAR *fileName2		= new TCHAR[MAX_PATH];
		TCHAR *tFileName	= new TCHAR[MAX_PATH];
		TCHAR *inputDir	= new TCHAR[MAX_PATH];

		
		if( !cTmp || !contTmp || !jFileTitle || !jFileName  || !curFileName || !fileName2 )
		{  _ERROR( ERR_OUT_OF_MEMORY ); return; }

		isOperating( true );

		FILE *fPtr			= 0;
		FILE *fPtrWrite		= 0;
		FILE *fPtrRead		= 0;
		long curPos			= 0;
		long fSize			= 0;
		long totalFSize		= 0;
		long curBuffSize	= MB;
		long iBytesWriten	= 0;
		bool firstLine		= true;
		bool secondLine		= false;

	
		if( ( fPtr = fileOpen( fileName, U("rb") ) ) )
		{
			while( !feof( fPtr ) )
			{
				fgetws( cTmp, MAX_PATH, fPtr );

				if( firstLine )
				{
					firstLine = false;
					secondLine = true;
					memset( jFileTitle, 0, MAX_PATH );
					wcsncat( jFileTitle, cTmp, wcslen( cTmp ) - wcslen( U("_\r\n") ) );
					totalFSize = _wtol( jFileTitle );
					pBar.reset();
					pBar.setRange( 0, totalFSize );

				}
				else if( secondLine )
				{
					secondLine = false;
					memset( jFileTitle, 0, MAX_PATH );
					wcsncat( jFileTitle, cTmp, wcslen( cTmp ) - wcslen( U("_\r\n") ) );
					swprintf( jFileName, U("%s\\%s"), outputDir, jFileTitle);
					

					if( !( fPtrWrite = fileOpen( jFileName, U("wb+") ) ) )
					{
						
						_ERROR( ERR_READINGFILE );
						goto cleanup;
					}
				}
				else if( !feof( fPtr ) )
				{
					memset( jFileTitle, 0, MAX_PATH );
					wcsncat( jFileTitle, cTmp, wcslen( cTmp ) - wcslen( U("_\r\n") ) );
					swprintf( tFileName, fileName);
					for( int iPos = wcslen(tFileName ); iPos > 0; iPos-- )
					{		
						if(tFileName[iPos]==  '\\' )
						{
							tFileName[iPos]='\0';
							swprintf( inputDir, tFileName);
							break;
						}
					}
					swprintf( curFileName, U("%s\\%s"), inputDir, jFileTitle );
									
					if( ( fPtrRead = fileOpen( curFileName, U("rb") ) ) )
					{
						fSize = getfileSize( curFileName );

						while( 1 )
						{
							curPos = ( fSize - ftell( fPtrRead )  );

							if( curPos >= MB )
								curBuffSize	= MB;
							else
								curBuffSize = curPos;

							fread( contTmp, curBuffSize, 1, fPtrRead );
							fwrite( contTmp, curBuffSize, 1, fPtrWrite );
							iBytesWriten += curBuffSize;

							doUIProgress( JOIN_MODE, pBar.add( curBuffSize ) );

							if( stopAction )
							{
								isOperating( false );
								stopAction = false;
								_ERROR( ERR_ACTION_CANCELLED );
								goto cleanup;
							}

							if( iBytesWriten >= fSize )
							{
								iBytesWriten = 0;
								fclose( fPtrRead );
								break;
							}
						}
					}
					else
					{
						
						_ERROR( ERR_READINGFILE );
						goto cleanup;
					}
				}
			}
		}
		else 
		{
			_ERROR( ERR_READINGFILE );
			goto cleanup;
		}
	
		getRealFileName(filename1);		
		msgbox( motherHwnd, U("Joining Successfully Done!!"), U("Success!") );
		filename1[15]='\0';
		writelog(hnd,2,filename1,totalFSize,fSize,numParts);
		cleanup:
		if( fPtr ) fclose( fPtr );
		isOperating( false );
		fclose( fPtrWrite );
		fclose( fPtrRead );
		delete [] cTmp;
		delete [] contTmp;
		delete [] fileName2;
		delete [] jFileName;
		delete [] curFileName;
		delete [] jFileTitle;
		pBar.reset();
	}

void OPJOIN::getRealFileName(TCHAR *szRet)
	{
		
		for( int iPos = wcslen(fileName ); iPos > 0; iPos-- )
		{
			if(fileName[iPos]==  '\\' )
			{
				swprintf( szRet, &fileName[iPos + 1] );
				break;
			}
		}

	}

void FILEINFO::nParts(int n){ numParts=n;}
int FILEINFO::nParts(){return numParts;}
void FILEINFO::setODir(TCHAR *oDir){swprintf(outputDir,oDir);}
void FILEINFO::setfName(TCHAR *fName){swprintf(fileName,fName);}
TCHAR* FILEINFO::getfName(){ return fileName;}
void FILEINFO::fSize(long fs){fileSize=fs;}
long FILEINFO::fSize(){return fileSize;}
void FILEINFO::pSize(long ps){partsSize=ps;}
TCHAR* FILEINFO::getODir(){return outputDir;}

void OPSPLIT::doSplitFile()
	{
		if( wcslen(fileName) < 2 ){ _ERROR( ERR_NOFILE ); return; }
		if( wcslen(outputDir) < 2 ){ _ERROR( ERR_EMTYDIR ); return; }
		if( opMode != SPLIT_MODE ){ _ERROR( ERR_JOINMODE ); return; }

		TCHAR *fileNameTmp	= new TCHAR[MAX_PATH];
		TCHAR *fileTitle	= new TCHAR[100];
		TCHAR *szSplitTmp	= new TCHAR[MB + 1];
		if( !fileNameTmp || !fileTitle || !szSplitTmp )
		{  _ERROR( ERR_OUT_OF_MEMORY ); return; }

		isOperating( true );

		FILE *fPtr			= 0;
		FILE *fPart			= 0;
		int curBuffSize		= MB;
		long iDone			= 0;
		long iBytesWritten	= 0;
		int iParts			= numParts;
		long curPos			= 0;
		int ctr				= 0;
		
		if( !( fPtr = fileOpen(fileName, U("rb") ) ) )
		{
			_ERROR( ERR_READINGFILE );
			goto cleanup;
		}

		getRealFileName( fileTitle );		
		pBar.reset();
		pBar.setRange( 0, fileSize );

		for( ctr = 0; ctr != iParts && !feof( fPtr ); ctr++ )
		{
			swprintf( fileNameTmp, U("%s\\%s.0%d"), outputDir, fileTitle, ctr ); 

			if( ( fPart = fileOpen( fileNameTmp, U("wb+") ) ) )
			{
				while( 1 )
				{
					curPos = ( fileSize - ftell( fPtr )  );

					if( curPos >= MB && ( partsSize - iDone ) >= MB )
						curBuffSize	= MB;
					else if( iParts - 1 != ctr )
						curBuffSize = ( partsSize - iDone );
					else
						curBuffSize = curPos;

					fread( szSplitTmp, curBuffSize, 1, fPtr );
					fseek( fPart, 0, SEEK_END );
					fwrite( szSplitTmp, curBuffSize, 1, fPart );
					
					iDone += curBuffSize;
					iBytesWritten += curBuffSize;				
					doUIProgress( SPLIT_MODE, pBar.add( curBuffSize ) );

					if( stopAction )
					{
						isOperating( false );
						fclose( fPart );
						stopAction = false;
						_ERROR( ERR_ACTION_CANCELLED );
						goto cleanup;
					}

					if( iDone >= partsSize && iParts - 1 != ctr )
					{
						iDone = 0;
						fclose( fPart );
						break;
					}
					else if( iBytesWritten >=fileSize )
					{
						iDone = 0;
						fclose( fPart );
						break;
					}
				}

			}
			else  _ERROR( ERR_FILECREATION );
			
		}

		createBatchFile();
		createSplitJoiner();		
		msgbox( motherHwnd, U("Splitting Successfully Done!!"), U("Success!") );
		fileTitle[15]='\0';
		writelog(hnd,1,fileTitle,fileSize,partsSize,numParts);
		cleanup:
		if( fPtr ) fclose( fPtr );
		isOperating( false );
		delete [] fileNameTmp;
		delete [] szSplitTmp;
		delete [] fileTitle;
		pBar.reset();
	}

int OPSPLIT::createSplitJoiner()
	{
		FILE *fPtr			= 0;
		TCHAR *tmpFile		= new TCHAR[MAX_PATH+100];
		TCHAR *tmpCont		= new TCHAR[100];
		TCHAR *tmpFileTitle	= new TCHAR[100];
		int iRet			= 1;

		getRealFileName( tmpFileTitle );
		swprintf( tmpFile, U("%s\\%s.spj"), outputDir, tmpFileTitle );

		if( ( fPtr = fileOpen( tmpFile, U("wb+") ) ) )
		{
			for( int ctr = 0; ctr != numParts; ctr++ )
			{
				if( !ctr )
				{
					swprintf( tmpCont, U("%ld_\r\n%s_\r\n"), fileSize, tmpFileTitle );
					filePuts( tmpCont, fPtr );
				}

				swprintf( tmpCont, U("%s.0%d_\r\n"), tmpFileTitle, ctr );
				filePuts( tmpCont, fPtr );
			}
		}
		else 
		{
			iRet = _ERROR( ERR_SPLITITJOINER );
			goto cleanup;
		}

		fclose( fPtr );
		cleanup:
		return iRet;

	}

int OPSPLIT::createBatchFile()
		{
		FILE *fPtr			= 0;
		TCHAR *tmpFile		= new TCHAR[MAX_PATH+100];
		TCHAR *tmpCont		= new TCHAR[100];
		TCHAR *tmpFileTitle	= new TCHAR[100];
		int ctr				= 0;
		int iRet			= 1;

		getRealFileName( tmpFileTitle );
		swprintf( tmpFile, U("%s\\%s.bat"), outputDir, tmpFileTitle );

		fPtr = fileOpen( tmpFile, U("wb+") );

		if( !fPtr )
		{
			iRet = _ERROR( ERR_BATCHFILE );
			goto cleanup;
		}

		swprintf( tmpCont, U("copy /b \"%s.00\""), tmpFileTitle );
		toAnsi( tmpCont );
		fputs( (char *)tmpCont, fPtr );

		for( ctr = 1; ctr != numParts; ctr++ )
		{
			swprintf( tmpCont, U("+\"%s.0%d\""), tmpFileTitle, ctr );
			toAnsi( tmpCont );
			fputs( (char *)tmpCont, fPtr );
		}
		swprintf( tmpCont, U(" \"%s\" "), tmpFileTitle );
		toAnsi( tmpCont );
		fputs( (char *)tmpCont, fPtr );
		fprintf(fPtr,"\n");

		swprintf( tmpCont, U("del /a \"%s.00\""), tmpFileTitle );
		toAnsi( tmpCont );
		fputs( (char *)tmpCont, fPtr );

		for( ctr = 1; ctr != numParts; ctr++ )
		{
			swprintf( tmpCont, U(" \"%s.0%d\""), tmpFileTitle, ctr );
			toAnsi( tmpCont );
			fputs( (char *)tmpCont, fPtr );
		}
		swprintf( tmpCont, U(" \"%s.bat\""),tmpFileTitle );
		toAnsi( tmpCont );
		fputs( (char *)tmpCont, fPtr );
		swprintf( tmpCont, U(" \"%s.spj\""),tmpFileTitle );
		toAnsi( tmpCont );
		fputs( (char *)tmpCont, fPtr );
		fclose( fPtr );

		cleanup:
		delete [] tmpCont;
		delete [] tmpFile;
		delete [] tmpFileTitle;
		return iRet;
	}

void OPSPLIT::getRealFileName(TCHAR *szRet)
	{
		for( int iPos = wcslen( fileName ); iPos > 0; iPos-- )
		{
			if( fileName[iPos]==  '\\' )
			{
				swprintf( szRet, &fileName[iPos + 1] );
				break;
			}
		}
	}


BOOL CALLBACK MainProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch( msg )
		{

			case WM_COMMAND:
			doCOMMAND( hwnd, msg, wParam, lParam );
			break;

			case WM_INITDIALOG:
			doINITDIALOG( hwnd, msg, wParam, lParam );
			break;	

			case WM_SYSCOMMAND:
			doCOMMAND( hwnd, WM_COMMAND, wParam, lParam );
			return FALSE;
			break;

			case WM_VSCROLL:
			doVSCROLL( hwnd, WM_COMMAND, wParam, lParam );
			break;

			case WM_CLOSE:
			EndDialog( hwnd, 0 );
			break;

			default:
			return FALSE;
		}

		return TRUE;
	}


	int doVSCROLL( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		if( GetWindowLong( (HWND) lParam, GWL_ID ) != fs_scroll )
			return 0;
		int parts= GetDlgItemInt( hwnd, fs_parts, 0, true );

		switch( LOWORD( wParam ) )
		{
			case SB_LINEUP:
			parts++;
			obsplit.nParts(parts);
			break;

            case SB_LINEDOWN:
			parts--;
			obsplit.nParts(parts);
            break;
		}

		if( obsplit.nParts() > -1 )
			SetDlgItemInt( hwnd, fs_parts, obsplit.nParts(), true );
		else
			obsplit.nParts(0);
		 

		return 1;
	}


	int doCOMMAND( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch( LOWORD( wParam ) )
		{
			case fs_exit:
			EndDialog( hwnd, 0 );
			break;

			case fs_getdir:
			doGetOutputDir( hwnd, msg, wParam, lParam );
			break;

			case fs_parts:
			doEditParts( hwnd, msg, wParam, lParam );
			break;

			case fs_openfile:
			doOpenFile( hwnd, msg, wParam, 0 );
			break;

			case fs_openfiletojoin:
			doOpenFile( hwnd, msg, wParam, 1 );
			break;


			case fs_encrypt:
			doOpenFile( hwnd, msg, wParam, 2 );
			break;

			case fs_decrypt:
			doOpenFile( hwnd, msg, wParam, 3 );
			break;


			case fs_split:
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SplitFile, 0, 0, &sId );			
			break;

			case fs_join:
			CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)JoinFile, 0, 0, &jId );
			
			break;
			
			case fs_cencrypt:
			CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)EFile, 0, 0, &eId );
			break;

			case fs_cdecrypt:
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DFile, 0, 0, &dId );
			break;

			case fs_Menu:
			doMenuPopup( hwnd, msg, wParam, lParam );
			break;

			case fs_cancel:
			stopAction = true;
			break;
			
			case fs_log:
			dlg.Run(hInstance,hwnd);
			dlg.~addlog();

			break;

			case fs_about:
			msgbox( hwnd, U("Universal File Splitting and Encryption by:\n Abhilash S.R, \nHari Vijayan, \nNoel Mathew  \nPrathik George"), U("About") );
			break;
		}

		return 1;
	}

	
	void SplitFile()
	{
		obsplit.doSplitFile();
	}

	void JoinFile()
	{
		objoin.doJoinFile();
	}
	void EFile()
	{
		obencrypt.RSAencrypt();
	}

	void DFile()
	{
		obdecrypt.RSAdecrypt();
	}


	int doGetOutputDir( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		TCHAR tempDir[MAX_PATH];
		BROWSEINFO bi;
		ZeroMemory( &bi, sizeof( bi ) );

		bi.hwndOwner		= hwnd;
		bi.pidlRoot			= NULL;
		bi.pszDisplayName	= NULL;
		bi.lpfn				= NULL;
		bi.lParam			= 0;
		bi.lpszTitle		= U("Please Choose a Directory to Output Files"); 
		ITEMIDLIST *idList	= { 0 };

		if( !( idList = SHBrowseForFolder( &bi ) ) )
			return _ERROR( ERR_GETDIR );

		if( !SHGetPathFromIDList( &*idList, tempDir ) )
		{
			return _ERROR( ERR_GETDIR );
		}
		obsplit.setODir(tempDir);
		objoin.setODir(tempDir);
		obencrypt.setODir(tempDir);
		obdecrypt.setODir(tempDir);
		setFileInfoView( hwnd );

		return 1;
	}


	int doEditParts( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		int iParts	= 0;

		switch( HIWORD( wParam ) )
		{
			case EN_CHANGE:
			iParts = GetDlgItemInt( hwnd, fs_parts, 0, true );
			obsplit.nParts(iParts);
			setFileInfoView( hwnd );		
			break;
		}

		return 1;
	}

	int doINITDIALOG( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		motherHwnd			= hwnd;
		int iArgc			= 0;
		TCHAR *szCmdLine	= 0;
		

		HICON appIcon = LoadIcon( GetModuleHandle( 0 ), MAKEINTRESOURCE( IDI_ICONSPLIT ) );
		HMENU sysMen  = GetSystemMenu( hwnd, false );
		AppendMenu( sysMen, MF_SEPARATOR, 0, 0 );
		AppendMenu( sysMen, MF_STRING, fs_about, U("About UEFS") );
		SendMessage( hwnd, WM_SETICON, ICON_SMALL, (LPARAM)appIcon );
		SetWindowText( GetDlgItem( hwnd, fs_parts ), U("2") );
		SetWindowText( GetDlgItem( hwnd, fs_size ), U("10") );

    	
		pBar.hwnd = GetDlgItem( hwnd, fs_progressbar );
		DestroyIcon( appIcon );
		isOperating( false );
		return 1;
	}

	

	int doOpenFile( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{

		TCHAR *filename			= new TCHAR[MAX_PATH];
		char *fname =new char[MAX_PATH];
		OPENFILENAME ofn		= {0};
		long fileS				= 0;

		memset( filename, 0, MAX_PATH );
		memset( &ofn, NULL, sizeof( OPENFILENAME ) );
		ofn.Flags             = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.hInstance         = GetModuleHandle( NULL );
		ofn.hwndOwner         = hwnd;
		ofn.lpstrCustomFilter = 0;
		ofn.lpstrFile         = filename;
		ofn.lpstrFileTitle    = 0;
		ofn.lStructSize       = sizeof( ofn );
		ofn.nMaxFile          = MAX_PATH;
		switch (lParam)
		{
		case 1:
			ofn.lpstrFilter		  = U("UEFS Files ( *.spj )\0*.spj\0");
			ofn.lpstrTitle		  = U("UEFS - Open File to Join");
			break;
		case 0:
			ofn.lpstrFilter			= U("All Files ( *.* )\0*.*\0");
			ofn.lpstrTitle			= U("UEFS - Open File to Split");
			break;
		case 2:
			ofn.lpstrFilter			= U("All Files ( *.* )\0*.*\0");
			ofn.lpstrTitle			= U("UEFS - Open File to Encrypt");
			break;
		case 3:
			ofn.lpstrFilter			= U("UEFS Files ( *.enc )\0*.enc\0");
			ofn.lpstrTitle			= U("UEFS - Open File to Decrypt");
			break;
		}
		
		if( !GetSaveFileName( &ofn ) )
		{
			delete [] filename;
			return 0;
		}
		switch (lParam)
		{
		case 1:
			SetWindowText( hwnd, U("UEFS : Join Mode") );
			opMode=JOIN_MODE;
			objoin.setfName(filename);
			break;
		case 0:
			SetWindowText( hwnd, U("UEFS : Split Mode") );
			fileS = getfileSize(filename );
			obsplit.fSize(fileS);
			opMode=SPLIT_MODE;
			obsplit.setfName(filename);

			break;
		case 2:
			SetWindowText( hwnd, U("UEFS : Encryption Mode") );
			opMode=ENCRYPT_MODE;
			obencrypt.setfName(filename);
			break;
		case 3:
			SetWindowText( hwnd, U("UEFS : Decryption Mode") );
			opMode=DECRYPT_MODE;
			obdecrypt.setfName(filename);
			break;
		}
				
		setFileInfoView(hwnd);
		pBar.reset();
		
		delete [] filename;
		return 1;
	}


	




	void setFileInfoView( HWND hwnd )
	{
		TCHAR *tSize	= new TCHAR[20];
		TCHAR oDir[MAX_PATH];
		TCHAR filename[MAX_PATH];
		char *fname =new char[MAX_PATH];
		char *oDir1 =new char[MAX_PATH];
		obsplit.pSize((long)partsSize( obsplit.fSize(), obsplit.nParts()));
		if(opMode==SPLIT_MODE)
		{
			getFormatSize( obsplit.fSize(), tSize );
			SetWindowText( GetDlgItem( hwnd, fs_filesize ), tSize );
			getFormatSize( partsSize( obsplit.fSize(), obsplit.nParts() ), tSize );
			SetWindowText( GetDlgItem( hwnd, fs_partsize ), tSize );
			swprintf(oDir,obsplit.getODir());
			SetWindowText( GetDlgItem( hwnd, fs_outputdir ), oDir );
			swprintf(filename,obsplit.getfName());
			SetWindowText( GetDlgItem( hwnd, fs_filename ), filename );
		}
		else if(opMode==JOIN_MODE)
		{
			getFormatSize( objoin.fSize(), tSize );
			getFormatSize( partsSize( objoin.fSize(), objoin.nParts() ), tSize );
			swprintf(oDir,objoin.getODir());
			SetWindowText( GetDlgItem( hwnd, fs_outputdir ), oDir );
			swprintf(filename,objoin.getfName());
			SetWindowText( GetDlgItem( hwnd, fs_filename ), filename );
		}
		else if(opMode==ENCRYPT_MODE)
		{
			swprintf(oDir,obencrypt.getoDir());
			swprintf(filename,obencrypt.getfName());
			SetWindowText( GetDlgItem( hwnd, fs_outputdir ), oDir );
			SetWindowText( GetDlgItem( hwnd, fs_filename ), filename );
		}
		else
		{
			swprintf(oDir,obdecrypt.getoDir());
			swprintf(filename,obdecrypt.getfName());
			SetWindowText( GetDlgItem( hwnd, fs_outputdir ), oDir );
			SetWindowText( GetDlgItem( hwnd, fs_filename ), filename );

		}
		objoin.pSize((long)partsSize( objoin.fSize(), objoin.nParts()));
		
		if( !obsplit.nParts() )
			SetWindowText( GetDlgItem( hwnd, fs_partsize ), U("Unknown") );

		delete [] tSize;

	}

	void doUIProgress( int iMode, int iProgress )
	{
		TCHAR *szCaption = new TCHAR[100];

		if( iMode == SPLIT_MODE )
			swprintf( szCaption, U(" Split Mode - %d %%"), iProgress ); 
		else if ( iMode == JOIN_MODE )
			swprintf( szCaption, U(" Join Mode - %d %%"), iProgress ); 
		else if ( iMode == ENCRYPT_MODE )
			swprintf( szCaption, U(" Encryption Mode - %d %%"), iProgress ); 
		else if ( iMode == DECRYPT_MODE )
			swprintf( szCaption, U(" Decryption Mode - %d %%"), iProgress ); 

		SetWindowText( motherHwnd, szCaption );

		delete [] szCaption;
	}

	
	int doMenuPopup( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		HMENU motherMen	 = CreateMenu();
		HMENU popupMen	 = CreatePopupMenu();
		RECT btnRect	 = {0};

		GetWindowRect( GetDlgItem( hwnd, fs_Menu ), &btnRect );

		AppendMenu( motherMen, MF_POPUP | MF_STRING, (UINT)popupMen, 0 );
		AppendMenu( popupMen, MF_STRING, fs_openfile, U("To Split") );
		AppendMenu( popupMen, MF_STRING, fs_openfiletojoin, U("To Join") );
		AppendMenu( popupMen, MF_STRING, fs_encrypt, U("To Encrypt") );
		AppendMenu( popupMen, MF_STRING, fs_decrypt, U("To Decrypt") );
		AppendMenu( popupMen, MF_SEPARATOR, 0, 0 );
		AppendMenu( popupMen, MF_STRING, fs_about, U("About") );
		
		TrackPopupMenu ( popupMen, 0, btnRect.left, btnRect.bottom - 1, 0, hwnd, 0 );
		DestroyMenu( motherMen );
		DestroyMenu( popupMen );
		return 1;
	}


	double partsSize( long double lFileSize, int iParts )
	{
		return ( lFileSize / iParts );
	}

	void getFormatSize( long double fSize, TCHAR *tRet )
	{
		TCHAR *szSuffix[]	= { U("bytes"), U("kb"), U("mb"), U("gb") };
		long iDividend[4]	= { 1, KB, MB, GB };
		int iIndex			= 0;
		long double iTotal	= 0;
		long iRemainder		= 0;

		if( fSize >= MB )
			iIndex = 2;
		else if( fSize >= GB )
			iIndex = 3;
		else if( fSize < KB )
			iIndex = 0;
		else 
			iIndex = 1;

		iTotal = fSize / iDividend[iIndex];
		swprintf( tRet, U("%.2Lf %s"), iTotal, szSuffix[iIndex] );
	}

	long getfileSize(TCHAR *wstr)
	{
			
		FILE *fPtr	= 0;
		long fSize	= 0;
		long curPos	= 0;

		fPtr = fileOpen( wstr, U("rb") );

		if( fPtr )
		{
			curPos = ftell( fPtr );
			fseek( fPtr, 0, SEEK_END );
			fSize = ftell( fPtr );
			fseek( fPtr, curPos, SEEK_SET );
			fclose( fPtr );
		}
		else return 0;

		return fSize;
	}

	int _ERROR( int iErr )
	{
		TCHAR *szErrMsg[] = {  

			U("Output Directory is not properly Set!!"),
			U("No File Chosen Yet!!"),
			U("Splitting of the File possible only in Split Mode!!"),
			U("Joining of the File possible only in Join Mode!!"),
			U("Please Choose an Output Directory\n before doing any actions!!"),
			U("Unable to Open File for Reading/Writing!!"),
			U("Problem Creating Joiner Batch File!!"),
			U("Error Occured While Creating File!!"),
			U("Error Creating SPL Joiner File!!"),
			U("Cannot Allocate Enough Memory!!"),
			U("Operation Cancelled!!"),
			U("Encryption of the File possible only in Encrypt Mode!!"),
			U("Decryption of the File possible only in Decrypt Mode!!"),
			U("No Operations Performed to Create Log Table!!"),
			U("File mismatch found. Can not Decrypt!!")
			U("Error connecting to the DataBase!!"),
			U("Failed to use the result acquired!!"),
			U("Failed to execute the query!!"),
			U("Failed to retrieve the Server Info String")
			
		};

		msgbox( motherHwnd, szErrMsg[iErr], U("Error") );

		return iErr;
	}



	int msgbox( HWND wnd, TCHAR *tMsg, TCHAR *tTitle )
	{
		MSGBOXPARAMS mParam;
		ZeroMemory( &mParam, sizeof( MSGBOXPARAMS ) );

		mParam.cbSize				= sizeof( MSGBOXPARAMS );
		mParam.hwndOwner			= wnd;
		mParam.hInstance			= (HINSTANCE)GetWindowLong( wnd, GWL_HINSTANCE );
		mParam.lpszText				= tMsg;
		mParam.lpszCaption			= tTitle;
		mParam.dwStyle				= MB_USERICON;
		mParam.lpszIcon				= MAKEINTRESOURCE( IDI_ICONSPLIT );
		mParam.dwContextHelpId		= NULL;
		mParam.lpfnMsgBoxCallback	= NULL;
		mParam.dwLanguageId			= LANG_ENGLISH;

   		return MessageBoxIndirect( &mParam );
	}

	void toAnsi( TCHAR *szStr )
	{
		TCHAR *szTmp	= new TCHAR[MAX_PATH];
		int iLen = wcslen( szStr );
		swprintf( szTmp, U("%s"), szStr );
		WideCharToMultiByte( CP_ACP, 0, (PWSTR)szTmp, iLen * ( sizeof( TCHAR ) ), (char *)szStr, iLen + 1, 0, 0 );
		delete [] szTmp;
	}



	void isOperating( bool bYes )
	{
		if( !bYes )
		{
			EnableWindow( GetDlgItem( motherHwnd, fs_split ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_join ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_parts ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_scroll ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_Menu ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_filename ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_outputdir ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_getdir ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_cencrypt ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_cdecrypt ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_log ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_cancel ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_exit ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_about ), 1 );
		}
		else
		{
			EnableWindow( GetDlgItem( motherHwnd, fs_split ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_join ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_parts ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_scroll ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_Menu ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_filename ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_outputdir ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_cancel ), 1 );
			EnableWindow( GetDlgItem( motherHwnd, fs_getdir ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_cencrypt ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_cdecrypt ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_log ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_exit ), 0 );
			EnableWindow( GetDlgItem( motherHwnd, fs_about ), 0 );
		}
	}


	void setFont( HWND wnd, TCHAR *font, int size )
	{
		HFONT f = CreateFont( size, 0, 0, 0, 0, false, false, 0, 0, 0, 0, 0, 0, font );
		SendMessage( wnd, WM_SETFONT, (WPARAM)f, true );
	}


	int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd )
	{
			InitCommonControls();
		DialogBox( hInstance, MAKEINTRESOURCE( fs_dlgsplit ), NULL, MainProc );	
			
			return 0;
	}
