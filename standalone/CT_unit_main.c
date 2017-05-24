//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include "CT_unit.h"

#define CT__UNIT_ARGC 8

// to do
int main(int argc, char** argv) {
  if(argc < CT__UNIT_ARGC) {
    printf("Usage: ");
    printf("--device <KEY> <SUBNET> <NODE> ");
    printf("--address <HOST> <SERVICE>\n");
  }
  return 0;
}
