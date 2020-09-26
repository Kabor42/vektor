#include <stdio.h>
#include <stdlib.h>

#include "vektor.h"


int main(int argc, char* argv[]) {
	printf("Hello world!\n");

	VECTOR_INIT(v);

	v.vegere_tesz(&v, 1);    
	v.vegere_tesz(&v, 2);    
	v.vegere_tesz(&v, 3);    
	v.vegere_tesz(&v, 4);    
	v.vegere_tesz(&v, 5);    

	v.kiir(&v);

	v.beallit(&v, 2, 8);

	v.kiir(&v);

	v.torol(&v, 3);

	v.kiir(&v);

	printf(" Min %+3.2lf\n", v.ertek(&v, v.min_pos(&v)));
	printf(" Max %+3.2lf\n", v.ertek(&v, v.max_pos(&v)));

	v.rendez(&v);

	v.kiir(&v);

	printf("Atlag: %+3.4lf\n", v.atlag(&v));
	printf("Szoras: %+3.4lf\n", v.szoras(&v));

	v.felszabadit(&v);
	return 0;
}
