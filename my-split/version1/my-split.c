/*
** Filename  :	my-split.c 
** Author	 :	LiQiang
** Create	 :  03/02/2018
** Decription:  A simulate process for linux system command split 
**              my-split --input filename --bytes  1000/1K/1M/1G
**						 -i --input=filename
**							input file name 
**						 -b --bytes=size
**							cut file by bytes
**						 -h --help
**							help for information
*/




/*****************************************************************/
/*************************INCLUDE ZONE****************************/
/*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>



/*****************************************************************/
/*************************DEFINE ZONE*****************************/
/*****************************************************************/
//#define  FNSIZE       100     //存储文件名称的bufffer 大小：File Name Size
#define  BUFFSIZE    1024     //读取文件数据的缓存取的大小：Buffer Size 



typedef enum{
	HELP_ALL=0,
	HELP_IN=1,
	HELP_BYTES=2,
	HELP_LACK_IN=3,
	HELP_LACK_BYTES=4,
	HELP_END
}HELP_INDEX;


/*****************************************************************/
/***********************Global varible ZONE***********************/
/*****************************************************************/
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


/*****************************************************************/
/**********************LOCALE FUNCTION ZONE***********************/
/*****************************************************************/
void usage(HELP_INDEX index)
{
	printf("%s\n", usagenote[index]);	
}

/*
**
** 主要处理函数：splitHadnle
**         输入：文件名称 每个子文件大小 
**         输出： -1   1
*/

int splitHandle(char * filename , unsigned long long eachFileBytes)
{
    FILE *      fp ;
    FILE *      fpnew;
    char *      buffer[BUFFSIZE + 1];
    int         realReadBytes;
    int         realWriteBytes;
    int         tag  = 1;
    //char        new_filename[2*FNSIZE];
    char*       new_filename;
    int         readRet;
    int         writeRet;
    //int           backRet;
    int         totalBytes = 0;
#ifndef FNSIZE
	int			FNSIZE = strlen(filename);		
#endif	
    fp = fopen(filename, "r");
	if (fp == NULL)
    {
        fprintf(stderr,"can't open the file %s \n", filename);
        return -1;
    }

	new_filename = (char *)malloc(2 * FNSIZE);
    /*
    **基本原则:读取文件大小不能超过buffer的大小
    **两种情况:1. BUFFSIZE 小于eachFileBytes  每次读取的大小为BUFFSIZE = realReadBytes 
    **         2. BUFFSIZE 大于eachFileBytes  每次读取的大小为eachFIleBytes = realReadBytes
    */
    if( eachFileBytes > BUFFSIZE )
    {
        realReadBytes = BUFFSIZE;
        totalBytes = eachFileBytes;
        while(readRet = fread( buffer, sizeof(char), realReadBytes, fp))
        {
            realWriteBytes = readRet;
            if(totalBytes == eachFileBytes) // 每一个子文件开始时需要新建一个文件
            {
                memset(new_filename, 0, 2*FNSIZE);
                sprintf(new_filename, "%s.%d", filename, tag ++);
                fpnew = fopen(new_filename, "w");
            }
            fwrite(buffer,sizeof(char), realWriteBytes,fpnew);
            totalBytes -= realWriteBytes;

            if (totalBytes < BUFFSIZE ) //当totalBytes小于buffer的size大小时，将realBytes设置为totalBytes 
            {
                realReadBytes = totalBytes;
            }
            if(totalBytes == 0) // 当totalBytes读取完成后,重新设置条件
            {
                fclose(fpnew);
                totalBytes = eachFileBytes;
                realReadBytes = BUFFSIZE;
            }
        }
    }
    else
    {
        //当BUFFSIZE 大于 realReadBytes 
        realReadBytes = eachFileBytes;
        while(readRet = fread( buffer, 1, realReadBytes, fp))
        {
            realWriteBytes = readRet;
            memset(new_filename, 0, 2*FNSIZE);
            //开始写入文件
            sprintf(new_filename, "%s.%d", filename, tag ++);
            fpnew = fopen(new_filename, "w");
			fwrite(buffer,sizeof(char), realWriteBytes,fpnew);
            fclose(fpnew);
            //是否已经读完
            if(realReadBytes > realWriteBytes)
            {
                break;
            }
            //backRet = ftell(fp);
            //fseek(fp, backRet, SEEK_SET);
        }
    }
	
    memset(new_filename, 0, 2*FNSIZE);
	free(new_filename);	
	new_filename = NULL;

    fclose(fp);
    return 0;
}
/*
**	function : argumentHandle 
**	input	 : filename  and bytes values
**	return	 : unsigned long long  
**             the reak bytes cut file. 
*/
unsigned long long argumentHandle(char * filename, char *bytesvalue)
{
	int						bunit ;
	char *					digial;
	unsigned long long		eachFileBytes=1;
	unsigned long long		vol = 1;

	/*
	printf("filename: %s \n", filename);
	printf("bytesvalue: %s \n", bytesvalue);
	*/
	assert(filename !=NULL);
	assert(bytesvalue !=NULL);

	/*
	** 将输入的bytesvalue参数的单位提取出来进行解析
	*/
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
			return 0;
	}

	printf("eachFileBytes: %lld \n", eachFileBytes);
	free(digial);
	digial = NULL;

	return eachFileBytes;
}

/*****************************************************************/
/***********************GLOBAL FUNCTION ZONE**********************/
/*****************************************************************/

int main(int argc, char * argv[])
{
	int					opt;
	char *				filename = NULL;
	char *				bytesvalue = NULL;
	HELP_INDEX			flag = HELP_ALL;
	unsigned long long	eachFileBytes = 0;
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
		eachFileBytes = argumentHandle(filename, bytesvalue);
		if(eachFileBytes == 0)
		{
			printf("the --bytes size or -b size shouldn't be 0 ");
			usage(HELP_LACK_BYTES);
			return 0;
		}
		splitHandle(filename, eachFileBytes);
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





