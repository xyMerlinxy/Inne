#include <stdio.h>
#include "struktury.h"
#include <stdlib.h>
#include "obsluga_pliku.h"

#define roszerzenie_zakodowanego "Huffman"

int szukaj_w_slowach(struct tablica_slow** slowa, unsigned char znak, int ilosc_slow) {
	int i;
	for (i = 0; i < ilosc_slow; i++) {
		if (znak == slowa[i]->numer_znaku)return i;
	}

	printf("Nie znaleziono znaku podzczas kodowanie");
	exit(EXIT_FAILURE);

}

void zapisz_slowa(struct tablica_slow **slowa, FILE* plik,int ilosc) {

	int i;
	int j;
	int wielkosc_inta = sizeof(int) * 8;
	for (i = 0; i < ilosc; i++) {
		int zmodyfikowane_slowo_kodowe=slowa[i]->slowo_kodowe;
		for (j = slowa[i]->ilosc_bitow; j < wielkosc_inta; j++) {
			zmodyfikowane_slowo_kodowe *= 2;
		}
		fwrite(&(slowa[i]->numer_znaku), sizeof(char), 1, plik);
		fwrite(&zmodyfikowane_slowo_kodowe, sizeof(int), 1, plik);
	}
}


//czy koniec jeœli nie zero to koniec
void zapisz_znak(char * slowo_kodowe, FILE* zapis,char czy_koniec) {
	//TO DO (nie pilne) mo¿na to zrobiæ na kontenerze, a nei statikach
	static int ilosc_w_buforze=0;
	static unsigned char bufor=0;
		int i;
		for (i = 0; slowo_kodowe[i]; i++) {
			if (slowo_kodowe[i] == '1')bufor++;
			ilosc_w_buforze++;
			if (ilosc_w_buforze == 8) {
				fwrite(&bufor, sizeof(unsigned char), 1, zapis);
				//fflush(zapis);
				ilosc_w_buforze = 0;
				bufor = 0;
			}
			bufor *= 2;
		}
	if(czy_koniec) {
		int i;
		for (i = 0; i < 7 - ilosc_w_buforze; i++) {
			bufor *= 2;
		}
		fwrite(&bufor, sizeof(unsigned char), 1, zapis);
	}
}

void przejscie_na_stringi(struct tablica_slow** slowa, int ilosc_slow, char *** tablica) {
	*tablica = calloc(sizeof(char*), ilosc_slow);
	if (*tablica == NULL) {
		printf("Blad alokacji");
		exit(EXIT_FAILURE);
	}

	int i,j;
	for (i = 0; i < ilosc_slow; i++) {
		//dodajemu 1 aby znak koñca stringa siê zmieœci³
		(*tablica)[i] = calloc(sizeof(char), slowa[i]->ilosc_bitow +1);
		if ((*tablica)[i] == NULL) {
			printf("Blad alokacji");
			exit(EXIT_FAILURE);
		}

		(*tablica)[i][slowa[i]->ilosc_bitow] = 0;
		unsigned int temp = slowa[i]->slowo_kodowe;

		for (j = 0; j < slowa[i]->ilosc_bitow; j++) {
			if ((temp % 2) == 1) {
				(*tablica)[i][slowa[i]->ilosc_bitow - j - 1] = '1';
			}
			else (*tablica)[i][slowa[i]->ilosc_bitow - j - 1] = '0';
			temp /= 2;
		}
	}
}

void zacznij_kodowanie(struct tablica_slow** slowa, char* nazwa, int ilosc_slow, int ilosc_bajtow) {

	

	FILE* zapis,*odczyt;
	zapis=otworz_plik_wb(zmaina_rozszerzenia(nazwa, roszerzenie_zakodowanego));
	odczyt = otworz_plik_rb(nazwa);

	

	fwrite(&ilosc_bajtow,sizeof(int),1,zapis);
	fwrite(&ilosc_slow, sizeof(int),1, zapis);
	zapisz_slowa(slowa, zapis, ilosc_slow);


	unsigned char **tablica_stringow;
	przejscie_na_stringi(slowa, ilosc_slow, &tablica_stringow);

	int pole_w_tablicy;
	unsigned char znak = 0;

	////test
	//zapisz_znak("1100110011", zapis, 0);
	//zapisz_znak("11111111", zapis, 0);
	//zapisz_znak("01010101", zapis, 1);

	int i,j=0;
	for (i = 0; i < ilosc_bajtow;i++) {
		fread(&znak, 1, 1, odczyt);
		if (znak == EOF) return;
		pole_w_tablicy = szukaj_w_slowach(slowa, znak, ilosc_slow);
		zapisz_znak(tablica_stringow[pole_w_tablicy], zapis,0);
		//if (i % 1048576==0) {
		//	printf("%i\n",j);
		//	j++;
		//}
	}
	zapisz_znak("", zapis, 1);
	fclose(zapis);
	fclose(odczyt);

}