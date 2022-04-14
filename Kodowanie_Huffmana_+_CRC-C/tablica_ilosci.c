//#include <stdlib.h>d
#include "obsluga_pliku.h"
#include "struktury.h"
#include <stdlib.h>
#include <stdio.h>


#define rozszerzenie_dla_modelu "model"
#define rozszerzenie_dla_wielkosci "ileBajtow"
#define rozszerzenie_dla_modelu_posortowanego "modelSort"



int utworz_plik_z_wielkoscia(FILE * plik,char *nazwa) {

	int ilosc_znakow = dlugosc_pliku(plik);
	FILE* zapis_wielkosci;
	zapis_wielkosci = otworz_plik_wb(zmaina_rozszerzenia(nazwa, rozszerzenie_dla_wielkosci));
	fprintf(zapis_wielkosci, "%d", ilosc_znakow);
	fclose(zapis_wielkosci);
	zapis_wielkosci = NULL;
	return ilosc_znakow;
}



struct element** utworz_tablice_czestotliwosci(char*nazwa,int * wielkosc_tablicy, int* ilosc_znakow) {

	FILE* plik;
	plik = otworz_plik_rb(nazwa);

	int tab[256] = { 0 };

	fseek(plik, 0, SEEK_SET);
	*ilosc_znakow = utworz_plik_z_wielkoscia(plik,nazwa);

	int i;
	int znak = 0;
	for (i = 0; i < *ilosc_znakow; i++) {
		fread(&znak, 1, 1, plik);
		tab[znak]++;
	}

	fclose(plik);

	(*wielkosc_tablicy) =0;

	for (i = 0; i < 256; i++) {
		if (tab[i] > 0) {
		(*wielkosc_tablicy)++;
		}
	}

	//alokacja tablicy i wpisanie w ni¹ wartoœci
	struct element** tablica = calloc(sizeof(struct element*), *wielkosc_tablicy);		//alokacja tablicy wskaŸników
	if (tablica == NULL) {
		printf("Blad alokacji");
		exit(EXIT_FAILURE);
	}

	int j=0;
	for (i = 0; i < 256; i++) {
		if (tab[i] > 0) {
			tablica[j] = malloc(sizeof(struct element));			//alokacja poszczególnych elementów
			if (tablica[j] == NULL) {
				printf("Blond alokacji");
				exit(EXIT_FAILURE);
			}
			tablica[j]->ilosc_wystapien = tab[i];
			tablica[j]->numer_znaku = i;
			j++;
		}
	}
	//wypisanie nieposortowanej
	/*for (i = 0; i <(*wielkosc_tablicy); i++) {
		printf("Znak numer %d wystepuje %d razy\n", tablica[i]->numer_znaku, tablica[i]->ilosc_wystapien);
	}*/

	FILE* zapis_krotnosci;
	zapis_krotnosci = otworz_plik_wb(zmaina_rozszerzenia(nazwa, rozszerzenie_dla_modelu));
	
	for (i = 0; i < (*wielkosc_tablicy); i++) {
		fprintf(zapis_krotnosci, "%d  %d\n", tablica[i]->numer_znaku, tablica[i]->ilosc_wystapien);
	}

	fclose(zapis_krotnosci);
	zapis_krotnosci = NULL;

	return tablica;
}

int warunek(const void* pierwsza, const void* druga) {
	struct element* _pierwsza = *(struct element**)pierwsza;
	struct element* _druga = *(struct element**)druga;
	return((_druga->ilosc_wystapien) - (_pierwsza->ilosc_wystapien));
}

void sortuj_tablice(struct element** tablica_znakow, int ilosc, char * nazwa) {

	qsort(tablica_znakow, ilosc, sizeof(*tablica_znakow), warunek);

	FILE* zapis_posort;
	zapis_posort = otworz_plik_wb(zmaina_rozszerzenia(nazwa, rozszerzenie_dla_modelu_posortowanego));
	int i;
	for (i = 0; i < ilosc; i++) {
		fprintf(zapis_posort, "%d  %d\n", tablica_znakow[i]->numer_znaku, tablica_znakow[i]->ilosc_wystapien);
	}

	fclose(zapis_posort);
	//wypisanie posortowanej
	//for (i = 0; i < ilosc; i++) {
	//	printf("Znak numer %d wystepuje %d razy\n", tablica_znakow[i]->numer_znaku, tablica_znakow[i]->ilosc_wystapien);
	//}


	zapis_posort = NULL;
}

void usun_tablice(struct element*** tablica_znakow, int wielkosc_tablicy) {
	int i;
	for (i = 0; i < wielkosc_tablicy; i++) {
		free((*tablica_znakow)[i]);
	}
	free(*tablica_znakow);
	*tablica_znakow = NULL;
}