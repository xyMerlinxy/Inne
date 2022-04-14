#pragma once

#include <stdio.h>

int spr_czy_istnieje_plik(char* nazwa);
FILE* otworz_plik_rb(char* nazwa);
FILE* otworz_plik_wb(char* nazwa);
int dlugosc_pliku(FILE* plik);
char* zmaina_rozszerzenia(char* stara_nazwa,char *roszerzenie);
char* dodanie_przedrostka(char* stara_nazwa, char* przedrostek);
