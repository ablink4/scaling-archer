/*
 * Author: ablink4
 * 
 * TODO list:
 *   1. ping IP address before trying to connect to it
 *   2. figure out how to reduce timeout on closed ports
 * 
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h> // memcpy()
#include <unistd.h> // close()
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

#define LAST_PORT 65535 // largest valid port number

void set_nonblock(int socket) 
{
    int flags;
    flags = fcntl(socket,F_GETFL,0);
    assert(flags != -1);
    fcntl(socket, F_SETFL, flags | O_NONBLOCK);
}

int main()
{
	int socket_fd = -1; 
	
	struct sockaddr_in sock_info;
	struct hostent *host_ptr;
	
	// using google as a test
	const char *hostname = "www.google.com"; 
	
	host_ptr = gethostbyname(hostname);
	
	if(host_ptr == NULL)
	{
		std::cerr << strerror(errno) << std::endl;
		close(socket_fd);
		exit(-2);
	}

	memcpy((char*)&sock_info.sin_addr, host_ptr->h_addr, host_ptr->h_length);
	sock_info.sin_family = AF_INET;
	
	for(int i = 1; i <= LAST_PORT; i++)
	{	
		socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
		
		if(socket_fd < 0)
		{
			std::cerr << strerror(errno) << std::endl;
			exit(-1);
		}
		
		//set_nonblock(socket_fd);

		sock_info.sin_port = htons(i); 

		if(connect(socket_fd, (struct sockaddr*)&sock_info, sizeof(sockaddr_in)) < 0)
		{
			std::cerr << strerror(errno) << std::endl;
			close(socket_fd);
		}
		else
		{
			std::cout << "Port " << i << " connected successfully!" << std::endl;
			close(socket_fd);
		}
	}
	
    return(0);
}
