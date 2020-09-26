#ifndef _H_VEKTOR_M_
#define _H_VEKTOR_M_

#include <stdio.h>
#include <stdlib.h>

#define VEKTOR_ALAP_KAPACITAS 100
#define UNDEFINED -1
#define SUCCESS 0
#define VEKTOR_START(vek) vektor vec;\
  vektor_start(&vek)

typedef struct _s_VektorLista {
  double *elemek;
  size_t kapacitas;
  size_t elemszam;
}vektorLista ;

typedef struct _s_Vektor vektor;
struct _s_Vektor {
  vektorLista lista;

  int (*hozzaad) (vektor *, double elem);
};

int _f_vektorHozzaad( vektor *, double);
int _f_vektorAtmeretez(vektor *, size_t);
void vektor_start(vektor *);

#endif
