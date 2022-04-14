#ifndef UNTITLED_GRA_H
#define UNTITLED_GRA_H

#include "plansza.h"
#include "tablica.h"
#include <list>

class gra {
int ilosc_statkow[5]{};
plansza P1W = plansza();   //plansza ze statkami gracza 1
plansza P2W = plansza();


std::list<int> lista_P1;
std::list<int> lista_P2;

//wskaźniki aby ich odrazu nie inicjalizować
tablica * tablica_P1, *  tablica_P2;

//tryb 0 - PvP, 1 - PvC, 2 CvC
int tryb;

	static int uint_od_uzytkownika();
	void ruch_gracza(int nr_gracza);
	void ruch_komputera(int nr_gracza);

public:
	gra();
	void uzupelnij_plansze();
	const int *getIloscStatkow() const;
	void wybor_trybu();
	void graj();

};


#endif //UNTITLED_GRA_H
