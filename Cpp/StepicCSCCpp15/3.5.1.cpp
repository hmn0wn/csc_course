#include <iostream>

/* Класс Cls определен точно таким образом:*/

struct Cls {
  Cls(char c, double d, int i): c(c), d(d), i(i){}
private:
  char c;
  double d;
  int i;
};

struct _Cls {

public:
  char c;
  double d;
  int i;
};


// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls){
  //return *((char *)&cls);
  return ((_Cls *)(&cls))->c;
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
  //return *(double *)((char *)&cls+1);
  return ((_Cls *)(&cls))->d;
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
   return ((_Cls *)(&cls))->i;
}

int _3_5_1(){
  Cls tcls('G', 3, 6);
  std::cout << get_c(tcls) << std::endl;
  std::cout << get_d(tcls) << std::endl;
  std::cout << get_i(tcls) << std::endl;
  return 0;
}
