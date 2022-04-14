#include <iostream>
#include <string>
#include "plansza.h"
#include <random>

plansza::plansza() {
	char znak='*';

	for (auto & i: tab) {
		for (auto & j : i) {
			j = znak;
		}
	}
}

void plansza::zam_wsp(std::string pole, int *x, int *y){

	//zbyt długa lub krótka nazwa pola(dwie cyfry, i max dwa pola znaków
	if((pole.length()>4)||(pole.length()<2)){
		*x = -1;
		*y = -1;
		return;
	}

	std::string znak, liczba;
	//pierwsza cyfra
	if(pole[0]>=48&&pole[0]<=57){
		//spr znak polski
		if((int)pole[pole.length()-2]<127&&(int)pole[pole.length()-2]>0){
			znak = pole.substr(pole.length()-1,1);
			liczba = pole.substr(0,pole.length()-1);
		}
		else{
			znak = pole.substr(pole.length()-2,2);
			liczba = pole.substr(0,pole.length()-2);
		}
	}
	//pierwszy znak
	else{
		//spr znak polski
		if((int)pole[0]<127&&(int)pole[0]>0){
			znak=pole.substr(0,1);
			liczba=pole.substr(1);
		}
		else{
			znak=pole.substr(0,2);
			liczba=pole.substr(2);
		}
	}
	//sprawdzenie poprawności wyciętych stringów
	if(znak.length()>2||znak.length()<1||liczba.length()>2||liczba.length()<1){
		*x = -1;
		*y = -1;
		return;
	}
	//sprawdzenie czy string liczba składa się tylko z cyfr
	for(char c : liczba){
		if(c<48||c>57){
			*x=-1;
			*y=-1;
			return;
		}
	}
	*x=std::stoi(liczba)-1;
	if(*x>29||*x<0){
		*x = -1;
		*y = -1;
		return;
	}

	if(znak=="A")*y=0;
	else if(znak=="Ą")*y= 1;
	else if(znak=="B")*y= 2;
	else if(znak=="C")*y= 3;
	else if(znak=="Ć")*y= 4;
	else if(znak=="D")*y= 5;
	else if(znak=="E")*y= 6;
	else if(znak=="Ę")*y= 7;
	else if(znak=="F")*y= 8;
	else if(znak=="G")*y= 9;
	else if(znak=="H")*y= 10;
	else if(znak=="I")*y= 11;
	else if(znak=="J")*y= 12;
	else if(znak=="K")*y= 13;
	else if(znak=="L")*y= 14;
	else if(znak=="Ł")*y= 15;
	else if(znak=="M")*y= 16;
	else if(znak=="N")*y= 17;
	else if(znak=="Ń")*y= 18;
	else if(znak=="O")*y= 19;
	else if(znak=="Ó")*y= 20;
	else if(znak=="P")*y= 21;
	else if(znak=="Q")*y= 22;
	else if(znak=="R")*y= 23;
	else if(znak=="S")*y= 24;
	else if(znak=="Ś")*y= 25;
	else if(znak=="T")*y= 26;
	else if(znak=="U")*y= 27;
	else if(znak=="V")*y= 28;
	else if(znak=="W")*y= 29;
	else {
		*x = -1;
		*y = -1;
		return;
	}
}

void plansza::clear(){
	for (auto & i: tab) {
		for (auto & j : i) {
			j = '*';
		}
	}
}

void plansza::wypisz(){
		std::cout<<"    ";
		char znak='A';

		for(int i=0;i<30;i++){
			switch (i){
				case 1: {
					std::cout<<"Ą ";
					break;}
				case 4: {
					std::cout<<"Ć ";
					break;}
				case 7: {
					std::cout<<"Ę ";
					break;}
				case 15: {
					std::cout<<"Ł ";
					break;}
				case 18: {
					std::cout<<"Ń ";
					break;}
				case 20: {
					std::cout<<"Ó ";
					break;}
				case 25: {
					std::cout<<"Ś ";
					break;}
				default:
					std::cout<<znak<<" ";
					znak++;
					break;
			}
		}
		std::cout<<std::endl;

		for (int i = 0; i < 30; i++) {
			if(i+1<10)std::cout<<"0";
			std::cout<<i+1<<"  ";
			for (int j = 0; j < 30; j++) {
				std::cout<<tab[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
	}

void plansza::wypisz_zakryte(){
	std::cout<<"    ";
	char znak='A';

	for(int i=0;i<30;i++){
		switch (i){
			case 1: {
				std::cout<<"Ą ";
				break;}
			case 4: {
				std::cout<<"Ć ";
				break;}
			case 7: {
				std::cout<<"Ę ";
				break;}
			case 15: {
				std::cout<<"Ł ";
				break;}
			case 18: {
				std::cout<<"Ń ";
				break;}
			case 20: {
				std::cout<<"Ó ";
				break;}
			case 25: {
				std::cout<<"Ś ";
				break;}
			default:
				std::cout<<znak<<" ";
				znak++;
				break;
		}
	}
	std::cout<<std::endl;

	for (int i = 0; i < 30; i++) {
		if(i+1<10)std::cout<<"0";
		std::cout<<i+1<<"  ";
		for (int j = 0; j < 30; j++) {
			if((tab[i][j]>=48)&&(tab[i][j]<=57)){
				std::cout<<"*";
				}
			else std::cout<<tab[i][j];
			std::cout<<" ";
		}
		std::cout<<std::endl;
	}
}

void plansza::ustawianie_statkow(const int *tabela){
	char tryb, tryb2;

	std::cout<<"Czy chesz ręcznie ustawić statki(T-tak, N-nie?"<<std::endl;
	while(true){
		std::cin>>tryb;
		if(tryb=='n'||tryb=='N'||tryb=='t'||tryb=='T')break;
		std::cout<<"Błędny znak"<<std::endl;
	}
	//wybranie trybu ręcznego
	if (tryb=='t'||tryb=='T'){
		(ustawianie_reczne(tabela));
	}
	//ustawienie automatyczne
	else {
		while(true) {
			if (!ustawienie_automatyczne(tabela)){
				wypisz();
				return;    //czy się powiodło
			}
			else{
				clear();
				std::cout << std::endl << "Nie udało się wygenerować planszy!" << std::endl;
				std::cout<< "Czy chcesz spróbować ponownie wygenerować plansze?(T - ponowna próba generowania, N - ręczne rozstawienie"<< std::endl;

				while (true) {
					std::cin >> tryb2;
					if (tryb2 == 'n' || tryb2 == 'N' || tryb2 == 't' || tryb2 == 'T') {
						break;
					}
					std::cout << "Błędny znak" << std::endl;
				}

				if (tryb2 == 'n' || tryb2 == 'N') {
					ustawianie_reczne(tabela);
					return;
				}
			}
		}
	}
}

//zwraca true gdy nie uda się wygenerować
bool plansza::ustawienie_automatyczne(const int *tabela){

	//ustawienie generatorów pseudolosowych
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<> rand_liczba(0, 29);
	std::bernoulli_distribution rand_bool(0.5);

	int licznik, ograniczenie_licznika, wielokrotnosc=20;
	/*jeśli licznik przekroczy wartość ograniczenia to program uznaje że nie da się
	wygenerować planszy. Ograniczenie bedzie równe 20 krotności ilości statków danego typu
	*/

	//Ustawianie pięciomasztowców
	licznik=0;
	ograniczenie_licznika=tabela[4]*wielokrotnosc;
	for(int i=0;i<tabela[4];licznik++){
		if(licznik>=ograniczenie_licznika)return true;
		if(wstaw(rand_liczba(gen) ,rand_liczba(gen) ,rand_bool(gen),5))i++;
	}
	//Ustawianie czteromasztowców
	licznik=0;
	ograniczenie_licznika=tabela[3]*wielokrotnosc;
	for(int i=0;i<tabela[3];licznik++){
		if(licznik>=ograniczenie_licznika)return true;
		if(wstaw(rand_liczba(gen) ,rand_liczba(gen) ,rand_bool(gen),4))i++;
	}
	//Ustawianie trójmasztowców
	licznik=0;
	ograniczenie_licznika=tabela[2]*wielokrotnosc;
	for(int i=0;i<tabela[2];licznik++){
		if(licznik>=ograniczenie_licznika)return true;
		if(wstaw(rand_liczba(gen) ,rand_liczba(gen) ,rand_bool(gen),3))i++;
	}
	//Ustawianie dwumasztowców
	licznik=0;
	ograniczenie_licznika=tabela[1]*wielokrotnosc;
	for(int i=0;i<tabela[1];licznik++){
		if(licznik>=ograniczenie_licznika)return true;
		if(wstaw(rand_liczba(gen) ,rand_liczba(gen) ,rand_bool(gen),2))i++;
	}
	//Ustawianie jednoszatowców
	licznik=0;
	ograniczenie_licznika=tabela[0]*wielokrotnosc;
	for(int i=0;i<tabela[0];licznik++){
		if(licznik>=ograniczenie_licznika)return true;
		if(wstaw(rand_liczba(gen) ,rand_liczba(gen) ,true,1))i++;
	}

	return false;
}

bool plansza::wstaw_recznie(int wielkosc){
	int x, y;
	char kierunek;
	std::string pole;
	//true pion, false_poziom
	bool b_kierunek=true;

	//jednomasztowce zawsze w pionie
	if(wielkosc>1){
		std::cout << "Pion czy poziom(_ - poziom, I - pion?";
		while(true) {
			std::cin >> kierunek;
			if(kierunek=='_'||kierunek=='I')break;
			std::cout<<"Błędny znak"<<std::endl;
		}
		if(kierunek=='I')b_kierunek=true;
		else b_kierunek=false;
	}
	std::cout<<"Podaj pozycje: ";
	std::cin>>pole;
	zam_wsp(pole,&x,&y);
	if(wstaw(x ,y ,b_kierunek,wielkosc))return true;
	return false;
}

void plansza::ustawianie_reczne(const int *tabela){
	wypisz();

	if(tabela[0])std::cout<<"Ustawianie jednoszatowców"<<std::endl;
	for(int i=0;i<tabela[0];){
		if(wstaw_recznie(1)){
			i++;
			wypisz();
		}
		else std::cout<<"Niepoprawne pole!"<<std::endl;
	}
	if(tabela[1])std::cout<<"Ustawianie dwumasztowców"<<std::endl;
	for(int i=0;i<tabela[1];){
		if(wstaw_recznie(2)){
			i++;
			wypisz();
		}
		else std::cout<<"Niepoprawne pole!"<<std::endl;
	}
	if(tabela[2])std::cout<<"Ustawianie trójmasztowców"<<std::endl;
	for(int i=0;i<tabela[2];){
		if(wstaw_recznie(3)){
			i++;
			wypisz();
		}
		else std::cout<<"Niepoprawne pole!"<<std::endl;
	}
	if(tabela[3])std::cout<<"Ustawianie czteromasztowców"<<std::endl;
	for(int i=0;i<tabela[3];){
		if(wstaw_recznie(4)){
			i++;
			wypisz();
		}
		else std::cout<<"Niepoprawne pole!"<<std::endl;
	}
	if(tabela[4])std::cout<<"Ustawianie pięciomasztowców"<<std::endl;
	for(int i=0;i<tabela[4];){
		if(wstaw_recznie(5)){
			i++;
			wypisz();
		}
		else std::cout<<"Niepoprawne pole!"<<std::endl;
	}
}

//zwraca 1 jeśli się powiodło //kierunek true - pion
int plansza::wstaw(int x, int y,bool kierunek, int wielkosc){

	if(x>29||y>29||x<0||y<0)return 0;
	if(kierunek&&(x+wielkosc-1>29))return 0;    //pion
	if(!kierunek&&(y+wielkosc-1>29))return 0;    //poziom

	//pion
	if(kierunek) {
		//sprawdzenie środka
		for (int i = x - 1; i <= x + wielkosc; i++) {
			if (sprawdz_pole(i, y))return 0;
		}
		//sprawdzenie lewej strony
		for(int i=x;i<x+wielkosc;i++){
			if(sprawdz_pole(i,y-1))return 0;
		}
		//sprawdzenie prawej strony
		for(int i=x;i<x+wielkosc;i++){
			if(sprawdz_pole(i,y+1))return 0;
		}
		//wstawianie
		for (int i = x; i < x + wielkosc; i++) {
			tab[i][y]=char(wielkosc+48);
		}
		return 1;
	}
	//poziom
	else {
		//sprawdzenie środka
		for (int i = y - 1; i <= y + wielkosc; i++) {
			if (sprawdz_pole(x, i))return 0;
		}
		//sprawdzenie góry strony
		for(int i=y;i<y+wielkosc;i++){
			if(sprawdz_pole(x-1,i))return 0;
		}
		//sprawdzenie dół strony
		for(int i=y;i<y+wielkosc;i++){
			if(sprawdz_pole(x+1,i))return 0;
		}
		//wstawianie
		for (int i = y; i < y + wielkosc; i++) {
			tab[x][i]=char(wielkosc+48);
		}
		return 1;
	}
}

//1 jeśli zajęte
int plansza::sprawdz_pole(int x,int y){

	if(x>29||y>29||x<0||y<0)return 0; //poza planszą
	if(tab[x][y]>='1'&&tab[x][y]<='5')return 1;
	else return 0;
}

void plansza::podmien(int x, int y, char znak){
	tab[x][y]=znak;
}

bool plansza::strzel(){
	int x, y;
	std::string pole;
	std::cout<<"Podaj pozycje ostrzału: ";
	while(true){
		std::cin>>pole;
		zam_wsp(pole,&x,&y);
		//piersze dwa warunki - sprawdzeni czy dobre kordy, pozostałe dwa czy już nie wstrzelone
		if((x!=-1&&y!=-1)&&(tab[x][y]!='-'&&tab[x][y]!='X'))break;
		std::cout<<"Niepoprawne pole";
	}
	int wynik=strzel(x,y);
	wypisz_zakryte();
	if(wynik==2){
		std::cout<<"Trafiono wrogi statek!\n";
		return true;
	}
	else if(wynik==3){
		std::cout<<"Zatopiono wrogi statek!\n";
		return true;
	}
	else {
		std::cout<<"Pudło!\n";
		return false;
	}
}

//0 - złe, 1 - puste pole, 2 - trafienie, 3 - zatopienie
int plansza::strzel(int x, int y){

	if(tab[x][y]=='-'||tab[x][y]=='X')return 0;

	if(tab[x][y]=='*'){
		tab[x][y]='-';
		return 1;
	}
	else {
		tab[x][y]='X';
		//spr czy zatopiony, aby odkryć wszystkie pola wokół
		bool nie_zatop=false;
		int i;
		for(i=x+1;i<30;i++){    //sprawdzam w dół
			if(tab[i][y]>48&&tab[i][y]<54){
				nie_zatop=true;
				break;
			}
			else if(tab[i][y]=='*'||tab[i][y]=='-')break;
		}
		if(!nie_zatop){
			for(i=x-1;i>=0;i--){    //sprawdzam w górę
				if(tab[i][y]>48&&tab[i][y]<54){
					nie_zatop=true;
					break;
				}
				else if(tab[i][y]=='*'||tab[i][y]=='-')break;
			}
		}

		if(!nie_zatop){
			for(i=y-1;i>=0;i--){    //sprawdzam lewo
				if(tab[x][i]>48&&tab[x][i]<54){
					nie_zatop=true;
					break;
				}
				else if(tab[x][i]=='*'||tab[x][i]=='-')break;
			}
		}
		if(!nie_zatop){
			for(i=y+1;i<30;i++){    //sprawdzam prawo
				if(tab[x][i]>48&&tab[x][i]<54){
					nie_zatop=true;
					break;
				}
				else if(tab[x][i]=='*'||tab[x][i]=='-')break;
			}
		}

		if(nie_zatop)return 2;
		else{//odkrycie miejsc
			for(i=x+1;i<30;i++){    //sprawdzam w dół
				if(tab[i][y]=='X'){
					tab[i][y+1]='-';
					tab[i][y-1]='-';
				}
				else {
					tab[i][y]='-';
					break;
				}
			}
			for(i=x-1;i>=0;i--){    //sprawdzam w górę
				if(tab[i][y]=='X'){
					tab[i][y+1]='-';
					tab[i][y-1]='-';
				}
				else {
					tab[i][y]='-';
					break;
				}
			}

			for(i=y-1;i>=0;i--){    //sprawdzam lewo
				if(tab[x][i]=='X'){
					tab[x+1][i]='-';
					tab[x-1][i]='-';
				}
				else {
					tab[x][i]='-';
					break;
				}
			}
			for(i=y+1;i<30;i++) {    //sprawdzam prawo
				if (tab[x][i] == 'X') {
					tab[x + 1][i] = '-';
					tab[x - 1][i] = '-';
				}
				else {
					tab[x][i]='-';
					break;
				}
			}
			return 3;
		}
	}
}

bool plansza::sprawdz_czy_wygrana(){
	for (auto & i: tab) {
		for (auto & j : i) {
			if((j>=48)&&(j<=57))return false;
		}
	}
	return true;
}

bool plansza::czy_trafione(int x, int y){
	if(tab[x][y]=='X'||tab[x][y]=='-')return true;
	return false;
}