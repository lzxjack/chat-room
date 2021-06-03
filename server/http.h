#ifndef __HTTP_H_
#define __HTTP_H_
/*
"Access-Control-Allow-Origin:47.110.144.145:4567\r\n"
"Access-Control-Allow-Methods:GET\r\n"
"Access-Control-Allow-Credentials:true\r\n"
*/
#include<iostream>
#include<string.h>
#include<unordered_map>
#include<string>
#include"NetBYdw.h"
#include<fcntl.h>
#include<stdlib.h>
#include <sys/stat.h>
#include<vector>
//响应头
const char success[]="HTTP/1.1 200 ok\r\n"
                    "Connection:keep-alive\r\n"
                    "Access-Control-Allow-Origin:*\r\n"
                    //"Access-Control-Allow-Origin:http://47.110.144.145:80\r\n"
                    "Access-Control-Allow-Methods:POST,GET,OPTIONS,DELETE\r\n"
                    "Access-Control-Max-Age:3600\r\n"
                    "Access-Control-Allow-Headers:x-requested-with,content-type\r\n"
                    "Access-Control-Expose-Headers:serve-header\r\n"
                    "Content-Length:";
class http{
    private:
        char login_status[16];
        struct _client{
            char name[10];
            char pwd[18];
            char _hash[32];
            int client_fd;
            std::vector<std::string> chat_record;
        }Client;
        
    public:
        char Request_method[8];//请求方法
        char Request_data[1024];//报文整体，相当于in_str
        char send_data[1024];//需要发送的报文数据
        char Newspaper_data[1024];//报文体
        std::unordered_map<std::string,std::string> data_map;//报文真实数据
        std::unordered_map<std::string,_client> data_client;//客户数据
        
    
    public:
        http();
        ~http();
        char * http_Request_method(char in_str[],char out_str[]);//
        char * http_get_Newspaper(char in_str[],char out_str[]);//
        int    http_send(char out_str[]);//
        int    http_put(int client_fd);
        int    http_post(int client_fd);
        int    http_get(int client_fd);
        int    http_get_data(char in_str[]);//
        int    http_delete(char in_str[]);
        int    http_get_original_news(char in_str[]);
};


#endif 
