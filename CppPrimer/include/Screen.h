
#include <string>

class Screen {
public:
  typedef std::string::size_type pos;
  Screen() = default;
  Screen(pos ht, pos wd, char c)
      : height(ht), width(wd), contents(ht * wd, c) {}

  char get() const { return contents[cursor]; }
  inline char get(pos ht, pos wd) const {
    pos row = ht * width;
    return contents[row + wd];
  }
  Screen &move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
  }

private:
  pos cursor = 0;
  pos height = 0, width = 0;
  std::string contents;
};
