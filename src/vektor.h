#ifndef __M_VEKTOR_H__
#define __M_VEKTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VECTOR_INIT(vec) vektor vec;\
	vector_init(&vec)
#define VEKTOR_ALAP_KAPACITAS 100
#define UNDEFINED -1
#define SUCCESS 0

typedef struct sVektorLista {
	double *elemek;
	int kapacitas;
	int elemszam;
} sVektorLista;

typedef struct sVector vektor;
struct sVector {
	sVektorLista lista;
	int sorted;
	int error;
	char* error_msg;
	// Függvény pointerek
	int (*elemszam)(vektor *);
	int (*atmeretez)(vektor *, int);
	int (*vegere_tesz)(vektor *, double);
	int (*beallit)(vektor *, int, double);
	double (*ertek)(vektor *, int);
	int (*torol)(vektor *, int);
	int (*felszabadit)(vektor *);
	void (*kiir) (vektor *);
	int (*min_pos) (vektor *);
	int (*max_pos) (vektor *);
	void (*rendez) (vektor *);
	double (*atlag) (vektor *);
	double (*szoras) (vektor *);
	size_t (*keres) (vektor *);
};

void vector_init(vektor *);
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
size_t vektorFindSorted(vektor *, double);
size_t vektorFind(vektor *, double);


#endif
