#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE  1024

int getStrings(char * str)
{
		char  c;
		int   len = 0;
		while(1)
		{
				scanf("%c",&c);
				if(c == '\n')
				{
						break;
				}
				if(len > BUFSIZE -1)
				{
						printf("Extend the length \n");
						break;
				}
				len ++;
				*str ++ = c;
		}   

		return len;
} 

int  getLenOfLastWord(char *str, int len)
{
		int  lenStep = len - 1;
		int  ret = 0;
		int flagBeginCalc = 0; 

		for(lenStep = len -1 ; lenStep >0; lenStep -- )
		{
				if(*(str+lenStep) == ' ')    
				{
						if(flagBeginCalc)
						{
								break;
						}
						continue;
				}
				flagBeginCalc = 1;
				ret ++;
		}
		if(lenStep == 0 && str[0] != ' ')
		{
				ret++;
		}

		return ret;
}

int main(int argv, char ** argc)
{
		char buf[BUFSIZE] = {'\0'};
		int  len = 0;
		int  ret = 0;
		len = getStrings(buf);

		ret = getLenOfLastWord(buf, len);

		printf("%d\n", ret);
		return 0;
}



