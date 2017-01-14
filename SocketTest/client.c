/* 客户端client.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT  8000
/* 端口号 */
#define MAXLINE	80


int main(int argc, char * argv[])
{
	struct sockaddr_in	servaddr;
	char				buf[MAXLINE];
	int					sockfd;
	int					n;
	char *				str;
	
	if (argc != 2)
	{
		fputs("usage: /client message \n", stderr);
		exit(1);
	}
	/* 第二参数为要发送到服务器的字符 */
	str = argv[1];
	/* 建立socket描述符，提供面向连接的TCP服务 */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/* 整个结构体清零 */
	bzero(&servaddr, sizeof(servaddr));
	/* 选用IPv4因特网协议 */
	servaddr.sin_family = AF_INET;
	/*
	**	原型: int inet_pton(int af, const char *src, void* dst); 
	**	src 为指向字符型的地址，即ASCII的地址的首地址（ddd ddd ddd ddd格式的），这里需要输入服务器IP地址。
	**	函数将该地址转换为in_addr的结构体，并复制在*dst中
	**	
	*/
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	
	/* 服务端口，转换成网络字节序 */
	servaddr.sin_port = htons(SERV_PORT);
	
	/* 连接服务器 */
	connect(sockfd,(struct sockaddr *)&servaddr, sizeof(servaddr));
	
	/* 写数据到服务器 */
	write(sockfd, str, strlen(str));
	
	n=read(sockfd, buf, MAXLINE);
	printf("response from server: \n");
	
	/* 把从服务器读到的数据输出到标准输出 */	
	write(STDOUT_FILENO,buf,n);
	printf("\n");
	/* 关闭连接 */
	close(sockfd);
	return 0;
}




