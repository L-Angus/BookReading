#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

void TestSocket5_6(const std::string& ip, const std::string& port){
    printf("TestSocket5_6......\n");
    const char* ip_ = ip.c_str();
    int port_ = atoi(port.c_str());

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_);
    inet_pton(AF_INET, ip_, &server_address.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    if(connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) == 0){
        printf("connect success!\n");
        const char* oob_data = "abc";
        const char* normal_data = "123";
        send(sockfd, normal_data, strlen(normal_data), 0);
        send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
        send(sockfd, normal_data, strlen(normal_data), 0);
    }else{
        printf("connect failed!\n");
    }

    close(sockfd);
    return;
}
