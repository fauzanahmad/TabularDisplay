#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>


#define ON 1
#define OFF 0

#define CONSOLE_PRINT OFF
#define FILE_PRINT ON 

#define DEBUG_ON ON

#define ENTRING_FUNCTION_STR "in function %s\n"
#define LEAVE_FUNCTION_STR "leaving function %s\n"

#define CHECK_NULL(X) X==NULL ? 1 : 0
#define CHECK_NOT_NULL(X) !CHECK_NULL(X)

/* indegree of zero degree vertext must be zero */
#define ZERO_DEGREE -1
#define NOT_ZERO_DEGREE 0

typedef struct vertext
{
        int iData;
	int iInDegree;
	int iOutDegree;
	struct edge *pEdAdjacentEdge;
        struct vertext *pVerNext;
}VERTEXT;

typedef struct edge
{
        struct vertext *pVerAdjcent;
        struct edge *pEdNext;
}EDGE;

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



/********************************************************** functions ***************************************************************************/
void writeinlogfile(char *szBuffer,...);
VERTEXT *InsertVertext(VERTEXT **,VERTEXT **,int,int);
void InsertAdjacentNode(VERTEXT **,VERTEXT**,VERTEXT**,int);
VERTEXT *FindVertext(VERTEXT*,int);
int PrintOption();
void display(VERTEXT*);
EDGE* findAdjecentnode(VERTEXT*,int);
/********************************************************** functions ***************************************************************************/

