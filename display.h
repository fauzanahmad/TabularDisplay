#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

#define ON 1
#define OFF 0

#define CONSOLE_PRINT OFF
#define FILE_PRINT OFF 

#define DEBUG_ON ON

/*
Black: \e[30m.
Red: \e[31m.
Green: \e[32m.
Yellow: \e[33m.
Blue: \e[34m.
Magenta: \e[35m.
Cyan: \e[36m.
White: \e[37m
*/

#define BOLD	"\e[1m"
#define ITELLIC	"\e[2m"
#define RESET   "\e[0m"
#define BLACK	"\e[0;30m"
#define RED     "\e[0;31m"
#define GREEN    "\e[0;32m"
#define YELLOW	"\e[0;33m"
#define BLUE	"\e[0;34m"
#define MAGENTA	"\e[0;35m"
#define CYAN    "\e[0;36m"
#define WHITE	"\e[0;37m"


#define ENTRING_FUNCTION_STR "in function %s\n"
#define LEAVE_FUNCTION_STR "leaving function %s\n"

#define CHECK_NULL(X) X==NULL ? 1 : 0
#define CHECK_NOT_NULL(X) !CHECK_NULL(X)

char g_cDataSeperator;
char g_cJoint;
char g_cColoumn;
char g_cRow;
char **g_Columns;
int *g_coloumns_len;
int g_iNumberOfColoumns = 0;
char g_szDataFileName[1024] = {0};

#define UPDATE_IF_GREATER(X,Y) if(X>Y) Y = X

void ReadSettingFile();
void SetData(char *szBuffer , char *data , int datatype);
void DrawLine();
void SetValues();
void ShrinkData(char **pcStart, char **pcEnd, char *szTemp, int size,char pcSeperator);
void DisplayData(struct Data *phead , struct Data *ptail);
void writeinlogfile(char *szBuffer,...);
void PrintfColoums();
void printSpace(int i);
