#include <arpa/inet.h>
#include <assert.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  std::cout << "--- Send OOB Msg ---" << std::endl;
  if (argc <= 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[0]));
    return 1;
  }

  const char *ip = argv[1];
  int port = atoi(argv[2]);

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(sockfd > 0);

  struct sockaddr_in server_address;
  bzero(&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  inet_pton(AF_INET, ip, &server_address.sin_addr);
  server_address.sin_port = htons(port);

  int sendbuf = atoi(argv[3]);
  int len = sizeof(sendbuf);
  setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
  getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *)&len);
  printf("the tcp send buffer size after setting is %d\n", sendbuf);

  if (connect(sockfd, (struct sockaddr *)&server_address,
              sizeof(server_address)) < 0) {
    printf("connection failed\n");
  } else {
    const char *oob_data = "abc";
    const char *normal_data = "123";
    send(sockfd, normal_data, strlen(normal_data), 0);
    send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
    send(sockfd, normal_data, strlen(normal_data), 0);
  }

  close(sockfd);
  return 0;
}