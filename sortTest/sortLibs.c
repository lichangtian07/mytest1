/*
** sortLibs.c
**
** history:
**		2020-12-13  create by lichangtian07
**
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define RANDSIZE (max-min)

void swap(int *a, int *b)
{
	int tmp = 0;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void printArray(int a[], int len)
{
	int i;
		
	for(i = 0; i < len; i ++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}



int createData(int nums[], int n, int min, int max)
{
	int		i=0;
	int		j=0;
	int		flag=0;
	int		randsize=max - min;

	//printf("Create Date Begin: \n");
	srand(time(NULL));
	if((max - min + 1 ) < n)
	{
		return 0;
	}

	for(i=0; i < n ; i++)
	{
		//printf("randsize:  %d \n", randsize);
		do{
			nums[i] = ((unsigned int )( (max - min + 1)*rand() ))%(randsize + 1) + min;
			flag = 0;
			for( j = 0; j<i; j++)
			{
				if(nums[i] == nums[j])
				{
					flag = 1; //if i is equal with nums before
				}

			}
		}while(flag);
	}

	return 1;
}

/*
**冒泡排序
** 
*/
void bubbleSort(int nums[], int n)
{
	int  i = 0;
	int  j = 0;
	
	for(i = 0 ; i < n; i++)
	{
		for(j =0 ; j < n-i-1; j ++)
		{
			if(nums[j] > nums[j+1])
			{
				swap(&nums[j], &nums[j+1]);
			}
		}		
	}
}



/*
** 快速排序
*/

int division(int nums[], int left, int right) 
{
	int base = nums[left];

	while(left<right)
	{
		while(left < right && nums[right] > base)
		{
			right--;
		}
		if(left < right)
		{
			nums[right] = nums[left];
		}
		while(left < right && nums[left] < base)
		{
			left ++;
		}
		if(left < right)
		{
			nums[left] = nums[right];
		}
	}

	nums[left] = base;
	return left;
}
void quicksort(int nums[], int left, int right)
{
	int i = 0;

	if(left < right)
	{
		i = division(nums, left, right);
		quicksort(nums, left, i-1);
		quicksort(nums, i+1, right);
	}

}

void insertSort(int nums, int n)
{

}

#if 0 
void BubbleSort(int a[], int n)
{
	int i , j, t;
	
	for (i = 0; i < n; i++) // 0 1 2 3 ....... n-1
	{
		for(j = n-1; j >i; j--) // n-1 n-2 ....... 3 2 1 0
		{
			if(a[j - 1] > a[j]) //  j ---> 
			{
				t = a[j - 1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
		printf("第 %2d 遍 \n", i+1);
		for(j = 0; j < n; j++)
		{
			printf("%d ", a[j]);
		}
		printf("\n");
	}

}

#endif







