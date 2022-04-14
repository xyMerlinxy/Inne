#pragma once
#include "struktury.h"

struct element** utworz_tablice_czestotliwosci(char*,int*,int * ilosc_bajtow);

int warunek(const void* pierwsza,const void *druga);
void sortuj_tablice(struct element** tablica_znakow, int ilosc_elementow,char* nazwa);
void usun_tablice(struct element*** tablica_znakow, int wielkosc_tablicy);