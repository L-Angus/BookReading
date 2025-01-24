#ifndef __FOLDER_HPP__
#define __FOLDER_HPP__

#include <set>

class Message;
class Folder {
public:
  Folder() = default;
  Folder(const Folder &rhs);
  Folder &operator=(const Folder &rhs);
  ~Folder();
  void addMsg(Message *msg);
  void remMsg(Message *msg);

private:
  void remove_from_Messages();
  void add_to_Messages(const Folder &f);
  std::set<Message *> messages;
};

#endif