#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vektor.h"

int _f_cmp(const void *a, const void *b) {
  double tmp = (*(double *)a - *(double *)b);
  return (tmp > 0) ? 1 : (tmp < 0) ? -1 : 0;
}

int main(int argc, char *argv[]) {

  clock_t t;

  if (argc < 4) {
    printf("Not enoug arguments\n");
    return -1;
  }
  char *filename = argv[1];
  size_t records = (size_t)atoi(argv[2]);
  double toFind = (double)atof(argv[3]);

  printf("FILENAME: %s\n", filename);
  printf("ELEMSZAM: %3ld\n", records);
  printf("KERESENDO: %lf\n", toFind);
  VECTOR_INIT(v);

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    v.felszabadit(&v);
    return -1;
  } else {
    char buff[50];
    while (fgets(buff, sizeof buff, fp) != NULL) {
      v.vegere_tesz(&v, atof(buff));
    }
  }
  fclose(fp);

  printf("Min %+3.2lf\n", v.ertek(&v, v.min_pos(&v)));
  printf("Max %+3.2lf\n", v.ertek(&v, v.max_pos(&v)));

  printf("Atlag: %+3.4e\n", v.atlag(&v));
  printf("Szoras: %+3.4lf\n", v.szoras(&v));

  printf("Elemszam: %10d\n", v.elemszam(&v));

  t = clock();
  size_t keresett_index = v.keres(&v, toFind);
  t = clock() - t;
  if (v.error) {
    printf("HIBA: %s\n", v.error_msg);
    v.error = 0;
  } else {
    printf("A keresett elem a %ld helyen van.\n", keresett_index);
    printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
    printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);
  }

  char ansver;
  int feof = 0;
  printf("QuickSort(q) vagy BubbleSort(b)?\n");
  do {
    printf("(q/b/s): ");
    feof = scanf(" %c", &ansver);
  } while (ansver != 'q' && ansver != 's' && ansver != 'b' && feof != EOF);

  t = clock();
  printf("Rendezes...\n");
  if (ansver == 'b')
    v.rendez(&v);
  if (ansver == 'q') {
    qsort(v.lista.elemek, v.lista.elemszam, sizeof(double), _f_cmp);
    v.sorted = 1;
    v.osszehas_szam = 0;
  }
  if (ansver == 's')
    v.qrendez(&v);
  printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
  t = clock() - t;
  printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);

  t = clock();
  keresett_index = v.keres(&v, toFind);
  t = clock() - t;
  if (v.error) {
    printf("HIBA: %s\n", v.error_msg);
    v.error = 0;
  } else {
    printf("A keresett elem a %ld helyen van.\n", keresett_index);
    printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
    printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);
  }

  printf("Elso: %10.5lf\nUtolso: %10.5lf\n", v.ertek(&v, 0),
         v.ertek(&v, v.elemszam(&v) - 1));

  printf("[ TEST ][ IS_SORTED ]");
  for (size_t i = 0; i < v.elemszam(&v); i++)
    if (v.ertek(&v, i - 1) > v.ertek(&v, i))
      printf("[ NOT SORTED ]");
  printf("\n");

  printf("  HEAD \n");
  for (size_t i = 0; i < 20; i++) {
    printf("%14.5lf", v.ertek(&v, i));
    if (i % 2 != 0)
      printf("\n");
  }
  printf("\n  TAIL \n");
  for (size_t i = v.elemszam(&v) - 20; i < v.elemszam(&v); i++) {
    printf("%14.5lf", v.ertek(&v, i));
    if (i % 2 != 0)
      printf("\n");
  }
  printf("\n");

  // v.vegere_tesz(&v, 1);
  // v.vegere_tesz(&v, 2);
  // v.vegere_tesz(&v, 3);
  // v.vegere_tesz(&v, 4);
  // v.vegere_tesz(&v, 5);

  // v.kiir(&v);

  // v.beallit(&v, 2, 8);

  // v.kiir(&v);

  // v.torol(&v, 3);

  // v.kiir(&v);

  // printf(" Min %+3.2lf\n", v.ertek(&v, v.min_pos(&v)));
  // printf(" Max %+3.2lf\n", v.ertek(&v, v.max_pos(&v)));

  // v.rendez(&v);

  // v.kiir(&v);

  // printf("Atlag: %+3.4lf\n", v.atlag(&v));
  // printf("Szoras: %+3.4lf\n", v.szoras(&v));

  v.felszabadit(&v);
  return 0;
}
