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

/*
**
** 主要处理函数：splitHadnle
** 输入：
** 输出：
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
	if( eachFileBytes > BUFFSIZE )	
	{
		realReadBytes = BUFFSIZE;
		while(readRet = fread( buffer, sizeof(char), realReadBytes, fp))
		{
			realWriteBytes = readRet;
			if(totalBytes == 0) // 每一个子文件开始时需要新建一个文件
			{
				memset(new_filename, 0, 2*FNSIZE);
				sprintf(new_filename, "%s.%d", filename, tag ++);
				fpnew = fopen(new_filename, "w");
			}
			fwrite(buffer,sizeof(char), realWriteBytes,fpnew);
			totalBytes += realWriteBytes;
				
			if (totalBytes == eachFileBytes  )
			{
				fclose(fpnew);
				totalBytes = 0;
			}
			if(realWriteBytes < realReadBytes)
			{
				fclose(fpnew);
				break;
			}
		}	
	}
	else
	{	
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



