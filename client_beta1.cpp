#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#define port 1500
#define bufsize 1024
using namespace std;

int main()
{
    int client;
    int server;
    bool isExit = false;
    char buffer[bufsize];
    char *ip= "10.0.0.8";

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client<0)
    {
        cout << "create socket failed." <<"\n";
        exit(1);
    }
    cout << "socket created" <<"\n";

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if(connect(client, (struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        cout <<"connecting failed"<<endl;
        exit(1);
    }
    recv(client, buffer, bufsize,0);
    cout<<"connected"<<endl;

    do{
        cout<<"client: ";
        do{
            cin>>buffer;
            send(client, buffer, bufsize,0);
            if(*buffer=='#')
            {
                *buffer='*';
                isExit=true;
            }
        }while(*buffer !='*');
        cout<<"server: ";
        do{
            recv(client,buffer,bufsize,0);
            cout<<buffer<<" ";
            if(*buffer=='#')
            {
                *buffer='*';
                isExit=true;
            }
        }while(*buffer !='*');
        cout<< endl;
    }while(!isExit);
    cout<<"disconnected"<<endl;
    close(client);
    return 0;
}
