


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUF_LEN		100

typedef enum {
	FALSE = -1,
	TRUE = 0
} BOOL8;

int getStrings(char * str)
{
	int i = 0 ;

	for(i = 0; i < BUF_LEN ; i ++)
	{
		scanf("%c",&str[i]);
		if(str[i] == '\n')
		{
			str[i] = '\0';
			i -- ;
			break;
		}
	}

	return i;
}

BOOL8 allocNum(int ** num, int len , int numb)
{
	*num =	(int *) malloc(len * numb);
	
	if(* num == NULL)
	{
		printf("malloc %d size %d falid \n", len , numb);
		return FALSE;
	}
	
	return TRUE;
}

int string2numArray(char* str, int * num)
{
	int i = strlen(str) - 1;
	int j = 0;

	while(i >= 0)
	{
		num[j++] = str[i -- ] - '0';
	}
	return j;
}

int numArray2string(int *res, char *str, int len)
{
	int	i = len;
	int	j = 0;
	
	while(i >= 0)
	{
		str[ j++ ] = res[ i-- ] + '0';	
	}
	
	return j;
}

int bigNumMultipy(char * str1, char *str2, char ** pRet)
{
	int		len1 = strlen(str1);
	int		len2 = strlen(str2);
	int		lenRes = len1 + len2;
	char *	ptr;
	int *	num1;
	int *	num2;
	int	*	res;
	int		i = 0;
	int		j = 0;
	int		k = 0;

	if(FALSE == allocNum(&num1, len1, sizeof(int)) )
	{
		printf("alloc Num1 failed \n");
		lenRes = -1;	
		goto multipy_end;
	}
	
	if(FALSE == allocNum(&num2, len2, sizeof(int)) )
	{
		printf("alloc Num2 failed \n");
		lenRes = -1;	
		goto multipy_end;
	}
	
	if(FALSE == allocNum(&res, lenRes, sizeof(int)) )
	{
		printf("alloc Num2 failed \n");
		lenRes = -1;	
		goto multipy_end;
	}

	string2numArray(str1, num1);
	string2numArray(str2, num2);
	
	for(i = 0; i < len1; i ++)
	{
		for(j = 0; j < len2; j ++)
		{
			res[i+j] += num1[i] * num2[j] ;
		}
	}

	for(k = 0; k < lenRes; k++)
	{
		if(res[k] >= 10)
		{
			res[k+1] += res[k] / 10;
			res[k] %= 10;
		}
	}

	while(res[k] == 0)
	{
		k --;
	}
	lenRes = k;
	
	ptr = (char * )malloc(k * sizeof(char));
	if(ptr == NULL)
	{
		printf("alloc ptr  %d failed \n", k);
		lenRes = -1;	
		goto multipy_end;
	}
	memset(ptr, 0, k*sizeof(char ));
	lenRes = numArray2string(res, ptr, lenRes);
	
	*pRet = ptr;

multipy_end:
	if(num1 != NULL)
	{
		free(num1);
	}
	if(num2 != NULL)
	{
		free(num2);
	}
	if(res != NULL)
	{
		free(res);
	}

	return lenRes;
}

int main(int argc, char *argv[])
{
	char num1[BUF_LEN] = {0};
	char num2[BUF_LEN] = {0};
	int	 nlen1 = 0;
	int  nlen2 = 0;
	char *res;

	printf("input num1 : ");
	nlen1 = getStrings(num1);
	printf("input num2 : ");
	nlen2 = getStrings(num2);
	
	bigNumMultipy(num1,num2,&res);
	if(res != NULL)
	{
		printf("the %s X %s = %s \n", num1, num2, res);
		free(res);
	}
	return 0;
}



