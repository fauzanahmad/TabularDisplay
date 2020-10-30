#include "display.h"

int main()
{

#if FILE_PRINT
	FILE *fptr = fopen("log.txt","w");
	if(CHECK_NULL(fptr))
	{
		printf("log file opening failed");
	}
	if(fptr)
		fclose(fptr);
#endif

	writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	if(ReadSettingFile() == 0)
	{	
		SetValues();
		FreeAllMemory();
	}

        writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);

	return 0;
}

void ShrinkData(char **pcStart, char **pcEnd, char *szTemp, int size , char cSeperator)
{

        writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	*pcEnd = strchr(*pcStart,cSeperator);
	if( CHECK_NULL(*pcEnd ))
	{
		printf("No proper data format");
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

	if(CHECK_NULL(fptr))
	{
		printf("data file opening failed.\n");
		return;
	}

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
			szBuffer[0] = g_cColoumn;
			szBuffer[1] = ' ';
			strcpy(szBuffer+2,szTemp);			
			ilen = strlen(szTemp);
						
			memset(szBuffer+ilen+2,' ',g_coloumns_len[iCounter]+1 - ilen);		

			if(iCounter == g_iNumberOfColoumns-1)
			{
				szBuffer[g_coloumns_len[iCounter]+3] = g_cColoumn;
				szBuffer[g_coloumns_len[iCounter]+4] = '\0';
				printf("%s\n",szBuffer);
			}
			else
				printf("%s",szBuffer);
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

	while(i < g_iNumberOfColoumns)
	{
		szBuffer[0] = g_cJoint;
		memset(szBuffer+1,(int)g_cRow,g_coloumns_len[i]+2);
		
		if(i+1 == g_iNumberOfColoumns)
			szBuffer[g_coloumns_len[i]+3] = g_cJoint;

		printf("%s",szBuffer);
		memset(szBuffer,0x00,sizeof(szBuffer));
		i++;
	}
	printf("\n");
        writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);
}



int ReadSettingFile()
{
	FILE *fptr = fopen("setting.txt","r");
	char szBuffer[5001] = {0};
	char *pcStart = NULL;
	char *pcEnd = NULL;
	char szTemp[25] = {0};
	int colcount = 0;
	int iCounter = 0;
	int ilen = 0;
	int iflag = 0;

        writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	if(CHECK_NULL(fptr))
	{
		printf("setting file opening failed.\n");
		return -1;
	}

	while( !feof(fptr))
	{
		memset(szBuffer,0x00,sizeof(szBuffer));
		fgets(szBuffer,sizeof(szBuffer),fptr);

		if(strstr(szBuffer,"set_coloumns"))
		{
			pcStart = strchr(szBuffer,'<');
			pcEnd = strchr(pcStart,'>');

			while(1)
			{
				if( CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd) )
				{
					if( (pcEnd-pcStart) > 1 )
						colcount++;
					else
						break;
				}
				else
					break;

				pcStart = strchr(pcEnd,'<');
				if(CHECK_NOT_NULL(pcStart))
					pcEnd = strchr(pcStart,'>');
				else
					break;
			}


			if(colcount)
			{
				g_iNumberOfColoumns = colcount;
				g_coloumns_len = (int *) malloc(colcount);
				
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

						iCounter++;
					}
					pcStart = pcEnd+1;
				}
			}
			else
			{
				iflag = 1;
				printf("coloumns not properly specified\n");
			}
		}
		else if(strstr(szBuffer,"set_joint"))
		{
			pcStart = strchr(szBuffer,'<');
			pcEnd = strchr(pcStart,'>');

			if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd) )
			{
				if(( pcEnd - pcStart ) > 1  )
				{
					memset(szTemp,0x00,sizeof(szTemp));
					pcStart +=1;
					strncpy(szTemp,pcStart,pcEnd-pcStart);
					g_cJoint = szTemp[0];
				}
				else
				{
					iflag = 1;
					printf("join for coloumn and row is not specified\n");
				}
			}
			pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"set_coloumn"))
		{
			pcStart = strchr(szBuffer,'<');
                	pcEnd = strchr(pcStart,'>');

                	if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd) )
			{
				if(( pcEnd - pcStart ) > 1 )
	               		{
		                        memset(szTemp,0x00,sizeof(szTemp));
					pcStart +=1;
                		        strncpy(szTemp,pcStart,pcEnd-pcStart);
                        		g_cColoumn = szTemp[0];
	        	        }
				else
                	        {
					iflag = 1;
                        	        printf("coloumn charecter is not specified\n");
                        	}
			}
			pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"data_seperator"))
		{
			pcStart = strchr(szBuffer,'<');
                	pcEnd = strchr(pcStart,'>');

                	if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd))
			{
				if((pcEnd-pcStart)>1)
	                	{
        	               		memset(szTemp,0x00,sizeof(szTemp));
					pcStart += 1;
                        		strncpy(szTemp,pcStart,pcEnd-pcStart);
	                        	g_cDataSeperator = szTemp[0];
                		}
				else
                        	{
					iflag = 1;
                                	printf("data seperator charecter is not specified\n");
        	                }
			}
			pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"set_row"))
		{
			pcStart = strchr(szBuffer,'<');
                        pcEnd = strchr(pcStart,'>');

                        if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd) )
			{
				if((pcEnd-pcStart)>1) 
                        	{
                        	        memset(szTemp,0x00,sizeof(szTemp));
                        	        pcStart += 1;
                        	        strncpy(szTemp,pcStart,pcEnd-pcStart);
                        	        g_cRow = szTemp[0];
                         
                        	}
                        	else
                        	{
					iflag = 1;
                        	        printf("row charecter is not specified\n");
                        	}
			}
                        pcStart = pcEnd+1;
		}
		else if(strstr(szBuffer,"file_name"))
		{
			pcStart = strchr(szBuffer,'<');
			pcEnd = strchr(pcStart,'>');

			if(CHECK_NOT_NULL(pcStart) && CHECK_NOT_NULL(pcEnd) )
			{
			 	if(	(pcEnd-pcStart)>1)
				{
					memset(szTemp,0x00,sizeof(szTemp));
					pcStart += 1;
					strncpy(szTemp,pcStart,pcEnd-pcStart);
					strcpy(g_szDataFileName,szTemp);
				}
                        	else
                        	{
					iflag = 1;
                        	        printf("file name is not specified\n");	
        	                }
			}
			pcStart = pcEnd+1;
		}
	}
	fclose(fptr);

	if(!iflag)
	{
		fptr = fopen(g_szDataFileName,"r");

		if(CHECK_NULL(fptr))
		{
			printf("data file opening failed.\n");
			return -1;
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
	}
	else
	{
		printf("\n\n\n ------------------------------------------------------------------------------------------\n\n\n");
		printf("settings you provided is wrong\n");
		printf("please read README.txt file for reference\n");
		printf("\n\n\n ------------------------------------------------------------------------------------------\n\n\n");
	}


        writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);

	return iflag;

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
		printf("settings file opening failed.\n");
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

					szMainBuffer[0] = g_cColoumn;
					szMainBuffer[1] = ' ';
					strcpy(szMainBuffer+2,szTemp);

					memset(szMainBuffer+ilen+2,' ',g_coloumns_len[icolcount]+1 - ilen);

					if(icolcount+1 == g_iNumberOfColoumns)
						szMainBuffer[g_coloumns_len[icolcount]+3] = g_cColoumn;
                                }
                                pcStart = pcEnd+1;

				printf("%s",szMainBuffer);
				memset(szMainBuffer,0x00,sizeof(szMainBuffer));

				icolcount++;
                        }
                }
	}
	fclose(fptr);
	printf("\n");	
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
			printf("log file opening failed\n");
			return;
		}
	#endif

	
	va_list valist;
	va_start(valist,szFormatBuffer);
	vsnprintf(szBuffer,sizeof(szBuffer),szFormatBuffer,valist);
	
	va_end(valist);

	#if CONSOLE_PRINT
		printf("%s\n",szBuffer);
	#endif

	#if FILE_PRINT
		fputs(szBuffer,fptr);
		fclose(fptr);
	#endif

#endif

}

void FreeAllMemory()
{
	writeinlogfile(ENTRING_FUNCTION_STR,__FUNCTION__);

	if(CHECK_NOT_NULL(g_coloumns_len))
		free(g_coloumns_len);

	writeinlogfile(LEAVE_FUNCTION_STR,__FUNCTION__);
}
