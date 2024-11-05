#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
void TestAddrConv()
{
    char * szValue1 = inet_ntoa("1.2.3.4");
    printf("address szValue1: %s\n", szValue1);
}