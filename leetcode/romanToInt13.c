
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int romanToInt(char * s)
{
	int		ret = 0;
	int		len = 0;
	int		i = 0;

	if(NULL == s)
	{
		return 0;
	}
	len = strlen(s);
	for(i = 0; i < len; i ++)
	{
		switch(s[i])
		{
		case 'I':
			ret += 1;
			break;
		case 'V':
			ret += 5;
			break;
		case 'X':
			ret += 10;
			break;
		case 'L':
			ret += 50;
			break;
		case 'C':
			ret += 100;
			break;
		case 'D':
			ret += 500;
			break;
		case 'M':
			ret += 1000;
			break;
		default:
			//printf("Error char \n");
			break;
		}
		
		if(i > 0)
		{
			if((s[i] =='V' && s[i-1] == 'I') || (s[i] == 'X' && s[ i-1 ] == 'I'))
			{
				ret -= 2;
			}
			if((s[i] =='L' && s[i-1] == 'X') || (s[i] == 'C' && s[ i-1 ] == 'X'))
			{
				ret -= 20;
			}
			if((s[i] =='D' && s[i-1] == 'C') || (s[i] == 'M' && s[ i-1 ] == 'C'))
			{
				ret -= 200;
			}
		}
		
	}


	return ret;
}

int main(int argc, char ** argv)
{
	int		ret = 0;
	char	str[] = "MCMXCIV";
	
	ret = romanToInt(str);
	
	printf("ret: %d \n", ret);

	return ret;
}


