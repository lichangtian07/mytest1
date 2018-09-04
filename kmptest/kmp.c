
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 256

void printMap(int map[], int n)
{
	int		i = 0;
	
	printf("[");
	for(i = 0; i < n; i ++)
	{
		printf(" %d", map[i]);
	}

	printf(" ]\n");
}
/*
*	str = "bacbababadababacambabacaddababacasdsd"
*	pstr = "ababaca"
*	pstr 处理位置next[0] next[1] next[2] next[3] next[4] next[5] next[6]
*	分别记住了 a ab aba abab ababac ababaca的相同的最长前缀和后缀的长度
*   对应的最长前缀和最长后缀为  ""  "" "a" "ab" "aba" "" "a" 所以对应的next的值为
*	next = [-1, -1, 0, 1, 2, -1, 0] -1表示不存在, 0 表示存在 长度1 2 3 
*   next值的意义表示, 下一次移动的位移
*/
void cal_next(char *str, int next[], int len)
{
	int		k = -1; //k 初始化 -1
	int		q = 1;

	next[0] = -1;// next 初始化为 -1 ,  -1 表示不存在相同的最大前缀和最大的后缀

	for( q = 1; q <= len - 1 ; q ++)
	{
		/*
		* 如果下一个不同,那么k就变成next[k] 注意next[k]是小于k的,无论k取何值
		*/
		while(k > -1 && str[k+1] != str[q])
		{
			k = next[k]; // 往前回溯
		}
		if(str[k + 1] == str[q]) //如果相同 则k ++ 
		{
			k = k + 1;
		}
		next[q] =  k; // 这个是算的k的值(就是相同最大前缀和最大后缀长) 赋值next[q]
	}
}

int KMP(char * str, int slen, char *ptr, int plen, int loc[], int locSize )
{
	int		*next;
	int		k = -1;
	int		i = 0;
	int		loclen = 0;
	
	next = (int *) malloc(plen * sizeof(int));
	cal_next(ptr, next, plen); //计算ptr的next数组

	printMap(next, plen);

	for(i = 0; i < slen; i ++)
	{
		while(k > -1 && ptr[k + 1] != str[i])// ptr 和 str不匹配，且k >-1(表示ptr和str有部分匹配)
		{
			k = next[k] ; // 往前回溯
		}
		
		if(ptr[k + 1] == str[i])
		{
			k = k + 1;
		}
		if( k == plen - 1) //说明k移动到ptr的最末端
		{	
			/*
			*  count << "在位置" << i - plen + 1 << endl;
			*  printf("在位置 %d \n", i - plen + 1);
			*  k = -1; //重新初始化， 寻找下一个
			*  i = i - plen + 1; //i定位到该位置，外层for循环i ++ 可以继续找下一个(这里默认存在两个匹配字符串可以部分重叠)
			*  return i - plen + 1; //返回相应的位置 
			*/
			loc[loclen ++ ] = i - plen + 1; 
		}
	}
	
	free(next);

	return loclen;
}

int getStrings(char * str)
{
	int		len = 0;
	char	c ; 
	
	while(1)
	{
		scanf("%c", &c);
		if(c == '\n')
		{
			break;
		}
		if( len > BUFF_SIZE - 1 )
		{
			printf("Extend the BUFF_SIZE \n");
			break;
		}
		len ++;
		*str ++= c ;
	}
	
	return len;
}

void initialMap(int map[], int n)
{
	int	 i = 0;

	for (i = 0; i < n ; i++)
	{
		map[i] = -1;
	}
}

void printKMPString(char * str, int loc[], int loclen)
{
	int i = 0;
	
	for (i = 0; i < loclen; i ++)
	{
		printf("str[loc[%d]=%d]: %s \n", i, loc[i], str+loc[i]);
	}
}

int main()
{
	char	str[BUFF_SIZE];
	char	ptr[BUFF_SIZE];
	
	int		loc[BUFF_SIZE];
	int		len = 0;
	int		plen = 0;
	int		loclen = 0;
	char	op = 0;
	int		fexit  = 0;
	int		fexec = 1;
	int		i = 0;


	while(1)
	{
		printf("***********************************\n");
		printf("op : 0 auto test 1 manually  e exit\n");
		printf("***********************************\n");
		
		scanf("%c",&op);
		getchar();
		
		fexit = 0;
		fexec = 1;

		memset(str, 0, BUFF_SIZE);
		memset(ptr, 0, BUFF_SIZE);

		initialMap(loc, BUFF_SIZE);

		printf("operation: %c \n", op);

		switch(op)
		{
			case '0':
				strcpy(str, "bacbababadababacambabacaddababacasdsd");
				strcpy(ptr, "ababaca");
				len = strlen(str);
				plen = strlen(ptr);
				printf("str: %s \n", str);
				printf("ptr: %s \n", ptr);
				break;

			case '1':
				printf("Please input the Dst string : ");
				len = getStrings(str);
				printf("Please input the find string : ");
				plen = getStrings(ptr);
				
				if(len < plen)
				{
					printf("Error : the Dst string length must be longer than find string \n");
				}
				break;
			case 'e':
				fexit = 1;
				break;
			default:
				printf("Error: operation code \n");
				break;
		}
		
		if(fexit)
		{
			break;
		}
		loclen = KMP(str, len, ptr, plen, loc, BUFF_SIZE);
		
		/*
		for(i = 0 ; i < loclen ; i ++)
		{
			//printMap(loc, BUFF_SIZE);
			printf("loc[%d] :  %d \n", i, loc[i]);
			printf("result: %s \n", str + loc[i]);
		}
		*/
		printKMPString(str, loc, loclen);
	}


	return 0;
}













