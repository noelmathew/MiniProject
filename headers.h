#ifndef HEADERS_H
#define HEADERS_H

	#define UNICODE

	#include<iostream>
	#include<fstream.h>
	#include<cmath>
	#include<shlobj.h>
	#include<shellapi.h>
	#include<shlwapi.h>
	#include<stdlib.h>
	#include<stdio.h>
	#include<windows.h>
	#include"resource.h"
	#include<commctrl.h>
	#include<time.h>
	#include<tchar.h>
	#include<io.h>
	#include"progressbar.h"
	#include <stdio.h> 
	#include "mysql.h" 


	#ifdef UNICODE

	 #define U(str) TEXT(str)
	 #define fileOpen( fname, pm ) _wfopen( fname, pm )
	 #define filePuts( szC, fp ) fputws( szC, fp )

	#else

	 #define U(str) (str)
	 #define fileOpen( fname, pm ) fopen( fname, pm )
	 #define filePuts( szC, fp ) fputs( szC, fp )

	#endif


	#define ERR_EMTYDIR 0
	#define ERR_NOFILE 1
	#define ERR_JOINMODE 2
	#define ERR_SPLITMODE 3
	#define ERR_GETDIR 4
	#define ERR_READINGFILE 5
	#define ERR_BATCHFILE 6
	#define ERR_FILECREATION 7
	#define ERR_SPLITITJOINER 8
	#define ERR_OUT_OF_MEMORY 9
	#define ERR_ACTION_CANCELLED 10
	#define ERR_ENCRYPT 11
	#define ERR_DECRYPT 12
	#define ERR_LOGNOTCREATED 13
	#define ERR_FILEMISMATCH 14
	#define ERR_DBCONNECTION 15
	#define ERR_RSLTACQRFAILED 16
	#define ERR_EXEQUERYFAILED 17
	#define ERR_SISRETFAILED 18
	 
	#define SPLIT_MODE 1
	#define JOIN_MODE 2
	#define	ENCRYPT_MODE 3
	#define DECRYPT_MODE 4

	#define KB 1024
	#define MB 1048526
	#define GB 1073741824

	

// change these to suit your setup 
	#define TABLE_OF_INTEREST "log" 
	#define SERVER_NAME "localhost" 
	#define DB_USER "root" 
	#define DB_USERPASS "pg123098" 
	#define DB_NAME "uefs" 
	
 // mysql connection handle 


	

#endif