#pragma once
#include <stdio.h>

void wpisz_dwie_wartosci(struct galaz** drzewo, unsigned char znak, int slowo, unsigned char znak2, int slowo2);
void wpisz_do_drzewa(struct galaz** drzewo, unsigned char znak, int slowo);
struct galaz* dekom_utworz_drzewo(FILE* odczyt);
void dekom_usun_drzewo(struct galaz* drzewo);