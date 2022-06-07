#include<iostream>
#include "display.h"

using namespace std;

int main()
{

#if FILE_PRINT
	FILE *fptr = fopen("log.txt","w");
	if(CHECK_NULL(fptr))
	{
		std::cout << "file opening failed" << endl;
	}
	fclose(fptr);
#endif

	writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	ReadSettingFile();
	SetValues();

        writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);

	return 0;
}

void ShrinkData(char **pcStart, char **pcEnd, char *szTemp, int size , char cSeperator)
{

    writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	*pcEnd = strchr(*pcStart,cSeperator);
	if( CHECK_NULL(*pcEnd ))
	{
		std::cout << "No proper data format" << endl;
		return;
	}
	memset(szTemp,0x00,size);
	strncpy( szTemp , *pcStart, *pcEnd - *pcStart);
	*pcStart = *pcEnd+1;

    writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);

}

void SetValues()
{
	FILE *fptr = fopen(g_szDataFileName,"r");
	char szBuffer[512] = {0};
	char *pcStart = NULL;
	char *pcEnd = NULL;
	char szTemp[51] = {0};
	char szBufferMax [1025] = {0};
	int iCounter = 0;
	int ilen = 0;

    writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	DrawLine();	
	PrintfColoums();
	DrawLine();

	while( !feof( fptr ) )
	{
		pcStart = fgets(szBufferMax, sizeof(szBuffer),fptr);

		if(NULL == pcStart)
			break;

		for ( iCounter = 0 ; iCounter < g_iNumberOfColoumns ; iCounter++)
		{
			memset(szBuffer,0x00,sizeof(szBuffer));
			ShrinkData(&pcStart,&pcEnd,szTemp,sizeof(szTemp),g_cDataSeperator);
			cout << RED << g_cColoumn << RESET << ' ';
			cout << GREEN << szTemp << RESET;

			ilen = strlen(szTemp);
			
			printSpace(g_coloumns_len[iCounter]-ilen);
			//memset(szBuffer+ilen+2,' ',g_coloumns_len[iCounter]+1 - ilen);

			if(iCounter == g_iNumberOfColoumns-1)
			{
				//szBuffer[g_coloumns_len[iCounter]+3] = g_cColoumn;
				//szBuffer[g_coloumns_len[iCounter]+4] = '\0';
				//std::cout << szBuffer << endl;

				cout << RED << g_cColoumn << RESET;
				cout << endl;
			}
			else
			{
				std::cout << GREEN << szBuffer << RESET;
			}
		}	
	}
	fclose(fptr);

	DrawLine();

    writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);
}

void DrawLine()
{
	int i = 0;
	char szBuffer[1025] = {0};

    writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);	

	std::cout << RED;
	while(i < g_iNumberOfColoumns)
	{
		szBuffer[0] = g_cJoint;
		memset(szBuffer+1,(int)g_cRow,g_coloumns_len[i]+2);
		
		if(i+1 == g_iNumberOfColoumns)
			szBuffer[g_coloumns_len[i]+3] = g_cJoint;
		std::cout << szBuffer;
		memset(szBuffer,0x00,sizeof(szBuffer));
		i++;
	}
	std::cout << RESET;
	std::cout << endl;
    writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);
}


void ReadSettingFile()
{
	FILE *fptr = fopen("setting.txt","r");
	char szBuffer[5001] = {0};
	char *pcStart = NULL;
	char *pcEnd = NULL;
	char szTemp[25] = {0};
	int colcount = 0;
	int iCounter = 0;
	int ilen = 0;

        writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	if(CHECK_NULL(fptr))
	{
		std::cout << "setting file opening failed.\n" << endl;
		return;
	}

	while( !feof(fptr))
	{
		memset(szBuffer,0x00,sizeof(szBuffer));
		fgets(szBuffer,sizeof(szBuffer),fptr);
		if(strstr(szBuffer,"set_coloumns"))
		{
			pcStart = strchr(szBuffer,'<');

			while(1)
			{
				if( CHECK_NOT_NULL(pcStart) && strchr(pcStart,'>'))
					colcount++;
				else
					break;

				pcStart = strchr(pcStart+1,'<');

			}
			g_iNumberOfColoumns = colcount;
			g_coloumns_len = (int *) malloc(colcount);
			g_Columns = (char **) malloc(colcount * sizeof(char *));

			pcStart = szBuffer;
			while(colcount--)
			{
				pcStart = strchr(pcStart,'<');
				pcEnd = strchr(pcStart,'>');
			
				if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
				{
					memset(szTemp,0x00,sizeof(szTemp));
					pcStart +=1; 
					strncpy(szTemp,pcStart,pcEnd-pcStart);

					ilen = strlen(szTemp);
					UPDATE_IF_GREATER(ilen,g_coloumns_len[iCounter]);

					g_Columns[iCounter] = (char *)malloc(ilen+1);
					iCounter++;
				}
				pcStart = pcEnd+1;
			}
		}
		else if(strstr(szBuffer,"set_joint"))
		{
			pcStart = strchr(szBuffer,'<');
			pcEnd = strchr(pcStart,'>');

			if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
			{
				memset(szTemp,0x00,sizeof(szTemp));
				pcStart +=1;
				strncpy(szTemp,pcStart,pcEnd-pcStart);
				g_cJoint = szTemp[0];
			}
			pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"set_coloumn"))
		{
			pcStart = strchr(szBuffer,'<');
                	pcEnd = strchr(pcStart,'>');

                	if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
               		{
	                        memset(szTemp,0x00,sizeof(szTemp));
				pcStart +=1;
                	        strncpy(szTemp,pcStart,pcEnd-pcStart);
                        	g_cColoumn = szTemp[0];
        	        }
			pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"data_seperator"))
		{
			pcStart = strchr(szBuffer,'<');
                	pcEnd = strchr(pcStart,'>');

                	if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
	                {
        	                memset(szTemp,0x00,sizeof(szTemp));
				pcStart += 1;
                        	strncpy(szTemp,pcStart,pcEnd-pcStart);
	                        g_cDataSeperator = szTemp[0];
                	}
			pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"set_row"))
		{
			pcStart = strchr(szBuffer,'<');
                        pcEnd = strchr(pcStart,'>');

                        if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
                        {
                                memset(szTemp,0x00,sizeof(szTemp));
                                pcStart += 1;
                                strncpy(szTemp,pcStart,pcEnd-pcStart);
                                g_cRow = szTemp[0];
                         
                        }
                        pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"file_name"))
		{
			pcStart = strchr(szBuffer,'<');
			pcEnd = strchr(pcStart,'>');

			if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
			{
				memset(szTemp,0x00,sizeof(szTemp));
				pcStart += 1;
				strncpy(szTemp,pcStart,pcEnd-pcStart);
				strcpy(g_szDataFileName,szTemp);
			}
			pcStart = pcEnd+1;
		}
	}
	fclose(fptr);


	fptr = fopen(g_szDataFileName,"r");

	if(CHECK_NULL(fptr))
	{
		std::cout << "file opening failed.\n" << endl;
		return;
	}

	while( !feof( fptr ) )
        {
		memset(szBuffer,0x00,sizeof(szBuffer));
                pcStart = fgets(szBuffer, sizeof(szBuffer),fptr);

                if(NULL == pcStart)
                        break;

                for ( iCounter = 0 ; iCounter < g_iNumberOfColoumns ; iCounter++)
                {
                        ShrinkData(&pcStart,&pcEnd,szTemp,sizeof(szTemp),g_cDataSeperator);
                        UPDATE_IF_GREATER(strlen(szTemp),g_coloumns_len[iCounter]);
                }

        }
        fclose(fptr);

        writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);

}

void PrintfColoums()
{	
	FILE *fptr = fopen("setting.txt","r");
	char szBuffer[1024] = {0};
	char szMainBuffer[1025] = {0};
	char *pcStart = NULL , *pcEnd = NULL;
	char szTemp[512] = {0};
	int icolcount = 0;
	int ilen = 0;

	writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	if(CHECK_NULL(fptr))
	{
		std::cout << ("file opening failed.\n");
		return;
	}

	while( !feof(fptr))
    {
	    memset(szBuffer,0x00,sizeof(szBuffer));
        fgets(szBuffer,sizeof(szBuffer),fptr);
        if(strstr(szBuffer,"set_coloumns"))
        {
            pcStart = szBuffer;
        	while(icolcount < g_iNumberOfColoumns)
            {
                pcStart = strchr(pcStart,'<');
            	pcEnd = strchr(pcStart,'>');

                if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
                {
                	memset(szTemp,0x00,sizeof(szTemp));
					pcStart +=1;
					strncpy(szTemp,pcStart,pcEnd-pcStart);
					ilen = strlen(szTemp);

					std::cout << RED << g_cColoumn << ' ' << RESET;
					std::cout << BLUE << szTemp << RESET;
					printSpace(g_coloumns_len[icolcount] - ilen);

					if(icolcount+1 == g_iNumberOfColoumns)
						std::cout << RED << g_cColoumn << RESET;
				}
                pcStart = pcEnd+1;

				//std::cout << ("%s", szMainBuffer);

				icolcount++;
           }
        }
	}
	fclose(fptr);
	std::cout << ("\n");	
	writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);
}

void writeinlogfile(char *szFormatBuffer,...)
{
	
#if DEBUG_ON
	
	char szBuffer[1001] = {0};

	#if FILE_PRINT
		FILE *fptr = NULL;
		fptr = fopen("log.txt","a");

		if(CHECK_NULL(fptr))
		{
			std::cout << ("log file opening failed\n");
			return;
		}
	#endif

	
	va_list valist;
	va_start(valist,szFormatBuffer);
	vsnprintf (szBuffer,sizeof(szBuffer),szFormatBuffer,valist);
	
	va_end(valist);

	#if CONSOLE_PRINT
		std::cout << ("%s\n",szBuffer);
	#endif

	#if FILE_PRINT
		fputs(szBuffer,fptr);
		fclose(fptr);
	#endif

#endif

}

void printSpace(int i)
{
	while (i>=0)
	{
		cout << ' ';
		i--;
	}
}
