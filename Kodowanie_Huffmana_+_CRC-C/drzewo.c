#include <stdlib.h>
#include <stdio.h>
#include "struktury.h"
#include "drzewo.h"
#include "obsluga_pliku.h"

#define rozszerzenie_dla_drzewa "drzewo"

int warunek_do_sortowania_w_drzewie(const void* pierwsza, const void* druga) {
	struct galaz* _pierwsza = *(struct galaz**)pierwsza;
	struct galaz* _druga = *(struct galaz**)druga;
	return((_druga->ilosc) - (_pierwsza->ilosc));
}

struct galaz* utworz_drzewo(struct element** tablica_znakow, int ilosc) {
	//utworzenie tablicy lasu

	struct galaz** las = calloc(ilosc,sizeof(struct galaz*));
	if (las == NULL) {
		printf("Blad alokacji");
		exit(EXIT_FAILURE);
	}
	//utworzenie galezi skladajacych sie tylko z elementow tablicy,
	int i;
	for (i = 0; i < ilosc; i++) {
		las[i] = malloc(sizeof(struct galaz));
		if (las[i] == NULL) {
			printf("Blad alokacji");
			exit(EXIT_FAILURE);
		}
		las[i]->potomek_lewy = NULL;
		las[i]->potomek_prawy = NULL;
		las[i]->numer_znaku = tablica_znakow[i]->numer_znaku;
		las[i]->ilosc = tablica_znakow[i]->ilosc_wystapien;
	}
	
	/*for (i = 0; i < ilosc; i++) {
		printf("Znak %i ilosc %i\n", las[i]->numer_znaku, las[i]->ilosc);
	}*/

	int pozostalo_w_tablicy = ilosc-1;//wartosc 0 oznacza ¿e zosta³ jeden element
	int numerowanie_wezlow = -1;
	//po prostu ³¹czê dwa ostatnie galezie, bo maja najmniejsza ilosc znakow

	while (pozostalo_w_tablicy) {
		struct galaz* nowy = malloc(sizeof(struct galaz));
		if (nowy == NULL) {
			printf("Blad alokacji");
			exit(EXIT_FAILURE);
		}
		nowy->ilosc = las[pozostalo_w_tablicy]->ilosc + las[pozostalo_w_tablicy - 1]->ilosc;
		nowy->numer_znaku = numerowanie_wezlow--;
		//lewy potomek ma wieksza ilosc
		nowy->potomek_prawy = las[pozostalo_w_tablicy - 1];
		nowy->potomek_lewy = las[pozostalo_w_tablicy];
		//wstawienie nowego zamiast prawego potomka i usuniecie z tablicy lewego potomka
		las[pozostalo_w_tablicy - 1] = nowy;
		las[pozostalo_w_tablicy] = NULL;
		pozostalo_w_tablicy--;

		/*for (i = 0; i <= pozostalo_w_tablicy; i++) {
			printf("Znak %i ilosc %i\n", las[i]->numer_znaku, las[i]->ilosc);
		}*/

		qsort(las, pozostalo_w_tablicy + 1, sizeof(*las), warunek_do_sortowania_w_drzewie);

		/*printf("\nPo sortowaniu\n");
		for (i = 0; i <= pozostalo_w_tablicy; i++) {
			printf("Znak %i ilosc %i\n", las[i]->numer_znaku, las[i]->ilosc);
		}*/
	}

	return *las;

}

void usun_drzewo(struct galaz* drzewo)
{
	if (drzewo == NULL)return;
	usun_drzewo(drzewo->potomek_prawy);
	usun_drzewo(drzewo->potomek_lewy);
	free(drzewo);
}



void wypisz_drzewo_rekurencyjnie(struct galaz* drzewo, FILE*plik)
{
	if (drzewo->potomek_prawy != NULL)wypisz_drzewo_rekurencyjnie(drzewo->potomek_prawy,plik);
	if (drzewo->potomek_lewy != NULL)wypisz_drzewo_rekurencyjnie(drzewo->potomek_lewy, plik);
	if((drzewo->potomek_prawy==NULL)||(drzewo->potomek_lewy==NULL))return;
	fprintf(plik,"%i %i %i\n",drzewo->numer_znaku,drzewo->potomek_prawy->numer_znaku,drzewo->potomek_lewy->numer_znaku);
}

void wypisz_drzewo(struct galaz* drzewo,char *nazwa)
{

	FILE* zapis_drzewa;
	zapis_drzewa = otworz_plik_wb(zmaina_rozszerzenia(nazwa, rozszerzenie_dla_drzewa));

	wypisz_drzewo_rekurencyjnie(drzewo, zapis_drzewa);

	fclose(zapis_drzewa);


}
