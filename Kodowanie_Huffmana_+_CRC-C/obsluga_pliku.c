#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* otworz_plik_rb(char* nazwa) {
	FILE* temp;
	temp = fopen(nazwa, "rb");

	if (temp==NULL) {
		printf("Nie mozna utworzyc pliku: %s", nazwa);
		exit(EXIT_FAILURE);
	}
	return temp;
}

//zwraca 1 gdy nie istnieje
int spr_czy_istnieje_plik(char* nazwa) {
	FILE* plik = fopen(nazwa, "r");
	if (plik == NULL)return 1;
	fclose(plik);
	return 0;
}


FILE* otworz_plik_wb(char* nazwa) {
	FILE* temp;
	temp = fopen(nazwa, "wb");

	if (temp == NULL) {
		printf("Nie mozna utworzyc pliku: %s",nazwa);

		exit(EXIT_FAILURE);
	}
	return temp;
}

int dlugosc_pliku(FILE* plik) {
	fpos_t pozycja;
	fgetpos(plik,&pozycja);
	fseek(plik, 0, SEEK_END);
	fpos_t dlugosc;
	fgetpos(plik, &dlugosc);
	fsetpos(plik, &pozycja);
	return (dlugosc);
}


char * zmaina_rozszerzenia(char*nazwa,char* rozszerzenie) {
	//char** nowa_nazwa = malloc(sizeof(char*));
	int dlugosc_do_alokacji= strlen(nazwa) + strlen(rozszerzenie) + 1;
	char* nowa_nazwa=NULL;
	do {
		nowa_nazwa = malloc(dlugosc_do_alokacji); //na zapas alokujemy pamiêæ równ¹ sumie d³ugoœci nazwy, roszerzenia i kropki miêdzy nimi
	} while (nowa_nazwa == NULL);
	
	int i;
	for (i = 0; i < dlugosc_do_alokacji; i++) {
		nowa_nazwa[i] = '\0';
	}



	int miejsce_kropki=0;

	for (i = strlen(nazwa); i >= 0; i--) {
		if (nazwa[i] == '.') {
			miejsce_kropki = i;
			break;
		}
	}
	if (i == -1)miejsce_kropki = strlen(nazwa);


	strncpy(nowa_nazwa, nazwa, miejsce_kropki);
	strcat(nowa_nazwa, ".");
	strcat(nowa_nazwa, rozszerzenie);
	
	int temp_dlugosc = strlen(nowa_nazwa)+1;

	//poniewa¿ zminiejszam rozmiar tablicy to nie muszê sie martwiæ wyciekiem pamiêci
	nowa_nazwa = realloc(nowa_nazwa, temp_dlugosc);



	return nowa_nazwa;
}





char* dodanie_przedrostka(char* stara_nazwa, char* przedrostek) {
	int dlugosc_do_alokacji = strlen(stara_nazwa) + strlen(przedrostek);
	char* nowa_nazwa = NULL;
	do {
		nowa_nazwa = calloc(dlugosc_do_alokacji,sizeof(char)); // alokujemy pamiêæ równ¹ sumie d³ugoœci nazwy i przedrostka
	} while (nowa_nazwa == NULL);

	strcat(nowa_nazwa, przedrostek);
	strcat(nowa_nazwa, stara_nazwa);
	return nowa_nazwa;
}