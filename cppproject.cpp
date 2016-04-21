//it's sever
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#define server_port 1111
#define buffer_size 1024
using namespace std;
int main()
{
    struct sockaddr_in addr;// google SOCKADDR_IN struct
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    addr.sin_port = htons(server_port);
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
        if( server_socket < 0)
        {
            cout<<"Create Socket Failed!"<<"\n";
        }
        else
        {
            cout<<"Socket Created!"<<"\n";
        }
        return 0;
}
