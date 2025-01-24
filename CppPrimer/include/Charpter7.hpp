#ifndef CHARPTER7_HPP
#define CHARPTER7_HPP

#include <string>

#include <iostream>
#include <string>

class Sales_data {
  friend std::istream &operator>>(std::istream &is,
                                  Sales_data &item); // 声明友元函数
  friend std::ostream &operator<<(std::ostream &os, const Sales_data &item);

  friend std::ostream &print(std::ostream &os, const Sales_data &item);

public:
  Sales_data() = default; // 默认构造函数
  Sales_data(const std::string &s) : bookNo(s) {}
  Sales_data(const std::string &s, unsigned n, double p)
      : bookNo(s), units_sold(n), revenue(p * n) {}
  Sales_data(std::istream &is) { is >> *this; } // 从输入流构造对象
  Sales_data(const Sales_data &rhs)
      : bookNo(rhs.bookNo), units_sold(rhs.units_sold), revenue(rhs.revenue) {
  } // 拷贝构造函数

  Sales_data &operator=(const Sales_data &rhs) {
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
  }

  std::string isbn() const { return bookNo; }
  Sales_data &combine(const Sales_data &rhs);
  inline double avg_price() const {
    return units_sold ? revenue / units_sold : 0;
  }

private:
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
};

// 定义 operator>> 函数
std::istream &operator>>(std::istream &is, Sales_data &item) {
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = item.units_sold * price;
  return is;
}

// 定义 operator<< 函数
std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
  os << item.isbn() << " " << item.units_sold << " " << item.revenue << " "
     << item.avg_price();
  return os;
}

Sales_data &Sales_data::combine(const Sales_data &rhs) {
  if (this != &rhs) { // 避免自合并
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
  }
  return *this;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
  os << item.isbn() << " " << item.units_sold << " " << item.revenue << " "
     << item.avg_price() << std::endl;
  return os;
}

#endif // CHARPTER7_HPP