#ifndef PROGRAM_HH
#define PROGRAM_HH

#include "Tablica.hpp"
#include "Kopiec.hpp" 
#include "Lista.hpp"
#include "DrzewoBST.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime> 
#include <random> 


using namespace std; 

class Program{
	private:
	
	int* dane; // dane pobrane z pliku
	Tablica tab;
	Kopiec kopiec; 
	Lista list;
	DrzewoBST bst;
	int rozmiar;
	// tutaj dodac kolejne struktury

	public:
	
	Program();
	~Program();
	void menu();
	void pobierzDane();
	void wyswietl();
};

#endif
