

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE  256

void initialMap(int map[], int len)
{
	int  i = 0;

	for(i = 0; i < len; i++)
	{
		map[i] = -1;
	}
}

int get_next(int next[], char *ptr, int plen)
{
	int		k = -1;
	int		q = 0;
	next[0] = -1;
	
	for (q = 1; q < plen ; q++)
	{
		while( k > -1 && ptr[k+1] != ptr[q])
		{
			k = next[k];
		}
		if(ptr[k+1] == ptr[q])
		{
			k ++;
		}
		next[q] = k;
	}
}


int kmp(char * str, int len, char *ptr, int plen)
{
	int * next;
	int   q = 0 ;
	int	  k = -1;
	next = (int * )malloc(plen * sizeof(int));
	initialMap(next, plen);	
	get_next(next, ptr, plen);
	
	for( q = 0; q < len; q ++)
	{
		while ( k > -1 && ptr [k + 1]  != str[q])
		{
			k = next[k];
		}
		if(ptr[k+1] == str[q])
		{
			k ++;
		}

		if( k == plen - 1 )
		{
			// k = -1
			// q = q - plen + 1;  // 定位到之前的字符串位置的下一位，这样可以找出重叠的子字符串
			return q - plen + 1;
			//return q - k;
		}
		
	}
	

	
	return -1;
}

int main()
{
	char str[BUFF_SIZE];
	char ptr[BUFF_SIZE];
	int  loc ;
	int  len ;
	int	 plen;


	strcpy(str, "bacbababadababacambabacaddababacasdsd");
	strcpy(ptr, "ababaca");
	printf("str: %s\n", str);
	printf("ptr: %s\n", ptr);
	len = strlen(str);
	plen = strlen(ptr);
	loc = kmp(str, len, ptr, plen);


	printf("the loc: %d\n", loc);
	printf("string :  %s\n", str + loc);
	
	return 0;
}






