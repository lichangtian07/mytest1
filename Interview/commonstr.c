

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100


int GetMaxCommStr(char * s1, char * s2 ,char * s3)
{
	// char * s1 = stra , s2=strb;
	char len1 = strlen(s1);
	char len2 = strlen(s2);
	char maxlen = 0;
	char as;
	char bs;
	char  i, j , r = 1;
	int count = 0;
	int	r1 = 0;

	for (i = 0; i < len1; i ++)
	{
		for (j = 0; j < len2; j ++)
		{
			if(s1[i] == s2[j])
			{
				as = i;
				bs = j;
				count = 1;
				while( (as + 1 < len1) && (bs + 1 < len2) && (s1[++as] == s2[++bs]))
				{
					count ++ ;
				}
				if( count > maxlen )
				{
					maxlen = count;
					r1 = i;
				}
			}
		}
	}
	if( maxlen > 0 )
	{
		for(i = 0; i < maxlen; i++)
		{
			*(s3 + i) = *(s1 + i);
		}
	}

	return maxlen;	
}


int getStrings(char * str)
{
	char  c;
	int	  len = 0;
	while(1)
	{
		scanf("%c",&c);
		if(c == '\n')
		{
			break;
		}
		if(len > N -1)
		{
			printf("Extend the length \n");
			break;
		}
		len ++;
		*str ++ = c;
	}

	return len;
}

int main()
{
	char a[N] = {0};
	char b[N] = {0};
	char str[N] = {0};
	int  maxoflen = 0;

	printf("Enter first string(the length < %d)! \n", N);
	getStrings(a);
	printf("Enter second string(the length < %d)! \n", N);
	getStrings(b);

	maxoflen = GetMaxCommStr(a,b,str);
	
	printf("max of length is : %d\n", maxoflen);

	return 0;
}






