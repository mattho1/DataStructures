#ifndef LISTA_HH
#define LISTA_HH

#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Element{
	int wartosc;
	Element * nastepny;
	Element * poprzedni;
	//int numer_na_liscie; // bez tego bo da sie to wyliczyc a tylko robi klopoty
}; 
       
class Lista{
	private:   
		
	Element* poczatek;
	Element* koniec;
	int rozmiar;
	
	private:
	long long int read_QPC();
	
	public:
	
	Lista();
	~Lista();
	
	//void ustawRozmiar(int rozm);
	int zwrocRozmiar();
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
