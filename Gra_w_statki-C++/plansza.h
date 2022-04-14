#ifndef UNTITLED_PLANSZA_H
#define UNTITLED_PLANSZA_H

#include <iostream>
#include <string>

class plansza{
	char tab[30][30]{};

	static void zam_wsp(std::string wsp,int *x,int *y);
	void ustawianie_reczne(const int *tabela);
	int wstaw(int x, int y, bool kierunek, int wielkosc);
	int sprawdz_pole(int x,int y);
	bool wstaw_recznie(int wielkosc);

public:

	plansza();

	bool ustawienie_automatyczne(const int *tabela);
	void clear();
	void wypisz();
	void wypisz_zakryte();
	void ustawianie_statkow(const int * tabela);
	//true jesli trafi
	bool strzel();
	//0 - złe, 1 - puste pole, 2 - trafienie, 3 - zatopienie
	int strzel(int x, int y);
	bool czy_trafione(int x, int y);
	//true jeśli wygrana
	bool sprawdz_czy_wygrana();
	void podmien(int x, int y, char znak);
};

#endif //UNTITLED_PLANSZA_H
