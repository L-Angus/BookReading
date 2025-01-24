#include <iostream>

void PrintRangeNum(int beg, int end) {
  for (int i = beg; i <= end; i++) {
    std::cout << i << " ";
  }
}

int main() {
  //   int x = 50;
  //   int sum = 0;
  //   while (x <= 100) {
  //     sum += x;
  //     x++;
  //   }

  //   std::cout << sum << std::endl;
  //   int x = 10;

  //   while (x >= 0) {
  //     std::cout << x << std::endl;
  //     x--;
  //   }
  int beg, end;

  std::cin >> beg >> end;
  PrintRangeNum(beg, end);

  return 0;
}