#ifndef MSG_HPP
#define MSG_HPP

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
void MSG_OOB_SEND(const std::string& ip_, const std::string& port_){
    const char* ip = ip_.c_str();
    int port = std::stoi(port_);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_address.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    int ret = connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));
    if(ret < 0){
        printf("Connection failed!\n");
    }else{
        const char* oob_data = "abc";
        const char* normal_data = "123";
        sendto(sockfd, normal_data, strlen(normal_data), 0, NULL, NULL);
        sendto(sockfd, oob_data, strlen(oob_data), 0, NULL, NULL);
        sendto(sockfd, normal_data, strlen(normal_data), 0, NULL, NULL);
        // send(sockfd, normal_data, strlen(normal_data), 0);
        // send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
        // send(sockfd, normal_data, strlen(normal_data), 0);
    }
    close(sockfd);
    return;
}

void MSG_OOB_RECV(const std::string& ip_, const std::string& port_){
    const char* ip = ip_.c_str();
    int port = std::stoi(port_);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));
    assert(ret >= 0);

    ret = listen(sockfd, 5);
    assert(ret >= 0);

    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address);
    int connfd = accept(sockfd, (struct sockaddr*)&client_address, &client_addrlength);
    if(connfd < 0){
        printf("errno is: %d\n", errno);
    }else{
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        ret = recv(connfd, buffer, BUFFER_SIZE-1, 0);
        printf("got %d bytes of normal data '%s'\n", ret, buffer);


        memset(buffer, '\0', BUFFER_SIZE);
        ret = recv(connfd, buffer, BUFFER_SIZE-1, MSG_OOB);
        printf("got %d bytes of OOB data '%s'\n", ret, buffer);

        memset(buffer, '\0', BUFFER_SIZE);
        ret = recv(connfd, buffer, BUFFER_SIZE-1, 0);
        printf("got %d bytes of normal data '%s'\n", ret, buffer);

        close(connfd);
    }

    close(sockfd);
    return;
}



#endif