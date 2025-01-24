#ifndef CHAPTER1_12_H
#define CHAPTER1_12_H

#include <stdio.h>
void Test1_12() {
  printf("Test1_12\n");
  int sum = 0;
  for (int i = -100; i <= 100; ++i) {
    sum += i;
  }
  printf("sum = %d\n", sum);
}

#endif // CHAPTER1_12_H