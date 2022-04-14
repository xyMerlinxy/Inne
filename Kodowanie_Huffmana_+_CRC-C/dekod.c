#include "struktury.h"
#include "dekom_drzewo.h"
#include <stdio.h>
#include "obsluga_pliku.h"

char podaj_znak(FILE *odczyt) {
	static char bufor[8];
	static char numer_bufora=0;
	if (numer_bufora > 0) {
		numer_bufora--;
		return bufor[numer_bufora];
	}
	unsigned char znak;
	fread(&znak, 1, 1, odczyt);

	int i;
	for (i = 0; i < 8; i++) {
		bufor[i] = znak % 2;
		znak /= 2;
	}
	numer_bufora = 7;
	return bufor[numer_bufora];
}

void zdekoduj_znak(FILE* zapis, FILE* odczyt, struct galaz* drzewo) {
	if ((drzewo->potomek_lewy == NULL) && (drzewo->potomek_prawy == NULL)) {
		fwrite(&(drzewo->numer_znaku), 1, 1, zapis);
		//fflush(zapis);
		return;
	}

	int temp = podaj_znak(odczyt);
	if (temp == 0)zdekoduj_znak(zapis, odczyt, drzewo->potomek_lewy);
	if (temp == 1)zdekoduj_znak(zapis, odczyt, drzewo->potomek_prawy);

}


void zdekoduj_plik(FILE* odczyt, struct galaz* drzewo, int ilosc_znakow, char * nazwa) {

	printf("otwarcie zapisu pliku: %s\n",nazwa);
	printf("otwarcie zapisu pliku: %s\n", zmaina_rozszerzenia(nazwa, "recovery"));

	FILE* zapis = otworz_plik_wb(zmaina_rozszerzenia(nazwa, "recovery"));


	int i,j=0;

	for (i = 0; i < ilosc_znakow; i++) {
		zdekoduj_znak(zapis, odczyt, drzewo);
		//printf("%i", podaj_znak(odczyt));
	/*	if (i % 1048576 == 0) {
			printf("%i\n", j);
			j++;
		}*/

	}


}