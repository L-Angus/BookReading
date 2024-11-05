#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>


#define BUF_SIZE 1024
int main(int argc, char *argv[]){
    if(argc <= 2){
        std::cout << "Usage: " << argv[0] << " ip port" << std::endl;
        return 1;
    }
    const char* ip_ = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in client_address;
    bzero(&client_address, sizeof(client_address));
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(port);
    inet_pton(AF_INET, ip_, &client_address.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&client_address, sizeof(client_address));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    if(connfd < 0){
        printf("errno is %d\n", errno);
        exit(1);
    }else{
        char buffer[BUF_SIZE];
        memset(buffer, 0, BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("recv %d bytes data: %s\n", ret, buffer);

        memset(buffer, 0, BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, MSG_OOB);
        printf("recv %d bytes OOB data: %s\n", ret, buffer);

        memset(buffer, 0, BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        printf("recv %d bytes data: %s\n", ret, buffer);
        close(connfd);
    }

    close(sockfd);

    return 0;
}