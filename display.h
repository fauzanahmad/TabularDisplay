#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

enum
{
	RESET=0,
	RED,
	BOLD_RED,
	GREEN,
	BOLD_GREEN,
	YELLOW,
	BOLD_YELLOW,
	BLUE,
	BOLD_BLUE,
	MAGENTA,
	BOLD_MAGENTA,
	CYAN,
	BOLD_CYAN
};

char *szFormat[] = {"[0m","[0;31m","[1;31m","[0;32m","[1;32m","[0;33m","[1;33m","[0;34m","[1;34m","[0;35m","[1;35m","[0;36m","[1;36m"};

#define ON 1
#define OFF 0

#define CONSOLE_PRINT OFF
#define FILE_PRINT ON 

#define DEBUG_ON OFF

#define ENTRING_FUNCTION_STR "in function %s\n"
#define LEAVE_FUNCTION_STR "leaving function %s\n"

#define CHECK_NULL(X) X==NULL ? 1 : 0
#define CHECK_NOT_NULL(X) !CHECK_NULL(X)

char g_cDataSeperator;
char g_cJoint;
char g_cColoumn;
char g_cRow;
int *g_coloumns_len;
int g_iNumberOfColoumns = 0;
char g_szDataFileName[1024] = {0};

#define UPDATE_IF_GREATER(X,Y) if(X>Y) Y = X

int ReadSettingFile();
void SetData(char *szBuffer , char *data , int datatype);
void DrawLine();
void SetValues();
void ShrinkData(char **pcStart, char **pcEnd, char *szTemp, int size,char pcSeperator);
void DisplayData(struct Data *phead , struct Data *ptail);
void deleteall(struct Data **phead);
void insertlast(struct Data **phead,struct Data **plast,struct Data data);
void copystr(char *str1,char *str2,int len);
void writeinlogfile(char *szBuffer,...);
void PrintfColoums();
void FreeAllMemory();
