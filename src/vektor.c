#include "vektor.h"

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

	v->lista.kapacitas = VEKTOR_ALAP_KAPACITAS;
	v->lista.elemszam = 0;
	v->lista.elemek = malloc(sizeof(double) * v->lista.kapacitas);
}

int vectorTotal(vektor *v) {
	int totalCount = UNDEFINED;
	if (v) {
		totalCount = v->lista.elemszam;
	}
	return totalCount;
}

int vectorResize(vektor *v, int capacity) {
	int status = UNDEFINED;
	if(v) {
		double *items = realloc(v->lista.elemek, sizeof(double) * capacity);
		if (items) {
			v->lista.elemek = items;
			v->lista.kapacitas = capacity;
			status = SUCCESS;
		}
	}
	return status;
}

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
	return status;
}

double vectorGet(vektor *v , int index) {
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

		for(i=index; (i < v->lista.elemszam-1); i++) {
			v->lista.elemek[i] = v->lista.elemek[i+1];
		}

		v->lista.elemszam--;

		if ((v->lista.elemszam>0) && ((v->lista.elemszam) == (v->lista.kapacitas - 101))) {
			vectorResize(v, v->lista.kapacitas - 100);
		}
		status = SUCCESS;
	}
	return status;
}

int vectorFree(vektor *v) {
	int status = UNDEFINED;
	if(v) {
		free(v->lista.elemek);
		v->lista.elemek = NULL;
		status =SUCCESS;
	}
	return status;
}


void printVektor(vektor *v) {
	for (size_t i=0; i < v->elemszam(v);i++)
		printf(" %2lf", v->ertek(v, i));
	printf("\n");
}

int vektorGetMaxPos(vektor *v) {
	double max = v->ertek(v, 0);
	size_t i_max = 0;
	if (v) {
		for ( size_t i=1; i < v->lista.elemszam; i++) {
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
		for ( size_t i=1; i < v->lista.elemszam; i++) {
			if (v->ertek(v, i) < min) {
				min = v->ertek(v, i);
				i_min = i;
			}
		}
	}
	return i_min;
}

void vektorSort(vektor *v){
	double tmp = 0;
	if (v) {
		for (size_t i=0; i < v->elemszam(v)-1;i++)
			for (size_t j=i+1; j < v->elemszam(v); j++)
				if ( v->ertek(v, i) > v->ertek(v, j)) {
					tmp = v->ertek(v, i);
					v->beallit(v, i, v->ertek(v, j));
					v->beallit(v, j, tmp);
				}
	}
}

double vektorAverage(vektor *v) {
	double cumsum = 0;
	if(v) {
		for (size_t i = 0; i < v->elemszam(v); i++)
			cumsum += v->ertek(v, i);
	}
	return cumsum/v->elemszam(v);
}

double vektorSzoras(vektor *v) {
	double cumsumsum= 0;
	for (size_t i = 0; i < v->elemszam(v); i++)
		cumsumsum += pow(v->ertek(v, i), 2);
	return sqrt(cumsumsum / v->elemszam(v));
}
