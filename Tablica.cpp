#include "Tablica.hpp"

// metoda menu s³u¿y do obs³ugi struktury danych i pozwala na wybór czynnoœci wykonywanej
// na tej strukturze
//
// argumenty wejsciowe:
// rodzajCzynnosci - jest to parametr metody na podstawie którego okreœlane jest
//      			 czy metoda ma wyœwietlaæ wynik testu czasowego (gdy wartosc 1)
//                   czy strukture (gdy wartosc 2) 

int Tablica::menu(int rodzajCzynnosci){
	int wybor;
	int element,wartosc,miejsce,pozycja;
	bool kontrolaPoprawnosci;
	long long int frequency, start, elapsed;
	
	do{
		cout << endl << "Wybierz operacje na strukturze." << endl;
		cout << "[1] dodaj element na koniec" << endl << "[2] dodaj element na poczatek" << endl << "[3] dodaj element we wskazane miejsce" << endl;
		cout << "[4] usun element z konca" << endl << "[5] usun element z poczatku" << endl << "[6] usun element z podanego miejsca" << endl;
		cout << "[7] wyszukaj elementu" << endl << "[8] wyswietl strukture" << endl << "[9] cofnij" << endl << "[111] zamknij" << endl << "Wybor opcji: ";
		cin >> wybor;
		cout << endl;
		switch(wybor){
		case 1:
			cout << endl << "Podaj wartosc dodawanego elementu: ";
			cin >> element;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
			start = read_QPC();
			dodajNaKoncu(element);
			elapsed = read_QPC() - start;
			if(rodzajCzynnosci==1){
				cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
			}else{
				this->wyswietl();
			}
		    break;
		case 2:
			cout << endl << "Podaj wartosc dodawanego elementu: ";
			cin >> element;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			dodajNaPoczatku(element);
			elapsed = read_QPC() - start;
			if(rodzajCzynnosci==1){
				cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
			}else{
				wyswietl();
			}
		    break;
		case 3:
			cout << endl << "Podaj wartosc dodawanego elementu: ";
			cin >> element;
			cout << endl << "Podaj miejsce na ktorym ma zostac dodany element: ";
			cin >> miejsce;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			kontrolaPoprawnosci=dodajNaPozycji(miejsce,element);
			elapsed = read_QPC() - start;
			if(kontrolaPoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{
				cout << endl << "Podane miejsce jest niepoprawne. \n";		
			}
		    break;
		case 4:
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
			start = read_QPC();
			kontrolaPoprawnosci=usunZKonca();
			elapsed = read_QPC() - start;
			if(kontrolaPoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{
				cout << endl << "Tablica jest pusta. \n";	
			}
		    break;
		case 5:
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			kontrolaPoprawnosci=usunZPoczatku();
			elapsed = read_QPC() - start;
			if(kontrolaPoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{
				cout << endl << "Tablica jest pusta. \n";	
			}
		    break;
		case 6:
			cout << endl << "Podaj miejsce z ktorego ma zostac usuniety element: ";
			cin >> miejsce;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			kontrolaPoprawnosci=usunZPozycji(miejsce);
			elapsed = read_QPC() - start;
			if(kontrolaPoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{
				cout << endl << "Podane miejsce jest niepoprawne. \n";		
			}	
		    break;
		case 7:
			cout << endl << "Podaj wartosc elementu wyszukiwanego: ";
			cin >> wartosc;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			pozycja=wyszukaj(wartosc);
			elapsed = read_QPC() - start;
			if(pozycja==-1){
				cout<<endl<<"Nie znaleziono wartosci w tablicy\n";
			}else{
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}
				cout<<endl<<"Podana wartosc jest na pozycji: " << pozycja << endl;
			}
		    break;
		case 8:
			this->wyswietl();
		    break;
		default:
			if(wybor!=9&&wybor!=111){
				cout<< endl << "Podano niepoprawna opcje." << endl;
			}
		    break;
		}
		cout << endl << endl;
	}while(wybor!=9&&wybor!=111);
	return wybor;
}

void Tablica::wyswietl(){ 
  for(int i=0;i<rozmiar;i++){
    cout << tab[i] << " ";
  }
} 

Tablica::Tablica(){
	rozmiar=0;
	tab = new int[rozmiar];
}

Tablica::~Tablica(){
	delete [] tab;
}

// metoda wyszukaj zwraca indeks tablicy pod ktorym znajduje sie szukana wartosc

int Tablica::wyszukaj(int wartosc){
	for(int i=0;i<rozmiar;i++){
		if(tab[i]==wartosc){
			return i;
		}
	}
	return -1;
}

// metoda dodaje do tablicy element o wartosci podanej jako drugi argument 
// metoda zwraca wartosc logiczna:
// true - gdy poprawnie doda³a
// false - gdy podany numer pozycji wykracza poza rozmiar tablicy 
// uwaga: dodawanie na poczatek jest mozliwe podajac indeks tablicy numer 0
//		  dodawanie na koniec gdy podana pozycja jest rown rozmairowi tablicy

bool Tablica::dodajNaPozycji(int pozycja, int wartosc){
		if(pozycja<0||pozycja>rozmiar){
			return false;
		}else{
			rozmiar++;
			int*tmp= new int[rozmiar];
			for(int i=0;i<pozycja;i++){
					tmp[i]=tab[i];
			}
			tmp[pozycja]=wartosc;
			for(int i=pozycja+1;i<rozmiar;i++){
					tmp[i]=tab[i-1];	
			}
			delete [] tab;
			tab=tmp;
			return true;
		}
}

// metoda usuwa z element z podanej pozycji w tablicy
// metoda zwraca wartosc logiczna:
// true - gdy element zostal poprawnie usuniety
// false - gdy podany numer pozycji wykracza poza rozmiar tablicy 
// uwaga: usuwanie z poczatku jest mozliwe podajac indeks tablicy numer 0
//		  usuwanie z konca gdy podana pozycja jest rown rozmairowi tablicy

bool Tablica::usunZPozycji(int pozycja){
	if(pozycja<0||pozycja>rozmiar){
		return false;
	}else{
		int*tmp= new int[rozmiar-1];
		for(int i=0;i<pozycja;i++){
			tmp[i]=tab[i];
		}
		for(int i=pozycja+1;i<rozmiar;i++){
			tmp[i-1]=tab[i];	
		}
		rozmiar--;
		delete [] tab;
		tab=tmp;
		return true;
	}
}

// metoda usuwa z element z konca tablicy
// metoda zwraca wartosc logiczna:
// true - gdy element zostal poprawnie usuniety
// false - gdy tablica jest pusta

bool Tablica::usunZKonca(){
	if(rozmiar<=0){
		return false;	
	}else{
		int*tmp= new int[rozmiar-1];
		for(int i=0;i<rozmiar-1;i++){
				tmp[i]=tab[i];
		}
		rozmiar--;
		delete [] tab;
		tab=tmp;
		return true;
	}
	
}

// metoda usuwa z element z poczatku tablicy
// metoda zwraca wartosc logiczna:
// true - gdy element zostal poprawnie usuniety
// false - gdy tablica jest pusta

bool Tablica::usunZPoczatku(){
	if(rozmiar<=0){
		return false;	
	}else{
		int*tmp= new int[rozmiar-1];
		for(int i=0;i<rozmiar-1;i++){
				tmp[i]=tab[i+1];
		}
		rozmiar--;
		delete [] tab;
		tab=tmp;
		return true;
	}
}

// metoda dodaje element na koncu tablicy

void Tablica::dodajNaKoncu(int wartosc){
	int*tmp= new int[rozmiar+1];
	for(int i=0;i<rozmiar;i++){
			tmp[i]=tab[i];
	}  
	tmp[rozmiar]=wartosc;     
	rozmiar++;
	delete [] tab;   
	tab=tmp;
} 

// metoda dodaje element na poczatku tablicy

void Tablica::dodajNaPoczatku(int wartosc){
	int*tmp= new int[rozmiar+1];
	for(int i=0;i<rozmiar;i++){
			tmp[i+1]=tab[i];
	}
	tmp[0]=wartosc;
	delete [] tab;
	tab=tmp;
	rozmiar++;
}

// metoda sluzaca do pomiaru czasu wykonania operacji

long long int Tablica::read_QPC()
{
 LARGE_INTEGER count;
 DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
 QueryPerformanceCounter(&count);
 SetThreadAffinityMask(GetCurrentThread(), oldmask);
 return((long long int)count.QuadPart); 
} 







