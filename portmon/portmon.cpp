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
	
	for(int i = 0; i <= LAST_PORT; i++)
	{
	
		socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
		
		if(socket_fd < 0)
		{
			perror("Could not create socket.\n");
			exit(-1);
		}
		
		set_nonblock(socket_fd);
		
		struct sockaddr_in sock_info;
		struct hostent *host_ptr;
		
		// using google as a test
		const char *hostname = "www.google.com"; 
		
		host_ptr = gethostbyname(hostname);
		
		if(host_ptr == NULL)
		{
			perror("Could not get host by name.\n");
			close(socket_fd);
			exit(-2);
		}

		memcpy((char*)&sock_info.sin_addr, host_ptr->h_addr, host_ptr->h_length);
		sock_info.sin_family = AF_INET;
		
		sock_info.sin_port = htons(i); 

		if(connect(socket_fd, (struct sockaddr*)&sock_info, sizeof(sockaddr_in)) < 0)
		{
			perror("Could not connect socket.\n");
			close(socket_fd);
			//exit(-3);
		}
		else
		{
			printf("Port %d connected successfully!\n", i);
			close(socket_fd);
		}
	}
	
    return(0);
}
