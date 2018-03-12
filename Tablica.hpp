#ifndef TABLICA_HH
#define TABLICA_HH

#include <iostream> 
#include <windows.h>  
#include <iomanip>
 
using namespace std; 
      
class Tablica{
	private:
		
	int*tab;
	int rozmiar;
	
	private:
	long long int read_QPC();
	
	public:
	
	Tablica();
	~Tablica();
	
    void wyswietl();
    int wyszukaj(int wartosc);
    void dodajNaKoncu(int wartosc);
    void dodajNaPoczatku(int wartosc);
    bool dodajNaPozycji(int pozycja, int wartosc);
    bool usunZPozycji(int pozycja);
    bool usunZKonca();
    bool usunZPoczatku();
    int menu(int rodzajCzynnosci);
};

#endif
