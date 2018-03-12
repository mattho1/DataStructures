#ifndef KOPIEC_HH
#define KOPIEC_HH

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
  
using namespace std;   
    
class Kopiec{  
	private:
		
	int*kopiec;
	int rozmiar;
	
	
	private:
	long long int read_QPC();
	void printBT(string cr,string cl,string cp,string sp, string sn, int v);
	
	public:
	
	Kopiec();
	~Kopiec();
	
    void wyswietl();
    bool wyszukaj(int wartosc);
    void dodaj(int wartosc);
    bool usun();
    int menu(int rodzajCzynnosci);
};

#endif
