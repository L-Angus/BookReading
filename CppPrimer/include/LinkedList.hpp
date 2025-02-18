#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__

#include <iostream>

template <typename T> struct ListNode {
  T val;          //数据域
  ListNode *next; // 下一级指针
  ListNode() : val(T()), next(nullptr) {}
};

template <typename T> class LinkedList {
public:
  LinkedList() : head(nullptr), curr(nullptr) {}
  //   ~LinkedList() {
  //     ListNode *p = head;
  //     while (p) {
  //       ListNode *tmp = p;
  //       p = p->next;
  //       delete tmp;
  //     }
  //   }

  void add(T val) {
    if (!head) {
      head = new ListNode<T>();
      head->val = val;
      head->next = nullptr;
      curr = head;
    } else {
      while (curr->next != nullptr) {
        curr = curr->next;
      }
      curr->next = new ListNode<T>();
      curr->next->val = val;
      curr->next->next = nullptr;
      curr = curr->next;
    }
  }

  void insert(int val) {}

  void remove(int val) {}

  void update(size_t pos, int val) {}

  void print() {
    std::cout << "print list: \n";
    ListNode<T> *p = head;
    while (p) {
      std::cout << p->val << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }

private:
  ListNode<T> *head;
  ListNode<T> *curr;
};

#endif