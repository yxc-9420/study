#include<iostream>
#include<winsock2.h>
#pragma comment(lib,"wsock32.lib")
using namespace std;
int main(int argc,char *argv[]){
    WSADATA wsd;
    //typedef unsigned short  WORD 无符号短整形 2个字节
    if(WSAStartup(MAKEWORD(2,2),&wsd)!=0){
        cout<<"WSAStartup failed!"<<endl;
        return -1;
    }
    cout<<"this is client!"<<endl;
    //socket
    SOCKET s = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
    if(s==INVALID_SOCKET){
        cout<<"Error:socket fialed!"<<endl;
        system("pause");
        return 0;
    }
    //connect
    struct sockaddr_in addr;
    addr.sin_port = htons(8000);
    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if(connect(s,(struct sockaddr*)&addr,sizeof(addr))==SOCKET_ERROR){
        cout<<"Error: connect failed!"<<endl;
        system("pause");
        return 0;
    }
    const int BUF_SIZE=64;
    char buf[BUF_SIZE];
    char sendbuf[BUF_SIZE];
    while(true){
        ZeroMemory(sendbuf,BUF_SIZE);
        cout<<"Sending data to the server:"<<endl;
        cin.getline(sendbuf,BUF_SIZE);
        int res = send(s,sendbuf,strlen(sendbuf),0);
        if(res==SOCKET_ERROR){
            cout<<"Error:send failed!"<<endl;
            closesocket(s);
            WSACleanup();
            system("pause");
            return -1;
        }
        ZeroMemory(buf,BUF_SIZE);
        recv(s,buf,BUF_SIZE,0);
        cout<<"the data of sending by server:"<<buf<<endl;
    }
    closesocket(s);
    WSACleanup();
    system("pause");
    return 0;
}
