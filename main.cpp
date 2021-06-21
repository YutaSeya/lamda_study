#include <iostream>

#include "SECD_Machine.h"

int main(void) {
  /* code */

  SECDMachine machine;
  bool is_act = machine.inputLambdaEquation();
  if (is_act) machine.extractApplicationActualArgument();
  
  bool is_end = false;
  while(!is_end) {
    is_end = machine.executeToLoadIdentifier();
  }
  //((@x.@y.(x y))((@x.@y.(x y))(@x.@y.y)))

  return 0;
}
