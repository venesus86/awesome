#include <iostream>

using std::cout;
using std::endl;

class Base
{
private:
  int a;
  int b;

public:
  virtual void who_am_i() { cout << "this is Base class" << endl; }
};

class Derived : public Base
{
private:
  int c;
  int d;

public:
  void who_am_i() { cout << "this is Derived class" << endl; }
};

int main()
{
  Base a;
  Derived b;

  cout << "sizeof(int): " << sizeof(int) << ", sizeof(int*): " << sizeof(int*) << endl;
  cout << "sizeof(Base): " << sizeof(Base) << ", sizeof(Derived):" << sizeof(Derived) << endl;
  cout << "&a: " << &a << ", &b: " << &b << endl;

  Base **p{new Base*[2]};
  p[0] = &a;
  p[1] = &b;

  void (**vta)() = *(void (***)())&a;
  void (**vtb)() = *(void (***)())&b;

  for (int i{}; i < 2; ++i) {
    void (**vt)() = *(void (***)())p[i];
    p[i]->who_am_i();
  }

  return 0;
}