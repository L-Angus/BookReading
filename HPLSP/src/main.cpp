#include <iostream>
#include <netdb.h>
#include <string>

// #include "ByteOrder.hpp"
// // #include "AddrConv.hpp"
// #include "Socket5_3.hpp"
// #include "Socket5_6.hpp"
// #include "MSG.hpp"
int main(int argc, char **argv) {
  // ByteOrder();
  // TestAddrConv();
  //   if (argc < 3) {
  //     std::cout << "Usage: " << argv[0] << " ip port" << std::endl;
  //     return 0;
  //   }
  // TestSocket5_3(argv[1], argv[2], "5");
  // TestSocket5_6(std::string{argv[1]}, std::string{argv[2]});
  //   MSG_OOB_SEND(argv[1], argv[2]);
  const char *error = gai_strerror(EAI_AGAIN);
  printf("EAI_AGAIN Error: %s\n", error);

  return 0;
}