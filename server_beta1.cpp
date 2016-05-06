#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define port 1500
#define bufsize 1024
using namespace std;

int main()
{
    int client;
    int server;
    int length;
    bool isExit = false;
    char buffer[bufsize];

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
        strcpy(buffer, "server connected...");
        send(server,buffer,bufsize,0);

        do{
        cout<<"client: ";
        length=recv(server,buffer,bufsize,0);
        buffer[length]='\0';
        cout<<buffer<<" ";
        if(*buffer == '#')
        {
             isExit =true;
             goto endloop;
        }
        cout<<"\nserver: ";
        cin>>buffer;
        send(server,buffer,bufsize,0);
        if(*buffer == '#')
        {
             isExit =true;
        }
        endloop:;

        }while(!isExit);
        cout <<"\nconnection terminated."<<endl;
        isExit=false;
        exit(1);
    }
close(client);
return 0;
}
