#include<iostream>
#include<winsock2.h>

#pragma comment(lib,"wsock32.lib")

using namespace std;
int main(int argc, char* argv[]){
    WSADATA wsd;
    if (WSAStartup(MAKEWORD(2,2), &wsd) != 0){
        cout << "WSAStartup failed!" << endl;
        return 1;
    }
    cout<<"this is server!"<<endl;

    //socket
    int socketSock = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
    if (socketSock == -1) {
        std::cout << "Error: socket" << std::endl;
        system("pause");
        return 0;
    }
    //bind
    struct sockaddr_in addr;
    addr.sin_port = htons(8000);
    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = INADDR_ANY;
    if(bind(socketSock,(struct sockaddr*)&addr,sizeof (addr))==SOCKET_ERROR){
        std::cout << "Error: bind" << std::endl;
        system("pause");
        return 0;
    }
    //listen
    if(listen(socketSock,5)==SOCKET_ERROR){
        std::cout << "Error: listen" << std::endl;
        system("pause");
        return 0;
    }
    //accept
    struct sockaddr_in addrclient;
    int addrclientlen = sizeof(addrclient);
    SOCKET sClient =accept(socketSock,(struct sockaddr*)&addrclient,&addrclientlen);
    if(sClient== INVALID_SOCKET){
        std::cout<<"Error:accept"<<std::endl;
        system("pause");
        return 0;
    }
    const int BUF_SIZE=64;
    char buf[BUF_SIZE];
    char sendbuf[BUF_SIZE];
    while(true){
        ZeroMemory(buf,BUF_SIZE);
        int retval = recv(sClient,buf,BUF_SIZE,0);
        if(SOCKET_ERROR == retval){
            cout << "recv failed!" << endl;
            closesocket(socketSock);
            closesocket(sClient);
            WSACleanup();
            system("pause");
            return -1;
        }
        if(buf[0]=='0'){
            break;
        }
        std::cout<<"The data of sending by client:"<<buf<<endl;

        cout<<"Sending data to the client:"<<endl;
        cin.getline(sendbuf,BUF_SIZE);

        send(sClient,sendbuf,strlen(sendbuf),0);
    }
    closesocket(socketSock);
    closesocket(sClient);
    WSACleanup();
    system("pause");
    return 0;
}
