/*
**
**  Filename: my-split.c 
**	Autrhor : Liqiang 
**  Create  : 31/01/2018
**  Descripton: a simulate for Linux system comand split for Interview 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/**************************************************************/
/************************* DEINE  ZONE   **********************/
/**************************************************************/
#define  FNSIZE       100     //存储文件名称的bufffer 大小：File Name Size
#define  BUFFSIZE    1024     //读取文件数据的缓存取的大小：Buffer Size 

/**************************************************************/
/************************* DEINE  ZONE   **********************/
/**************************************************************/
//使用说明
const char *usagenote = "Usage: my-split <filename> <bytes-per-file>\n\t<filename>: file name \n\t<bytes-per-file>: each sub file include bytes ";

void usage()
{
	//printf("Usage: my-split <filename> <bytes-per-file>\n");
	printf("%s\n",  usagenote);
}

/****************************************************************/
/************************* Local  FUNCTION **********************/
/***************************************************************/

/*
**
** 主要处理函数：splitHadnle
**		   输入：文件名称 每个子文件大小 
**         输出： -1   1
*/

int splitHandle(char * filename , int eachFileBytes)
{
	FILE *		fp ;
	FILE *		fpnew;
	char *		buffer[BUFFSIZE + 1];	
	int			realReadBytes;
	int			realWriteBytes;
	int			tag  = 1;
	char 		new_filename[2*FNSIZE];
	int			readRet;
	int			writeRet;
	//int			backRet;
	int			totalBytes = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr,"can't open the file %s \n", filename);
		return -1;
	}
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


	fclose(fp);

	return 0;
}

/****************************************************************/
/************************* Test  FUNCTION **********************/
/***************************************************************/
int main(int argc, char *argv[])
{
	char				filename[FNSIZE];
	unsigned int		eachFileBytes;

	if(argc < 3)
	{
		usage();
		return 0;
	}
	/*
	*  need check filename size 
	*/
	if(strlen(argv[1]) > FNSIZE)
	{
		printf("The file name length too long !!! (length < %d)", FNSIZE);
		return 0;
	}
	/*
	*识别参数   参数改进： 使用 optarg 
	*/
	strcpy(filename, argv[1]);
	eachFileBytes = atoi(argv[2]);
    /*
	**打印参数：
	*/
	printf("filename : %s \n",filename);
	printf("eachFileBytes: %d \n", eachFileBytes);

	splitHandle(filename, eachFileBytes);

	return  0;
}



