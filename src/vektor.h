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

/** Lista a vektor elemeinek tarolasara.
 *
 * elemek: taroljak az elemeket egy HEAP-ben mukodo listan,
 * hogy ne a stack-en jojjenek letre az elemek.
 */
typedef struct sVektorLista {
	double *elemek; ///< Dinamikus tomb, az nagy elemu vektorok miatt.
	int kapacitas; ///< A vektor aktualisan lefoglalt terulete.
	int elemszam; ///< A vektor aktualisan ennyi elemekt tartalmaz.
} sVektorLista;

typedef struct sVector vektor;
/** Vektor struktura.
 *
 * Egyszerubb igy dolgozni, mintha mindig figyelni kellene a dinamikus tomb
 * meretere, es toltottsegere.
 *
 * Osszefogja a hozza tartozo fuggvenyeket,
 * amik onmagan valtoztatnak.
 * Mintha C++-ban mindig meghivnank a self-et is.
 */
struct sVector {
	sVektorLista lista; ///< Dinamukus lista.
	int sorted; ///< A vektor aktualisan rendezett-e.
	int error; ///< Tortent-e hiba a legutobbi muveletnel.
	char* error_msg; ///< A hiba szovege.
	size_t osszehas_szam; ///< Osszehasonlitasok szama az utolso muveletnel, ha ismert.
	// Függvény pointerek
	int (*elemszam)(vektor *); ///< Hany elem van a vektorban.
	int (*atmeretez)(vektor *, int); ///< Vektor nagysaganak valtoztatasa.
	int (*vegere_tesz)(vektor *, double); ///< Berak egy elemet a vegere.
	int (*beallit)(vektor *, int, double); ///< Bellait egy elemet adott helyre.
	double (*ertek)(vektor *, int); ///< Erteket ad vissza egy adott helyrol.
	int (*torol)(vektor *, int); ///< Elemet torol egy adott helyrol.
	int (*felszabadit)(vektor *); ///< Felszabaditja a vektor altal foglalt helyet.
	void (*kiir) (vektor *); ///< Szovegesen kiirja a vektort.
	int (*min_pos) (vektor *); ///< A legkisebb elem helyet adja vissza.
	int (*max_pos) (vektor *); ///< A legnagyobb elem helyet adja vissza.
	void (*rendez) (vektor *); ///< Sorba rendez.
	double (*atlag) (vektor *); ///< Atlagolas.
	double (*szoras) (vektor *); ///< Vektor elemeinek szorasa.
	size_t (*keres) (vektor *, double); ///< Elemet keres a vektorban.
};


void vector_init(vektor *);


#endif
