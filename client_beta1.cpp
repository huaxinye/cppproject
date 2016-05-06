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
    int length;
    bool isExit = false;
    char buffer[bufsize];

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
    length=recv(client, buffer, bufsize,0);
    buffer[length]='\0';
    cout<<buffer;

    do{
        cout<<"\nclient: ";

        cin>>buffer;
        send(client, buffer, bufsize,0);
           if(*buffer=='#')
            {

                isExit=true;
                goto endloop;

            }
           cout<<"server: ";
            length=recv(client,buffer,bufsize,0);
            buffer[length]='\0';
            cout<<buffer<<" ";
            if(*buffer=='#')
            {
                isExit=true;
            }
            endloop:;

    }while(!isExit);
    isExit = false;
    cout<<"\ndisconnected"<<endl;
    close(client);
    return 0;
}
