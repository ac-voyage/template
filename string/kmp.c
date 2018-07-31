/* KMP, by Abreto<m@abreto.net>. */
#include <string.h>

/* !!NEED IMPROVING!! */

#define MAXL	(1000010)

char W[MAXL], T[MAXL];
int f[MAXL];
int lW, lT;

int count(void)
{
	int cnt = 0;
	int i, j;
	lW = strlen(W); lT = strlen(T);
	// -- self-matching
	f[0] = j = -1;
	for(i = 1;i < lW;i++)
	{
		while( j >= 0 && W[j+1] != W[i] )
			j = f[j];
		if( W[j+1] == W[i] ) j++;
		f[i] = j;
	}
	// ---
	j = -1;
	for(i = 0;i < lT;i++)
	{
		while( j >= 0 && W[j+1] != T[i] )
			j = f[j];
		if( W[j+1] == T[i] ) j++;
		if( j == lW-1 )
		{
			cnt++;
			j = f[j];
		}
	}
	return cnt;
}
