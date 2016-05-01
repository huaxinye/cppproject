//it's sever
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#define server_port 1111
#define buffer_size 1024

using namespace std;
int main()
{
    int client;
    int server;
    bool isExit = false;
    char buffer[buffer_size];

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
    server_addr.sin_port = htons(server_port);

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


    return 0;
}
