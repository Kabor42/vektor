#include "vektor.h"

int vectorResize(vektor *, int);
int vectorPushBack(vektor *, double);
int vectorSet(vektor *, int, double);
double vectorGet(vektor *, int);
int vectorDelete(vektor *, int);
int vectorFree(vektor *);
int vectorTotal(vektor *);
void printVektor(vektor *);
int vektorGetMinPos(vektor *);
int vektorGetMaxPos(vektor *);
void vektorSort(vektor *);
double vektorAverage(vektor *);
double vektorSzoras(vektor *);
size_t vektorFindUnsorted(vektor *, double);
size_t vektorFindSorted(vektor *, size_t, size_t, double);
size_t vektorFind(vektor *, double);

/** Inicializalja a vektor strukturat.
 * @param v vektor amit inicializalni kell.
 *
 * Beallitja a helyes kezdoertekeket.
 * Lefoglalaja az alap mamoria teruletet.
 * Beallitja a helyes fuggvenypointereket.
 */
void vector_init(vektor *v) {
  v->vegere_tesz = vectorPushBack;
  v->beallit = vectorSet;
  v->ertek = vectorGet;
  v->felszabadit = vectorFree;
  v->elemszam = vectorTotal;
  v->atmeretez = vectorResize;
  v->torol = vectorDelete;
  v->kiir = printVektor;
  v->min_pos = vektorGetMinPos;
  v->max_pos = vektorGetMaxPos;
  v->rendez = vektorSort;
  v->atlag = vektorAverage;
  v->szoras = vektorSzoras;
  v->keres = vektorFind;

  v->lista.kapacitas = VEKTOR_ALAP_KAPACITAS;
  v->lista.elemszam = 0;
  v->lista.elemek = malloc(sizeof(double) * v->lista.kapacitas);
  v->sorted = 0;
  v->error = 0;
  v->error_msg = NULL;

  v->osszehas_szam = 0;
}

/**
 * @brief Vektor elemszama segedfuggveny.
 *
 * @param v vektor.
 *
 * @return vektor elemszam.
 */
int vectorTotal(vektor *v) {
  int totalCount = UNDEFINED;
  if (v) {
    totalCount = v->lista.elemszam;
  }
  return totalCount;
}

/**
 * @brief Vektor atmeretezes seged.
 *
 * @param v vektor.
 * @param capacity uj meret.
 *
 * @return statusz, sikeres, vagy sem.
 */
int vectorResize(vektor *v, int capacity) {
  int status = UNDEFINED;
  if (v) {
    double *items = realloc(v->lista.elemek, sizeof(double) * capacity);
    if (items) {
      v->lista.elemek = items;
      v->lista.kapacitas = capacity;
      status = SUCCESS;
    }
  }
  return status;
}

/**
 * @brief Vektor elem betesz seged.
 *
 * @param v vektor;
 * @param item elem amit behelyez.
 *
 * @return sikeres-e a behelyezes.
 */
int vectorPushBack(vektor *v, double item) {
  int status = UNDEFINED;
  if (v) {
    if (v->lista.kapacitas == v->lista.elemszam) {
      status = vectorResize(v, v->lista.kapacitas + 100);
      if (status != UNDEFINED) {
        v->lista.elemek[v->lista.elemszam++] = item;
      }
    } else {
      v->lista.elemek[v->lista.elemszam++] = item;
      status = SUCCESS;
    }
  }
  v->sorted = 0;
  return status;
}

int vectorSet(vektor *v, int index, double item) {
  int status = UNDEFINED;
  if (v) {
    if ((index >= 0) && (index < v->lista.elemszam)) {
      v->lista.elemek[index] = item;
      status = SUCCESS;
    }
  }
  v->sorted = 0;
  return status;
}

double vectorGet(vektor *v, int index) {
  double readData = 0.0;
  if (v) {
    if ((index >= 0) && (index < v->lista.elemszam)) {
      readData = v->lista.elemek[index];
    }
  }
  return readData;
}

int vectorDelete(vektor *v, int index) {
  int status = UNDEFINED;
  int i = 0;
  if (v) {
    if ((index < 0) || (index >= v->lista.elemszam)) {
      return status;
    }

    for (i = index; (i < v->lista.elemszam - 1); i++) {
      v->lista.elemek[i] = v->lista.elemek[i + 1];
    }

    v->lista.elemszam--;

    if ((v->lista.elemszam > 0) &&
        ((v->lista.elemszam) == (v->lista.kapacitas - 101))) {
      vectorResize(v, v->lista.kapacitas - 100);
    }
    status = SUCCESS;
  }
  return status;
}

int vectorFree(vektor *v) {
  int status = UNDEFINED;
  if (v) {
    free(v->lista.elemek);
    v->lista.elemek = NULL;
    status = SUCCESS;
  }
  return status;
}

void printVektor(vektor *v) {
  for (size_t i = 0; i < v->elemszam(v); i++)
    printf(" %2lf", v->ertek(v, i));
  printf("\n");
}

int vektorGetMaxPos(vektor *v) {
  double max = v->ertek(v, 0);
  size_t i_max = 0;
  if (v) {
    for (size_t i = 1; i < v->lista.elemszam; i++) {
      if (v->ertek(v, i) > max) {
        max = v->ertek(v, i);
        i_max = i;
      }
    }
  }
  return i_max;
}

int vektorGetMinPos(vektor *v) {
  double min = v->ertek(v, 0);
  size_t i_min = 0;
  if (v) {
    for (size_t i = 1; i < v->lista.elemszam; i++) {
      if (v->ertek(v, i) < min) {
        min = v->ertek(v, i);
        i_min = i;
      }
    }
  }
  return i_min;
}

void vektorSort(vektor *v) {
  v->osszehas_szam = 0;
  double tmp = 0;
  if (v) {
    for (size_t i = 0; i < v->elemszam(v) - 1; i++) {
      fprintf(stdout, "\r%6ld / %6d", i, v->lista.elemszam);
      fflush(stdout);
      for (size_t j = i + 1; j < v->elemszam(v); j++)
        if (v->ertek(v, i) > v->ertek(v, j)) {
          v->osszehas_szam++;
          tmp = v->ertek(v, i);
          v->beallit(v, i, v->ertek(v, j));
          v->beallit(v, j, tmp);
        }
    }
  }
  printf("\n");
  v->sorted = 1;
}

double vektorAverage(vektor *v) {
  double cumsum = 0;
  if (v) {
    for (size_t i = 0; i < v->elemszam(v); i++)
      cumsum += v->ertek(v, i);
  }
  return cumsum / v->elemszam(v);
}

double vektorSzoras(vektor *v) {
  double cumsumsum = 0;
  for (size_t i = 0; i < v->elemszam(v); i++)
    cumsumsum += pow(v->ertek(v, i), 2);
  return sqrt(cumsumsum / v->elemszam(v));
}

size_t vektorFindUnsorted(vektor *v, double elem) {
  for (size_t i = 0; i < v->elemszam(v); i++) {
    v->osszehas_szam++;
    if (fabs(elem - v->ertek(v, i)) <= 1e-9)
      return i;
  }
  v->error = 1;
  v->error_msg = "A keresett elem nem talalhato!.";
  return 0;
}
size_t vektorFindSorted(vektor *v, size_t b, size_t j, double elem) {
  if (j >= b) {
    v->osszehas_szam++;
    size_t koz = b + (j - b) / 2;
    if (v->lista.elemek[koz] == elem) {
      v->osszehas_szam++;
      return koz;
    }
    if (v->lista.elemek[koz] > elem) {
      v->osszehas_szam++;
      return vektorFindSorted(v, b, koz - 1, elem);
    }
    return vektorFindSorted(v, koz + 1, j, elem);
  }
  v->error = 1;
  v->error_msg = "A függvény még nincs implementálva!";
  return 0;
}
size_t vektorFind(vektor *v, double elem) {
  v->osszehas_szam = 0;
  v->error = 0;
  if (v->sorted)
    return vektorFindSorted(v, 0, v->lista.elemszam, elem);
  return vektorFindUnsorted(v, elem);
}
