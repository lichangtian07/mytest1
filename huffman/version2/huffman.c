

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "huffman.h"

#ifdef WIN32
#include <winsock2.h>
#include <malloc.h>
#define alloca _alloca
#else
#include <netinet/in.h>
#endif

/********************************************************************************************/
/********************************The local interface function********************************/
/********************************************************************************************/

// 主要的共用函数
static unsigned long numbytes_from_numbits(unsigned long numbits);
static unsigned char get_bit(unsigned char	*bits, unsigned long  i);
static void reverse_bits(unsigned char *bits, unsigned long numbits);
static huffman_code * new_code(const huffman_code * leaf);
static huffman_node * new_leaf_node(unsigned char symbol);
static huffman_node * new_onleaf_node(unsigned long count, huffman_node *zero, huffman_node * one);
static void	free_huffman_tree(huffman_node *subtree);
static void free_code(huffman_code *p);
static void free_encoder(SymbolEncoder *pSE);
static void print_freqs(SymbolFrequencies *pSF);
{
}
static int  SFComp(const void *p1, const void *p2);
{
}


//编码最重要的几个函数
static void build_symbol_encoder(huffman_node *subtree, SymbolEncoder *pSF);
{

}
static SymbolEncoder* calculate_huffman_codes(SymbolFrequencies *pSF);
{
}
int huffST_getSymFrequencies(SymbolFrequencies *SF, huffman_stat *st, int total_count);




// 
static huffman_node * read_code_table(FILE * in, unsigned int *pDataBytes);
static int write_code_table(FILE * out, SymbolEncoder *se, unsigned int symbol_count);

static int do_file_encode(FILE * in, FILE * out, SymbolEncoder *se);


//static int do_file_decode(FILE * in, FILE *out );
// 统计需要函数

huffman_stat *init_huffstatistics();
static void init_frequencies(SymbolFrequencies *pSF);

static int get_frequencies_from_memory(SymbolFrequencies *pSF, const unsigned char *bufin, unsigned int bufinlen);
{
}
static int get_symbol_frequencies(SymbolFrequencies *pSF, FILE *in);
{
}
int huffST_getcodeword(SymbolEncoder *se, huffman_stat *st);
void output_huffman_statistics(hufman_stat *st, FILE *out_Table);


// 内存处理需要的函数
static int do_memory_encode(buf_cache *pc, const unsigned char *buflin, unsigned int bufinlen,SymbolEncoder *se);
static int init_cache(buf_cache *pc, 
                     unsigned int cache_size, 
					 unsigned char **pbufout, 
					 unsigned int *pbufoutlen);
static void free_cache(buf_cache *pc);
static int	flush_cache(buf_cache *pc);

static int	memread(const unsigned char * buf,
					unsigned int	buflen,
					unsigned int	*pindex,
					void			*bufout;
					unsigned int	readlen
					);

static huffman_node * read_code_table_from_memory(const unsigned char	*bufin,
												  unsigned int			bufinlen,
												  unsigned int			*pindex,
												  unsigned int			*pDataByte
												);

static write_code_table_to_memory(buf_cache *pc, SymbolEncoder *se, unsigned int symbol_count);

static int write_cache(buf_cache *pc, const void *to_write, unsigned int to_write_len);
{
}

/*******************************************************************************************/
/********************************The main interface function********************************/
/*******************************************************************************************/
/*
** 两种接口： 
**   1 读文件 处理之后 放入文件
**   2 读内存 处理之后 放入内存  最典型的实例时  uboot下的解压或者压缩
*/
//读文件 处理完成之后放入 文件
int huffman_encode_file(FILE * in , FILE *out, FILE * out_table );
int	huffman_decode_file(FILE *in, FILE *out);
//读内存 处理完成之后放入 内存
int	memory_encode_file(FILE *in, FILE *out);
int	memory_decode_file(FILE *in, FILE *out);

/********************************************************************************************/
/********************************The local interface function********************************/
/********************************************************************************************/

static huffman_node * read_code_table(FILE * in, unsigned int *pDataBytes)
{
	//
	huffman_node		*root = new_nonleaf_node(0, NULL, NULL); 
	unsigned int		count;

	/*
	** Read the number of entries
	** (it is stored in network byte order).
	*/
	if(fread(&count, sizeof(count), 1, in) != 1)
	{
		free_huffman_tree(root);
		return NULL;
	}

	count  = ntohl(count);
	
	/* Read the number of data bytes this encoding represents */
	if(fread(pDataBytes, sizeof(*pDataBytes), 1, in) != 1)
	{
		free_huffman_tree(root);
		return NULL;
	}
	*pDataBytes = ntohl(*pDataBytes);

	while( count -- > 0)
	{
		int					c;
		unsigned int		curbit;
		unsigned char		symbol;
		unsigned char		numbits;
		unsigned char		numbytes;
		unsigned char		*bytesl
		huffman_node		*p = root;
		
		if(memread(bufin, bufinlen, pindex, &symbol, sizeof(symbol)))
		if((c = fgetc(in)) == EOF)
		{
			free_huffman_tree(root);
			return NULL;
		}
		symbol = (unsigned char) c;
		
		if((c = fgetc(in)) == EOF)
		{
			free_huffman_tree(root);
			return NULL;
		}
		numbits= (unsigned char )c;
		numbytes = (unsigned char)numbytes_from_numbits(numbits);
		bytes = (unsigned char *) malloc(numbytes);
		
		if(fread(bytes, 1, numbytes, in) != numbytes)
		{
			free(bytes);
			free_huffman_tree(root);
			return NULL;
		}
		/*
		** Add the entry to the Huffman tree. the value
		** of the current bit is used switch between
		** zero and one child nodes in the tree.New nodes
		** are added as needed in the tree
		*/
		for(curbit = 0 ; curbit < numbits; ++curbit)
		{
			if(get_bit(bytes, curbit))
			{
				if(p->one == NULL)
				{
					p->one = curbit == (unsigned char)(numbits - 1) 
							 ? new_leaf_node(symbol)
							 : new_nonleaf_node(0, NULL, NULL);
					p->one->parent = 0;
				}
				p = p->one;
			}
			else
			{
				if(p->zero == NULL)
				{
					p->zero = curbit == (unsigned char)(numbits - 1) 
							 ? new_leaf_node(symbol)
							 : new_nonleaf_node(0, NULL, NULL);
					p->zero->parent = 0;
				}
				p = p->zero;
			}
		}
		free(bytes);
	}

	return root;

}

static int write_code_table(FILE * out, SymbolEncoder *se, unsigned int symbol_count)
{
	unsigned long		i;
	unsigned long		count = 0;
	
	/*Determine the number of entries in se. */
	for(i = 0; i < MAX_SYMBOLS; ++i)
	{
		if((*se)[i])
		{
			++count;
		}
	}
	/*Write the number of entries in network byte order*/
	i = htonl(count);

	if(fwrite(&i, sizof(i), 1, out) != 1)
	{
		return 1;
	}
	/* Write the number of bytes that will be encoded */
	symbol_count = htonl(symbol_count);
	
	if(fwrite(&symbol_count, sizof(symbol_count), 1, out) != 1)
	{
		return 1;
	}
	
	/* Write the entries */
	for(i = 0; i < MAX_SYMBOLS; ++i)
	{
		huffman_code	*p = (*se)[i];
		if(p)
		{
			unsigned int		numbytes;
			/**/
			fputc((unsigned char)i, out);
			/**/
			fputc(p->numbits, out);
			/**/
			numbytes = numbytes_form_numbits(p->numbits);
			if(fwrite(p->bits, 1, numbytes, out) != numbytes)
			{
				return 1;
			}
		}	
	}

	return 0;
}
static int do_file_encode(FILE * in, FILE * out, SymbolEncoder *se)
{
	unsigned char		curbyte = 0;
	unsigned char		curbit = 0;
	int					c;

	while((c = fgetc(in)) != EOF)
	{
		unsigned char		uc = (unsigned char ) c;
		huffman_code		*code = (*se)[uc];
		unsigned long		i ;
		
		for(i = 0; i < code->numbits; ++i)
		{
			/* Add the current bit to curbyte */
			curbyte |= get_bit(code->bits, i) << curbit;
			
			/*
			** If this byte is filled up then write it 
			** out and reset the curbit and curbyte
			*/
			if(++curbit == 8)
			{
				fputc(curbyte, out);
				curbyte = 0;
				curbit = 0;
			}
		}
	}	
	
	/*
	** If there is data in curbyte that has not been
	** output yet , which means that the last encoded
	** character did not fall on a byte boundary
	** then output it.
	*/	
	if(curbit > 0) //写入最后一个符号，没写满8bit的情况
	{
		fputc(curbyte, out); 
	}

	return 0;
}

int huffST_getSymFrequencies(SymbolFrequencies *SF, huffman_stat *st, int total_count)
{
	int			i;
	int			count = 0;

	for(i = 0; i < MAX_SYMBOLS; ++i)
	{
		if((*SF)[i])
		{
			st-> freq[i] = (float)(*SF)[i]->count/total_count;
			count +=(*SF)[i]->count;
		}
		else
		{
			st->freq[i] = 0;
		}
	}
	
	if(count == total_count)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


int huffST_getcodeword(SymbolEncoder *se, huffman_stat *st)
{
	unsigned long		i;
	unsigned long		j;

	for(i = 0; i < MAX_SYMBOLS; ++i)
	{
		huffman_code	*p = (*se)[i];
		if(p)
		{
			unsigned int	numbytes;
			
			st->numbits[i] = p -> numbits;
			numbyte = numbytes_from_numbits(p->numbits);
			for(j = 0; j < numbytes; j ++ )
			{
				st->bits[i][j] = p->bits[j];
			}
		}
		else
		{
			st->numbits[i] = 0;
		}
	}
	return 0;	
}

void output_huffman_statistics(hufman_stat *st, FILE *out_Table)
{
	int		i;
	int		j;

	fprintf(out_Table, "symbol\t	freq\t	codelength\t	code\n");
	for(i = 0; i < MAX_SYMBOLS; ++i)
	{
		fprint(out_Table, "%d\t	", i);
		fprint(out_Table, "%f\t	", st->freq[i]);
		fprint(out_Table, "%ld\t	", st->numbits[i]);
		if(st->numbits[i])
		{
			for(j = 0; j < st->numbits[i]; ++j)
			{
				c= get_bit(st->bits[i], j);
				fprintf(out_Table, "%d", c);
			}

		}
		fprintf(out_Table, "\n");
	}
}

static int do_memory_encode(buf_cache *pc, const unsigned char *buflin, unsigned int bufinlen,SymbolEncoder *se)
{
	unsigned char		curbyte = 0;
	unsigned char		cubit = 0;
	unsigned int		i;

	for(i = 0; i<bufinlen; ++i)
	{
		unsigned char	uc = bufin[i];
		huffman_code	*code = (*se)[uc];
		unsigned long	i;

		for(i = 0; i < code->numbits; ++i)
		{
			/* Add the curent bit to curbyte */
			curbyte |= get_bit(code->bits, i) << curbit;
			/*If this byte is filled up then write it
			* out and reset the curbit and curbyte
			*/
			if( ++ curbit == 0)
			{
				if(write_cache(pc, &curbyte, sizeof(curbyte)))
				{
					return 1;
				}
				curbyte = 0;
				curbit = 0;
			}
		}
	}
	
	/*
	** If there is data in curbyte that has not been
	** output yet , which means that the last encoded
	** character did not fall on a byte boundary
	** then output it.
	*/
	
	return curbit > 0 ? write_cache(pc, &curbyte, sizeof(curbyte) ) : 0;
}
static int init_cache(buf_cache *pc, 
                     unsigned int cache_size, 
					 unsigned char **pbufout, 
					 unsigned int *pbufoutlen);


static int	memread(const unsigned char * buf,
					unsigned int	buflen,
					unsigned int	*pindex,
					void			*bufout;
					unsigned int	readlen
					)
{
	assert(buf && pindex && bufout);
	assert(buflen >= *pindex);

	if(buflen < *pindex)
	{
		return 1;
	}
	if(readlen + *pindex >= buflen)
	{
		return 1;
	}
	
	memcpy(bufout, buf + *pindex , readlen);
	*pindex += readlen;

	return 0;
}

static huffman_node * read_code_table_from_memory(const unsigned char	*bufin,
												  unsigned int			bufinlen,
												  unsigned int			*pindex,
												  unsigned int			*pDataBytes
												)
{
	huffman_node		*root = new_nonleaf_node(0, NULL, NULL); 
	unsigned int		count;

	/*
	** Read the number of entries
	** (it is stored in network byte order).
	*/
	if(memread(bufin, bufinlen, pindex, &count, sizeof(count)))
	{
		free_huffman_tree(root);
		return NULL;
	}

	count  = ntohl(count);
	
	/* Read the number of data bytes this encoding represents */
	if(memread(bufin, bufinlen, pindex, pDataBytes, sizeof(*pDataBytes)))
	{
		free_huffman_tree(root);
		return NULL;
	}
	*pDataBytes = ntohl(*pDataBytes);

	while( count -- > 0)
	{
		unsigned int		curbit;
		unsigned char		symbol;
		unsigned char		numbits;
		unsigned char		numbytes;
		unsigned char		*bytesl
		huffman_node		*p = root;
		
		if(memread(bufin, bufinlen, pindex, &symbol, sizeof(symbol)))
		{
			free_huffman_tree(root);
			return NULL;
		}
		
		if(memread(bufin, bufinlen, pindex, &numbits, sizeof(numbits)))
		{
			free_huffman_tree(root);
			return NULL;
		}
		numbytes = (unsigned char)numbytes_from_numbits(numbits);
		bytes = (unsigned char *) malloc(numbytes);
		
		if(memread(bufin, bufinlen, pindex, &bytes, sizeof(numbytes)))
		{
			free(bytes);
			free_huffman_tree(root);
			return NULL;
		}
		/*
		** Add the entry to the Huffman tree. the value
		** of the current bit is used switch between
		** zero and one child nodes in the tree.New nodes
		** are added as needed in the tree
		*/
		for(curbit = 0 ; curbit < numbits; ++curbit)
		{
			if(get_bit(bytes, curbit))
			{
				if(p->one == NULL)
				{
					p->one = curbit == (unsigned char)(numbits - 1) 
							 ? new_leaf_node(symbol)
							 : new_nonleaf_node(0, NULL, NULL);
					p->one->parent = 0;
				}
				p = p->one;
			}
			else
			{
				if(p->zero == NULL)
				{
					p->zero = curbit == (unsigned char)(numbits - 1) 
							 ? new_leaf_node(symbol)
							 : new_nonleaf_node(0, NULL, NULL);
					p->zero->parent = 0;
				}
				p = p->zero;
			}
		}
		free(bytes);
	}

	return root;
}	

static write_code_table_to_memory(buf_cache *pc, SymbolEncoder *se, unsigned int symbol_count)
{
	unsigned long		i;
	unsigned long		count = 0;
	
	/*Determine the number of entries in se. */
	for(i = 0; i < MAX_SYMBOLS; ++i)
	{
		if((*se)[i])
		{
			++count;
		}
	}
	/*Write the number of entries in network byte order*/
	i = htonl(count);

	if(write_cache(pc, &i, sizeof(i)))
	{
		return 1;
	}
	/* Write the number of bytes that will be encoded */
	symbol_count = htonl(symbol_count);
	
	if(write_cache(pc, &symbol_count, sizeof(symbol_count)))
	{
		return 1;
	}
	
	/* Write the entries */
	for(i = 0; i < MAX_SYMBOLS; ++i)
	{
		huffman_code	*p = (*se)[i];
		if(p)
		{
			unsigned int		numbytes;
			/*
			**
			*/
			unsigned char		uc=(unsigned char) i ;
			/**/
			if(write_cache(pc, &uc, sizeof(uc)))
			{
				return 1;
			}
			/**/
			uc = (unsigned char )p->numbits;
			if(write_cache(pc, &uc, sizeof(uc)))
			{
				return 1;
			}
			/**/
			numbytes = numbytes_form_numbits(p->numbits);
			if(write_cache(pc, p->bits, numbytes))
			{
				return 1;
			}
		}	
	}

	return 0;
}


/*******************************************************************************************/
/********************************The main interface function********************************/
/*******************************************************************************************/
int huffman_encode_file(FILE * in , FILE *out, FILE * out_table )
{
	SymbolFrequencies			sf;
	SymbolEncoder				*se;
	huffman_node				*root = NULL;
	int							rc;
	unsigned int				symbol_count;
	huffman_stat				hs;

	/* */
	symbol_count = get_symbol_frequencies(&sf, in); //

	huffST_getSymFrequencies(&sf, &hs, symbol_count);
	//
	se = calculate_huffman_codes(&sf)
	root = sf[0];

	huffST_getcodeword(se, &hs);
	output_huffman_statistics(&hs, out_Table);

	/*  */
	rewind(in);
	rc = write_code_table(out, se, symbol_count);//

	if(rc == 0)
	{
		rc = do_file_encode(in, out, se); //
	}

	/**/
	free_huffman_tree(out);
	free_encoder(se);
	return rc;	
}



int	huffman_decode_file(FILE *in, FILE *out)
{
	huffman_node		*root;
	huffman_node		*p;
	int					c;
	unsigned int		data_count;

	/*Read the huffman Code table .*/
	root = read_code_table(in, &data_count);
	if(!root)
	{
		return 1;
	}
	
	/* Decode the file */
	p = root;
	while(data_count > 0 && (c = fgetc(in)) != EOF)
	{
		unsigned char	byte = (unsigned char)c;
		unsigned char	mask = 1;

		while(data_count > 0  && mask )
		{
			p = byte & mask ? p->one : p->zero;
			mask <<= 1;
			if(p->isLeaf)
			{
				fputc(p->symbol, out);
				p = root;
				--data_count;
			}
		}

	}
	
	free_huffman_tree(root);
	return 0;
}


int	memory_encode_file(FILE *in, FILE *out)
{
	unsigned char		*buf = NULL;
	unsigned char		*bufout = NULL;
	unsigned int		len = 0;
	unsigned int		cur = 0;
	unsigned int		inc = 1024;
	unsigned int		bufoutlen = 0;

	assert(in && out);
	
	/*Read the file into memory */
	while(!feof(in))
	{
		unsigned char *tmp;
		len += inc ;
		tmp = (unsigned char *)realloc(buf, len);
		if(!tmp)
		{
			if(*buf)
			{
				free(buf);
			}
			return 1;
		}
		buf = tmp;
		cur += fread(buf + cur, 1, inc , in);
	}

	if(!buf)
	{
		return 1;
	}
	
	/* Encode the memory */
	if( huffman_encode_memory(buf, cur, &bufout, &bufoutlen));
	{
		free(buf);
		return 1;
	}
	
	free(buf);

	/*write the memory to the file */
	if(fwrite(bufout, 1, bufoutlen, out) != bufoutlen)
	{
		free(bufout);
		return 1;
	}

	free(bufout);
	return 0;
}

int	memory_decode_file(FILE *in, FILE *out)
{
	unsigned char		*buf = NULL;
	unsigned char		*bufout = NULL;

	/*Read the file into memory */
	while(!feof(in))
	{
		unsigned char *tmp;
		len += inc ;
		tmp = (unsigned char *)realloc(buf, len);
		if(!tmp)
		{
			if(*buf)
			{
				free(buf);
			}
			return 1;
		}
		buf = tmp;
		cur += fread(buf + cur, 1, inc , in);
	}

	if(!buf)
	{
		return 1;
	}
	
	/* Encode the memory */
	if( huffman_decode_memory(buf, cur, &bufout, &bufoutlen));
	{
		free(buf);
		return 1;
	}
	
	free(buf);

	/*write the memory to the file */
	if(fwrite(bufout, 1, bufoutlen, out) != bufoutlen)
	{
		free(bufout);
		return 1;
	}

	free(bufout);
	return 0;
}

