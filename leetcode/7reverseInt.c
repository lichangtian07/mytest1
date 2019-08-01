

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse(int x)
{
	unsigned int	tmp = 0;	
	unsigned int	min = (1 << 31) ;
	unsigned int	max = min - 1;
	int				num = x;
	int				flag = 0; 
	int				ret = 0;

	if(x < 0)
	{
		flag = 1;
		num = 0 - x;
	}
	
	while(num)
	{
		tmp = tmp * 10 +  num%10;
		num /= 10;
		if(flag)
		{
			if( tmp > min)
			{
			  return 0;
			}
		}
		else
		{
			if( tmp  > max)
			{
				return 0;
			}
		}
	}


	if(flag)
	{
		ret = (int)( 0 - tmp );
	}

	return ret;
}


int main(int x)
{
	int ret =  0;
	int	i = 2 ;
	int	num	= 1;

	printf("ret %d \n", ret);
	num = reverse(num);
	printf("num %d \n", num);
	
	return 0;
}






