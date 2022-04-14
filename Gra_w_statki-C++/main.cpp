#include <iostream>
#include "plansza.h"
#include "gra.h"
/*
Adres pola można wprowadzać A1 lub 1A
Oznaczenia: * - pole zakryte, - - puste pole, X - pole trafione
1,2,3,4,5 - statek

Automatyczne generowanie plansz z większą ilością statków może kończyć się niepowodzeniem
Powyżej ustawienia ilości 20,20,20,20,20 automatyczne generowanie często kończy się niepowodzeniem
 */

int main() {
	std::cout<<"Witam w grze w statki\n";
	std::cout<<"Oznaczenia:\n* - pole zakryte, - - puste pole, X - pole trafione\n"<<"1,2,3,4,5 - statek\n";
	std::cout<<"Proszę wybrać liczności poszczególnych statków:\n";
	gra test;
	test.wybor_trybu();
	test.uzupelnij_plansze();
	test.graj();

	return 0;
}
