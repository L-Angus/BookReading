// 检查头文件路径是否正确
#include "../include/Message.hpp"
#include "../include/Folder.hpp"

Message::Message(const std::string &str) : contexts(str) {}
Message::Message(const Message &rhs)
    : contexts(rhs.contexts), folders(rhs.folders) {
  add_to_Folders(rhs);
}
Message &Message::operator=(const Message &rhs) {
  remove_from_Folders();
  contexts = rhs.contexts;
  folders = rhs.folders;
  add_to_Folders(*this);
  return *this;
}
Message::~Message() { remove_from_Folders(); }
void Message::save(Folder &f) {
  f.addMsg(this);
  addFolder(&f);
}
void Message::remove(Folder &f) {
  f.remMsg(this);
  rmFolder(&f);
}

void Message::addFolder(Folder *f) { folders.insert(f); }
void Message::rmFolder(Folder *f) { folders.erase(f); }

void Message::add_to_Folders(const Message &m) {
  for (auto f : m.folders)
    f->addMsg(this);
}

void Message::remove_from_Folders() {
  for (auto f : folders)
    f->remMsg(this);
}

void swap(Message &lhs, Message &rhs) {
  using std::swap;
  for (auto f : lhs.folders) {
    f->remMsg(&lhs);
  }
  for (auto f : rhs.folders) {
    f->remMsg(&rhs);
  }
  swap(lhs.contexts, rhs.contexts);
  swap(lhs.folders, rhs.folders);
  for (auto f : lhs.folders) {
    f->addMsg(&lhs);
  }
  for (auto f : rhs.folders) {
    f->addMsg(&rhs);
  }
}
