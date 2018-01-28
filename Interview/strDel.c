

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUFF_SIZE  200
#define ENDCHAR '\n'

int findEinStr(char * str, char element)
{
	assert(str != NULL);
	while(*str != '\0')
	{
		if(element == *str)
		{
			return 1;
		}
		str ++ ;
	}
	return 0;
}

void strDel(char * src , char *delstr)
{
	char	buff[BUFF_SIZE];
	int		i = 0;
	char *  pstr = src;
	memset(buff, 0 , BUFF_SIZE);
	
	while(* pstr != '\0' )
	{
		if(!findEinStr(delstr, *pstr))
		{
			buff[i++] = *pstr; 
		}
		pstr ++ ;
	}
	strncpy(src, buff, BUFF_SIZE);
}

void getStrings( char * str)
{
	char c;
	int  len = 0;
	while(1)
	{
		scanf("%c",&c);
		if(c == ENDCHAR)
			break;
		len ++;
		if(len > BUFF_SIZE)
		{
			printf("WARNING: extend the BUFF_SIZE");
			break;	
		}
		*str++ = c;
	}

}


int main()
{
	char  str1[BUFF_SIZE];
	char  str2[BUFF_SIZE];
	
	memset(str1, 0 , BUFF_SIZE);
	memset(str2, 0 , BUFF_SIZE);

	printf("please input origin strings: ");
	getStrings(str1);
	printf("please input del chars: ");
	getStrings(str2);
	
	strDel(str1, str2);
	
	printf("please reslut strings: %s \n", str1);

	return 0;
}	








