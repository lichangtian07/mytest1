#include <stdlib.h>
#include <stdio.h>

//#define RANDSIZE  RAND_MAX
#define RANDSIZE (max-min)

int CreateData(int arr[], int n, int min, int max)
{	
	int i,j,flag;
	
	printf("Create Date Begin: \n");
	srand(time(NULL));

	if((max - min + 1 ) < n)
	{
		return 0;	
	}
	
	for(i=0; i < n ; i++)
	{
		printf("RANDSIZE:  %d \n", RANDSIZE);
		do{
			arr[i] = ((unsigned int )( (max - min + 1)*rand() ))%(RANDSIZE + 1) + min;
			flag = 0;
			for( j = 0; j<i; j++)
			{
				if(arr[i] == arr[j])
				{
					flag = 1; //if i is equal with arr before 
				}
			
			}
		}while(flag);
	}
	
	return 1;
}



