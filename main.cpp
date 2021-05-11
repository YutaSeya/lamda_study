#include <iostream>

#include "SECDstack.h"

int main(void) {
  /* code */
  SECDStack s;

  s.inputListBack("hello world");
  s.inputListBack("cost");
  s.inputListBack("draw");

  std::cout << s.getListSecond() << std::endl;

  // std::list<std::string> x = s.getRemoveFrontList();

  // for (auto itr = x.begin(); itr != x.end(); ++itr) std::cout << *itr <<
  // std::endl;
}
