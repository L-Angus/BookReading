#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <set>
#include <string>

class Folder;
class Message {
  friend void swap(Message &lhs, Message &rhs);

public:
  Message() = default;
  explicit Message(const std::string &str = "");
  Message(const Message &rhs);
  Message &operator=(const Message &rhs);
  ~Message();
  void save(Folder &fd);
  void remove(Folder &fd);
  void addFolder(Folder *fd);
  void rmFolder(Folder *fd);

private:
  std::string contexts;
  std::set<Folder *> folders;
  void add_to_Folders(const Message &msg);
  void remove_from_Folders();
};

#endif