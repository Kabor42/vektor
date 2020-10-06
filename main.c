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

void beolvas(char *fajl, double *t) {
  FILE *fp = fopen(fajl, "r");
  if (fp == NULL)
    return;
  char line[30];
  while (fgets(line, sizeof line, fp) != NULL) {
    t[elemszam++]=atof(line);
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

  printf("Fajl %s\nMeret: %ld\nKeresett szam: %3.2lf\n",
      fajlnev,
      vektro_merete,
      keresett_szam);
  // Mivel itt mar tudom, hogy minden valtozo megvan,
  // lefoglalom a tomb helyet a memoriaban.
  lefoglalt = vektro_merete;
  tomb = (double *)malloc(sizeof(double) * lefoglalt);

  beolvas( fajlnev, tomb);


  double ossz = osszeg(tomb);
  if(!HIBA)
    printf("Osszeg: %3.6lf\n", ossz);
  double atl = atlag_fgv(tomb);
  if(!HIBA)
    printf("Atlag: %3.6lf\n", atl);
  double mini = minimum_fgv(tomb);
  if(!HIBA)
    printf("Min: %3.6lf\n", mini);
  return 0;
}

double atlag_fgv(double *t) { return (osszeg(tomb) / elemszam); }
double minimum_fgv(double *t) { return (indexeles_fgv(t, minimum_index(t))); }
double osszeg(double *t) {
  double sum = 0;
  HIBA=0;
  for (size_t i = 0; i < elemszam; i++){
    sum += indexeles_fgv(tomb, i);
    if (HIBA) {
      printf("%s\n", hibakod);
      return 0;
    }
  }
  return sum;
}

double indexeles_fgv(double *t, size_t index) {
  HIBA=0;
  if (0 <= index && index <= elemszam)
    return t[index];

  HIBA=1;
  hibakod = "AJJAJ!, tulindexeltel.";
  return 0;
}

size_t minimum_index(double *t) {
  double min = 0;
  for(size_t i=0; i<elemszam;i++)
    if (indexeles_fgv(t, min) > indexeles_fgv(t, i))
      min = i;
  return min;
}
