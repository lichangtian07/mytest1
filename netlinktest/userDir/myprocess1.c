
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/socket.h>
#include <errno.h>

#define MAX_PAYLOAD 1024 
#define NETLINK_TEST 25

int main(int argc, char * argv[])
{
	int state;

	struct sockaddr_nl src_addr, dest_addr;

	struct nlmsghdr * nlh = NULL; // Netlink packet header
	struct iovec  iov;
	struct msghdr	msg;
	
	int		sock_fd, retval;
	int		state_smg = 0;

	sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);

	if(sock_fd == -1)
	{
		printf("error getting socket : %s \n", strerror(errno));
		return -1;
	}
	// To prepare binding 
	memset(&src_addr, 0 , sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = 100; // A: set source port
	src_addr.nl_groups = 0;

	//Bind 
	retval = bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

	if(retval < 0 )
	{
		printf("bind failed : %s ", strerror(errno));
		close(sock_fd);
		return -1;
	}
	nlh = (struct nlmsghdr *) malloc(NLMSG_SPACE(MAX_PAYLOAD));
	if(!nlh)
	{
		printf("malloc nlmsghdr eror \n");
		close(sock_fd);
		return -1;
	}
	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;
	dest_addr.nl_pid = 0; // B: set dest port
	dest_addr.nl_groups = 0;
	//nlh 	
	nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
	nlh->nlmsg_pid = 100; // c: set source port
	nlh->nlmsg_flags = 0;
	strcpy(NLMSG_DATA(nlh), "hello you !"); // set message data
	
	iov.iov_base = (void *)nlh;
	iov.iov_len = NLMSG_SPACE(MAX_PAYLOAD);
	//create message
	memset(&msg, 0, sizeof(msg));
	msg.msg_name = (void *)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	//send message 
	printf("state_smg \n");
	state_smg = sendmsg(sock_fd, &msg, 0);
	if(state_smg == -1)
	{
		printf("get error sendmsg = %s \n", strerror(errno));
	}
	memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
	//receive message 
	printf("wating received!\n");

	while(1)
	{
		printf("In while recvmsg \n");
		state = recvmsg(sock_fd, &msg, 0);
		if(state < 0 )
		{
			printf("state < 1");
		}
		printf("Received message : %s \n", (char *)NLMSG_DATA(nlh));
	}

	close(sock_fd);
	
	return 0;
}



