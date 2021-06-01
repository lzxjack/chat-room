#include"http.h"

http::http(){
    std::cout<<"http is created!"<<std::endl;
}
http::~http(){
}
/*
    报文的请求方法解析，成功返回请求方法，失败返回nullptr；
*/
char* http::http_Request_method(char in_str[],char out_str[]){//数组不能引用
    int len=0;
    for(len=0;len<10;++len){
        if(in_str[len]!=' '){
            out_str[len]=in_str[len];
        }else{
            break;
        }
    }
    if(len>=10) return nullptr;

    return out_str;
}
/*
    报文体解析，成功返回报文体，失败返回nullptr；
*/
char * http::http_get_Newspaper(char in_str[],char out_str[]){
    int len=0,flag=0,addr=0;
    for(len=0;in_str[len]!='\0';++len){
        //printf("%s\n",this->login_status);
       if(flag==0){
            addr++;
            if(in_str[len]=='/'){
                flag=1;
            }
            continue;
        }
        if(flag==1&&in_str[len]!='?'){
            this->login_status[len-addr]=in_str[len];
        }else{
            this->login_status[len-addr]='\0';
            break;
        } 
    }
    //printf("this->login_status:%s\n",this->login_status);
    len=0,flag=0,addr=0;
    for(len=0;len<1024;++len){
        if(flag==0){
            addr++;
            if(in_str[len]=='?'){
                flag=1;
            }
            continue;
        }
        if(flag==1&&in_str[len]!=' '){
            out_str[len-addr]=in_str[len];
        }else{
            out_str[len-addr]='\0';
            break;
        }
    }
    if(len>=1024) return nullptr;

    return out_str;
}
/*
    解析报文体，获取data
*/
int  http::http_get_data(char in_str[]){
    //unordered_map是深拷贝吗？
    this->data_map.clear();
    for(int i=0;in_str[i]!='\0';++i){
        //char *first=new char [1024];
        std::string first;
        for(int j=0;j<1024;++j){
            if(in_str[i]=='\0'){
                //400 客户端语法错误
                return -1;
            }
            if(in_str[i]!='='){
                first.push_back(in_str[i]);
                ++i;
            }else {
                first.push_back('\0');
                ++i;
                break;
            }
        }
        //char *second=new char [1024];
        std::string second;
        for(int j=0;j<1024;++j){
            if(in_str[i]!='&'&&in_str[i]!='\0'){
                second.push_back(in_str[i]);
                ++i;
            }else {
                second.push_back('\0');
                break;
            }
        }
        
        this->data_map.insert(std::make_pair(first.c_str(),second.c_str()));//必须这么存才能在哈希表里找到，不能存对象
    }
    return 0;
}
/*
    把数据改成发送的键值对；
*/
int  http::http_send(char out_str[]){
    auto pos=this->data_map.begin();
    if(pos==this->data_map.end()){
        return -1;
    }
    char first[1024];
    memset(first,0,sizeof(first));
    strcpy(first,"{");
    int flag=0;
    for(;pos!=this->data_map.end();++pos){
        if(flag==0){
            strcat(first,R"(")"); 
            flag=1;
        }else{
            strcat(first,R"(,")"); 
        }
        //printf("%s\n",pos->first);
        //strcat(first,pos->first);
        //delete [] pos->first;
        strcat(first,R"(":")");
        //printf("%s\n",pos->second);
        //strcat(first,pos->second);
        //delete [] pos->second;
        strcat(first,R"(")");
       
    }
    strcat(first,"}");
    strcpy(out_str,first);
    //this->data_map.clear();
    return 0;
}
int http::http_get_original_news(char str[]){//获取原始报文
    strcpy(this->Request_data,str);
    std::cout<<"http is created!"<<std::endl;
    return 0;
}
int  http::http_put(int client_fd){
    printf("%s",success);
    write(client_fd,success,strlen(success));

    this->http_get_Newspaper(this->Request_data,this->Newspaper_data);
    this->http_get_data(this->Newspaper_data);

    if(strcmp(this->login_status,"logout")==0){ 
    this->data_client.erase(this->data_map["name"].c_str());
             
    char str[]=R"({"delete":0})";
    char c_size[1024];
    memset(c_size,0,sizeof(c_size));
    itoa(strlen(str),c_size,10);
    printf("%s\r\n\r\n",c_size);
    write(client_fd,c_size,strlen(c_size));
    write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
    write(client_fd,str,strlen(str));
        
    }

    return 0;
}
int  http::http_post(int client_fd){
    printf("%s",success);
    write(client_fd,success,strlen(success));

    this->http_get_Newspaper(this->Request_data,this->Newspaper_data);
    this->http_get_data(this->Newspaper_data);

    if(strcmp(this->login_status,"information")==0){
        memset(this->Client.name,0,sizeof(this->Client.name));
        strcpy(this->Client.name,this->data_map["name"].c_str());
        
        int fd=open("chat_record",O_RDWR|O_APPEND);
        if(fd==-1){
            perror("open error");
            return -1;
        }
        std::string st;
        st=st+R"({"name":")";
        st=st+this->data_map["name"];
        st=st+R"(","msg":")";
        st=st+this->data_map["msg"];
        st=st+R"(","time":)";
        st=st+this->data_map["time"];
        st=st+R"(,"id":")";
        st=st+this->data_map["id"];
        st=st+R"("})";
        write(fd,st.c_str(),strlen(st.c_str()));
        write(fd,"\n",strlen("\n"));

        auto pos=this->data_client.begin();
        for(;pos!=this->data_client.end();++pos){
            pos->second.chat_record.push_back(st);
        }
            char str[]=R"({"msg":0})";
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            itoa(strlen(str),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));
        
    }
    return 0;
}
int  http::http_get(int client_fd){
    

    //printf("tthis->Request_data:%s\n",this->Request_data);
    this->http_get_Newspaper(this->Request_data,this->Newspaper_data);
    //printf("*******************");
    //printf("this->login_status:%s\n",this->login_status);
    this->http_get_data(this->Newspaper_data);
    //printf("%s\n",this->Client.name);

    if(strcmp(this->login_status,"login")==0){ //name=-1不存在//pwd=-1密码错误//login=1成功登录，token=密钥
        printf("%s",success);
        write(client_fd,success,strlen(success));
        memset(this->Client.name,0,sizeof(this->Client.name));
        strcpy(this->Client.name,this->data_map["name"].c_str());
        memset(this->Client.pwd,0,sizeof(this->Client.pwd));
        strcpy(this->Client.pwd,this->data_map["pwd"].c_str());
        int ret=open(this->Client.name,O_RDONLY);
        
        if(ret==-1){
            char str[]=R"({"login":-1,"error": 0})";
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            itoa(strlen(str),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));
            perror("open error");
            return -1;
        }else{
            char str[18];
			read(ret,str,sizeof(str));
            for(int i=0;i<32;++i){
                if(str[i]=='\n'){
                    str[i]='\0';
                    break;
                }
            }

            if(strcmp(this->Client.pwd,str)==0){//登陆成功
                for(int i=0;i<32;++i){
                    int x=rand()%26;
                    this->Client._hash[i]='A'+x;
                }
                this->Client.client_fd=client_fd;
                //printf("*****%d\n",this->Client.name);
                //if(this->data_client.find(this->Client.name)==this->data_client.end())
                this->data_client.insert(std::make_pair(this->Client.name,Client)); 
                /*else{
                    char str[]=R"({"login":-1,"error":2})"; //表示已经登陆
                    char c_size[1024];
                    memset(c_size,0,sizeof(c_size));
                    itoa(strlen(str),c_size,10);
                    printf("%s\r\n\r\n",c_size);
                    write(client_fd,c_size,strlen(c_size));
                    write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
                    write(client_fd,str,strlen(str));
                    return -1;
                }*/
                char str[256];
                memset(str,0,sizeof(str));
                strcpy(str,R"({"login":0,"token":")");
                strncat(str,this->Client._hash,32);
                strcat(str,R"("})");
                
                char c_size[1024];
                memset(c_size,0,sizeof(c_size));
                itoa(strlen(str),c_size,10);
                printf("%s\r\n\r\n",c_size);
                write(client_fd,c_size,strlen(c_size));
                write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
                write(client_fd,str,strlen(str));
                printf("%s\n",str);
                printf("this->data_client.size()%ld\n\n",this->data_client.size());

                return 0;
            }else{
                char str[]=R"({"login":-1,"error":1})";
                char c_size[1024];
                memset(c_size,0,sizeof(c_size));
                itoa(strlen(str),c_size,10);
                printf("%s\r\n\r\n",c_size);
                write(client_fd,c_size,strlen(c_size));
                write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
                write(client_fd,str,strlen(str));
                return -1;
            }

        }
        //close(client_fd);

    }else if(strcmp(this->login_status,"register")==0){
        printf("%s",success);
        write(client_fd,success,strlen(success));
        memset(this->Client.name,0,sizeof(this->Client.name));
        strcpy(this->Client.name,this->data_map["name"].c_str());
        memset(this->Client.pwd,0,sizeof(this->Client.pwd));
        strcpy(this->Client.pwd,this->data_map["pwd"].c_str());
        //printf("&&&&&&&&&&&&%s\n",this->Client.name);
        int ret=open(this->Client.name,O_RDONLY);        
        if(ret!=-1){
            char str[]=R"({"register":-1,"error": 0})";
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            itoa(strlen(str),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));
            return -1;
        }else if(strlen(this->Client.name)<3||strlen(this->Client.name)>10){
            char str[]=R"({"register":-1,"error": 1})";
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            itoa(strlen(str),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));
            return -1;
        }else if(strlen(this->Client.pwd)<6||strlen(this->Client.pwd)>18){
            char str[]=R"({"register":-1,"error": 2})";
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            itoa(strlen(str),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));
            return -1;
        }
        umask(0000);
        int fd=open(this->Client.name,O_RDWR|O_CREAT,0777); 
        if(fd==-1){
            char str[]=R"({"register":-1,"error": 3})";
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            itoa(strlen(str),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));
            perror("open error");
            return -1;
        }else{
            char str[]=R"({"register":0})";
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            itoa(strlen(str),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));
            write(fd,this->Client.pwd,strlen(this->Client.pwd));
            write(fd,"\n\n",strlen("\n\n"));
            return 0;
        }
            return -1;    
    }else if(strcmp(this->login_status,"information")==0){
            printf("%s",success);
            write(client_fd,success,strlen(success));
            memset(this->Client.name,0,sizeof(this->Client.name));
            strcpy(this->Client.name,this->data_map["name"].c_str());
            if(this->data_client.find(this->Client.name)==this->data_client.end()){
                char str[]=R"({"information":-1})";
                char c_size[1024];
                memset(c_size,0,sizeof(c_size));
                itoa(strlen(str),c_size,10);
                printf("%s\r\n\r\n",c_size);
                write(client_fd,c_size,strlen(c_size));
                write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
                write(client_fd,str,strlen(str));
                return -1;
            }
            char c_size[1024];
            memset(c_size,0,sizeof(c_size));
            int size=this->data_client[this->Client.name].chat_record.size();
            if(size==0){
                char str[]=R"({"information":-1,"msg":[],"userCount":)";
                char sstr[32];
                memset(sstr,0,sizeof(sstr));
                itoa(this->data_client.size(),sstr,10);
                strcat(str,sstr);
                strcat(str,"}");
                char c_size[1024];
                memset(c_size,0,sizeof(c_size));
                itoa(strlen(str),c_size,10);
                printf("%s\r\n\r\n",c_size);
                write(client_fd,c_size,strlen(c_size));
                write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
                write(client_fd,str,strlen(str));
                return 0;
            }
            std::string send_string=R"({"information":0,"msg":[)";
            for(int i=0;i<size;++i){
                send_string+=this->data_client[this->Client.name].chat_record[i].c_str();
                send_string+=",";
            }
            send_string[send_string.size()-1]=']';
            send_string+=R"(,"userCount":)";
            char sstr[32];
            memset(sstr,0,sizeof(sstr));
            itoa(this->data_client.size(),sstr,10);
            send_string+=sstr;
            send_string.push_back('}');
            itoa(strlen(send_string.c_str()),c_size,10);
            printf("%s\r\n\r\n",c_size);
            write(client_fd,c_size,strlen(c_size));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,send_string.c_str(),strlen(send_string.c_str()));
            this->data_client[this->Client.name].chat_record.clear();
            /*char str[]=R"({"name":"dw","msg":"qwer"})";
            char cc[1024];
            memset(cc,0,sizeof(cc));
            itoa(strlen(str),cc,10);
            printf("%s\r\n\r\n",cc);
            write(client_fd,cc,strlen(cc));
            write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
            write(client_fd,str,strlen(str));*/
            
        
    }else if(strcmp(this->login_status,"logout")==0){ 
        memset(this->Client.name,0,sizeof(this->Client.name));
        strcpy(this->Client.name,this->data_map["name"].c_str());
        this->data_client.erase(this->Client.name);
                
        /*char str[]=R"({"delete":0})";
        char c_size[1024];
        memset(c_size,0,sizeof(c_size));
        itoa(strlen(str),c_size,10);
        printf("%s\r\n\r\n",c_size);
        write(client_fd,c_size,strlen(c_size));
        write(client_fd,"\r\n\r\n",strlen("\r\n\r\n"));
        write(client_fd,str,strlen(str));*/
        
    }else {
        return -1;
    }
    return 0;   
}
int    http::http_delete(char in_str[]){return 0;}