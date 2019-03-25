

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max		1000

char * multiBigInteger(char * a, char * b)
{
	char*	retChar;	
    int     c[Max], d[Max], e[Max];
	int     alen, blen;
	int		i = 0;
	int		j = 0;
	int		x = 0;

	memset(c, 0, sizeof(c));
	memset(d, 0, sizeof(d));
	memset(e, 0, sizeof(e));
	
	alen = strlen(a);
	blen = strlen(b);
	
	for (i = alen - 1; i >= 0; i--)
	{
		c[x] = a[i]-'0';
		x ++;

	}
	x = 0;
	for(i = blen - 1; i>=0; i--)
	{
		d[x] = b[i] - '0';
		x ++;
	}
	
	for ( i = 0; i < alen; i++ )
	{
		for(int j = 0; j < blen; j++)
		{
			e[i+j] += (c[i]  * d[j]);
		}
	}
	
	for( j = 0; j < Max; j ++)
	{
		if(e[j] >=10)
		{
			e[j+1] += e[j]/10;
			e[j] %= 10;
		}
	}
	
	for(i = Max -1 ; i >= 0; i --)
	{
		if(e[i]!=0)
		{
			break;
		}
	}
	/*
	printf("%s * %s = ", a, b);
	for(;i>=0; i--)
	{
		printf("%d", e[i]);
	}
	printf("\n");
	*/
	
	if(i == -1)
	{
		i = 0;
	}
	retChar = (char *) malloc( i+2);
	x = 0;
	for(; i >= 0; i --)
	{
		retChar[x++] = e[i] + '0';
	}
	
	retChar[x] = '\0'; 

	return retChar;
}

int getStrings(char * str)
{
	char	c;
	int		len = 0;

	while(1)
	{
		scanf("%c", &c);
		if(c == '\n')
		{
			break;
		}
		if(len > Max - 1)
		{
			printf("Extend the length \n");
			break;
		}
		len ++ ;
		*str ++ = c;
	}
	
	return len ;
}

int main(int argc, char *argv[])
{
	char    a[Max], b[Max]; 
	char	* ret ;
	
	memset(a, 0, Max);
	memset(b, 0, Max);

	printf("input a: ");
	getStrings(a);
	printf("input b: ");
	getStrings(b);
	
	ret = multiBigInteger(a, b);

	printf("%s * %s = %s \n", a, b, ret);
		
	free(ret);
	ret = NULL;
	return 0;
}



