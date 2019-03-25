
#include <stdio.h>
#include <stdlib.h>

#define MSIZE 100

void printMonkey(int map[], int n)
{
	int		i;

	printf("Monkey : %d [ ", map[0]);

	for(i = 1; i < n; i ++)
	{
		printf("%d ", map[i]);
	}

	printf(" ] \n");
}

int newStart(int map[], int start, int n)
{
	int		k = 0;
	
	for( k = start; k < n; k ++)
	{
		if( map[k] == 1 )
		{
			break;
		}
		k = (k % n) + 1;
	}

	return k;
}

int JesphLoop(int n, int m)
{
	int		monkey[MSIZE];
	int		i = 0;
	int		j = 0;
	
	if( n > MSIZE - 1)
	{
		printf("the n(%d) > MSIZE (%d)", n, MSIZE);
		return - 1;
	}
	
	for( i = 0; i <MSIZE; i ++)
	{
		monkey[i] = 1;
	}
	
	monkey[0] = n;

	i = 1;
	do {
		printMonkey(monkey, n+1);
		j = 1;
		while(j < m + 1)
		{
			if(monkey[i] == 1)
			{
				j ++  ;
			}
			if(j == m + 1)
			{
				monkey[i] = 0;
				monkey[0] -- ;
			}

			i = (i % n) + 1;
		}
	
	} while(monkey[0] > 1);
	
	printMonkey(monkey, n+1);

	for( i = 1; i < n + 1; i ++)
	{
		if(monkey[i] == 1)
		{
			return i;
		}
	}
	
	return -1;
}

int main(int argc, char * argv[])
{
	int		n = 0;
	int		m = 0;
	int		res = 0;

	printf("n : ");
	scanf("%d", &n);
	printf("m : ");
	scanf("%d", &m);
	
	JesphLoop(n, m);

	return 0;
}









