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

#define port 1500
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


void Recem(char bufferr[bufsize],int client,int server,time_t lt,int length)
{

    while(1){
    length=recv(server,bufferr,bufsize,0);
    bufferr[length]='\0';
    cout<<"client: "<<bufferr<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';
    if(*bufferr == '#')
    {
        cout <<"\ndisconnected by client."<<endl;
        close(client);
        exit(1);
    }}
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
            std::thread t1(Sendm,buffers,client,server,lt);
            std::thread t2(Recem,bufferr,client,server,lt,length);
            t1.join();
            t2.join();
           /* Sendm(buffers,client,server,lt);
            Recem(bufferr,client,server,lt,length);*/

    }

    return 0;
}

