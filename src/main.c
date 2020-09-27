#include <stdio.h>
#include <stdlib.h>

#include "vektor.h"


int main(int argc, char* argv[]) {
	printf("Hello world!\n");

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

	printf("Atlag: %+3.4lf\n", v.atlag(&v));
	printf("Szoras: %+3.4lf\n", v.szoras(&v));

	printf("Elemszam: %10d\n", v.elemszam(&v));

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
