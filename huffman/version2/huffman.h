

#ifndef  __HUFFMAN_H_ 
#define  __HUFFMAN_H_


/*************************************************************************************/
/********************************The Global DEFINE************************************/
/*************************************************************************************/
#define MAX_SYMBOLS		256
#define CACHE_SIZE		1024


/*************************************************************************************/
/********************************The Global Struct************************************/
/*************************************************************************************/

typedef struct  huffman_node_tag{
	unsigned char				isLeaf; // 是否是树叶结点， 1代表是 0代表否
	unsigned char				count; // 结点代表的符号加权和
	struct huffman_node_tag		*parent;//父结点指针
	union {
		struct {                  // 如果不是叶子结点 
			struct huffman_node_tag		*zero;	// 指向左孩子  即0 
			struct huffman_node_tag		*one;	// 指向右孩子  即1
		};
		unsigned char			symbol; //如果是叶子结点 存放信源符号 （1字节）
	};
	
} huffman_node;



typedef struct huffman_code_tag{
	/* The length of this code is bits*/
	unsigned long			numbits;   //码字长度 单位：位
	/*
	**码字的第1位存于bit[0]第1位，
	**码字的第2位存于bit[0]第2位，
	**码字的第8位存于bit[0]第8位，
	**码字的第9位存于bit[1]第1位，
	*/
	unsigned char			*bits; //指向该码字比特串的指针

} huffman_code;

//用于统计的结构体：存放信源符号的信息：符号频率 比特数 符号码字
typedef struct huffman_statistic_result{
	float					freq[256];
	unsigned long			numbits[256];
	unsigned char			bit[256][100];
} huffman_stat;


//用于内存处理的结构体
typedef struct buf_cache_tag{
	unsigned char			*cache;
	unsigned int			cache_len;
	unsigned int			cache_cur;
	unsigned char			**pbufout;
	unsigned int			*pbufoutlen;
}buf_cache;



typedef huffman_node	*SymbolFrequencies[MAX_SYMBOLS]; //表示信源符号的数组 
typedef huffman_code	*SymbolEncoder[MAX_SYMBOLS]; //表示码字的数组，用于保存码表


#endif //__HUFFMAN_H_

