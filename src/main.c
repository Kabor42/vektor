#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vektor.h"

/** Seged fuggveny a rendszer QSortjahoz.
 */
int _f_cmp(const void *a, const void *b)
{
  double tmp = (*(double *)a - *(double *)b);
  return (tmp > 0) ? 1 : (tmp < 0) ? -1 : 0;
}

int main(int argc, char *argv[])
{

  clock_t t;

  // Teszt, hogy megfelelo szamu parametert adtunk-e meg.
  if (argc < 4)
  {
    printf("Not enoug arguments\n");
    return -1;
  }

  // Seged valtozok a parameterekhez.
  char *filename = argv[1];
  size_t records = (size_t)atoi(argv[2]);
  double toFind = (double)atof(argv[3]);

  // Parameterek elenorzese.
  printf("\n********************************************************************************\n");
  printf("FILENAME: %s\n", filename);
  printf("ELEMSZAM: %3ld\n", records);
  printf("KERESENDO: %lf\n", toFind);

  // Vektor inicializalas.
  VECTOR_INIT(v);

  // Fajl beolvasasa.
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    v.felszabadit(&v);
    return -1;
  }
  else
  {
    char buff[50];
    while (fgets(buff, sizeof buff, fp) != NULL)
    {
      v.vegere_tesz(&v, atof(buff));
    }
  }
  fclose(fp);

  // Vektor masolasa a szorgalmi feladat osszehasonlitas reszehez.
  VECTOR_INIT(a);
  VECTOR_INIT(b);
  vector_copy(&v, &a);
  vector_copy(&v, &b);

  // Keresse meg a vektor legkisebb elemét, és írja ki annak indexét és értékét is! (A)
  printf("\n********************************************************************************\n");
  printf("Min %+3.2lf %d\n", v.ertek(&v, v.min_pos(&v)), v.min_pos(&v));
  printf("Max %+3.2lf %d\n", v.ertek(&v, v.max_pos(&v)), v.max_pos(&v));

  // Írjunk egy függvényt, ami visszaadja az adatsor átlagát és a szórását, és a program írja ki ezeket! (A)
  printf("\n********************************************************************************\n");
  printf("Atlag: %+3.4e\n", v.atlag(&v));
  printf("Szoras: %+3.4lf\n", v.szoras(&v));

  // printf("Elemszam: %10d\n", v.elemszam(&v));

  // rjunk egy függvényt, ami kiírja,
  // hogy a parancssori paraméterként megadott keresett szám szerepel-e a vektor elemei között,
  // és ha igen, hányadik indexnél!
  // Írja ki azt is, hogy ehhez hány összehasonlításra volt szükség! (A)
  printf("\n********************************************************************************\n");
  t = clock();
  size_t keresett_index = v.keres(&v, toFind);
  t = clock() - t;
  if (v.error)
  {
    printf("HIBA: %s\n", v.error_msg);
    v.error = 0;
  }
  else
  {
    printf("A keresett elem a %ld helyen van.\n", keresett_index);
    printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
    printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);
  }

  // Rendezze növekvő sorrendbe a beolvasott vektor elemeit a buborékos rendezés segítségével,
  // és írja ki az elvégzett összehasonlítások számát!
  // Ha legfeljebb 20 eleme van a vektornak, akkor írja ki a sorrendezett vektort is! (T)
  printf("\n********************************************************************************\n");
  t = clock();
  v.osszehas_szam = 0;
  v.rendez(&v);
  printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
  t = clock() - t;
  printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);

  // Tekintsük a d) feladatrészben sorbarendezett vektort!
  // Keresse meg a program ebben a vektorban a parancssori bemenetként megadott számot és írja ki az indexét,
  // valamint az összehasonlítások számát!
  // Találjunk olyan algoritmust, hogy minél kevesebb összehasonlításra legyen szükség! (T)
  printf("\n********************************************************************************\n");
  t = clock();
  keresett_index = v.keres(&v, toFind);
  t = clock() - t;
  if (v.error)
  {
    printf("HIBA: %s\n", v.error_msg);
    v.error = 0;
  }
  else
  {
    printf("A keresett elem a %ld helyen van.\n", keresett_index);
    printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
    printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);
  }

  // Szorgalmi: Ismerkedjünk meg a quick sort algoritmussal és írjunk egy saját implementációt,
  // amely sorbarendezi a beolvasott vektor elemeit!
  // Írja ki az elvégzett összehasonlítások számát!
  // Ha legfeljebb 20 eleme van a vektornak, akkor írja ki a sorrendezett vektort is!
  // Hasonlítsuk össze a saját algoritmus gyorsaságát az stdlib qsort függvénynével!
  printf("\n********************************************************************************\n");

  t = clock();
  printf("Rendezes STD QSort ...\n");
  qsort(v.lista.elemek, v.lista.elemszam, sizeof(double), _f_cmp);
  v.sorted = 1;
  v.osszehas_szam = 0;
  printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
  t = clock() - t;
  printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);

  printf("\n********************************************************************************\n");
  t = clock();
  v.osszehas_szam = 0;
  printf("Rendezes sajat QSort ...\n");
  v.qrendez(&v);
  printf("%ld darab osszehasonlitas tortent.\n", v.osszehas_szam);
  t = clock() - t;
  printf("%lf masodpercet vett igenybe.\n", ((double)t) / CLOCKS_PER_SEC);
  printf("\n********************************************************************************\n");

  // Befejezes.
  v.felszabadit(&v);
  a.felszabadit(&a);
  b.felszabadit(&b);

  return 0;
}
