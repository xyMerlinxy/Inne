#pragma once

struct element {
	int numer_znaku;
	int ilosc_wystapien;
};


struct galaz {
	//ujemne wartoœci numeru oznaczaja numer wezla
	int numer_znaku;
	int ilosc;
	struct galaz *potomek_lewy;
	struct galaz *potomek_prawy;
	unsigned int slowo;
};

struct tablica_slow {
	unsigned int slowo_kodowe;
	unsigned char numer_znaku;
	short int ilosc_bitow;
	
};