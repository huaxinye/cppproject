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

    char file_name[FILE_NAME_MAX_SIZE+1];
    char bufferfile[BUFFER_SIZE];

    int length=recv(server_socket,file_name,BUFFER_SIZE,0);

    file_name[length+1]='\0';
    cout<<"file name:"<<file_name;

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

void Sendm(char buffers[bufsize],int client,int server,time_t lt,char name[32])
{
    while(1){
    cin.getline(buffers,bufsize);
    send(server,buffers,bufsize,0);
    cout<<"server: "<<buffers<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';
    if(*buffers == '*')
    {
        cout <<"\nconnection terminated."<<endl;
        close(client);
                exit(1);
    }

    }
}


void Recem(char bufferr[bufsize],int client,int server,time_t lt,int length,char name[32])
{

    while(1){
    length=recv(server,bufferr,bufsize,0);
    bufferr[length]='\0';
    cout<<name<<": "<<bufferr<<"  --message sent by ";
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
    char name[32];
    bzero(name, 32);
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

    listen(client,4);

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
        strcpy(buffer, "your user name:");
        send(server,buffer,bufsize,0);
        length=recv(server,name,32,0);
        buffer[length]='\0';

            std::thread t1(Sendm,buffers,client,server,lt,name);
            std::thread t2(Recem,bufferr,client,server,lt,length,name);
            t1.join();
            t2.join();
           /* Sendm(buffers,client,server,lt);
            Recem(bufferr,client,server,lt,length);*/

    }

    return 0;
}

