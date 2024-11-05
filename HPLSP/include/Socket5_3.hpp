#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>


static bool stop = false;
static void handle_term(int sig){
    stop = true;
}

void TestSocket5_3(char * input_ip, char * input_port, char* blocklog)
{
    printf("TestSocket5_3......\n");
    signal(SIGTERM, handle_term);
    const char* ip  = input_ip;
    int port = atoi(input_port);
    int blocks = atoi(blocklog);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    // create IPv4 address
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    // bind socket
    int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(sock, blocks);
    assert(ret != -1);

    // while and wait
    while(!stop){
        sleep(1);
    }

    // close socket
    close(sock);
    return;
}