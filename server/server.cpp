#include"NetBYdw.h"
#include"Net_epoll.h"
#include "sign_in.h"
#include <unordered_map>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "http.h"
#include<sys/sendfile.h>

#define port 4567
char ip[]="172.17.56.228";
//char ip[]="172.16.10.66";
struct _client{	
	int fd_id;
	int flag;
	char name[1024];	
};
int main(int argc,char *argv[]){
	int r_ret=fork();
	if(r_ret==0){
		setsid();
	}else{
		sleep(1);
		exit(1);
	}
	int server_fd,client_fd,epfd;
	int client[MAXSIZE];
	int flag1=0,flag2=0;
	std::unordered_map<int,_client> client_map;
	socklen_t server_len,client_len;
	net Server;
	sockaddr_in Client;
	struct epoll_event tev;
	Epoll _epoll;
	http _http;

	Server.set_sockaddr_in(AF_INET,ip,htons(port));

	server_fd=Server.Socket(AF_INET,SOCK_STREAM,0);
	const int reuse = 1;            
	setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));//解决服务器先关闭
	Server.Bind(server_fd,(struct sockaddr *)&Server.server,sizeof(Server.server));

	Server.Listen(server_fd,128);

//	client_fd=Server.Accept(server_fd,(struct sockaddr *)&client,&client_len);
	
	int i=0;
	for(i=0;i<MAXSIZE;++i)
		client[i]=-1;
	int _addr=-1;

	epfd=_epoll.Epoll_create(MAXSIZE);

	tev.events=EPOLLIN;
	tev.data.fd=server_fd;
	_epoll.Epoll_ctl(epfd,EPOLL_CTL_ADD,server_fd,&tev);

	while (1){
		int ret;
		ret=_epoll.Epoll_wait(epfd,_epoll.e_event,MAXSIZE,0);

		for(i=0;i<ret;++i){
			if((EPOLLIN&_epoll.e_event[i].events)==0)
				continue;
			if(_epoll.e_event[i].data.fd==server_fd){
				client_fd=Server.Accept(server_fd,(struct sockaddr*)&Client,&client_len);
				char str[64];
				std::cout<<"received from "<<inet_ntop(AF_INET,&Client.sin_addr.s_addr,str,sizeof(str))<<" at PORT"<<ntohs(Client.sin_port)<<std::endl;
				//把建立连接的客户端文件描述符写入clinet数组
				int j;
				for(j=0;i<MAXSIZE;++j){
					if(client[j]<0){
						client[j]=client_fd;
						break;
					}
				}
				
				//判断是否达到连接上限
				if(j==MAXSIZE){
					std::cout<<"client is full"<<std::endl;
					break;
				}
				client_map.insert(std::pair<int,_client>(client_fd,{client_fd,0,0}));
				//把指向栈顶的指针_addr移位
				if(j>_addr) _addr=j;
				//把得到的客户端文件描述符写入epfd中
				tev.events=EPOLLIN;
				tev.data.fd=client_fd;
				_epoll.Epoll_ctl(epfd,EPOLL_CTL_ADD,client_fd,&tev);
				//登陆界面
				char __str[1024];
				memset(__str,0,sizeof(__str));
				int __ret=read(client_fd,__str,sizeof(__str));
				if(__ret<0){
					perror("post read error\n");
				}
				printf("%s\n",__str);
				_http.http_get_original_news(__str);
				_http.http_Request_method(_http.Request_data,_http.Request_method);
				if(strcmp(_http.Request_method,"GET")==0){
						std::cout<<"22222"<<std::endl;
						_http.http_get(client_fd);
						memset(_http.Request_method,0,sizeof(_http.Request_method));
						memset(_http.Request_data,0,sizeof(_http.Request_data));
						
					}else if(strcmp(_http.Request_method,"PUT")==0){
						std::cout<<"3333"<<std::endl;
						_http.http_put(client_fd);
						memset(_http.Request_method,0,sizeof(_http.Request_method));
						memset(_http.Request_data,0,sizeof(_http.Request_data));

					}else if(strcmp(_http.Request_method,"POST")==0){
						std::cout<<"44444"<<std::endl;
						_http.http_post(client_fd);
						memset(_http.Request_method,0,sizeof(_http.Request_method));
						memset(_http.Request_data,0,sizeof(_http.Request_data));

					}else if(strcmp(_http.Request_method,"Delete")==0){

					}else{

					}
			}else{
				int read_fd=_epoll.e_event[i].data.fd;
				int ret_sum;
				char buf[1024];
				memset(buf,0,sizeof(buf));
				ret_sum=read(read_fd,buf,sizeof(buf));
				if(ret_sum<0){
					perror("read error");   
				}else if(ret_sum==0){
					char str[64];
					std::cout<<inet_ntop(AF_INET,&Client.sin_addr,str,sizeof(str))<<"  is closed"<<std::endl;
					int j=0;
					for(j=0;j<MAXSIZE;++j){
						if(client[j]==read_fd){
							client[j]=-1;
							break;
						}
					}
					client_map.erase(read_fd);
					_epoll.Epoll_ctl(epfd,EPOLL_CTL_DEL,read_fd,_epoll.e_event);
					close(read_fd);
				}else{
					printf("%s\n",buf);
					_http.http_get_original_news(buf);
					_http.http_Request_method(_http.Request_data,_http.Request_method);
					memset(buf,0,sizeof(buf));
					if(strcmp(_http.Request_method,"GET")==0){
						std::cout<<"22222"<<std::endl;
						_http.http_get(read_fd);
						memset(_http.Request_method,0,sizeof(_http.Request_method));
						memset(_http.Request_data,0,sizeof(_http.Request_data));
						
					}else if(strcmp(_http.Request_method,"PUT")==0){
						std::cout<<"3333"<<std::endl;
						_http.http_put(read_fd);
						memset(_http.Request_method,0,sizeof(_http.Request_method));
						memset(_http.Request_data,0,sizeof(_http.Request_data));

					}else if(strcmp(_http.Request_method,"POST")==0){
						std::cout<<"44444"<<std::endl;
						_http.http_post(read_fd);
						memset(_http.Request_method,0,sizeof(_http.Request_method));
						memset(_http.Request_data,0,sizeof(_http.Request_data));

					}else if(strcmp(_http.Request_method,"Delete")==0){

					}else{

					}
				}
			}
		}
	}
	close(server_fd);
	close(epfd);
	return 0;
}