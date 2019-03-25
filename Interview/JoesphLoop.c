
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#define MSIZE  200

void printMap(int map[], int nsize)
{
	int i = 0 ;
	
	printf("Map: %d [", map[0]);

	for(i = 1; i < nsize; i ++)
	{
		printf(" %d", map[i]);
	}
	printf(" ] \n");
	
}

void initialMap(int map[], int nsize)
{
	int  i = 0;

	for(i = 0; i < nsize ; i++ )
	{
		map[i] = 1;
	}
}

int checkMap(int map[], int nsize)
{
	int  i = 0;

	for(i = 1; i < nsize; i++)
	{
		if(map[i] == 1)
		{
			return i;
		}
	}

	return 0;
}

int JoesphLoop(int n, int m)
{
	int		i = 1 ;
	int		j = 1 ;
	int		res;
	int		monkey[MSIZE]; // 0 1 2 3 ..... n n+1

	assert(n < MSIZE - 1);

	initialMap(monkey, MSIZE);
	
	monkey[0] = n;

	do{
		j = 1;
		printMap(monkey, n+1);
		while(j < m + 1)
		{
			if(monkey[i] == 1)
			{
				j++;
			}
			if ( j == m + 1)
			{
				monkey[i] = 0;
				monkey[0] -- ;
			}
			i = i%n + 1;
		}
	} while(monkey[0] > 1);

	printMap(monkey, n+1);
	res = checkMap(monkey, n+1);

	if(!res)
	{
		printf("find error\n");
	}
	
	return res; 	
}



int main()
{
	int  monkeynum;
	int  order;
	int	 ret;
	
	printf("please input monkey number : ");
	scanf("%d", &monkeynum);
	printf("please input monkey order : ");
	scanf("%d", &order);
	
	ret = JoesphLoop(monkeynum, order);
	if (ret)
	{
		printf("the Monkey King is : %d \n", ret);	
	}
	else
	{
		printf("processer is error !!\n");
	}

	return 0;
}



