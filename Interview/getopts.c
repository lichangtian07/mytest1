

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef enum{
	HELP_ALL=0,
	HELP_IN=1,
	HELP_BYTES=2,
	HELP_LACK_IN=3,
	HELP_LACK_BYTES=4,
	HELP_END
}HELP_INDEX;


const char* usagenote[] = {
"my-split [option] <value> \n\
\t-i  filename \n\
\t\tinput filename \n\
\t-b  bytes \n\
\t\tcut file by bytes \n\
\t-h  help for more information",
"my-split:need a argument -i \n\
Try 'split -h' for more information",
"my-split:need a argument -b \n\
Try 'split -h' for more information",
"my-split:need -i filename  \n\
Try 'split -h' for more information",
"my-split:need -b bytes\n\
Try 'split -h' for more information",
""
};

void usage(HELP_INDEX index)
{
	printf("%s\n", usagenote[index]);	
}

int splitHandle(char * filename, char *bytesvalue)
{
	int						bunit ;
	char *					digial;
	unsigned long long		eachFileBytes=1;
	unsigned long long		vol = 1;

	printf("filename: %s \n", filename);
	printf("bytesvalue: %s \n", bytesvalue);

	bunit = bytesvalue[strlen(bytesvalue) - 1];
	digial = (char *)malloc(strlen(bytesvalue));
	
	strncpy(digial, bytesvalue, strlen(bytesvalue) - 1);
	digial[strlen(bytesvalue) - 1] = '\0';
	eachFileBytes = atol(digial);
	/*
	printf("%s\n", digial);	
	printf("%lld \n", eachFileBytes);
	printf("unit : %c\n", bunit);
	*/
	switch(bunit)
	{
		case 'G':
		case 'g':
				vol *= 1024;
				printf("%lld \n", vol);
		case 'M':
		case 'm':
				vol *= 1024; 
				printf("%lld \n", vol);
		case 'K':
		case 'k':
				vol *= 1024;
				printf("%lld \n", vol);
				eachFileBytes *= vol;
				break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			eachFileBytes = eachFileBytes *10 + bunit - '0';	
			break;
		default:
			printf("the %c is unkown unit \n", bunit);
			return -1;
	}


	printf("eachFileBytes: %lld \n", eachFileBytes);
	free(digial);
	digial = NULL;

	return 0;
}

int main(int argc, char * argv[])
{
	int				opt;
	char *			filename = NULL;
	char *			bytesvalue = NULL;
	HELP_INDEX		flag = HELP_ALL;

	while((opt=getopt(argc, argv, "i:b:h")) != -1)
	{
		printf("optind: %d\n", optind);
		printf("opt: %c\n", opt);
		switch(opt)
		{
			case 'i':
				filename = optarg;
				if(filename == NULL)
				{
					flag = HELP_IN;
				}
				else
				{
					flag = HELP_LACK_BYTES;
				}
				break;	
			case 'b':
				bytesvalue = optarg;
				if(bytesvalue == NULL)
				{
					flag = HELP_BYTES;
				}
				else
				{
					flag = HELP_LACK_IN;
				}
				break;	
			case 'h':
				filename = optarg;
				flag = HELP_ALL;
				break;	
			default:
				filename = optarg;
				break;	
		}
	}
	//printf("flag: %d \n", flag);
	if(filename != NULL && bytesvalue != NULL)
	{
		splitHandle(filename, bytesvalue);
	}
	/*
	else if(filename == NULL && bytesvalue != NULL)
	{
		usage(HELP_LACK_IN);
	}
	else if(filename != NULL && bytesvalue == NULL)
	{
		usage(HELP_LACK_BYTES);
	}
	*/
	else
	{
		usage(flag);
	}

	return 0;
}





