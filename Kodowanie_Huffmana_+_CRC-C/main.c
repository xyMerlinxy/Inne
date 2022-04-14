
#include <stdlib.h>
#include <stdio.h>
#include "tablica_ilosci.h"
#include "obsluga_pliku.h"
#include "drzewo.h"
#include "tablica_kodowa.h"
#include "kodowanie.h"

#include "dekom_drzewo.h"
#include "dekod.h"

#include "CRC.h"

//char nazwa[40] = "wynik/tekstCRC.txt";

void kodowanie(char * nazwa) {
	int wielkosc_tablicy = 0;
	struct element** tablica_znakow;

	int ilosc_znakow;
	tablica_znakow = utworz_tablice_czestotliwosci(nazwa, &wielkosc_tablicy, &ilosc_znakow);


	sortuj_tablice(tablica_znakow, wielkosc_tablicy, nazwa);

	struct galaz* drzewo;
	drzewo = utworz_drzewo(tablica_znakow, wielkosc_tablicy);
	wypisz_drzewo(drzewo, nazwa);

	struct tablica_slow** slowa;
	slowa = utworz_tablice_slow(wielkosc_tablicy);

	zapisz_tablcie_kodowa(drzewo, nazwa, slowa);

	zacznij_kodowanie(slowa, nazwa, wielkosc_tablicy, ilosc_znakow);

	usun_drzewo(drzewo);
	usun_tablice(&tablica_znakow, wielkosc_tablicy);

	printf("Poprawnie zakodowano plik\n");
	printf("Czy chesz usunac pliki pomocnicze?(T - tak, N - nie\n");
	char* napis;
	char tryb = getch();
	if (tryb == 'T' || tryb == 't'){
		napis = zmaina_rozszerzenia(nazwa, "drzewo");
		if (remove(napis)) {
			printf("Nie udało się usunąć pliku %s\n", napis);
		}
		else printf("Pomyślnie usunięto plik %s\n", napis);

		napis = zmaina_rozszerzenia(nazwa, "ileBajtow");
		if (remove(napis)) {
			printf("Nie udało się usunąć pliku %s\n", napis);
		}
		else printf("Pomyślnie usunięto plik %s\n", napis);

		napis = zmaina_rozszerzenia(nazwa, "model");
		if (remove(napis)) {
			printf("Nie udało się usunąć pliku %s\n", napis);
		}
		else printf("Pomyślnie usunięto plik %s\n", napis);

		napis = zmaina_rozszerzenia(nazwa, "modelSort");
		if (remove(napis)) {
			printf("Nie udało się usunąć pliku %s\n", napis);
		}
		else printf("Pomyślnie usunięto plik %s\n", napis);

		napis = zmaina_rozszerzenia(nazwa, "tabelaKodu");
		if (remove(napis)) {
			printf("Nie udało się usunąć pliku %s\n", napis);
		}
		else printf("Pomyślnie usunięto plik %s\n", napis);
		free(napis);
	}
}

void dekodowanie(char* nazwa) {
	FILE* odczyt = otworz_plik_rb(nazwa);

	int wielkosc_pliku;
	fread(&wielkosc_pliku, sizeof(int), 1, odczyt);

	struct galaz* drzewo;
	drzewo = dekom_utworz_drzewo(odczyt);


	zdekoduj_plik(odczyt, drzewo, wielkosc_pliku, nazwa);

	dekom_usun_drzewo(drzewo);
	drzewo = NULL;
	fclose(odczyt);
	printf("Poprawnie zdekodowano plik\n");
}

int main(int argc, char* argv[])
{

	char* nazwa;
	if (argc == 2){
		nazwa = argv[1];
	}
	else{
		printf("Zla liczba parametrow.  %d", argc);
		exit(EXIT_FAILURE);
	}

	
	printf("Co chcesz zrobic z plikiem(1 - kodowanie Huffmana, 2 - dekodowanie Huffmana, 3 - Obliczenie CRC, 4 - Sprawdzenie CRC, 0 - wyjscie?)\n");
	char tryb=getch();
	switch (tryb) {
		case '1': {
			kodowanie(nazwa);
			break;
		}
		case '2': {
			dekodowanie(nazwa);
			break;
		}
		case '3': {
			CRC_funkcja(0, nazwa);
			break;
		}
		case '4': {
			CRC_funkcja(1, nazwa);
			break;
		}


		case '0': {
			break;
		}
		default: {
			printf("Bledny znak");
			break;
		}
	}


	getch();
	getch();
	return (0);


}