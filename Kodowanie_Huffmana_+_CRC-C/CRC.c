#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "obsluga_pliku.h"

struct kontener_bufor {
	int ilosc_w_buf;
	unsigned  char buffor;

};

int dlugosc_wiel_gen(unsigned int wielom) {
	int dlug;
	for (dlug = 0; wielom != 0;dlug++) {
		wielom /= 2;
	}
	if (dlug == 0) {
		printf("Niepoprawny wielomian!!");
		exit(1);
	}
	return dlug;
}

//zwraca ilosc wygenerowanych masek
int generowanie_masek(int ilosc, unsigned int ** maski, unsigned int ** mnozniki) {
	
	(*maski) = calloc(ilosc, sizeof(unsigned int));
	(*mnozniki) = calloc(ilosc, sizeof(unsigned int));
	if (*maski == NULL || *mnozniki == NULL) {
		printf("Blad alokacji 1");
		getch();
		exit(1);
	}


	int i;
	for (i = 0; i <ilosc; i++) {
		(*mnozniki)[i] = (int)pow(2, (ilosc - i - 1) * 8);
		(*maski)[i] = (*mnozniki)[i] * 0xff;
	}



	return ilosc;
}

int odczyt_bitu(FILE* odczyt, struct kontener_bufor* kont) {
	if (kont->ilosc_w_buf == 0) {
		if (!(fread(&(kont->buffor), 1, 1, odczyt)))return -1;;
		kont->ilosc_w_buf = 8;

		//printf("%x\t", kont->buffor);
	}
	
	int zwracana = kont->buffor /128;
	kont->buffor *= 2;
	kont->ilosc_w_buf--;
	return zwracana;
}

void wyswietl_binarnie(int liczba, int dlugosc) {
	int i;
	for (i = 0; i < 32-dlugosc; i++) {
		//if (liczba / 0x80000000)break;
		liczba *= 2;
	}
	int j;
	for (j = 0; j < 32 - i; j++) {
		if (liczba / 0x80000000)printf("1");
		else printf("0");
		liczba *= 2;
	}

}



int CRC_funkcja(int wybor_spr_decyzja, char * nazwa)
{
	
	//wielomian generujący domyślny
	//unsigned int wielomian = 0x4C11DB7;
	unsigned int wielomian = 0xB71DC104;
	//unsigned int wielomian =0x0DB88320;
	//unsigned int wielomian =0x00c;
	int dlugosc_wielomianu = dlugosc_wiel_gen(wielomian);


	//Wypisanie wielomianu

	unsigned int* maski = NULL;
	unsigned int *mnozniki;
	int ilosc_masek = (dlugosc_wielomianu - 1) / 8 + 1;
	generowanie_masek(ilosc_masek, &maski, &mnozniki);
		
	int i;
	for (i = 0; i < ilosc_masek;i++) {
		int do_wypisania = wielomian & maski[ilosc_masek - i - 1];
		printf("Wartosc %d. bajtu wielomianu to: %02x\n", i, do_wypisania/mnozniki[ilosc_masek-i-1]);
	}

	//printf("Czy chesz sprawdzic integralnosc pliku CRC?(T - tak, N - nie)");
	//char wybor_spr_decyzja = getch();
	//if (wybor_spr_decyzja == 'T' || wybor_spr_decyzja == 't')wybor_spr_decyzja = 1;
	//else wybor_spr_decyzja = 0;
	//jak zero to nie sprawdzamy poprawności

	//char nazwa[100];
	//printf("\nPodaj nazwe pliku: ");
	//scanf("%s", nazwa);

	//jeśli sprawdzamy to sprawdzam czy plik kontrolny istnieje


	FILE* odczyt=otworz_plik_rb(nazwa);
	if (!odczyt) {
		printf("Plik %s nie istnieje", nazwa);
		exit(1);
	}
	
	if (wybor_spr_decyzja) {
		if (spr_czy_istnieje_plik(dodanie_przedrostka(nazwa, "CRC"))) {
			printf("Plik do sprawdzenia nie istnieje\n");
			exit(1);
		}
	}

	struct kontener_bufor kont;
	kont.buffor = 0;
	kont.ilosc_w_buf = 0;

	
	unsigned int CRC=0;
	int bit=0;


	//wczytanie o jeden mniej do CRC bitów niż ma wielomian
	for (i = 0; i < dlugosc_wielomianu; i++) {
		if ((bit = odczyt_bitu(odczyt,&kont)) == -1) {
			break;
		}
		CRC *= 2;
		CRC += bit;
	}


	unsigned int maska_pierwszy_bit = pow(2, dlugosc_wielomianu-1);
	int temp=0;
	if (bit == -1) temp = -1;


	//liczneie CRC
	if (bit != -1) {
		while ((bit = odczyt_bitu(odczyt, &kont)) != -1) {//jesli odzczyt bitu się powiedzie
			

			CRC *= 2;
			CRC += bit;

			/*wyswietl_binarnie(CRC,dlugosc_wielomianu);
			printf("\n");
			wyswietl_binarnie(wielomian, dlugosc_wielomianu);
			printf("\n\n");*/

			if (CRC & maska_pierwszy_bit) {
						CRC = CRC ^ wielomian;
			}
		}
	}

	int licznik = 0;
	fclose(odczyt);


	//dopisywanie dodatkowych zer na końcu
	for (i = 0; i < dlugosc_wielomianu-1;i++) {
		licznik++;
		CRC *= 2;

		if (CRC & maska_pierwszy_bit) {
			CRC = CRC ^ wielomian;
		}
	}

	//przesunięcie wielomianu do lewej strony na bitach
	for (i = 0; i <= (ilosc_masek * 8) - dlugosc_wielomianu ; i++) {
		CRC *= 2;
	}

	if (!wybor_spr_decyzja) {
		FILE* zapis_crc = otworz_plik_wb(zmaina_rozszerzenia(nazwa, "crc"));
		fwrite(&CRC, sizeof(unsigned int), 1, zapis_crc);

		fclose(zapis_crc);
		printf("\nZapisano wartosc CRC do pliku %s\n", zmaina_rozszerzenia(nazwa, "crc"));
	}
	
	printf("Wynik CRC: ");
	wyswietl_binarnie(CRC, dlugosc_wielomianu);
	printf("\n%x\n", CRC);

	//przerobienie CRC na postać do zapisu


	if (!wybor_spr_decyzja) {
		FILE* odczyt_koncowy = otworz_plik_rb(nazwa);
		FILE* zapis_koncowy = otworz_plik_wb(dodanie_przedrostka(nazwa, "CRC"));

		char znak = 0;
		while (fread(&znak, 1, 1, odczyt_koncowy)) {
			fwrite(&znak, 1, 1, zapis_koncowy);
		}

		unsigned char do_zapisania;
		for (i = 0; i < ilosc_masek; i++) {

			do_zapisania = (char)((CRC & maski[i]) / mnozniki[i]);
			fwrite(&do_zapisania, 1, 1, zapis_koncowy);
		}

		fclose(odczyt_koncowy);
		fclose(zapis_koncowy);
	}
	else {
		

		FILE* plik = otworz_plik_rb(dodanie_przedrostka(nazwa, "CRC"));
		unsigned char CRC_z_pliku[10];
		fseek(plik, -ilosc_masek, SEEK_END);
		fread(&CRC_z_pliku, sizeof(char), ilosc_masek, plik);
		fclose(plik);
		unsigned int CRC_odwrocone = 0;
		int i;
		for (i = 0; i < ilosc_masek; i++) {
			CRC_odwrocone *= 256;
			CRC_odwrocone += CRC_z_pliku[i];
		}


		if (CRC == CRC_odwrocone) {
			printf("Pliki nie zostal naruszony\n");
		}
		else printf("Plik zostal zmodyfikowany!!!");
	}

	return 0;

}