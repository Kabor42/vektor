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
void vektorQsort(vektor *);
double vektorAverage(vektor *);
double vektorSzoras(vektor *);
size_t vektorFindUnsorted(vektor *, double);
size_t vektorFindSorted(vektor *, size_t, size_t, double);
size_t vektorFind(vektor *, double);
void _f_qsort(double *, double *);
void _f_part(double *, double *, double **, double **, double **, double **);
void _f_insrt(double *, double *);

/** Inicializalja a vektor strukturat.
 * @param v vektor amit inicializalni kell.
 *
 * Beallitja a helyes kezdoertekeket.
 * Lefoglalaja az alap mamoria teruletet.
 * Beallitja a helyes fuggvenypointereket.
 */
void vector_init(vektor *v)
{
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
  v->qrendez = vektorQsort;
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

/** Vektor deep copy a-t b-be.
 * 
 * @param a vektor amit masolunk.
 * @param b vektor amibe masolunk.
 */
void vector_copy(vektor * a, vektor * b) {
  b->lista.kapacitas = a->lista.kapacitas;
  b->lista.elemszam = a->lista.elemszam;
  b->lista.elemek = (double *)realloc(b->lista.elemek, sizeof(double) * b->lista.kapacitas);
  for(size_t i = 0; i < b->lista.elemszam; i++)
     *(b->lista.elemek + i) = *(a->lista.elemek + i);
}

/**
 * @brief Vektor elemszama segedfuggveny.
 *
 * @param v vektor.
 *
 * @return vektor elemszam.
 */
int vectorTotal(vektor *v)
{
  int totalCount = UNDEFINED;
  if (v)
  {
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
int vectorResize(vektor *v, int capacity)
{
  int status = UNDEFINED;
  if (v)
  {
    double *items = realloc(v->lista.elemek, sizeof(double) * capacity);
    if (items)
    {
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
int vectorPushBack(vektor *v, double item)
{
  int status = UNDEFINED;
  if (v)
  {
    if (v->lista.kapacitas == v->lista.elemszam)
    {
      status = vectorResize(v, v->lista.kapacitas + 100);
      if (status != UNDEFINED)
      {
        v->lista.elemek[v->lista.elemszam++] = item;
      }
    }
    else
    {
      v->lista.elemek[v->lista.elemszam++] = item;
      status = SUCCESS;
    }
  }
  v->sorted = 0;
  return status;
}

/** Vektor elem valtoztatasa indexen levo helyen.
 * 
 * @param v vektor ami valtoztatunk.
 * @param index melyik helyen vegezzuk a valtoztatast.
 * @param item mire valtoztatunk.
 * @return statusz sikeres-e.
 */
int vectorSet(vektor *v, int index, double item)
{
  int status = UNDEFINED;
  if (v)
  {
    if ((index >= 0) && (index < v->lista.elemszam))
    {
      v->lista.elemek[index] = item;
      status = SUCCESS;
    }
  }
  v->sorted = 0;
  return status;
}

/** Vector elem lekerese indexrol.
 * 
 * @param v vektor amibol kerunk.
 * @param index melyik indexet kerjuk.
 * @returns lekert ertek.
 */
double vectorGet(vektor *v, int index)
{
  double readData = 0.0;
  if (v)
  {
    if ((index >= 0) && (index < v->lista.elemszam))
    {
      readData = v->lista.elemek[index];
    }
  }
  return readData;
}

/** Adott index torlese.
 * 
 * Majd minden elemet a torolt elem utan egyel athelyez.
 * Nagyon koltseges folyamat.
 * 
 * @param v vektor amibol torolunk.
 * @param index melyik indexet toroljuk.
 * @return sikeresseg.
 */
int vectorDelete(vektor *v, int index)
{
  int status = UNDEFINED;
  int i = 0;
  if (v)
  {
    if ((index < 0) || (index >= v->lista.elemszam))
    {
      return status;
    }

    for (i = index; (i < v->lista.elemszam - 1); i++)
    {
      v->lista.elemek[i] = v->lista.elemek[i + 1];
    }

    v->lista.elemszam--;

    if ((v->lista.elemszam > 0) &&
        ((v->lista.elemszam) == (v->lista.kapacitas - 101)))
    {
      vectorResize(v, v->lista.kapacitas - 100);
    }
    status = SUCCESS;
  }
  return status;
}

/** Vektor felszabaditasa.
 * 
 * @param v vektor.
 * @return sikersseg.
 */
int vectorFree(vektor *v)
{
  int status = UNDEFINED;
  if (v)
  {
    free(v->lista.elemek);
    v->lista.elemek = NULL;
    status = SUCCESS;
  }
  return status;
}

/** Vektor kiirasa.
 * 
 * @param v vektor amit kiirunk.
 */
void printVektor(vektor *v)
{
  for (size_t i = 0; i < v->elemszam(v); i++)
    printf(" %2lf", v->ertek(v, i));
  printf("\n");
}

/** Maximalis elem indexenek visszaadasa.
 * 
 * @param v vektor.
 * @return legnagyobb elem indexe.
 */
int vektorGetMaxPos(vektor *v)
{
  double max = v->ertek(v, 0);
  size_t i_max = 0;
  if (v)
  {
    for (size_t i = 1; i < v->lista.elemszam; i++)
    {
      if (v->ertek(v, i) > max)
      {
        max = v->ertek(v, i);
        i_max = i;
      }
    }
  }
  return i_max;
}

/** Minimalis elem indexenek visszaadasa.
 * 
 * @param v vektor.
 * @return legkisebb elem indexe.
 */
int vektorGetMinPos(vektor *v)
{
  double min = v->ertek(v, 0);
  size_t i_min = 0;
  if (v)
  {
    for (size_t i = 1; i < v->lista.elemszam; i++)
    {
      if (v->ertek(v, i) < min)
      {
        min = v->ertek(v, i);
        i_min = i;
      }
    }
  }
  return i_min;
}

/** Vektor rendezese, bubbleSort.
 * 
 * Egyszeru BubbleSort algoritmus hasznalata O(n^2).
 * 
 * @param v vektor amit rendezunk.
 */
void vektorSort(vektor *v)
{
  v->osszehas_szam = 0;
  double tmp = 0;
  if (v)
  {
    for (size_t i = 0; i < v->elemszam(v) - 1; i++)
    {
      fprintf(stdout, "\r%6ld / %6d", i, v->lista.elemszam);
      fflush(stdout);
      for (size_t j = i + 1; j < v->elemszam(v); j++)
        if (v->ertek(v, i) > v->ertek(v, j))
        {
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

/** Vektor elemeinek atlaga.
 * @param v vektor.
 * @returns atlag.
 */
double vektorAverage(vektor *v)
{
  double cumsum = 0;
  if (v)
  {
    for (size_t i = 0; i < v->elemszam(v); i++)
      cumsum += v->ertek(v, i);
  }
  return cumsum / v->elemszam(v);
}

/** Vektor elemeinek szorasa.
 * 
 * @param v vektor.
 * @return szoras.
 */
double vektorSzoras(vektor *v)
{
  double cumsumsum = 0;
  for (size_t i = 0; i < v->elemszam(v); i++)
    cumsumsum += pow(v->ertek(v, i), 2);
  return sqrt(cumsumsum / v->elemszam(v));
}

/** Keress a rendezetlen vektorban.
 * 
 * Ha rendezetlen akkor nem tudunk vmi okos algortmust hasznalni,
 * igy csak sorba vegigmegyunk az elemeken.
 * 
 * @param v vektor amiben keresunk.
 * @param elem elem amit keresunk.
 * @return elem indexe.
 * A fugveny hibat allit be ha nincs meg az elem.
 * Ezt figyelni kell!!.
 */
size_t vektorFindUnsorted(vektor *v, double elem)
{
  for (size_t i = 0; i < v->elemszam(v); i++)
  {
    v->osszehas_szam++;
    if (fabs(elem - v->ertek(v, i)) <= 1e-9)
      return i;
  }
  v->error = 1;
  v->error_msg = "A keresett elem nem talalhato!.";
  return 0;
}

/** Keress a rendezett vektorban.
 * 
 * Mivel a vektor mar rendezett igy binaris keresest alkalmazunk.
 * 
 * @param v vektor amiben keresunk.
 * @param b bal index.
 * @param j jobb index.
 * @param elem keresett elem.
 * @return keresett elem indexe.
 * A fugveny hibat allit be ha nincs meg az elem.
 * Ezt figyelni kell!!.
 */
size_t vektorFindSorted(vektor *v, size_t b, size_t j, double elem)
{
  if (j >= b)
  {
    v->osszehas_szam++;
    size_t koz = b + (j - b) / 2;
    if (v->lista.elemek[koz] == elem)
    {
      v->osszehas_szam++;
      return koz;
    }
    if (v->lista.elemek[koz] > elem)
    {
      v->osszehas_szam++;
      return vektorFindSorted(v, b, koz - 1, elem);
    }
    return vektorFindSorted(v, koz + 1, j, elem);
  }
  v->error = 1;
  v->error_msg = "A függvény még nincs implementálva!";
  return 0;
}

/** Kereses a vektorban.
 * Automatikusan a megfelelo keresest valasztja.
 * @param v vektor amiben keresunk.
 * @param elem keresett elem.
 */
size_t vektorFind(vektor *v, double elem)
{
  v->osszehas_szam = 0;
  v->error = 0;
  if (v->sorted)
    return vektorFindSorted(v, 0, v->lista.elemszam, elem);
  return vektorFindUnsorted(v, elem);
}

// Seged makrok a QuickSort-hoz.
#define swap(a, b) \
  {                \
    double h = a;  \
    a = b;         \
    b = h;         \
  }
#define min(a, b) ((a) < (b) ? (a) : (b))
#define sort3(a, b, c) \
  if (b < a)           \
  {                    \
    if (c < a)         \
    {                  \
      if (c < b)       \
      {                \
        swap(a, c);    \
      }                \
      else             \
      {                \
        double h = a;  \
        a = b;         \
        b = c;         \
        c = h;         \
      }                \
    }                  \
    else               \
    {                  \
      swap(a, b);      \
    }                  \
  }                    \
  else                 \
  {                    \
    if (c < b)         \
    {                  \
      if (c < a)       \
      {                \
        double h = c;  \
        c = b;         \
        b = a;         \
        a = h;         \
      }                \
      else             \
      {                \
        swap(b, c);    \
      }                \
    }                  \
  }
/** Qsort Particio segedfuggveny.
 * Azert igy nez ki, mert az elagazasok elhagyasa miatt 
 * szet van bontva a fuggveny.
 */
void _f_part(double *left0, double *right0, double **l1, double **r1,
             double **l2, double **r2)
{
  double *left = left0 + 1;
  double *right = right0;

  double *mid = left0 + (right0 - left0) / 2;
  double piv = *mid;
  sort3(*left0, piv, *right0);
  *left = piv;

  while (1)
  {
    do
      left += 1;
    while (*left < piv);
    do
      right -= 1;
    while (*right > piv);
    if (left >= right)
      break;
    swap(*left, *right);
  }
  *(left0 + 1) = *right;
  *right = piv;
  if (right < mid)
  {
    *l1 = left0;
    *r1 = right - 1;
    *l2 = right + 1;
    *r2 = right0;
  }
  else
  {
    *l1 = right + 1;
    *r1 = right0;
    *l2 = left0;
    *r2 = right - 1;
  }
}
/** InsertionSort a rendezett halmazok osszefuzesehez.
 */
void _f_insrt(double *left, double *right)
{
  for (double *pi = left + 1; pi <= right; pi++)
    if (*pi < *left)
      swap(*pi, *left);
  for (double *pi = left + 2; pi <= right; pi++)
  {
    double h = *pi;
    double *pj = pi - 1;
    while (h < *pj)
    {
      *(pj + 1) = *pj;
      pj -= 1;
    }
    *(pj + 1) = h;
  }
}
/** QuickSort
 */
void _f_qsort(double *left, double *right)
{
  double *l, *r;
  while (right - left >= 50)
  {
    _f_part(left, right, &l, &r, &left, &right);
    _f_qsort(l, r);
  }
  _f_insrt(left, right);
}
/** Vektor QuickSort
 */
void vektorQsort(vektor *v)
{
  v->osszehas_szam = 0;
  _f_qsort(v->lista.elemek, v->lista.elemek + v->lista.elemszam - 1);
  v->sorted = 1;
}
