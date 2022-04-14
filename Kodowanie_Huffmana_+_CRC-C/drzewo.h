#pragma once
#include "struktury.h"


struct galaz* utworz_drzewo(struct element** tablica_znakow, int ilosc);
void usun_drzewo(struct galaz* drzewo);
void wypisz_drzewo(struct galaz* drzewo, char* nazwa);