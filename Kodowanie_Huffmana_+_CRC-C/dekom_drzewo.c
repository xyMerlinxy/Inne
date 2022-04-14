#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "struktury.h"
#include "dekom_drzewo.h"

void dekom_usun_drzewo(struct galaz* drzewo)
{
	if (drzewo == NULL)return;
	dekom_usun_drzewo(drzewo->potomek_prawy);
	dekom_usun_drzewo(drzewo->potomek_lewy);
	free(drzewo);
}

void wpisz_dwie_wartosci(struct galaz** drzewo, unsigned char znak, int slowo, unsigned char znak2, int slowo2) {
	if ((*drzewo) == NULL) {
		int i=1;//temp
		(*drzewo) = malloc(sizeof(struct galaz));
		if ((*drzewo) == NULL) {
			printf("Blad alokacji");
			exit(EXIT_FAILURE);
		}
		(*drzewo)->potomek_lewy = NULL;
		(*drzewo)->potomek_prawy = NULL;
		(*drzewo)->numer_znaku = -1;
		(*drzewo)->slowo = 0;

		wpisz_dwie_wartosci(drzewo, znak, slowo, znak2, slowo2);
		return;
	}

	if ((slowo > UINT_MAX / 2) && (slowo2 > UINT_MAX / 2)) {
		//mno¿enie jest po to ¿e jak przechodzimy do kolejnego poziomu drzewa to usuwamy pierwsze bity ze s³ów
		wpisz_dwie_wartosci((&(*drzewo)->potomek_prawy), znak, slowo * 2, znak2, slowo2 * 2);
		return;
	}
	if ((slowo <= UINT_MAX / 2) && (slowo2 <= UINT_MAX / 2)) {
		wpisz_dwie_wartosci(&((*drzewo)->potomek_lewy), znak, slowo * 2, znak2, slowo2 * 2);
		return;
	}
	if ((slowo > UINT_MAX / 2) && (slowo2 <= UINT_MAX / 2)) {
		wpisz_do_drzewa(&((*drzewo)->potomek_prawy), znak, slowo * 2);
		wpisz_do_drzewa(&((*drzewo)->potomek_lewy), znak2, slowo2 * 2);
		return;
	}
	else
	{
		wpisz_do_drzewa(&((*drzewo)->potomek_lewy), znak, slowo * 2);
		wpisz_do_drzewa(&((*drzewo)->potomek_prawy), znak2, slowo2 * 2);
		return;
	}
}

void wpisz_do_drzewa(struct galaz** drzewo, unsigned char znak, int slowo) {
	if ((*drzewo) == NULL) {
		(*drzewo) = malloc(sizeof(struct galaz));
		if ((*drzewo) == NULL) {
			printf("Blad alokacji");
			exit(EXIT_FAILURE);
		}
		(*drzewo)->potomek_lewy = NULL;
		(*drzewo)->potomek_prawy = NULL;
		(*drzewo)->numer_znaku = znak;
		(*drzewo)->slowo=slowo;
		return;
	}

	//jest ju¿ jakiœ znak tymczasowo przypisany do tego wêz³a
	if (((*drzewo)->potomek_prawy == NULL) && ((*drzewo)->potomek_lewy == NULL)) {
		wpisz_dwie_wartosci(drzewo, znak, slowo, (*drzewo)->numer_znaku, (*drzewo)->slowo);
		(*drzewo)->numer_znaku = 0;
	}
	//jeœli mamy wpisaæ do prawego potomka
	else if (slowo > UINT_MAX / 2) {
		wpisz_do_drzewa(&((*drzewo)->potomek_prawy), znak, slowo * 2);
	}
	else
	{
		wpisz_do_drzewa(&((*drzewo)->potomek_lewy), znak, slowo * 2);
	}


}

struct galaz * dekom_utworz_drzewo(FILE* odczyt) {

	int ilosc_slow;
	fread(&ilosc_slow, sizeof(int), 1, odczyt);

	struct galaz* drzewo = NULL;

	unsigned char znak;
	int slowo;
	int i;
	for (i = 0; i < ilosc_slow; i++) {
		fread(&znak, sizeof(unsigned char), 1, odczyt);
		fread(&slowo, sizeof(int), 1, odczyt);

		wpisz_do_drzewa(&drzewo, znak, slowo);

	}
	//printf("%i", i);

	return drzewo;
}