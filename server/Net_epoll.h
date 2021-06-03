#ifndef __NET_EPOLL_H_
#define __NET_EPOLL_H_

#include "NetBYdw.h"
#include<sys/epoll.h>
const int MAXSIZE=1024;
class Epoll{
	public:
		struct epoll_event e_event[MAXSIZE];
	public:
		Epoll();
		~Epoll();
		int Epoll_create(int size);
		void Epoll_ctl(int epfd,int op,int fd,struct epoll_event *event);
		int Epoll_wait(int epfd,struct epoll_event *events,int maxevents,int timeout);
};
#endif
