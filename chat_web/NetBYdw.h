/* filename: NetBYdw.h
 * date:     2021.5.21
 * by:       dw
 * version:  0.1
*/
#ifndef __NETBYDW_H_
#define __NETBYDW_H_

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<errno.h>
#include<iostream>
class net{
	public:
		sockaddr_in server;
		socklen_t len;
	public:
		net();
		~net();
		int Socket(int Domain,int Type,int protocol);
		void Bind(int Socketfd,const struct sockaddr *addr,socklen_t addrlen);
		void Listen(int Socketfd,int backlog);
		int Accept(int Socketfd,struct sockaddr *addr,socklen_t *addrlen);
		void Connect(int Socketfd,const struct sockaddr *addr,socklen_t addrlen);
		void set_sockaddr_in(int Domain,char *ip,int port);
};
char* itoa(int num,char* str,int radix);
#endif
