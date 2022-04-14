#include "tablica.h"
#include <random>
#include <iostream>

tablica::tablica() {
	for(short i=0;i<900;i++)tab[i]=i;

	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<> rand_liczba(0, 29);

	int losowa;
	short temp;
	for(short & i: tab){
		losowa=rand_liczba(gen);
		temp=i;
		i=tab[losowa];
		tab[losowa]=temp;
	}
	for(short & i: tab){
		losowa=rand_liczba(gen);
		temp=i;
		i=tab[losowa];
		tab[losowa]=temp;
	}
	for(short & i: tab){
		losowa=rand_liczba(gen);
		temp=i;
		i=tab[losowa];
		tab[losowa]=temp;
	}
}

int tablica::daj_kordy(){

	indeks++;
	if(indeks>899){
		std::cout<<"Błąd odzytu z tabeli";
		exit(1);
	}
	return tab[indeks];
}