#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<thread>
#include<ctime>
#include<stdio.h>
#define port 1501
#define bufsize 1024
#define FILE_NAME_MAX_SIZE 512
#define BUFFER_SIZE 1024


using namespace std;
void filetransmission(int server_socket)
{

    char bufferfile[BUFFER_SIZE];
    bzero(bufferfile, BUFFER_SIZE);
    int length=recv(server_socket,bufferfile,BUFFER_SIZE,0);

    char file_name[FILE_NAME_MAX_SIZE+1];
    bzero(file_name, FILE_NAME_MAX_SIZE+1);
    strncpy(file_name, bufferfile, strlen(bufferfile)>FILE_NAME_MAX_SIZE?FILE_NAME_MAX_SIZE:strlen(bufferfile));
//        int fp = open(file_name, O_RDONLY);
//        if( fp < 0 )
    printf("%s\n",file_name);
    FILE * fp = fopen(file_name,"r");
    if(NULL == fp )
    {
        printf("File:\t%s Not Found\n", file_name);
    }
    else
    {
        bzero(bufferfile, BUFFER_SIZE);
        int file_block_length = 0;
//        while( (file_block_length = read(fp,buffer,BUFFER_SIZE))>0)
        while( (file_block_length = fread(bufferfile,sizeof(char),BUFFER_SIZE,fp))>0)
        {
            printf("file_block_length = %d\n",file_block_length);
                //发送buffer中的字符串到new_server_socket,实际是给客户端
            if(send(server_socket,bufferfile,file_block_length,0)<0)
            {
                printf("Send File:\t%s Failed\n", file_name);

            }
            bzero(bufferfile, BUFFER_SIZE);
        }
//            close(fp);
        fclose(fp);
        printf("File:\t%s Transfer Finished\n",file_name);
    }
        //关闭与客户端的连接
    close(server_socket);

}
void ptime(time_t lt)
{

    lt =time(NULL);
    printf(ctime(&lt));
}

void Sendm(char buffers[bufsize],int client,int server,time_t lt)
{
    while(1){

    cin.getline(buffers,bufsize+);

    send(server,buffers,bufsize,0);
    cout<<"server: "<<buffers<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';
    if(*buffers == '#')
    {
        cout <<"\nconnection terminated."<<endl;
        close(client);
                exit(1);
    }}
}


void Recem(char user_name[length],char bufferr[bufsize],int client,int server,time_t lt,int length)
{

    while(1){
    length=recv(server,bufferr,bufsize,0);
    bufferr[length]='\0';
    cout<<"user_name: "<<bufferr<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';
    if(*bufferr == '*')
    {
        cout <<"\ndisconnected by client."<<endl;
        close(client);
        exit(1);
    }
    if(*bufferr == '#')
    { filetransmission(client);}
    }
}

int main()
{
    int client;
    int server;
    int length;
    bool isExit = false;
    char buffer[bufsize];
    char buffers[bufsize];
    char bufferr[bufsize];

    struct tm *ptr;
    time_t lt;

    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client<0)
    {
        cout << "establishing connection failed." <<"\n";
        exit(1);
    }
    cout << "connection established." << "\n";

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if(bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
    {
        cout<< "binding socket failed."<<"\n";
        exit(1);
    }
    size=sizeof(server_addr);
    cout<< "searching for client..."<<"\n";

    listen(client,1);

    server = accept(client,(struct sockaddr*)&server_addr, &size);

    if (server<0)
    {
        cout<<"error on accepting."<<"\n";
        exit(1);
    }
    while (server >0)
    {
        strcpy(buffer, "server connected...\n");
        send(server,buffer,bufsize,0);
        length=recv(server,buffer,bufsize,0);
        buffer[length]='\0';
        cout<<buffer<<endl;
        
        
        length=recv(server,buffer,bufsize,0);
        buffer[length]='\0';
        char user_name[length+1];
        strcpy(user_name,buffer);
        str;
            std::thread t1(Sendm,buffers,client,server,lt);
            std::thread t2(Recem,bufferr,client,server,lt,length);
            t1.join();
            t2.join();
           /* Sendm(buffers,client,server,lt);
            Recem(bufferr,client,server,lt,length);*/
       
    }

    return 0;
}

void filetransmission()
{
    struct sockaddr_in client_addr;  
    socklen_t length = sizeof(client_addr);  
  
        //接受一个到server_socket代表的socket的一个连接  
        //如果没有连接请求,就等待到有连接请求--这是accept函数的特性  
        //accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信  
        //new_server_socket代表了服务器和客户端之间的一个通信通道  
        //accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中  
    int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);  
    if ( new_server_socket < 0)  
    {  
        printf("Server Accept Failed!\n");  
        break;  
    } 
    char bufferfile[BUFFER_SIZE];  
    bzero(bufferfile, BUFFER_SIZE);  
    length = recv(new_server_socket,bufferfile,BUFFER_SIZE,0);  
    if (length < 0)  
    {  
        printf("Server Recieve Data Failed!\n");  
        break;  
    }  
    char file_name[FILE_NAME_MAX_SIZE+1];  
    bzero(file_name, FILE_NAME_MAX_SIZE+1);  
    strncpy(file_name, bufferfile, strlen(buffer)>FILE_NAME_MAX_SIZE?FILE_NAME_MAX_SIZE:strlen(bufferfile));  
//        int fp = open(file_name, O_RDONLY);  
//        if( fp < 0 )  
    printf("%s\n",file_name);  
    FILE * fp = fopen(file_name,"r");  
    if(NULL == fp )  
    {  
        printf("File:\t%s Not Found\n", file_name);  
    }  
    else  
    {  
        bzero(bufferfile, BUFFER_SIZE);  
        int file_block_length = 0;  
//        while( (file_block_length = read(fp,buffer,BUFFER_SIZE))>0)  
        while( (file_block_length = fread(bufferfile,sizeof(char),BUFFER_SIZE,fp))>0)  
        {  
            printf("file_block_length = %d\n",file_block_length);  
                //发送buffer中的字符串到new_server_socket,实际是给客户端  
            if(send(new_server_socket,bufferfile,file_block_length,0)<0)  
            {  
                printf("Send File:\t%s Failed\n", file_name);  
                break;  
            }  
            bzero(bufferfile, BUFFER_SIZE);  
        }  
//            close(fp);  
        fclose(fp);  
        printf("File:\t%s Transfer Finished\n",file_name);  
    }  
        //关闭与客户端的连接  
    close(new_server_socket);
    return 0;
}
