#ifndef SALES_ITEM_H
#define SALES_ITEM_H

#include <iostream>

class Sales_item {
  friend std::istream &operator>>(std::istream &is, Sales_item &item) {
    is >> item.isbn >> item.units_sold >> item.sold_price;
    if (!is) {
      item = Sales_item();
    }
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Sales_item &item) {
    double revenue = item.units_sold * item.sold_price;
    double avg_price = revenue / item.units_sold;
    os << item.isbn << " " << item.units_sold << " " << revenue << " "
       << avg_price;
    return os;
  }

  friend Sales_item operator+(const Sales_item &lhs, const Sales_item &rhs) {
    Sales_item sum = lhs;
    if (lhs.isbn == rhs.isbn) {
      sum.units_sold += rhs.units_sold;
      sum.sold_price += rhs.sold_price;

      return sum;
    } else {
      return Sales_item();
    }
  }

public:
  Sales_item() = default;

private:
  std::string isbn;
  unsigned int units_sold;
  double sold_price = 0.0;

  double revenue = 0.0;
};

#endif