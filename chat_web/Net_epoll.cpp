#include"Net_epoll.h"

Epoll::Epoll(){
}
Epoll::~Epoll(){}

int Epoll::Epoll_create(int size){
	int epfd;
	epfd=epoll_create(size);
	if(epfd<0){
		perror("Epoll is error");
		exit(-1);
	}

	return epfd;
}
void Epoll::Epoll_ctl(int epfd,int op,int fd,struct epoll_event *event){
	int ret;
	ret=epoll_ctl(epfd,op,fd,event);
	if(ret<0){
		perror("Epoll_ctl is error");
		exit(-1);
	}
}
int Epoll::Epoll_wait(int epfd,struct epoll_event *events,int maxevents,int timeout){
	int ret;
	ret=epoll_wait(epfd,events,maxevents,timeout);
	if(ret<0){
		perror("Epoll_ctl is error");
		exit(-1);
	}

	return ret;
}
