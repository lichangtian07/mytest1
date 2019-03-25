
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




