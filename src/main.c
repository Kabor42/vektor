#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vektor.h"

int _f_cmp(const void *a, const void *b) {
	double tmp = ( *(double*)a - *(double*)b );
	return (tmp > 0) ? 1 : (tmp < 0 ) ? -1 : 0;
}

int main(int argc, char* argv[]) {
	printf("Hello world!\n");

	clock_t t;

	for(size_t i=0;i<argc;i++)
		printf("%3ld\t%s\n",i,argv[i]);

	if (argc < 4) {
		printf("Not enoug arguments\n");
		return -1;
	}
	char* filename = argv[1];
	size_t records = (size_t) atoi(argv[2]);
	double toFind = (double) atof(argv[3]);

	printf("FILENAME: %s\n",filename);
	printf("ELEMSZAM: %3ld\n",records);
	printf("KERESENDO: %lf\n",toFind);
	VECTOR_INIT(v);


	FILE *fp = fopen(filename, "r");
	if ( fp == NULL) {
		v.felszabadit(&v);
		return -1;
	} else {
		char buff[50];
		while(fgets(buff, sizeof buff, fp) !=NULL) {
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
		printf("(q/b): ");
		feof = scanf(" %c", &ansver);
	} while (ansver != 'q' && ansver != 'b' && feof != EOF);

	t = clock();
	printf("Rendezes...\n");
	if (ansver == 'b') v.rendez(&v);
	if (ansver == 'q') {
		qsort(v.lista.elemek, v.lista.elemszam, sizeof(double), _f_cmp);
		v.sorted = 1;
		v.osszehas_szam = 0;
	}
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
