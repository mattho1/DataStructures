#ifndef DRZEWOBST_HH
#define DRZEWOBST_HH

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Wezel{
	int wartosc;
	Wezel * lewySyn;
	Wezel * prawySyn;
	Wezel * rodzic;
};

class DrzewoBST{
	private:
		
	Wezel* korzen;  
	int rozmiar;
	        
	
	private: 
	long long int read_QPC();
	int calkowitylog2(int potega);
	
	public:
	Wezel * znajdzNastepnik(Wezel * p);
	DrzewoBST();
	~DrzewoBST();
	
	bool  rotacjaWLewo(int wartosc);
	bool  rotacjaWPrawo(int wartosc);
	void rownowazDrzewo();
	void printBT(string cr,string cl,string cp,string sp, string sn, Wezel* v);
    void wyswietl();
    Wezel* wyszukaj(int wartosc);
    void dodaj(int wartosc);
    bool usun(int wartosc);
    void usunDrzewo();
    int menu(int rodzajCzynnosci);
};

#endif
