/*
 * Author: ablink4
 * 
 * TODO: 
 * 
 * 1.  see if I can figure out how to determine filtered ports on the
 *     TCP connect scan to eliminate unnecessary timeout so scan doesn't
 *     take forever.
 * 2.  implement a TCP SYN scan with raw packets to try and improve
 *     performance.  
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
#include <signal.h>

#define LAST_PORT 65535 // largest valid port number

// to catch SIGALRM raised by alarm()
void signal_handler(int signum)
{
	// ignore signal, interrupt current blocking call, and continue
}

// function to do a TCP connect scan
// assumes signal handler for SIGALRM is already setup
void tcp_conn_scan(const char* host)
{
	int socket_fd = -1; 
	
	struct sockaddr_in sock_info;
	struct hostent *host_ptr;
	
	host_ptr = gethostbyname(host);
	
	if(host_ptr == NULL)
	{
		std::cerr << strerror(errno) << std::endl;
		close(socket_fd);
		exit(-1);
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

		sock_info.sin_port = htons(i); 

		// use alarm to timeout for closed sockets
		// set rc to an unsuccessful value upfront so if we timeout we 
		// go into error block
		int rc = -1;
		alarm(1);
		rc = connect(socket_fd, (struct sockaddr*)&sock_info, sizeof(sockaddr_in));
		alarm(0);

		if(rc < 0)
		{
			//std::cerr << strerror(errno) << std::endl;
			close(socket_fd);
		}
		else
		{
			std::cout << "Port " << i << " connected successfully!" << std::endl;
			close(socket_fd);
		}
	}
}

int main(int argc, char *argv[])
{
	if(argv[1] == NULL)
	{
		std::cerr << "Invalid argument: arg 1 must be hostname to scan." << std::endl;
		exit(-1);
	}
	
	const char *hostname = strdup(argv[1]); 
	
	// register SIGALRM hanlder with sigaction()
	// to ensure connect() is interrupted when alarm is raised
	struct sigaction sa;
	
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	
	if(sigaction(SIGALRM, &sa, NULL) == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(-1);
	}
	
	tcp_conn_scan(hostname);
	
    return(0);
}
