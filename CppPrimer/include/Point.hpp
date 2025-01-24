#ifndef __POINT_HPP__
#define __POINT_HPP__

#include <iostream>

class Point {
public:
  Point() = default;
  Point(const Point &rhs) { std::cout << "copy constructor" << std::endl; }
};

Point global;
Point foo_bar(Point arg) {
  Point local = arg, *heap = new Point(global);
  *heap = local;
  Point pa[4] = {local, *heap};
  return *heap;
}

#endif