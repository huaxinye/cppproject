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

#define port 1500
#define bufsize 1024
#define FILE_NAME_MAX_SIZE 512  

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
    cout<<"client: "<<buffers<<"  --message sent by ";
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
    length=recv(client,bufferr,bufsize,0);
    bufferr[length]='\0';
    cout<<"server: "<<bufferr<<"  --message sent by ";
    ptime(lt);
    cout<<'\n';
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



void filetransimisson()
{
    char file_name[FILE_NAME_MAX_SIZE+1];  
    bzero(file_name, FILE_NAME_MAX_SIZE+1);  
    printf("Please Input File Name On Server:\t");  
    scanf("%s", file_name);  
      
    char bufferfile[BUFFER_SIZE];  
    bzero(bufferfile,BUFFER_SIZE);  
    strncpy(bufferfile, file_name, strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));  
    //向服务器发送buffer中的数据  
    send(client,bufferfile,BUFFER_SIZE,0);  
  
//    int fp = open(file_name, O_WRONLY|O_CREAT);  
//    if( fp < 0 )  
    FILE * fp = fopen(file_name,"w");  
    if(NULL == fp )  
    {  
        printf("File:\t%s Can Not Open To Write\n", file_name);  
        exit(1);  
    }  
      
    //从服务器接收数据到buffer中  
    bzero(bufferfile,BUFFER_SIZE);  
    int length = 0;  
    while( 0!= (length = recv(client,bufferfile,BUFFER_SIZE,0)))  
    {  
        printf("recv return %d\n",length);  
        if(length < 0)  
        {  
            printf("Recieve Data From Server %s Failed!\n", argv[1]);  
            break;  
        }  
//        int write_length = write(fp, bufferfile,length);  
                  
        int write_length = fwrite(bufferfile,sizeof(char),length,fp);  
        if (write_length<length)  
        {  
            printf("File:\t%s Write Failed\n", file_name);  
            break;  
        }  
        bzero(bufferfile,BUFFER_SIZE);      
    }  
    printf("Recieve File:\t %s From Server[%s] Finished\n",file_name, argv[1]);  
      
    fclose(fp);
    return 0;
}
