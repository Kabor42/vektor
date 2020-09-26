#include "vektor.h"

int _f_vektorHozzaad(vektor *v, double elem) {
  int _statusz = UNDEFINED;
  if (v) {
    if (v->lista.kapacitas == v->lista.elemszam) {
     _statusz = _f_vektorAtmeretez(v, v->lista.kapacitas + 100);
     v->lista.elemek[v->lista.elemszam++] = elem;
    } else {
     v->lista.elemek[v->lista.elemszam++] = elem;
     _statusz = SUCCESS;
    }
  }
  return _statusz;
}

int _f_vektorAtmeretez(vektor *v, size_t uj_meret) {
  int _statusz = UNDEFINED;
  if (v) {
    double *elemek = realloc( v->lista.elemek,
        sizeof(double) * uj_meret);
    if ( elemek ) {
      v->lista.elemek = elemek;
      _statusz = SUCCESS;
    }
  }
  return _statusz;
}

void vektor_start(vektor *v) {
  v->lista.kapacitas = VEKTOR_ALAP_KAPACITAS;
  v->lista.elemszam = 0;
  v->lista.elemek = (double *) malloc(
      sizeof(double) * v->lista.kapacitas);

  v->hozzaad = _f_vektorHozzaad;
}

