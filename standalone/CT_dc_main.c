//
// Created by Gustavo Viegas on 2017/05
//

#include <stdio.h>
#include "CT_dc.h"

#define CT__DC_ARGC 8

// to do
int main(int argc, char** argv) {
  if(argc < CT__DC_ARGC) {
    printf("Usage: ");
    printf("--device <KEY> <SUBNET> <NODE> ");
    printf("--address <HOST> <SERVICE> ");
    printf("...\n");
  }
  return 0;
}
