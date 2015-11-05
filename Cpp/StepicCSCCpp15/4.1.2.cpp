#include <iostream>

struct Foo {
  void say() const { std::cout << "Foo says: " << msg << "\n"; }
protected:
  Foo(const char *msg) : msg(msg) { }
private:
  const char *msg;
};




// Вам нужно определить функцию get_foo, как описано в задании,
// чтобы компилировался и работал как ожидается следующий код:
//
// foo_says(get_foo("Hello!"));

struct Foo_ : Foo{
  Foo_(const char *msg) : Foo(msg) {};
};

void foo_says(const Foo &foo) { foo.say(); }

const Foo_ get_foo(const char *msg) {
  return Foo_(msg);
}

int _4_1_2(){
  foo_says(get_foo("Hello"));
}
