#ifndef LOG_H
#define LOG_H
#include"headers.h"


void writelog ( MYSQL *handle, int mode, TCHAR *filename, long size, long partsize, int numparts) 
{ 

toAnsi(filename);
MYSQL_RES *res=NULL; // result of querying for all rows in table 
MYSQL_ROW row; // one row returned 
char sql[1024]; // sql statement used to get all rows 
int i,y=0,numf=0; 
const char *sinf=NULL;// number of fields returned from the query 
handle = mysql_init(NULL);

	if (mysql_real_connect(handle,SERVER_NAME,DB_USER,DB_USERPASS,DB_NAME,0,NULL,0)==NULL) 
	{ 
		_ERROR(ERR_DBCONNECTION);
		return;
	} 
	else 
	{	 
		sinf = mysql_get_server_info(handle); 
		if (sinf != NULL) 
		{ 
			
			if(mode==1)
			sprintf(sql,"insert into log (mode,filename,size,numparts,partsize) values ('%s','%s',%d,%d,%d);","Split",filename,size,numparts,partsize); 
			else
			sprintf(sql,"insert into log (mode,filename,size,numparts,partsize) values ('%s','%s',%d,%d,%d);","Join",filename,size,numparts,partsize); 

			if (!mysql_query(handle,sql)) 
			{ 
				res = mysql_store_result(handle); 
				if (!res) 
				{ 
				mysql_free_result(res); 
				goto cleanup;
				} 
				else 
				{ 
		
					_ERROR(ERR_RSLTACQRFAILED);
				return;
	
				} 
			} 
			else 
			{ 
				_ERROR(ERR_EXEQUERYFAILED);
				return;

			} 

		} 
		else 			
		{ 
				_ERROR(ERR_SISRETFAILED);
				return;
		} 

	
	}
cleanup:
	mysql_close(handle); 
return; 
} 

void writelog ( MYSQL *handle, int mode, TCHAR *filename) 
{ 

toAnsi(filename);
MYSQL_RES *res=NULL; // result of querying for all rows in table 
MYSQL_ROW row; // one row returned 
char sql[1024]; // sql statement used to get all rows 
int i,y=0,numf=0; 
const char *sinf=NULL;// number of fields returned from the query 


	handle = mysql_init(NULL);

	if (mysql_real_connect(handle,SERVER_NAME,DB_USER,DB_USERPASS,DB_NAME,0,NULL,0)==NULL) 
	{ 
		_ERROR(ERR_DBCONNECTION);
		return;
	} 
	else 
	{	 
		sinf = mysql_get_server_info(handle); 
		if (sinf != NULL) 
		{ 
			
			if(mode==3)
				sprintf(sql,"insert into log (mode,filename) values ('%s','%s');","Encrypt",filename);//,size,numparts,partsize); 
			else
				sprintf(sql,"insert into log (mode,filename) values ('%s','%s');","Decrypt",filename);

		if (!mysql_query(handle,sql)) 
{ 
	res = mysql_store_result(handle); 
	if (!res) 
	{ 
			mysql_free_result(res); 
	} 
	else 
	{ 
		_ERROR(ERR_RSLTACQRFAILED);
		return;
	
	} 
} 
else 
{ 
	_ERROR(ERR_EXEQUERYFAILED);
	return;
} 

} 
		else 			
		{ 
			_ERROR(ERR_SISRETFAILED);
			return;
		} 

	mysql_close(handle); 
		}
return; 
} 


#endif