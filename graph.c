#include "graph.h"

int main()
{
	VERTEXT *pVerStart = NULL;
	VERTEXT *pVerEnd = NULL;

	VERTEXT *pVerEntry = NULL;

	FILE *fptr = NULL;

	int iData = 0;

	writeinlogfile ( ENTRING_FUNCTION_STR, __FUNCTION__ );

#ifdef FILE_PRINT
	fptr = fopen ( "log.txt", "w" );
	if(CHECK_NULL(fptr))
	{
		printf ( "logfile file opening failed.\n" );
	}
	if( fptr )
		fclose ( fptr );
#endif

	while( 1 )
	{
		switch( PrintOption() )
		{
			case 1:
			{
				printf ( "Enter data you want to add : ");
				scanf ( "%d", &iData );

				if( 0 == iData )
				{
					writeinlogfile( "invlid data, data must be positive number\n" );
					return NULL;
				}
				pVerEntry = InsertVertext ( &pVerStart, &pVerEnd, iData, NOT_ZERO_DEGREE );
				InsertAdjacentNode ( &pVerStart, &pVerEnd, &pVerEntry, ON );
			}break;

			case 2:
			{

			}break;

			case 3:
			{
				display ( pVerStart );
			}break;

			case 4:
			{
				printf ( "Enter data you want to add : " );
				scanf ( "%d", &iData );

				if( 0 == iData )
				{
					writeinlogfile( "invlid data, data must be positive number\n" );
					return NULL;
				}
				pVerEntry = InsertVertext ( &pVerStart, &pVerEnd, iData, ZERO_DEGREE );
				if( NULL == pVerEntry )
						continue;
				InsertAdjacentNode ( &pVerStart, &pVerEnd, &pVerEntry, ON);
			}break;

			case 5:
			{
				goto LBL_EXIT;
			}break;
		}
	}

	LBL_EXIT:
	printf ( "exiting...\n" );

	ReleaseAllMemory ( &pVerStart, &pVerEnd );

	writeinlogfile ( LEAVE_FUNCTION_STR, __FUNCTION__ );

	return 0;
}

/*
 * display options and return the entered option value.
 */
int PrintOption()
{
	int iNum = 0;
	
	writeinlogfile( ENTRING_FUNCTION_STR , __FUNCTION__ );

	printf ( "1. Insert Vertex.\n" );
	printf ( "2. Delete Vertext.\n" );
	printf ( "3. Display Graph.\n" );
	printf ( "4. Add Zero Degree Vertext.\n" );
	printf ( "5. Quit.\n" );
	printf ( "Your option : " );
	scanf ( "%d", &iNum );

	writeinlogfile( LEAVE_FUNCTION_STR, __FUNCTION__ );

	return iNum;
}

VERTEXT* InsertVertext(VERTEXT **pVerHead,VERTEXT **pVerTail, int iData ,int zero_degree_flag)
{
	VERTEXT *pVerEntry = NULL;

	writeinlogfile ( ENTRING_FUNCTION_STR, __FUNCTION__ );

	if( ZERO_DEGREE == zero_degree_flag )
	{
			if( NULL != FindVertext ( *pVerTail, iData ))
			{
					printf( "Vertext is already present.\n" );
					return NULL;
			}
	}

	pVerEntry = (VERTEXT *) malloc ( sizeof( VERTEXT ));

	if( CHECK_NULL( pVerEntry ) )
	{
		writeinlogfile ( "malloc failed.\n" );
		return NULL;
	}

	pVerEntry->iData = iData;

	if( ZERO_DEGREE == zero_degree_flag )
	{
			pVerEntry->iInDegree = zero_degree_flag;
	}
	else if( NOT_ZERO_DEGREE == zero_degree_flag )
	{
		pVerEntry->iInDegree = 0;
	}
	pVerEntry->iOutDegree = 0;
	pVerEntry->pVerNext = NULL;
	pVerEntry->pEdAdjacentEdge = NULL;

	if( CHECK_NULL( *pVerHead ) && CHECK_NULL( *pVerTail ) )
	{
		(*pVerHead) = pVerEntry;
		(*pVerTail) = pVerEntry;
		writeinlogfile("Entered Vertet %d\n",iData);
	}
	else
	{
		(*pVerTail)->pVerNext = pVerEntry;
		(*pVerTail) = pVerEntry;
		writeinlogfile("Entered Vertext %d\n",iData);
	}

	writeinlogfile ( LEAVE_FUNCTION_STR, __FUNCTION__ );

	return pVerEntry;
}


void InsertAdjacentNode(VERTEXT **pVerHead ,VERTEXT **pVerTail,VERTEXT **pVerEntry,int iAvoidRecursionFlag)
{
	int iNumber = 0;
	int i = 0;
	int iVertext = 0;
	int iData = 0;
	EDGE *pEdgeVertext = NULL;
	EDGE *pEdgeTemp = NULL;
	VERTEXT *pVertex = NULL;
	VERTEXT *pVerNewVertext = NULL;

	writeinlogfile ( ENTRING_FUNCTION_STR, __FUNCTION__ );

	while ( 1 )
	{
		printf ( "How many Adjacent Vertext for %d : ", (*pVerEntry)->iData );
		scanf ( "%d", &iNumber );

		if( iNumber > 0 )
			break;
		else
		{
			printf ( "invalid entery please enter positive number\n" );
			writeinlogfile ( "invalid number for adjacent vertext for vertext : %d\n", (*pVerEntry)-> iData );
		}
	}

	pEdgeTemp = (*pVerEntry)-> pEdAdjacentEdge;
	
	while ( i < iNumber )
	{
		printf ( "Enter which vertext you want to put as a adjucent of %d : ", (*pVerEntry)-> iData );
		scanf ( "%d", &iData );

		if ( 0 == iData )
		{
			printf ( "Enter valid vertext\n" );
			continue;
		}

		if ( NULL != findAdjecentnode ( *pVerEntry, iData ) )
		{
				printf ( "already present as a adjacent, please insert another vertext number\n" );
				continue;
		}		
		
		pVertex = FindVertext ( *pVerHead, iData );

		if ( CHECK_NULL ( pVertex ) )
		{	
			pVertex = InsertVertext ( pVerHead, pVerTail, iData, NOT_ZERO_DEGREE );
			writeinlogfile ( "added new vertext to graph %d\n", iData );
		}
		if ( pVertex )
		{
			if ( pVertex-> iInDegree == ZERO_DEGREE )
			{
				printf ( "%d is zero degree vertext please innsert another vertext.\n", iData );
				continue;
			}

			pEdgeVertext = (EDGE *) malloc ( sizeof ( EDGE ) );

			if ( NULL == pEdgeVertext )
			{
				printf ( "malloc failed\n" );
				writeinlogfile ( "malloc failed in %s\n", __FUNCTION__ );
				return NULL;
			}
			else
			{
				pEdgeVertext-> pVerAdjcent = pVertex;
				pEdgeVertext-> pEdNext = NULL;

				if(pEdgeTemp)
				{
					pEdgeTemp-> pEdNext = pEdgeVertext;
					pEdgeTemp = pEdgeVertext;
					writeinlogfile ( "Added adjacent node to %d\n", pVertex-> iData );
				}
				else
				{
					(*pVerEntry)-> pEdAdjacentEdge = pEdgeVertext;
					pEdgeTemp = pEdgeVertext;
					writeinlogfile ( "Added first adjacent node to %d\n", pVertex->iData );
				}
				pVertex->iInDegree += 1;
				(*pVerEntry)->iOutDegree += 1;
			}
		}		
		i++;
	}	

	if ( iAvoidRecursionFlag )
	{
		pVertex = (*pVerHead)-> pVerNext;
		while ( pVertex )
		{
			if ( pVertex-> iOutDegree == 0 )
			{
				writeinlogfile ( "adding adjacent nodes for vertext %d\n", pVertex-> iData );
				InsertAdjacentNode ( pVerHead, pVerTail, &pVertex, OFF );
			}
			pVertex = pVertex-> pVerNext;
		}
	}

	writeinlogfile ( LEAVE_FUNCTION_STR, __FUNCTION__ );
}

VERTEXT *FindVertext ( VERTEXT *pVerStart, int iData )
{
	while ( pVerStart ) 
	{
		if( iData == pVerStart-> iData )
				return pVerStart;
		pVerStart = pVerStart->pVerNext;
	}
	return NULL;
}

void display( VERTEXT *pVerHead )
{
	writeinlogfile ( ENTRING_FUNCTION_STR, __FUNCTION__ );

	EDGE *pEdPtr = NULL;

	printf ( "--- node --- --- adjacent node ---\n" );
	while ( pVerHead )
	{
		printf( "\n   %d      -->",pVerHead-> iData );
		
		pEdPtr = pVerHead-> pEdAdjacentEdge;
		while ( pEdPtr )
		{
			printf( " %d ", pEdPtr->pVerAdjcent-> iData );
			pEdPtr = pEdPtr-> pEdNext;
		}
		pVerHead = pVerHead-> pVerNext;
	}
	printf( "\n------------------------------------\n" );

	writeinlogfile ( LEAVE_FUNCTION_STR, __FUNCTION__ );
}

/*
 * will show log in both file/consol
 */
void writeinlogfile( char *szFormatBuffer, ...)
{

#if DEBUG_ON

        char szBuffer[1001] = {0};

        #if FILE_PRINT
                FILE *fptr = NULL;
                fptr = fopen ( "log.txt", "a" );

                if ( CHECK_NULL ( fptr ) )
                {
                        printf ( "log file opening failed\n" );
                        return;
                }
        #endif


        va_list valist;
        va_start ( valist, szFormatBuffer );
        vsnprintf ( szBuffer, sizeof ( szBuffer ), szFormatBuffer, valist );

        va_end ( valist );

        #if CONSOLE_PRINT
                printf( "%s\n", szBuffer );
        #endif

        #if FILE_PRINT
                fputs( szBuffer, fptr );
                fclose( fptr );
        #endif

#endif

}

void ReleaseAllMemory( VERTEXT **pVerStart, VERTEXT **pVerEnd )
{
	EDGE *pEdge = NULL;
	VERTEXT* pVertext = NULL;

	writeinlogfile ( ENTRING_FUNCTION_STR, __FUNCTION__ );

	pVertext = *pVerStart;
	while ( pVertext )
	{
		/* --- delete adjacent vertext --- */
		pEdge = pVertext->pEdAdjacentEdge;
		while ( pEdge )
		{
			pEdge = pVertext->pEdAdjacentEdge;
			pVertext->pEdAdjacentEdge = pEdge->pEdNext;

			writeinlogfile ( "deleating %d adjacent vertext of %d\n", pEdge->pVerAdjcent-> iData, pVertext-> iData );

			
			pEdge-> pVerAdjcent = NULL;
			pEdge-> pEdNext = NULL;
			free ( pEdge );
						
			pEdge = pVertext-> pEdAdjacentEdge;
		}
		pVertext = pVertext-> pVerNext;
	}

	pVertext = *pVerStart;
	while ( pVertext )
	{
        (*pVerStart) = pVertext->pVerNext;

		writeinlogfile ( "deleating vertex %d\n", pVertext-> iData );

        pVertext-> pEdAdjacentEdge = NULL;
        pVertext-> pVerNext        = NULL;
        free ( pVertext );
		
		pVertext = (*pVerStart);
	}

	pVerStart = pVerEnd = NULL;

	writeinlogfile ( LEAVE_FUNCTION_STR, __FUNCTION__ );
}

EDGE* findAdjecentnode ( VERTEXT* pVerStart, int iData )
{
	EDGE *pEdPtr = pVerStart->pEdAdjacentEdge;

	writeinlogfile ( ENTRING_FUNCTION_STR, __FUNCTION__ );
	
	while ( pEdPtr )
	{
			if ( pEdPtr-> pVerAdjcent-> iData == iData )
			{
					writeinlogfile ( "found adjacent vertext %d in %d\n", iData, pVerStart-> iData);
					return pEdPtr;
			}
			pEdPtr = pEdPtr-> pEdNext;
	}
	writeinlogfile ( "%d is not present in vertext list of %d\n", iData, pVerStart-> iData );
	writeinlogfile ( LEAVE_FUNCTION_STR, __FUNCTION__ );
	return NULL;
}
