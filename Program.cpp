#include "Program.hpp"

// metoda menu odpowiada za pobranie danych z pliku, uzupelnienie struktur pobranymi danymi i 
// wybranie ktory rodzaj struktury chcemy uzyc

void Program::menu(){
	
	
	int wybor,wyborCzynnosci;
	this->pobierzDane();
	cout << endl << "[1] test czasowy" << endl << "[2] prezentacja" << endl << "Wybor opcji: ";
	cin >> wyborCzynnosci;
	cout << endl;
	
	for(int i=0;i<rozmiar;i++){
		tab.dodajNaKoncu(dane[i]);
	}
	for(int i=0;i<rozmiar;i++){
		kopiec.dodaj(dane[i]);
	}
	
	for(int i=0;i<rozmiar;i++){
		list.dodajNaKoncu(dane[i]);
	}
	
	for(int i=0;i<rozmiar;i++){
		bst.dodaj(dane[i]);
	}
	
		do{
			cout << "Wybierz strukture na ktorej maja byc wykonywane dzialania." << endl;
			cout << "[1] tablica" << endl << "[2] lista dwukierunkowa" << endl << "[3] kopiec" << endl << "[4] drzewo BST" << endl << endl << "[111]zakoncz"<< endl << "Wybor opcji: ";
			cin >> wybor;
			switch(wybor){
			case 1:
				wybor=tab.menu(wyborCzynnosci);
			    break;
			case 2:
				wybor=list.menu(wyborCzynnosci);
			    break;
			case 3:
				wybor=kopiec.menu(wyborCzynnosci);
			    break;
			case 4:
				wybor=bst.menu(wyborCzynnosci);
			    break;
			default:
			    if(wybor!=111){
				cout<< endl << "Podano niepoprawna opcje." << endl;
				wybor=0;
				}
			    break;
			}
		}while(wybor!=111);
		
}

// metoda pobierzDane sluzy do pobierania danych z pliku i umieszczania ich w tablicy dane
// Uwaga: nazwa pliku z danymi musi byc: Dane.txt

void Program::pobierzDane(){
	ifstream plik;
	plik.open( "Dane.txt" );
	if( plik.good() )
	{
    	plik >> rozmiar;
    	dane = new int[rozmiar];
    	for(int i=0;i<rozmiar;i++){
    		plik>>dane[i];
		}
	} else
	{
    	cout << endl << "Plik z danymi nie zostal poprawnie otwarty. Sprawdz czy nazwa pliku to 'Dane.txt' ";
		cout << "jezeli nie to zmien nazwe pliku i uruchom ponownie." << endl;
		cin >> rozmiar;
		exit( 0 );
	} 	
	plik.close(); 
}

void Program::wyswietl(){
	for(int i=0;i<rozmiar;i++){  
		cout << dane[i] << " ";
	}
}

Program::Program(){
	Tablica tab();
	Kopiec kopiec();
	Lista list();
	DrzewoBST bst();
} 

Program::~Program(){
	delete[] dane;
} 



