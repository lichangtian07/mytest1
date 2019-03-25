
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * improxyCfg = "\
igmp \t%s \tversion \t%d\n\
mld \t%s\n\
upstream \t%s\n\
downstream \t%s\n\
";

#define IMPROXY_CONF "./improxyCfg.conf"


int readFile()
{
	char igmpEnable[10] = {0};
	//int version;
	char version[10];
	char mldEnable[10] = {0};
	char upStream[10] = {0};
	char downStream[10] = {0};
	FILE	*fp;

	fp = fopen(IMPROXY_CONF, "r");

	if(fp == NULL)
	{
		printf("Open file failure !!!");
		return 0;
	}
	
	//fscanf(fp, improxyCfg, &igmpEnable, &version, &mldEnable, &upStream, &downStream);
	fscanf(fp, "igmp \t%s \tversion \t%d\n", &igmpEnable, &version);
	
	printf("igmpEnable: %s \n", igmpEnable);
	printf("version: %s \n", version);
	printf("mldEnable: %s \n", mldEnable);
	printf("upStream: %s \n", upStream);
	printf("downStream: %s \n", downStream);

	return 1;
}

int writeFile()
{
	char igmpEnable[10] = {0};
	int version;
	char mldEnable[10] = {0};
	char upStream[10] = {0};
	char downStream[10] = {0};
	FILE	*fp;

	fp = fopen(IMPROXY_CONF, "w");

	if(fp == NULL)
	{
		printf("Open file failure !!!");
		return 0;
	}
	
	strncpy(igmpEnable, "enable", 10);
	strncpy(mldEnable, "enable", 10);
	strncpy(upStream, "br0", 10);
	strncpy(downStream, "eth1.1", 10);
	version=3;


	fprintf(fp, improxyCfg, igmpEnable, version, mldEnable, upStream, downStream);
	
	return 1;
}


int main(int argc, char * * argv)
{
	
	writeFile();
	readFile();
	
	return 1;
}




