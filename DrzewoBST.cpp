#include "DrzewoBST.hpp"


// metoda menu s³u¿y do obs³ugi struktury danych i pozwala na wybór czynnoœci wykonywanej
// na tej strukturze
//
// argumenty wejsciowe:
// rodzajCzynnosci - jest to parametr metody na podstawie którego okreœlane jest
//      			 czy metoda ma wyœwietlaæ wynik testu czasowego (gdy wartosc 1)
//                   czy strukture (gdy wartosc 2) 


int DrzewoBST::menu(int rodzajCzynnosci){
	int wybor;
	int element,wartosc,wyborKierunkuRotacji;
	bool sprawdzeniePoprawnosci;
	Wezel* tmp;
	long long int frequency, start, elapsed;
	do{
		cout << endl << "Wybierz operacje na strukturze." << endl;
		cout << "[1] dodaj element" << endl << "[2] usun element" << endl << "[3] wyszukaj element" << endl;
		cout << "[4] wyswietl strukture" << endl << "[5] rotacja" << endl << "[6] rownowazenie drzewa" << endl << "[9] cofnij"  << endl << "[111] zamknij" << endl << "Wybor opcji: ";
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
			cout << endl << "Podaj wartosc elementu ktory chcesz usunac: ";
			cin >> element;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			sprawdzeniePoprawnosci=usun(element);
			elapsed = read_QPC() - start;
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [us] = " << setprecision(3) << (1000000.0 * elapsed) / frequency << endl; 	
				}else{
					wyswietl();
				}
			}else{
				cout << endl << "Drzewo jest puste lub nie ma elementu o wartosic ktora podales\n";
			}
		    break;
		case 3:
			cout << endl << "Podaj wartosc elementu wyszukiwanego: ";
			cin >> wartosc;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			start = read_QPC();
			tmp=wyszukaj(wartosc);
			elapsed = read_QPC() - start;
			if(tmp!=NULL){
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
			this->wyswietl();
		    break; 
		case 5:
			cout << endl << "Podaj wartosc elementu ktory chcesz rotowac: ";
			cin >> wartosc;
			cout << endl << "Wybierz rodzaj rotacji:" << endl << "[1] W lewo " << endl << "[2] W prawo" << endl;
			cin >> wyborKierunkuRotacji;
			cout << endl;
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency); 
			if(wyborKierunkuRotacji==1){
				start = read_QPC();
				sprawdzeniePoprawnosci=this->rotacjaWLewo(wartosc);
				elapsed = read_QPC() - start;
			}else if(wyborKierunkuRotacji==2){
				start = read_QPC();
				sprawdzeniePoprawnosci=this->rotacjaWPrawo(wartosc);
				elapsed = read_QPC() - start;
			}else{
				cout << endl << "Zle wybrana rotacja." << endl;
			}
			
			if(sprawdzeniePoprawnosci){
				if(rodzajCzynnosci==1){
					cout << "Czas [ms] = " << setprecision(3) << (1000.0 * elapsed) / frequency << endl; 	
				}else{
					this->wyswietl();
				}
			}else{
				cout << endl << "Nie mozna wykonac rotacji." <<endl;
			}
		    break;
		case 6:   
			rownowazDrzewo();  
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

DrzewoBST::DrzewoBST(){
	korzen=NULL;
	rozmiar=0;
}

DrzewoBST::~DrzewoBST(){
	bool log;
	do{
		log=usun(korzen->wartosc);
	}while(log);
}


// metoda sluzaca do rownowazenia drzewa bst za pomoca algorytmu DSW 

void DrzewoBST::rownowazDrzewo(){
	Wezel*tmp=korzen;
	int licznik=0,liczbaObrotow,pom;
	if(rozmiar>1){
		while(tmp){
			if(tmp->lewySyn!=NULL){
				rotacjaWPrawo(tmp->wartosc);
				tmp=tmp->rodzic;
			}else{
				licznik++;
				tmp=tmp->prawySyn;
			}		
		}
		
		tmp=korzen;
		
		liczbaObrotow=licznik - (pow(2, calkowitylog2(licznik + 1)) - 1 );
	
		for(int i=0;i<liczbaObrotow;i++){
			rotacjaWLewo(tmp->wartosc);
			if(tmp->rodzic->prawySyn){
				tmp=tmp->rodzic->prawySyn;
			}else{
				break;
			}
		}
			
		licznik=licznik-liczbaObrotow;
		
		while(licznik > 1){
	  	  licznik = licznik/2;                      
	  	  tmp = korzen;                     
	    	for(int i = 0; i < licznik; i++){
	  	   		rotacjaWLewo(tmp->wartosc);
	  	   		if(tmp->rodzic->prawySyn){
	  	    		tmp = tmp->rodzic->prawySyn;
				}else{
					break;
				}  
	  	 	}
	 	}		
	}
}

// metoda prywatna sluzaca do obliczania logarytmu calkowitego przy podstawie z dwoch
// wykorzystywana w metodzie rownowazacej drzewo

int DrzewoBST::calkowitylog2(int wynik){
	int logarytm=1,licznik=0;
	while(logarytm<wynik){
		licznik++;
		logarytm=2*logarytm;
	}
	licznik--;
	return licznik;
}

// metoda wykorzystywana do rotacji wybranego wezla
// wezel wybieramy podajac jego wartosc 
// metoda zwraca wartosc logiczna
// false - gdy nie moze dokonac rotacji poniewaz podana wartosc nie istnieje w drzewie
//		   albo nie ma prawego syna niezbednego przy rotacji w lewo
// true - gdy dokona rotacji 

bool  DrzewoBST::rotacjaWLewo(int wartosc){
	Wezel*znalezionyElement=wyszukaj(wartosc);
	if(znalezionyElement==NULL){
		return false;
	}else{
		if(znalezionyElement->prawySyn!=NULL){
		znalezionyElement->prawySyn->rodzic=znalezionyElement->rodzic;
		if(znalezionyElement!=korzen){
			if(znalezionyElement->rodzic->prawySyn==znalezionyElement){
				znalezionyElement->rodzic->prawySyn=znalezionyElement->prawySyn;
			}else{
				znalezionyElement->rodzic->lewySyn=znalezionyElement->prawySyn;
			}
		}else{
			korzen=znalezionyElement->prawySyn;
		}	
		znalezionyElement->rodzic=znalezionyElement->prawySyn;
		if(znalezionyElement->prawySyn->lewySyn!=NULL){
			znalezionyElement->prawySyn->lewySyn->rodzic=znalezionyElement;
			znalezionyElement->prawySyn=znalezionyElement->prawySyn->lewySyn;
		}else{
			znalezionyElement->prawySyn=NULL;
		}
		znalezionyElement->rodzic->lewySyn=znalezionyElement;
		}else{
			return false;
		}	
	}
	return true;
}

// metoda wykorzystywana do rotacji wybranego wezla
// wezel wybieramy podajac jego wartosc 
// metoda zwraca wartosc logiczna
// false - gdy nie moze dokonac rotacji poniewaz podana wartosc nie istnieje w drzewie
//		   albo nie ma lewego syna niezbednego przy rotacji w prawo
// true - gdy dokona rotacji 

bool  DrzewoBST::rotacjaWPrawo(int wartosc){
	Wezel*znalezionyElement=wyszukaj(wartosc);
	if(znalezionyElement==NULL){
		return false;
	}else{
		if(znalezionyElement->lewySyn!=NULL){
		znalezionyElement->lewySyn->rodzic=znalezionyElement->rodzic;
		if(znalezionyElement!=korzen){
			if(znalezionyElement->rodzic->prawySyn==znalezionyElement){
				znalezionyElement->rodzic->prawySyn=znalezionyElement->lewySyn;
			}else{
				znalezionyElement->rodzic->lewySyn=znalezionyElement->lewySyn;
			}
		}else{
			korzen=znalezionyElement->lewySyn;
		}	
		znalezionyElement->rodzic=znalezionyElement->lewySyn;
		if(znalezionyElement->lewySyn->prawySyn!=NULL){
			znalezionyElement->lewySyn->prawySyn->rodzic=znalezionyElement;
			znalezionyElement->lewySyn=znalezionyElement->lewySyn->prawySyn;
		}else{
			znalezionyElement->lewySyn=NULL;
		}
		znalezionyElement->rodzic->prawySyn=znalezionyElement;
		}else{
			return false;
		}	
	}
	return true;
}

// metoda wyswietla drzewo BST przy wykorzystaniu metody printBT

void DrzewoBST::wyswietl(){
	string cr,cl,cp;
	cr = cl = cp = "  ";
  	cr[0] = 218; cr[1] = 196;
  	cl[0] = 192; cl[1] = 196;
  	cp[0] = 179;
  	if(rozmiar!=0){
  		printBT(cr,cl,cp,"", "", korzen);
	}	
} 

// metoda sluzaca do rysowania drzewa bst 
// argumenty wejsciowe:
// cr, cl, cp, sp, sn - graficzne elementy ramki
// v - wezel ktorego wartosc zostanie wyswietlona

void DrzewoBST::printBT(string cr,string cl,string cp,string sp, string sn, Wezel * v)
{
  string s;	
  if(v){
    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';
    printBT(cr,cl,cp,s + cp, cr, v->prawySyn);

    s = s.substr(0,sp.length()-2);
    cout << s << sn << v->wartosc << endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    printBT(cr,cl,cp,s + cp, cl, v->lewySyn);
  } 
}

// metoda wyszukaj sluzy do wyszukiwania elementu
// metoda wyszukuje element struktury, ktorego wartosc jest rowna wartosci argumentu wejsciowego
// metoda zwraca wskaznik na znaleziony wezel
// uwaga: gdy jest wiecej elementow o takiej samej wartosci metoda zwroci najblizszy korzeniowi 

Wezel* DrzewoBST::wyszukaj(int wartosc){ 
	Wezel* tmp;
	tmp=korzen;
	while(tmp!=NULL){
		if(tmp->wartosc==wartosc){
			return tmp;
		}else{
			if(tmp->wartosc<wartosc){
				tmp=tmp->prawySyn;
			}else{
				tmp=tmp->lewySyn;
			}	
		}
	}	
	return tmp;
}

void  DrzewoBST::dodaj(int wartosc){
	if(rozmiar==0){
		Wezel* nowy;
		nowy=new Wezel();
		nowy->wartosc=wartosc;
		nowy->lewySyn=NULL;
		nowy->prawySyn=NULL;
		nowy->rodzic=NULL;
		korzen=nowy;
		rozmiar++;
	}else{
		Wezel* tmp,* nowy;
		nowy=new Wezel();
		tmp=korzen;
		do{
			if(tmp->wartosc<=wartosc){
				if(tmp->prawySyn==NULL){
					nowy->wartosc=wartosc;
					nowy->rodzic=tmp;
					tmp->prawySyn=nowy;
					nowy->prawySyn=NULL;
					nowy->lewySyn=NULL;
					rozmiar++;
					break;
				}else{
					tmp=tmp->prawySyn;
				}
			}else{
				if(tmp->lewySyn==NULL){
					nowy->wartosc=wartosc;
					nowy->rodzic=tmp;
					tmp->lewySyn=nowy;
					nowy->prawySyn=NULL;
					nowy->lewySyn=NULL;
					rozmiar++;
					break;
				}else{
					tmp=tmp->lewySyn;
				}
			}
		}while(tmp!=NULL); //zawsze ma byc true
	}
}

// metoda znajduje nastepnik elementu podanego jako argument
// metoda zwraca wskaznik na znaleziony element

Wezel * DrzewoBST::znajdzNastepnik(Wezel * szukany){
  Wezel * tmp;

  if(szukany!=NULL){
    if(szukany->prawySyn!=NULL){
    	tmp=szukany->prawySyn;
    	if(tmp!=NULL){
    		while(tmp->lewySyn!=NULL){
    			tmp = tmp->lewySyn;
			} 
		}
  		return tmp;	
	}else{
      tmp = szukany->rodzic;
      while((tmp!=NULL) && (szukany == tmp->prawySyn)){
        szukany = tmp;
        tmp = tmp->rodzic;
      }
      return tmp;
    }
  }
  return szukany;
}

// metoda sluzy do usuwania wezla z drzewa
// metoda zwraca wartosc logiczna
// true - gdy usunie wezel
// false - gdy nie usunie lub drzewo jest puste

bool  DrzewoBST::usun(int wartosc){
	Wezel* tmp;
	Wezel*znalezionyElement=wyszukaj(wartosc);
	if(znalezionyElement==NULL){
		return false;
	}else{
		if(rozmiar==1){
		rozmiar--;
		delete korzen;
		return false;
		}else{
			if(znalezionyElement->prawySyn==NULL&&znalezionyElement->lewySyn==NULL){
					if(znalezionyElement->wartosc>=znalezionyElement->rodzic->wartosc){ 
						znalezionyElement->rodzic->prawySyn=NULL;
						delete znalezionyElement;
					}else{
						znalezionyElement->rodzic->lewySyn=NULL;
						delete znalezionyElement;
					}
				rozmiar--;
				return true;	
			}else{
				if(znalezionyElement->prawySyn!=NULL&&znalezionyElement->lewySyn!=NULL){
					tmp=znajdzNastepnik(znalezionyElement);
					if(znalezionyElement->prawySyn!=tmp&&znalezionyElement->lewySyn!=tmp){
						if(tmp->prawySyn!=NULL){
							tmp->prawySyn->rodzic=tmp->rodzic;
							if(tmp->rodzic->prawySyn==tmp){
								tmp->rodzic->prawySyn=tmp->prawySyn;
							}else{
								tmp->rodzic->lewySyn=tmp->prawySyn;
							}	
						}else{
								if(tmp->rodzic->prawySyn==tmp){
									tmp->rodzic->prawySyn=NULL;
								}else{
									tmp->rodzic->lewySyn=NULL;
								}
								
						}
					}			
					if(znalezionyElement!=korzen){
						if(znalezionyElement->rodzic->prawySyn==znalezionyElement){
							znalezionyElement->rodzic->prawySyn=tmp;
							tmp->rodzic=znalezionyElement->rodzic;
						}else{
							znalezionyElement->rodzic->lewySyn=tmp;
							tmp->rodzic=znalezionyElement->rodzic;	
						}	
					}else{
						tmp->rodzic=NULL;
						korzen=tmp;
					}
					
					if(znalezionyElement->lewySyn!=tmp){
						tmp->lewySyn=znalezionyElement->lewySyn;
						znalezionyElement->lewySyn->rodzic=tmp;
					}
					if(znalezionyElement->prawySyn!=tmp){
						tmp->prawySyn=znalezionyElement->prawySyn;
						znalezionyElement->prawySyn->rodzic=tmp;
					}
					delete znalezionyElement;
					rozmiar--;	
					return true;
				}else{
					if(znalezionyElement!=korzen){
					if(znalezionyElement->wartosc>=znalezionyElement->rodzic->wartosc){
						if(znalezionyElement->prawySyn==NULL){
							znalezionyElement->rodzic->prawySyn=znalezionyElement->lewySyn;
							znalezionyElement->lewySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}else{
							znalezionyElement->rodzic->prawySyn=znalezionyElement->prawySyn;
							znalezionyElement->prawySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}	
					}else{
						if(znalezionyElement->prawySyn==NULL){
							znalezionyElement->rodzic->lewySyn=znalezionyElement->lewySyn;
							znalezionyElement->lewySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}else{
							znalezionyElement->rodzic->lewySyn=znalezionyElement->prawySyn;
							znalezionyElement->prawySyn->rodzic=znalezionyElement->rodzic;
							delete znalezionyElement;
						}
					}	
					}else{
						if(znalezionyElement->lewySyn!=NULL){
							tmp=znalezionyElement->lewySyn;
							delete korzen;
							tmp->rodzic=NULL;
							korzen=tmp;
						}else{
							tmp=znalezionyElement->prawySyn;
							delete korzen;
							tmp->rodzic=NULL;
							korzen=tmp;
						}
					}
				}
				rozmiar--; 
				return true; 
			}  
		}  
	}
	return false;
}

// metoda sluzaca do pomiaru czasu wykonania operacji 

long long int DrzewoBST::read_QPC(){
 LARGE_INTEGER count;
 DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
 QueryPerformanceCounter(&count);
 SetThreadAffinityMask(GetCurrentThread(), oldmask);
 return((long long int)count.QuadPart);  
} 

// metoda sluzaca do usuwania calego drzewa
void DrzewoBST::usunDrzewo(){
	while(rozmiar!=0){
		usun(korzen->wartosc);
	}
}
