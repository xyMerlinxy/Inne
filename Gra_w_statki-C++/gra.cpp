#include "gra.h"
#include <iostream>

#include "plansza.h"

gra::gra(){
	std::cout << "Podaj ilość jednomasztowców:";
	ilosc_statkow[0]=uint_od_uzytkownika();

	std::cout<<"Podaj ilość dwyumasztowców:";
	ilosc_statkow[1]=uint_od_uzytkownika();

	std::cout<<"Podaj ilość trójmasztowców:";
	ilosc_statkow[2]=uint_od_uzytkownika();

	std::cout<<"Podaj ilość czteromasztowców:";
	ilosc_statkow[3]=uint_od_uzytkownika();

	std::cout<<"Podaj ilość pięciomasztowców:";
	ilosc_statkow[4]=uint_od_uzytkownika();

	tablica_P1=nullptr;
	tablica_P2=nullptr;
	tryb=-1;
}

int gra::uint_od_uzytkownika(){
	std::string napis;
	bool sprawdzanie;
	while(true) {
		std::cin >> napis;
		sprawdzanie=true;

		for(char c: napis){
			if(c<48||c>57){
				std::cout<<"Błędna liczba! Proszę wpisz poprawną: ";
				sprawdzanie=false;
				break;
			}
		}
		if(sprawdzanie)return std::stoi(napis);
	}
}

void gra::uzupelnij_plansze(){

	if(tryb==2){
		if(P1W.ustawienie_automatyczne(getIloscStatkow())
					||P2W.ustawienie_automatyczne(getIloscStatkow())){
			std::cout<<"Nie udało wygenerować się plansz dla graczy komputerowych"<<std::endl;
			exit(1);
		}

		return;
	}
	char czy_kont;
	std::cout << "GRACZ 1" << std::endl;

	while(true) {
		P1W.ustawianie_statkow(getIloscStatkow());
		std::cout<<"Czy chcesz ponownie rozstawić plansze(T - Tak, N - Nie?";
		std::cin>>czy_kont;
		if(czy_kont!='T'&&czy_kont!='t')break;
		P1W.clear();
	}

	//czyszczenie ekranu przed kolejnym graczem
	for(int i=0;i<40;i++){
		std::cout<<std::endl;
	}

	if(tryb==1){
		if(P2W.ustawienie_automatyczne(getIloscStatkow())){
			std::cout<<"Nie udało wygenerować się planszy dla gracza komputerowego"<<std::endl;
			exit(1);
		}
		//czyszczenie ekranu
		for(int i=0;i<40;i++)std::cout<<std::endl;
		return;
	}

	std::cout << "GRACZ 2" << std::endl;
	while(true) {
		P2W.ustawianie_statkow(getIloscStatkow());
		std::cout<<"Czy chcesz ponownie rozstawić plansze(T - Tak, N - Nie?";
		std::cin>>czy_kont;
		if(czy_kont!='T'&&czy_kont!='t')break;
		P2W.clear();
	}
	//czyszczenie ekranu
	for(int i=0;i<40;i++)std::cout<<std::endl;
}

const int *gra::getIloscStatkow() const {
	return ilosc_statkow;
}

void gra::wybor_trybu(){
	std::string napis;
	std::cout << "Wybierz tryb gry(0 - PvP, 1 - PvC, 2 CvC)" << std::endl;
	while(true) {
		std::cin>>napis;
		if(napis=="0"){
			tryb=0;
			break;
		}
		else if(napis=="1"){
			tryb=1;
			break;
		}
		else if(napis=="2"){
			tryb=2;
			break;
		}
		std::cout<<"Błędny znak!\n";
	}
}

void gra::graj(){
	std::string nic;

	//PvP
	if(tryb == 0){
		//zdaję sobie sprawę że program wykrywa jako pętlę nieskończoną,
		//ale warunki zakończenia są w metodzie ruch_gracza
		while(true){
			std::cout<<"Tura Gracza nr 1 (wpisz jakikolwiek znak)\n";
			std::cin>>nic;

			ruch_gracza(1);

			std::cout<<std::endl;
			std::cout<<"Tura Gracza nr 2 (wpisz jakikolwiek znak)\n";
			std::cin>>nic;

			ruch_gracza(2);
		}
	}

	//PvC
	if(tryb == 1){
		tablica_P2=new tablica;

		while(true){
			std::cout<<"Tura Gracza nr 1 (wpisz jakikolwiek znak)\n";
			std::cin>>nic; //czyszczenie bufora
			getchar();
			ruch_gracza(1);
			std::cout<<std::endl;

			std::cout<<"Tura Komputera nr 2(wpisz jakikolwiek znaki)\n";
			std::cin>>nic;
			ruch_komputera(2);
			std::cout<<std::endl;
		}
	}

	//CvC
	else {
		while (true) {
			tablica_P1 = new tablica;
			tablica_P2 = new tablica;
			std::cout << "Tura Komputera nr 1 (wpisz jakikolwiek znak)\n";
			std::cin>>nic;
			ruch_komputera(1);
			std::cout<<std::endl;
			std::cout << "Tura Komputera nr 2 (wpisz jakikolwiek znak)\n";
			std::cin>>nic;
			ruch_komputera(2);
		}
	}
}

void gra::ruch_gracza(int nr_gracza){
	plansza * P;
	if(nr_gracza==2)P=&P1W;
	else P=&P2W;
	P->wypisz_zakryte();
	while(true) {

		if (!P->strzel())break;
		else if(P->sprawdz_czy_wygrana()){
			P->wypisz_zakryte();
			if(nr_gracza==1){
				std::cout<<"GRACZ NR 1 WYGRAL!!!!!!!";
				exit(0);
			}
			else {
				std::cout<<"GRACZ NR 2 WYGRAL!!!!!!!";
				exit(0);
			}
		}
	}
}

void gra::ruch_komputera(int nr_gracza){
	plansza * P;
	tablica * T;
	std::list<int> * lista;
	if(nr_gracza==2){
		P=&P1W;
		T=tablica_P2;
		lista=&lista_P2;
	}
	else {
		P=&P2W;
		T=tablica_P1;
		lista=&lista_P1;
	}

	std::list<int>::iterator iter;
	int x, y;
	int wynik;
	int kordy;
	while(true) {

		if(lista->size()){
			iter=lista->begin();
			kordy=*iter;
			lista->erase(iter);
		}
		else kordy=T->daj_kordy();
		/*else{
			std::cout<<"Kord:";
			std::cin>>kordy;
		}*/

		x=kordy/30;
		y=kordy%30;
		wynik=P->strzel(x,y);

		if (wynik==1){
			P->wypisz_zakryte();
			break;
		}
		else if(wynik==2) {
			//P->wypisz_zakryte();
			lista->push_back(kordy + 1);
			lista->push_back(kordy - 1);
			lista->push_back(kordy + 30);
			lista->push_back(kordy - 30);
		}
		else if(wynik==3){
			lista->clear();
			//P->wypisz_zakryte();
			if(P->sprawdz_czy_wygrana()){
				if(nr_gracza==1){
					std::cout<<"GRACZ NR 1 WYGRAL!!!!!!!";
					exit(0);
				}
				else {
					std::cout<<"GRACZ NR 2 WYGRAL!!!!!!!";
					exit(0);
				}
			}
		}
	}
}
