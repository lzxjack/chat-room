server:	server.o NetBYdw.o Net_epoll.o sign_in.o http.o
		g++ -g server.o NetBYdw.o Net_epoll.o sign_in.o http.o -o server 
server.o: server.cpp Net_epoll.h NetBYdw.h
		g++ -c server.cpp -o server.o -g
Net_epoll.o: Net_epoll.cpp Net_epoll.h
		g++ -c Net_epoll.cpp  -o Net_epoll.o -g
NetBYdw.o: NetBYdw.cpp NetBYdw.h
		g++ -c NetBYdw.cpp  -o NetBYdw.o -g
sign_in.o: sign_in.cpp sign_in.h
		g++ -c sign_in.cpp  -o sign_in.o -g
http.o: http.cpp http.h
		g++ -c http.cpp  -o http.o -g

clean:
	rm -rf server.o Net_epoll.o NetBYdw.o sign_in.o http.o