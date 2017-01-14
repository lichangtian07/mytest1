/* 服务器端程序service.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 80  /* 缓冲区大小  */
#define SERV_PORT   8000
/* 8000端口 */


int main()
{
	struct sockaddr_in  servaddr, cliaddr;
	socklen_t	cliaddr_len;
	int			listenfd, connfd;
	char		buf[MAXLINE];
	char		str[INET_ADDRSTRLEN];
	int			i,n; /* IPV4  16 为了防止溢出 */

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	/* 建立socke他描述符，提供面向连接的TCP服务 */
    bzero(&servaddr,sizeof(servaddr)); /* 整个结构体清零 */
	servaddr.sin_family = AF_INET;  /* 选用IPv4因特网协议 */
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	/* 服务器IP选任意， 转换成网络字节序 */	
	servaddr.sin_port = htons(SERV_PORT);
		
	/* 服务器端口，转换成网络字节序 */
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	listen(listenfd, 20);
	printf("Accepting connections .....\n");
	
	while(1)
	{
		memset(buf, '\0', MAXLINE);
		cliaddr_len =	sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		/* 等待客户端的连接请求 */
		n = read(connfd, buf, MAXLINE);
		/* 从客户端读数据到缓冲区 */
		//printf(“received from %s at PORT %d\n”,inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));	
		printf("received from %s at PORT %d\n",(char *)inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
		printf(" recieve  message from client : %s \n", buf);	
		
		printf("\n");	
		for (i = 0 ; i < n; i ++)
		{
			buf[i] = toupper(buf[i]); /* 变小写为大写 */
		}

		write(connfd, buf, n); /* 大写后再写回客户端 */
		close(connfd);		/* 关闭连接 */
	}

	
	return 1;
}





