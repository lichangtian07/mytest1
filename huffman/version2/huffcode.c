

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "huffman.h"


#ifdef WIN32
extern int		getopt(in, char **, char *); //window 
extern char*	optarg;
#else
#include <uistd.h>
#endif


/*************************************************************************************/
/********************************The Global Define************************************/
/*************************************************************************************/


/*************************************************************************************/
/********************************The Global Struct************************************/
/*************************************************************************************/

/*************************************************************************************/
/********************************The Local Function***********************************/
/*************************************************************************************/


static void version(FILE *out)
{
	fputs("huffcode 0.3  \n"
		  "Copyright (C) 2003 Douglas Ryn Richardson",
		  "; Gauss Interprise , Inc\n"
		  ,out);
}

static void usage(FILE *out)
{
	fputs("Usage : huffcode [-i<input file>] [-o<output file>] [-d|-c]\n"
		  "-i - input file(defualt is standard input) \n"
		  "-o - output file(defualt is standard output) \n"
		  "-d - decompress \n"
		  "-c - compress (defualt) \n"
		  "-m - read file into memory, compres, then write to file (not defualt) \n"
		  "-t - outpu huffman statistics \n"
	      ,out);
}


/*************************************************************************************/
/********************************The Global Function**********************************/
/*************************************************************************************/
int main(int argc, char * argv[])
{
	char			memory		= 0 ; //
	char			compress	= 1; //
	int				opt;
	const char		*file_in	= NULL;
	const char		*file_out	= NULL;

	FILE			*in			= stdin;
	FILE			*out		= stdout;
	//
	FILE			*outTable	= NULL; //
	

	while ( (opt = getopt(argc, argv, "i:o:cdhvmt:") ) != -1)
	{
		switch (opt)
		{
			case 'i' :  //
				file_in = optarg;
				break;
			case 'o' :  //
				file_out = optarg;
				break;
			case 'c' :  //
				compress =1; 
				break;
			case 'd' :  //
				compress =0;
				break;
			case 'h' :  //
				usage(stdout);
				return 0;
			case 'v' :  //
				version(stdout);
				return 0;
			case 'm':   //
				memory = 1;
			case 't':   //
				file_out_table = optarg;
				break;
			default:  //
				usage(stderr);
				return 1;

		}
	}

	/* if an input file is given then open it .*/
	if(file_in) //
	{
		in = fopen(file_in, "rb");
		if(!in)
		{
			fprintf(stderr, 
				"can't open input file '%s': %s \n"
				, file_out, strerror(errno));
			return 1;
		}
	}
	/* If an output file is given then create it . */
	if(file_out) //
	{
		out = fopen(file_out, "wb");
		if(!out)
		{
			fprintf(stderr, 
				"can't open input file '%s': %s \n"
				, file_out, strerror(errno));
			return 1;
		}
	}
		
	if(file_out_table) //
	{
		outTable = fopen(file_out_table, "w");
		if(!outTable)
		{
			fprintf(stderr, 
				"can't open input file '%s': %s \n"
				, file_out_table, strerror(errno));
			return 1;
		}
	}
	
	if(memory) // 
	{
		return compress ? memory_encode_file(in, out) : memory_decode_file(in, out);
	}
	
	if(compress)//
	{
		huffman_encode_file(in, out, outTable); // 
	}
	else
	{
		huffman_decode_file(in, out);
	}

	if(in)
	{
		fclose(in);
	}
	if(out)
	{
		fclose(out);
	}
	if(outTbale)
	{
		fclose(outTable);
	}
	
	return 0;
}







