/*
 * Author: ablink4
 * Description: class to implement IP raw packets
 *
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h> 
 
#include <arpa/inet.h> // for inet_addr
 
class RawPacket
{
	public:
		RawPacket()
		{
			// TODO: implement other socket types (ICMP, UDP)
			// TODO: take value to initialize port
			
			// opens a raw TCP socket - note: AF_INET is equivalent to PF_INET
			_sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
			
			if(_sock < 0)
			{
				std::cerr << strerror(errno) << std::endl;
				
				// FXIME: best way to handle this error?
			}
			else
			{
				build_tcp_header();
			}
		}
	
		void do_work()
		{
			// TODO
		}
		
	private:
		
		int _sock;
		char _packet[4096]; // buffer for IP header, transport header, and payload; // TODO: where does 4096 come from?
		struct sockaddr_in _sin;
		int _port;  // TODO: initialize this
		char* _address; // TODO: initialize this
		
		void build_tcp_header()
		{
			struct ipheader *iph = (struct ipheader*)_packet;
			struct tcpheader *tcphdr = (struct tcpheader*)_packet + sizeof(struct ipheader);
			
			_sin.sin_family = AF_INET;
			_sin.sin_port = htons(_port); // TODO: need to initialize _port
			_sin.sin_addr.s_addr = inet_addr(_address); // TODO: need to initialize this 
			
			// TODO: complete this function
			
		}
		
		
		// compute 16-bit 1s complement checksum (for IPv4)
		unsigned short cksum(unsigned short *buffer, int nwords)
		{
			unsigned long cksum; // do 32-bit addition for efficiency
			
			// sum each 16-bit word together 
			for(cksum = 0; nwords > 0; nwords--)
			{
				cksum += *buffer;
				++buffer;
			}
			
			// add overflow from most significant word into least significant word
			cksum = (cksum >> 16) + (cksum & 0xffff);
			
			// first addition could potentially overflow least significant word, so we 
			// add any remaining overflow - don't need to do this 3 times
			cksum += cksum >> 16;
			
			// return the 1s complement. The cast is for clarity - the value we
			// return is only 2 bytes long
			return((unsigned short)~cksum);
		}
		
		/***** packet header data structures *****/
		
		/* NOTE: we could use structures from Linux headers, but define our own for portability */
		
		/* IP header structure - used to fill in header for IP packets */
		struct ipheader 
		{
			unsigned char ip_hl:4, ip_v:4; // each member has 4 bits; hl is almost always 5, v is always 4
			unsigned char ip_tos; // type of service - typically 0
			unsigned short int ip_len; // total packet length, including transport header and payload
			unsigned short int ip_id; // seq num for fragmented packets
			unsigned short int ip_off; // fragmented packet offset
			unsigned char ip_ttl; // time to live
			unsigned char ip_p; // transport protocol - 1 (icmp), 6 (tcp), 17 (udp)
			unsigned short int ip_sum; // 16-bit 1s complement checksum
			unsigned int ip_src; // source address converted to long format by inet_addr()
			unsigned int ip_dst; // destination address converted to long format by inet_addr()
		}; // total ip header length: 20 bytes 
		
		/* transport layer header for ICMP packets */
		struct icmpheader 
		{
			unsigned char icmp_type; // message type
			unsigned char icmp_code; // code for error messages
			unsigned short int icmp_cksum; // checksum of transport-layer message (icmp header + payload)
			unsigned short int icmp_id; // identifies request in echo messages
			unsigned short int icmp_seq; // sequence of echo messages
		}; // total icmp header length: 8 bytes 
		
		/* transport layer header for UDP packets */
		struct udpheader 
		{
			unsigned short int uh_sport; // source port
			unsigned short int uh_dport; // destination port
			unsigned short int uh_len; // length of udp header + payload
			unsigned short int uh_check; // header + payload checksum
		}; // total udp header length: 8 bytes
		
		struct tcpheader 
		{
			unsigned short int th_sport; // source port
			unsigned short int th_dport; // destination port
			unsigned int th_seq; // segment sequence number
			unsigned int th_ack; // used with segments
			unsigned char th_x2:4, th_off:4; // x2 is 0x00 (unused); off is 5 unless there are tcp header options
			unsigned char th_flags; // flags
			unsigned short int th_win; // window 
			unsigned short int th_sum; // checksum
			unsigned short int th_urp; // urgent pointer - only used with TH_URG flag, otherwise 0
		}; // total tcp header length: 20 bytes (=160 bits) 
};
