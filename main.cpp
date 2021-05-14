#include <iostream>

#include "SECD_Machine.h"

int main(void) {
  /* code */

  SECDMachine machine;
  bool is_act = machine.inputLambdaEquation();
  if (is_act) {
    machine.extractApplicationActualArgument();
    machine.loadIdentifierS();
    machine.loadIdentifierS();
    machine.loadIdentifierS();
  }

  return 0;
}
