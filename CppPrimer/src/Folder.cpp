#include "../include/Folder.hpp"
#include "../include/Message.hpp"

Folder::Folder(const Folder &rhs) : messages(rhs.messages) {
  add_to_Messages(rhs);
}
Folder &Folder::operator=(const Folder &rhs) {
  remove_from_Messages();
  messages = rhs.messages;
  add_to_Messages(*this);
  return *this;
}
Folder::~Folder() { remove_from_Messages(); }

void Folder::addMsg(Message *msg) { messages.insert(msg); }
void Folder::remMsg(Message *msg) { messages.erase(msg); }

void Folder::add_to_Messages(const Folder &f) {
  for (auto m : f.messages) {
    m->save(*this);
  }
}
void Folder::remove_from_Messages() {
  for (auto m : messages) {
    m->remove(*this);
  }
}