

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int   UINT32;
typedef unsigned short UINT16;
typedef unsigned char  UINT8;


int isEndianLittle()
{
	union {
		UINT16  integer;
		struct {
			UINT8  c1;
			UINT8  c2;
		} element;
	} myunion;
	
	myunion.integer = 0x01;
	// show union 
	printf("myunion.integer :  0x%x \n", myunion.integer);
	printf("myunion.element.c1 :  0x%x \n", myunion.element.c1);
	printf("myunion.element.c2 :  0x%x \n", myunion.element.c2);


	if(myunion.element.c1 == 0x1)
	{
		return 1;
	}

	return 0;
}


int main()
{
	int ret ;
	
	ret = isEndianLittle();

	if(ret)
	{
		printf("The arch is little Endian \n");
	}
	else
	{
		printf("The arch is big Endian \n");
	}
	
	return 0;
}










