#include <stdio.h>
#include "vektor.h"

int main(int argc, char* argv[]) {
  VEKTOR_START(v);

  v.hozzaad(&v, 2.34);

  return 0;
}
