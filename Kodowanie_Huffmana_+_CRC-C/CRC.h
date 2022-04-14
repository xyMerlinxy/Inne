#pragma once
#include <stdio.h>

struct kontener_bufor;
int dlugosc_wiel_gen(unsigned int wielom);
int generowanie_masek(int ilosc, unsigned int** maski, unsigned int** mnozniki);
int odczyt_bitu(FILE* odczyt, struct kontener_bufor* kont);
void wyswietl_binarnie(int liczba, int dlugosc);
int CRC_funkcja(int wybor_spr_decyzja, char * nazwa);