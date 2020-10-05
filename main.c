#include <stdio.h>
#include <stdlib.h>

size_t elemszam = 0; ///< Tomb aktualis elemszama.
size_t lefoglalt = 100; ///< Tomb aktialisan lefoglalt terulete.
double *tomb; ///< Pointer a tombbe.

int HIBA = 0; ///< Tortent-e hiba.
char *hibakod; ///< Mi volt a hiba.

double osszeg(double *t);
double atlag_fgv(double *t);
double indexeles_fgv(double *t, size_t index);
double szoras_fgv(double *t);
size_t minimum_index(double *t);
double minimum_fgv(double *t);
size_t keres(double *t, double elem);

void lefoglal(double *tomb, size_t uj_meret) {
  double *uj_tomb = (double *)realloc(tomb, uj_meret);
  if (uj_tomb) {
    tomb = uj_tomb;
    lefoglalt = uj_meret;
  } else {
    HIBA = 1;
    hibakod = "AJJAJ!, valamiert nem sikerult memoriat foglalni.";
  }
}

void betesz(double *tomb, double elem) {
  if (elemszam == lefoglalt)
    lefoglal(tomb, lefoglalt + 100);
  tomb[elemszam] = elem;
  elemszam += 1;
}

void beolvas(char *fajl, double *t) {
  FILE *fp = fopen(fajl, "r");
  char line[100];
  while (fgets(line, sizeof(line), fp) != NULL) {
    betesz(t, atof(line));
  }
  fclose(fp);
}

int main(int argc, char *argv[]) {
  // Megnezem meg van-e a szukseges argumentumok szama.
  if (argc <= 3)
    return -1; // Ha nincs meg kilep.
  // Elmentem a vektor meretet az argumentumokbol.
  size_t vektro_merete = atoi(argv[2]);
  // Elmentem a keresett szamot az argumentumokbol.
  double keresett_szam = atof(argv[3]);
  // Elmentem a fajl nevet az argumentumokbol.
  char* fajlnev = argv[1];
  // Mivel itt mar tudom, hogy minden valtozo megvan,
  // lefoglalom a tomb helyet a memoriaban.
  // Alapesetben 100 elemet, ha tobb kell majd foglalok meg.
  tomb = (double *)malloc(sizeof(double) * 100);

  beolvas( fajlnev, tomb);
  

}

double atlag_fgv(double *t) { return (osszeg(tomb) / elemszam); }
double minimum_fgv(double *t) { return (indexeles_fgv(t, minimum_index(t))); }
double osszeg(double *t) {
  double sum = 0;
  for (size_t i = 0; i < elemszam; i++)
    sum += indexeles_fgv(tomb, i);
  return sum;
}

double indexeles_fgv(double *t, size_t index) {
  if (0 <= index && index <= elemszam)
    return t[index];

  HIBA=1;
  hibakod = "AJJAJ!, tulindexeltel.";
  return 0;
}
