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

	v.felszabadit(&v);
	return 0;
}
