#include <stdlib.h>
#include <stdio.h>
#include "struktury.h"
#include "obsluga_pliku.h"

#define rozszerzenie_dla_kodu "tabelaKodu"

void wypisz_element(struct galaz* drzewo, FILE* plik, short int dlugosc_slowa,unsigned int * wartosc_kodowa_znaku, struct tablica_slow** slowa, int * ilosc_zapisanych_slow) {
	if (drzewo->potomek_prawy == NULL) {
		//numer znaku, liczba kodowa, lie bitow z liczby kodowej
		fprintf(plik, "%i%c%u%c%i\n",drzewo->numer_znaku,9,*wartosc_kodowa_znaku,9,dlugosc_slowa);
		slowa[*ilosc_zapisanych_slow]->slowo_kodowe = *wartosc_kodowa_znaku;
		slowa[*ilosc_zapisanych_slow]->ilosc_bitow = dlugosc_slowa;
		//przypisanie typu int do typu short int, aczkolwiek w drzewie potrzebny mi by³ wiêkszy zakres aby oznaczaæ wêz³y
		//znaki i tak przyjmój¹ wartoœci 0-255 wiêc na short siê zmieszcz¹ bez problemu
		slowa[*ilosc_zapisanych_slow]->numer_znaku = drzewo->numer_znaku;
		(*ilosc_zapisanych_slow)++;
		return;
	}


	if(drzewo->potomek_prawy!=NULL) {
		//zrobienie miejsca w slowie na kolejny bit
		(*wartosc_kodowa_znaku) *= 2;
		(*wartosc_kodowa_znaku)++;
		
		wypisz_element(drzewo->potomek_prawy, plik, dlugosc_slowa+1, wartosc_kodowa_znaku, slowa, ilosc_zapisanych_slow);
		
		(*wartosc_kodowa_znaku) /= 2;
	}


	if (drzewo->potomek_lewy != NULL) {
		//zrobienie miejsca w slowie na kolejny bit
		(*wartosc_kodowa_znaku) *= 2;
		wypisz_element(drzewo->potomek_lewy, plik, dlugosc_slowa + 1, wartosc_kodowa_znaku, slowa, ilosc_zapisanych_slow);
		(*wartosc_kodowa_znaku) /= 2;

	}

}

//kod znaku jest zapisany na najm³odszych bitach liczby
void zapisz_tablcie_kodowa(struct galaz* drzewo, char* nazwa, struct tablica_slow** slowa) {
	unsigned int wartosc_kodowa_znaku=0;
	//short int dlugosc_slowa=0;
	FILE* zapis_kodu;
	int ilosc_zapisanych_slow=0;

	zapis_kodu = otworz_plik_wb(zmaina_rozszerzenia(nazwa, rozszerzenie_dla_kodu));

	//fprintf(zapis_kodu,"Nr znak, Slowo, ilosc bitow\n");
	wypisz_element(drzewo, zapis_kodu, 0, &wartosc_kodowa_znaku, slowa, &ilosc_zapisanych_slow);

	fclose(zapis_kodu);

}

struct tablica_slow** utworz_tablice_slow(int ilosc) {

	struct tablica_slow** glowny = calloc(ilosc,sizeof(struct tablica_slow*));
	if (glowny == NULL) {
		printf("Blad alokacji");
		exit(EXIT_FAILURE);
	}
	int i;
	for (i = 0; i < ilosc;i++) {
		glowny[i]=malloc(sizeof(struct tablica_slow));
		if (glowny[i] == NULL) {
			printf("Blad alokacji");
			exit(EXIT_FAILURE);
		}
	}

	return glowny;
}