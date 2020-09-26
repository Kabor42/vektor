#include <stdio.h>
#include "vektor.h"

int main(int argc, char* argv[]) {
  vektor v;
  vektor_start(&v);

  v.hozzaad(&v, 2.34);

  return 0;
}
