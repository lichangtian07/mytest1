
#include <stdio.h>
#include "CreateData.c"
#include "BubbleSort.c"
#define ARRAYLEN 6

void printArray(int a[], int len)
{
	int i;
	for(i = 0; i < len; i ++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int i, a[ARRAYLEN];

	//初始化数据数组，清空数组
	printf("test main begin: \n");
	for(i = 0; i < ARRAYLEN; i++)
	{
		a[i] = 0;
	}

	if( ! CreateData(a, ARRAYLEN, 1, 100))
	{
		printf(" 生成随机数失败，退出 \n");
		getchar();

		return 1;
	}

	printf("生成的随机数，原始数据为： \n");
	
	printArray(a, ARRAYLEN);
	BubbleSort(a, ARRAYLEN);

	printf("排序后数据： \n");

	printArray(a, ARRAYLEN);

	getchar();
	return 0;
}



