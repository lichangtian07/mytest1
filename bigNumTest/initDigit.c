

#include <stdio.h>
#include <stdlib.h>


int printNum(int  input)
{
	int ret = 0;
	do {
		ret ++;
		printf("%d ,", input%10);
		input /=10;
	} while(input/10 != 0);

	printf("%d\n", input);

	return ret;
}

void initDigital(int input)
{
	int		numbit = 0;
	int		num = input;
	int		reverseNum = 0;
	
	do {
		numbit ++;
		reverseNum = num % 10 + reverseNum*10 ;
		num /= 10;
	} while(num != 0);
	
	printf("length: %d \n", numbit);
	printNum(reverseNum);
	printNum(input);
}

int main(int argc, char ** argv)
{
	int	test = 123456;

	initDigital(test);

	return 0;
}

