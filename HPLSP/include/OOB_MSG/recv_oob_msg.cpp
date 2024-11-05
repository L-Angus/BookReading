#include <arpa/inet.h>
#include <assert.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024
int main(int argc, char *argv[]) {
  std::cout << "--- Recv OOB Msg ---" << std::endl;
  if (argc <= 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[0]));
    return 1;
  }

  const char *ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &address.sin_addr);
  address.sin_port = htons(port);
  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(sockfd > 0);

  int recvbuf = atoi(argv[3]);
  int len = sizeof(recvbuf);
  setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &recvbuf, sizeof(recvbuf));
  getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &recvbuf, (socklen_t *)&len);
  printf("the tcp recv buffer size after setting is %d\n", recvbuf);

  int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
  assert(ret = -1);

  ret = listen(sockfd, SOMAXCONN);
  struct sockaddr_in client;
  socklen_t client_len = sizeof(client);
  int connfd =
      accept(sockfd, (struct sockaddr *)&client, (socklen_t *)&client_len);
  if (connfd < 0) {
    printf("errno is : %d\n", connfd);
  } else {
    char buffer[BUF_SIZE];
    memset(buffer, '\0', BUF_SIZE);
    ret = recv(connfd, buffer, BUF_SIZE - 1, 0);
    printf("got %d bytes of normal data '%s'\n", ret, buffer);

    memset(buffer, '\0', BUF_SIZE);
    ret = recv(connfd, buffer, BUF_SIZE - 1, MSG_OOB);
    printf("got %d bytes of OOB data '%s'\n", ret, buffer);

    memset(buffer, '\0', BUF_SIZE);
    ret = recv(connfd, buffer, BUF_SIZE - 1, 0);
    printf("got %d bytes of normal data '%s'\n", ret, buffer);

    close(connfd);
  }

  close(sockfd);

  return 0;
}