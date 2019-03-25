

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  isPrime(int num)
{
	int  i = 0;

	for (i = 2; i < num/2 ; i ++ )
	{
		if (num%i == 0)
		{
			return 0;
		}
	}
	return 1;
}	


int factorHandle(int num)
{
	int i = 0;

	for (i = 2; i < num/2; i ++)
	{
		if(num%i == 0)
		{
			return i;
		}
	}

	return num;	
}

int main()
{
	int  numtest;
	int  numtmp;
	int  tmp;

	printf("please input a test number : ");
	scanf("%d", &numtest);
	
	printf("%d = ", numtest);
	
	//if(isPrime(numtest))
	if(factorHandle(numtest) == numtest)
	{
		printf(" 1 * %d \n", numtest);
	}
	else 
	{
		numtmp = numtest;
		//tmp = numtmp;
		while((tmp = factorHandle(numtmp)) != numtmp)
		{
			printf(" %d *", tmp);
			numtmp = numtmp/tmp;
		}
		printf(" %d\n", tmp);
	}

	return 0;
}



