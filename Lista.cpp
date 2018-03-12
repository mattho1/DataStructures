#include "Lista.hpp"

// metoda menu s³u¿y do obs³ugi struktury danych i pozwala na wybór czynnoœci wykonywanej
// na tej strukturze
//
// argumenty wejsciowe:
// rodzajCzynnosci - jest to parametr metody na podstawie którego okreœlane jest
//      			 czy metoda ma wyœwietlaæ wynik testu czasowego (gdy wartosc 1)
//                   czy strukture (gdy wartosc 2) 

int Lista::menu(int rodzajCzynnosci){
	int wybor;
	int element,wartosc,miejsce,pozycja;
	bool sprawdzeniePoprawnosci;
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
				wyswietl();
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
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			sprawdzeniePoprawnosci=dodajNaPozycji(miejsce,element);
			elapsed = read_QPC() - start;
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{	
				cout << endl << "Podana pozycja wykracza po za liste" << endl;
			}
		    break;
		case 4:
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			sprawdzeniePoprawnosci=usunZKonca();
			elapsed = read_QPC() - start;
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}	
			}else{
				cout << endl << "Lista jest pusta.\n";
			}
		    break;
		case 5:
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			sprawdzeniePoprawnosci=usunZPoczatku();
			elapsed = read_QPC() - start;
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{
				cout << endl << "Lista jest pusta.\n";	
			}
		    break;
		case 6:
			cout << endl << "Podaj miejsce z ktorego ma zostac usuniety element: ";
			cin >> miejsce;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			sprawdzeniePoprawnosci=usunZPozycji(miejsce);
			elapsed = read_QPC() - start;
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{
				cout << "Podana pozycja wykracza po za liste" << endl;	
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
			if(pozycja!=-1){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}
				cout << endl << "Element o podanej wartosci jest na pozycji: " << pozycja << endl;
			}else{
				cout << endl << "Nie znaleziono elementu o podanej wartosci." << endl;
			}
		    break;
		case 8:
			wyswietl();
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

Lista::Lista(){
	rozmiar=0;
	poczatek=NULL;
	koniec=NULL;
}

Lista::~Lista(){
	bool log;
	do{
		log=usunZKonca();
	}while(log);
}

void Lista::wyswietl(){
	
	if(rozmiar!=0){
		Element elemWyswietl;
		elemWyswietl=*poczatek;
		while(true){
			cout << elemWyswietl.wartosc << " ";
			if(elemWyswietl.nastepny==NULL){
				break;
			}
			elemWyswietl=*elemWyswietl.nastepny;
		}
		
	}
	cout << endl;
}



void Lista::dodajNaKoncu(int wartosc){
	Element* elem;
	elem=new Element();
	elem->wartosc=wartosc;
	elem->poprzedni=NULL;
	elem->nastepny=NULL;
	if(rozmiar==0){
		rozmiar++;
		poczatek=elem;
		koniec=elem;
	}else{
		rozmiar++;
		koniec->nastepny=elem;
		elem->poprzedni=koniec;
		koniec=elem;	
	}
}

void Lista::dodajNaPoczatku(int wartosc){
	Element* elem;	
	elem=new Element();
	elem->wartosc=wartosc;
	elem->poprzedni=NULL;
	elem->nastepny=NULL;
	if(rozmiar==0){
		rozmiar++;
		poczatek=elem;
		koniec=elem;
	}else{
		rozmiar++;
		poczatek->poprzedni=elem;
		elem->nastepny=poczatek;
		poczatek=elem;	
	}
}

bool Lista::usunZPoczatku(){
	if(rozmiar!=0){
		if(rozmiar==1){
			rozmiar--;
			delete poczatek;
			koniec=NULL;
			poczatek=NULL;
			return true;
		}
		rozmiar--;
		Element* tmp;
		poczatek->nastepny->poprzedni=NULL;
		tmp = poczatek->nastepny;
		delete poczatek;
		poczatek = tmp;
		return true;
	}else{
		return false;
	}
}

bool Lista::usunZKonca(){
	if(rozmiar!=0){
		if(rozmiar==1){
			rozmiar--;
			delete koniec;
			koniec=NULL;
			poczatek=NULL;
			return true;
		}
		rozmiar--;
		Element* tmp;
		koniec->poprzedni->nastepny=NULL;
		tmp=koniec->poprzedni;
		delete koniec;
		koniec=tmp;
		return true;
	}else{
		return false;
	}
}

bool Lista::usunZPozycji(int pozycja){ // rozpatrzyc przypadek usuwania z konca/poczatku
		if(pozycja>=0&&pozycja<rozmiar){
			if(pozycja==0){
				return usunZPoczatku();
			}
			if(pozycja==(rozmiar-1)){
				return usunZKonca();
			}
			if(pozycja < rozmiar/2){
				Element* przeszukiwany;
				przeszukiwany=poczatek;
				for(int i=0;i<rozmiar/2;i++){
					if(i==pozycja){
						przeszukiwany->poprzedni->nastepny=przeszukiwany->nastepny;
						przeszukiwany->nastepny->poprzedni=przeszukiwany->poprzedni;
						break;
					}
					przeszukiwany=przeszukiwany->nastepny;
				}
			}else{
				Element* przeszukiwany;
				przeszukiwany=koniec;
				for(int i=rozmiar-1;i>(rozmiar/2)-1;i--){
					if(i==pozycja){
						przeszukiwany->poprzedni->nastepny=przeszukiwany->nastepny;
						przeszukiwany->nastepny->poprzedni=przeszukiwany->poprzedni;
						break;
					}
					przeszukiwany=przeszukiwany->poprzedni;
				}	
			}
			rozmiar--;	
			return true;
		}else{
			return false;
		}		
}

bool Lista::dodajNaPozycji(int pozycja,int wartosc){// rozpatrzyc przypadek dodania na koncu/poczatku
		if(pozycja>=0&&pozycja<=rozmiar){
			if(pozycja==0){   
				dodajNaPoczatku(wartosc); 
				return true;
			}
			if(pozycja==rozmiar){
				dodajNaKoncu(wartosc);
				return true;
			}
			Element* elem;
			elem=new Element();
			elem->wartosc=wartosc;
			elem->poprzedni=NULL;
			elem->nastepny=NULL;   
			Element* przeszukiwany;   
			if(pozycja < rozmiar/2){ 
				przeszukiwany=poczatek;
				for(int i=0;i<rozmiar/2;i++){
				if(i==pozycja){
					przeszukiwany->poprzedni->nastepny=elem;
					elem->poprzedni=przeszukiwany->poprzedni;
					elem->nastepny=przeszukiwany;
					przeszukiwany->poprzedni=elem;
					break;
				}
				przeszukiwany=przeszukiwany->nastepny;
			}
			}else{
				przeszukiwany=koniec;
				for(int i=rozmiar-1;i>(rozmiar/2)-1;i--){
				if(i==pozycja){
					przeszukiwany->poprzedni->nastepny=elem;
					elem->poprzedni=przeszukiwany->poprzedni;
					elem->nastepny=przeszukiwany;
					przeszukiwany->poprzedni=elem;
					break;
				}
				przeszukiwany=przeszukiwany->poprzedni;
				}
			}
			
			rozmiar++;
			return true;
		}else{
			return false;
		}		
}

// m

int Lista::wyszukaj(int wartosc){
	int pozycja=-1;
	Element*elem;
	elem=poczatek;
	for(int i=0;elem->nastepny!=NULL;i++){
		if(elem->wartosc==wartosc){
			pozycja=i;
			break;
		}else{
			elem=elem->nastepny;
		}
	}
	return pozycja;
}

// metoda sluzaca do pomiaru czasu wykonania operacji

long long int Lista::read_QPC(){
	 LARGE_INTEGER count;
 	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
 	QueryPerformanceCounter(&count);
 	SetThreadAffinityMask(GetCurrentThread(), oldmask);
 	return((long long int)count.QuadPart); 
} 
