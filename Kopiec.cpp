#include "Kopiec.hpp"

// metoda menu s³u¿y do obs³ugi struktury danych i pozwala na wybór czynnoœci wykonywanej
// na tej strukturze
//
// argumenty wejsciowe:
// rodzajCzynnosci - jest to parametr metody na podstawie którego okreœlane jest
//      			 czy metoda ma wyœwietlaæ wynik testu czasowego (gdy wartosc 1)
//                   czy strukture (gdy wartosc 2) 

int Kopiec::menu(int rodzajCzynnosci){
	int wybor;
	int element,wartosc;
	bool sprawdzeniePoprawnosci;
	long long int frequency, start, elapsed;
	do{
		cout << endl << "Wybierz operacje na strukturze." << endl;
		cout << "[1] dodaj element" << endl << "[2] usun element" << endl << "[3] wyszukaj element" << endl;
		cout << "[4] wyswietl strukture" << endl << "[9] cofnij"  << endl << "[111] zamknij" << endl << "Wybor opcji: ";
		cin >> wybor;
		cout << endl;
		switch(wybor){
		case 1:
			cout << endl << "Podaj wartosc dodawanego elementu: ";
			cin >> element;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			dodaj(element);
			elapsed = read_QPC() - start;
			if(rodzajCzynnosci==1){
				cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
			}else{
				this->wyswietl();
			}
		    break;
		case 2:
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			sprawdzeniePoprawnosci=usun();
			elapsed = read_QPC() - start;
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					this->wyswietl();
				}
			}else{
				cout << endl << "Kopiec jest pusty\n";
			}
			
		    break;
		case 3:
			cout << endl << "Podaj wartosc elementu wyszukiwanego: ";
			cin >> wartosc;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			sprawdzeniePoprawnosci=wyszukaj(wartosc);     
			elapsed = read_QPC() - start;  
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					cout << endl << "Znaleziono element o takiej wartosci." <<endl;
				}
			}else{
				cout << endl << "Nie znaleziono elementu o zadanej wielkosci." <<endl;
			}
		    break;
		case 4:
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

// metoda wyswietla kopiec przy wykorzystaniu metody printBT
void Kopiec::wyswietl(){ 
	string cr,cl,cp;
	cr = cl = cp = "  ";
  	cr[0] = 218; cr[1] = 196;
  	cl[0] = 192; cl[1] = 196;
  	cp[0] = 179;
	printBT(cr,cl,cp,"", "", 0);  
} 

// metoda sluzaca do rysowania drzewa bst 
// argumenty wejsciowe:
// cr, cl, cp, sp, sn - graficzne elementy ramki
// v - numer indeksu wyswietlanego elementu

void Kopiec::printBT(string cr,string cl,string cp,string sp, string sn, int v)
{
  string s;

  if(v < rozmiar)
  {
    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';  
    printBT(cr,cl,cp,s + cp, cr, 2 * v + 2);

    s = s.substr(0,sp.length()-2);

    cout << s << sn << kopiec[v] << endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    printBT(cr,cl,cp,s + cp, cl, 2 * v + 1);
  }
}

Kopiec::Kopiec(){
	rozmiar=0;
	kopiec = new int[rozmiar];
}

Kopiec::~Kopiec(){
	delete[] kopiec;
}

// metoda wyszukiwania w kopcu 
// ze wzgledu na wykorzystanie tablicy do implementacji kopca
// element o szukanej wartosci jest wyszukiwany poprzez przejscie przez tablice
// od poczatku do konca

bool Kopiec::wyszukaj(int wartosc){
	for(int i=0;i<rozmiar;i++){
		if(wartosc==kopiec[i]){
			return true;
		}	
	}
	return false;
} 

// metoda dodaj dodaje element o podanej jako 
// argument wartosci do kopca i porzadkuje kopiec
void Kopiec::dodaj(int wartosc){ 
	rozmiar++;
	int * tmp;
	int rodzic,pm,numer;
	tmp= new int[rozmiar];
	
	for(int i=0;i<rozmiar-1;i++){
		tmp[i]=kopiec[i];
	}
	
	tmp[rozmiar-1]=wartosc;
	
	delete []kopiec;
	kopiec=tmp;
	numer=rozmiar-1;
	while(numer>0){
		rodzic=floor((numer-1)/2);
		if(kopiec[rodzic]<kopiec[numer]){
			pm=kopiec[numer];
			kopiec[numer]=kopiec[rodzic];
			kopiec[rodzic]=pm;
		}else{
			break;
		}
		numer=rodzic;
	}
} 

// metoda usun usuwa korzen i odbudowuje kopiec

bool Kopiec::usun(){ 
	int * tmp;
	int pm,lewySyn,prawySyn,i=0;
	
	if(rozmiar==0){
		return false;
	}else{
		rozmiar--;
		
		tmp= new int[rozmiar];
		
		tmp[0]=kopiec[rozmiar];
		for(int i=1;i<rozmiar;i++){
			tmp[i]=kopiec[i];
		}
		
		delete []kopiec;
		kopiec=tmp;
		
		lewySyn=2*0+1;
		prawySyn=2*0+2;
		while(lewySyn<rozmiar||prawySyn<rozmiar){
			if(prawySyn<rozmiar){
				if(kopiec[i]<kopiec[lewySyn]||kopiec[i]<kopiec[prawySyn]){
				if(kopiec[prawySyn]>kopiec[lewySyn]){
					pm=kopiec[i];
					kopiec[i]=kopiec[prawySyn];
					kopiec[prawySyn]=pm;
					i=prawySyn;
					lewySyn=2*i+1;
					prawySyn=2*i+2;
				}else{
					pm=kopiec[i];
					kopiec[i]=kopiec[lewySyn];
					kopiec[lewySyn]=pm;	
					i=lewySyn;
					lewySyn=2*i+1;
					prawySyn=2*i+2;
				}
				}else{
					break;
				}
			}else{
				if(kopiec[i]<kopiec[lewySyn]){
					pm=kopiec[i];  
					kopiec[i]=kopiec[lewySyn];
					kopiec[lewySyn]=pm;	
					i=lewySyn;
					lewySyn=2*i+1;
				}else{
					break;
				}
			}
			
		}
		return true;
	}
} 

// metoda sluzaca do pomiaru czasu wykonania operacji

long long int Kopiec::read_QPC()
{
 LARGE_INTEGER count;
 DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
 QueryPerformanceCounter(&count);
 SetThreadAffinityMask(GetCurrentThread(), oldmask);
 return((long long int)count.QuadPart);  
} 
