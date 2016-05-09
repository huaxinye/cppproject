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
#include<netdb.h>

#define port 1501
#define bufsize 1024

using namespace std;

void ptime(time_t lt)
{

    lt =time(NULL);
    printf(ctime(&lt));
}

void Sendm(char buffers[bufsize],int client,int server,time_t lt)
{
    while(1){
    cin.getline(buffers,bufsize);

    send(client,buffers,bufsize,0);
        if((*buffers != '\0')&&(*buffers != ' ')){
    cout<<"client: "<<buffers<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';}
    if(*buffers == '#')
    {
        cout <<"\nconnection terminated."<<endl;
        close(client);
                exit(1);
    }}
}


void Recem(char bufferr[bufsize],int client,int server,time_t lt,int length)
{
    while(1){
    length=recv(client,bufferr,bufsize,0);
    bufferr[length]='\0';
        if((*bufferr != '\0')&&(*bufferr != ' ')){
    cout<<"server: "<<bufferr<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';}
    if(*bufferr == '#')
    {
        cout <<"\ndisconnected by server."<<endl;
        close(client);
                exit(1);
    }}
}
int main()
{
    int client;
    int server;
    int length;

    char buffer[bufsize];
    char buffers[bufsize];
    char bufferr[bufsize];
    char* IP="10.0.0.8";
    struct tm *ptr;
    time_t lt;

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client<0)
    {
        cout << "create socket failed." <<"\n";
        exit(1);
    }
    cout << "socket created" <<"\n";

    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET,IP,&server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    if(connect(client, (struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        cout <<"connecting failed"<<endl;
        exit(1);
    }
    length=recv(client, buffer, bufsize,0);
    buffer[length]='\0';
    cout<<buffer;
    strcpy(buffer, "client connected...\n");
    send(client,buffer,bufsize,0);
        std::thread t1(Sendm,buffers,client,server,lt);
        std::thread t2(Recem,bufferr,client,server,lt,length);
        t1.join();
        t2.join();
        /*Sendm(buffers,client,server,lt);
        Recem(bufferr,client,server,lt,length);*/



    return 0;
}
