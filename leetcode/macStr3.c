
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int  isUniqe2(char *s , int start, int end)
{	
	int ret = 1;
	int i = start;
	int	len = strlen(s);
	int	j = 0;
	char * substr ;

	substr = (char *)malloc((end -start) * sizeof(char ));
	if( NULL == substr )
	{
		printf("malloc %d failed \n", end-start );
		return 0;
	}
	for (i = start; i < end; i ++)
	{
		if(strchr(substr,s[i]))
		{
			ret = 0;
			goto uniqe_end;
		}
		substr[j ++ ] = s[i];
	}

uniqe_end:
	free(substr);
	return ret;
}

int  isUniqe(char *s , int start, int end)
{
	int i = 0;
	
	int mapAscii[256] = {0};
	
	for (i = start ; i <end; i ++)
	{
		mapAscii[s[i]]  ++;
		if(mapAscii[s[i]] > 1)
			return 0;
	}

	return  1;
}

int lengthOfLongestSubstring(char* s) 
{
	int		ret = 1;
	int		len = strlen(s);
	char *	substr ;
	int		i = 0;
	int		j = 1;
	

	if(s == NULL || len == 0)
	{
		return 0;
	}
	/*	
	for ( i = 0 ; i < len; i++ )
	{
		for(j = i + 1;j <=len; j ++ )
		{
			if (isUniqe(s, i, j))
			{
				ret = ret > (j - i) ? ret : (j - i);
			}
		}
	}
	*/
	
	while(i < len && j <= len)
	{
		//printf("s[i=%d]: %c \n", i, s[i]);
		//printf("s[j=%d]: %c \n", j, s[j]);
		if(isUniqe(s, i, j))
		{
			ret = ret > (j - i)? ret : (j - i);
			j++;
			//printf("i : %d \n", i);
			//printf("j : %d \n", j);
		}
		else
		{
			i ++;
			//printf("tag i : %d \n", i);
			//printf("tag j : %d \n", j);
		}
	}
	

	return ret ; 
}

int main(int argc, char ** argv)
{
	//char	str[] = "abcabcbb";
	//char	str[] = "bbbbb";
	char	str[] = "pwwkew";
	//char str[] = "";
	//char str[] = " ";
	//char str[] = "au";
	int		len = 0;
	
	len = lengthOfLongestSubstring(str);	
	
	printf("len: %d \n", len);

	return 0;
}






