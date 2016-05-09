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
int number=0;
using namespace std;



void ptime(time_t lt)
{

    lt =time(NULL);
    printf(ctime(&lt));
}

void Sendm(char buffers[bufsize],int client,int server,time_t lt)
{
    while(server>0){
    cin.getline(buffers,bufsize);
    send(server,buffers,bufsize,0);
    if((*buffers != '\0')&&(*buffers != ' ')){
    cout<<"server: "<<buffers<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';}
    if(*buffers == '#')
    {
        cout <<"\nconnection terminated."<<endl;
        close(client);
        close(server);
                exit(1);
    }}
}


void Recem(char bufferr[bufsize],int client,int server,time_t lt,int length)
{

    while(server>0){
    length=recv(server,bufferr,bufsize,0);
    bufferr[length]='\0';
     if((*bufferr != '\0')&&(*bufferr != ' ')){
    cout<<"client: "<<bufferr<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';}

    if(*bufferr == '#')
    {
        cout <<"\ndisconnected by client."<<endl;
        ::number--;
        close(server);

        server=0;
        bufferr[0]='\0';

    }}
}
void accept_c(int client,int server,socklen_t size,sockaddr_in server_addr,int length,char buffer[bufsize],time_t lt)
{
    while(1){
    if((::number<=2)&&(server==0)){
    server = accept(client,(struct sockaddr*)&server_addr, &size);
    if (server<0)
      cout<<"error on accepting."<<"\n";
    strcpy(buffer, "server connected...\n");
    send(server,buffer,bufsize,0);
    length=recv(server,buffer,bufsize,0);
    buffer[length]='\0';
    cout<<buffer<<endl;
    number++;}
}
}
int main()
{
    int client;
    int server=0,server2=0;
    int length;
    bool isExit = false;
    char buffer[bufsize];
    char buffers[bufsize];
    char bufferr[bufsize];
    char buffers2[bufsize];
    char bufferr2[bufsize];
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

    listen(client,10);

    server = accept(client,(struct sockaddr*)&server_addr, &size);
    number++;
    if (server<0)
    {
        cout<<"error on accepting."<<"\n";
        exit(1);
    }
    if((server >0)||(server2 >0))
    {
        strcpy(buffer, "server connected...\n");
        send(server,buffer,bufsize,0);
        length=recv(server,buffer,bufsize,0);
        buffer[length]='\0';
        cout<<buffer<<endl;
            std::thread t1(Sendm,buffers,client,server,lt);
            std::thread t2(Recem,bufferr,client,server,lt,length);
            //accept_c(int client,int server,socklen_t size,sockaddr_in server_addr)
            std::thread t3(accept_c,client, server2, size, server_addr,length, buffer, lt);
            std::thread t4(accept_c,client, server, size, server_addr,length, buffer, lt);
            std::thread t5(Sendm,buffers,client,server2,lt);
            std::thread t6(Recem,bufferr2,client,server2,lt,length);

            t1.join();
            t2.join();
            t3.join();
            t4.join();
            t5.join();
            t6.join();
           /* Sendm(buffers,client,server,lt);
            Recem(bufferr,client,server,lt,length);*/

    }

    return 0;
}



