#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <windows.h>  //sleep
#include <conio.h>  //getch()





/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

void menu();
void instrukcja();
void autorzy();

class karta
{
public:
char wartosc;
char kolor;
int numer_karty;
bool ukryta=false;
bool zaznaczony=false;
karta * next= NULL;
public:
void wypisz()
{
	if (ukryta) 
	{
	cout<<" |##| ";
	}	
else if(zaznaczony)
	{
		cout<<">"<<"|"<<kolor<<wartosc<<"|"<<"<";
	}
else  {
	cout<<" |"<<kolor<<wartosc<<"| ";	
	}
}	

};

class talia
{
	public:
	karta* tablicatali =new karta[52];
	
	



void wypelnienie_kart(karta * tablicatali)
{
	char znak[4] ={003,004,005,006};
//char figura[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char figura[13] = {'A','2','3','4','5','6','7','8','9','X','J','Q','K'};
	int i=3;
	int j=1;
	
	
		for(int x=47; x>=0 ;x--)
	{

	tablicatali[x].wartosc=figura[j];
	tablicatali[x].kolor=znak[i];
	tablicatali[x].numer_karty=x;


	i--;
		if(i<0)
		{
			j++;
			i=3;
		}
		
	}
	
	for(int g=48 ;g<52 ;g++)
	{
		
	tablicatali[g].wartosc=figura[0];
	tablicatali[g].kolor=znak[g-48];
	tablicatali[g].numer_karty=g;
	j++;
	}
	
	
	
	
}

void tasowanie ()
{
	
	srand(time(0));

    int  los;

    int random;
    karta temp;

       for (los = 0; los < 48; los++)

      {
		//	if(los ==13 || los==26 || los==39  ) los++;
            random = rand() % 47;

            temp = tablicatali[los];
			tablicatali[los] = tablicatali[random];
			tablicatali[random] = temp;
        }
        
}
};


class stos
{
public:
karta *nowa = NULL	;
karta *root = NULL; 
	
	bool tylko_dla_pustych=false;

 public:
//zdejmij element ze stosu (root)
karta zdejmij ()
{
	
if (root !=NULL) //sprawdz czy stos nie jest juz pusty , chyba niepotrzebne tak jak ten else ni¿ej
{

karta *temp=root;
karta result =*root;
root=(root)->next;
result.ukryta=false;
delete temp;

return result;
}
/* else 
	{		karta *zerowa= NULL;
	
		return *zerowa; 
	} */

}
void dodaj (karta *temp)
{  

karta *nowa = new karta;
nowa->wartosc = temp->wartosc;
//nowa = temp;
nowa->kolor =temp->kolor;
nowa->ukryta=temp->ukryta;
nowa->numer_karty=temp->numer_karty;
nowa->next=root;
root=nowa;




}
void wyswietl_wszystko()
{

	 while(true)  // wyswietla ca³y stos
	 {
	
		 root->wypisz() ;cout<< "  ";
		 if (root->next==NULL)
		 { 
		 cout <<"stos pusty"<<endl; break;  
		}
		 else
		  root = root->next;
	 };
}
	void wypisz(karta *root)
{

	 
	
	 	 while(true)  // wyswietla jedn¹ karte
	 {
		 if (root==NULL && tylko_dla_pustych==true) cout<<">|--|<";
		 else if(tylko_dla_pustych==false && root==NULL) cout<<" |--| ";
		 else
		{
		 root->wypisz() ;//cout<< "  ";
		}
		 break; 	
	 };
//	 cout << endl;
}
	

};



void przenoszenie(stos & przenoszona , stos &docelowa, int wiersz )
{

if(docelowa.root==0){

	docelowa.dodaj(przenoszona.root);
	przenoszona.zdejmij ();
	return;
}

int numer = docelowa.root->numer_karty - przenoszona.root->numer_karty ;
if (wiersz==0 && numer==4)
{
		docelowa.dodaj(przenoszona.root);
	przenoszona.zdejmij ();
	
}


}

void zwyciestwo(stos kier, stos karo , stos trefl ,stos pik)
{
	if(pik.root->numer_karty==3 && trefl.root->numer_karty==2 
	&& karo.root->numer_karty==1 && kier.root->numer_karty==0 )
	{
	cout<<"Brawo ! Ulozyles Pasjansa !"<<endl;
	cout<<"Wcisnij ESC wrocic do menu";
		char x;
		while (true)
		{
			x=getch();
			if(x==27) menu();
			 
		}
	}
	
}

void porazka(stos dywan[],stos beta, stos alfa, stos kier, stos karo , stos trefl ,stos pik)
{

if(alfa.root !=0) return;
	for(int i=0 ; i<20 ; i++)
	{
		if(dywan[i].root==0) return;
		
		int numer = kier.root->numer_karty - dywan[i].root->numer_karty ;
		if(numer==4)	return;
	}
	for(int i=0 ; i<20 ; i++)
	{
	int numer = karo.root->numer_karty - dywan[i].root->numer_karty ;
	if(numer==4)	return;	
	}
		for(int i=0 ; i<20 ; i++)
	{
	int numer = pik.root->numer_karty - dywan[i].root->numer_karty ;
	if(numer==4)	return;	
	}
		for(int i=0 ; i<20 ; i++)
	{
	int numer = trefl.root->numer_karty - dywan[i].root->numer_karty ;
	if(numer==4)	return;	
	}
	
	if(beta.root==0) return;

	int numer =  kier.root->numer_karty - beta.root->numer_karty  ;
	if(numer==4) return;
	numer=karo.root->numer_karty -beta.root->numer_karty ;
	if(numer==4) return;
	numer=trefl.root->numer_karty -beta.root->numer_karty ;
	if(numer==4) return;
	numer=pik.root->numer_karty -beta.root->numer_karty ;
	if(numer==4) return;


	cout<<"Nie mozesz juz wykowac zadnego ruchu !"<<endl;
	cout<<"Przegrales, nacisnij ESC aby wrocic do menu"<<endl;
			char x;
		while (true)
		{
			x=getch();
			if(x==27) menu();
		
		}
	
}




void gra() {
	
	talia pasjans;
	
	
	  pasjans.wypelnienie_kart(pasjans.tablicatali);
	  
	  
	stos kier;
	stos karo;
	stos pik;
	stos trefl;

		kier.dodaj(&pasjans.tablicatali[48]);
	  	karo.dodaj(&pasjans.tablicatali[49]);
	  	trefl.dodaj(&pasjans.tablicatali[50]);
	  	pik.dodaj(&pasjans.tablicatali[51]);
	  
	  pasjans.tasowanie();


	stos alfa;
	stos beta;


	for(int i=0 ; i<27; i++)
	{
		
		karta pomocnicza =pasjans.tablicatali[i];
		pomocnicza.ukryta =true;
		alfa.dodaj(&pomocnicza);
	}


		beta.dodaj(&pasjans.tablicatali[27]);


stos dywan [20];
	for(int i=28 ,j=0 ; i<48; i++ , j++)
	{
		
		karta pomocnicza =pasjans.tablicatali[i];
		
		dywan[j].dodaj(&pomocnicza);
		
		
	}

     char c;
     int kolumna=1, wiersz=1;
	stos * zaznaczony =0;
	stos * zaznaczony_aktualnie=0;

	int numer =1;



do
{
// numer = (wiersz-1) * 5 + kolumna;

if(kolumna != 6 && wiersz !=0)zaznaczony_aktualnie=&dywan[numer-1];
else if(kolumna == 6 ) zaznaczony_aktualnie=&beta;
else if(wiersz==0)
{

	switch(kolumna){
	
	case 1: zaznaczony_aktualnie =&pik;
	break;
	case 2: zaznaczony_aktualnie =&kier;
	break;
	case 3: zaznaczony_aktualnie =&trefl;
	break;
	case 4:zaznaczony_aktualnie =&karo;
	break;
}
}

if(zaznaczony_aktualnie->root==0) 
zaznaczony_aktualnie->tylko_dla_pustych=true;
else zaznaczony_aktualnie->root->zaznaczony=true;





//	alfa.wypisz(alfa.root);cout <<endl;
//	beta.wypisz(beta.root);cout <<endl;
pik.wypisz(pik.root);cout<<"\t" ;kier.wypisz(kier.root); cout<<"\t";
trefl.wypisz(trefl.root);cout<<"\t";karo.wypisz(karo.root);cout<<"\t"<<endl;

	cout<<endl<<endl;
	for (int i =0; i<20 ; i++)
	{
			if(i%10==0 && i%20!=0){cout<<"\t  ";alfa.wypisz(alfa.root);}
			if(i%15==0 && i%30!=0){cout<<"\t  ";beta.wypisz(beta.root);}
			if(i%5==0){
			
			 cout<<endl;
			 };
			dywan[i].wypisz(dywan[i].root);
			cout<<" \t";
		
	}
	cout<<endl<<endl<<endl;


    zwyciestwo( kier,  karo ,trefl , pik);
    porazka( dywan, beta, alfa, kier,  karo ,trefl , pik);



c=getch();
switch (c)
  {              
                case 72:
                        {

						
						if(wiersz >0 && kolumna !=6) wiersz=wiersz-1;
						 if (kolumna ==5 && wiersz ==0) kolumna =4;
						 
						
                
                 break;
                }
                case 80:
                        
                        	if(kolumna==6){
							
                        karta *a=alfa.root;
						if(a!=NULL){
						karta b=alfa.zdejmij();
						beta.tylko_dla_pustych=false;
						beta.dodaj(&b);
						
						} 
                 		}
                 		else if (wiersz <4)wiersz = wiersz +1;
                 		
                 break;
                
                                case 75:
                        {
                          if(kolumna >1) kolumna= kolumna-1;  
                        
                 break;
                 }
                                 case 77:
                        {
                          if(kolumna <6) kolumna=kolumna+1;  
                        	if(wiersz==0 && kolumna ==5) kolumna--;
                 break;
                 }
                				case 13:
                				{		
									if(zaznaczony !=0)
									{
									zaznaczony->root->zaznaczony=false;
									przenoszenie(*zaznaczony , *zaznaczony_aktualnie , wiersz);
									zaznaczony_aktualnie->tylko_dla_pustych=false;
									zaznaczony=0;
                					}
                					else if (zaznaczony_aktualnie->root==0) ;
									else if(wiersz!=0 && kolumna!=6)
									zaznaczony = &dywan[numer-1];
									else if(kolumna ==6) zaznaczony =&beta;
									

                					break;
								}
                	
  
    }

system("CLS");


kier.root ->zaznaczony=false;
 karo.root ->zaznaczony=false;
trefl.root ->zaznaczony=false;
pik.root ->zaznaczony=false;



if(kolumna==6 && beta.root !=0) beta.root->zaznaczony=true;
else if(beta.root ==0 ) zaznaczony_aktualnie->tylko_dla_pustych=false;
else beta.root->zaznaczony=false;


if(wiersz!=0)numer = (wiersz-1) * 5 + kolumna;



if(zaznaczony_aktualnie->root != 0 ) zaznaczony_aktualnie->root->zaznaczony=false;
else zaznaczony_aktualnie->tylko_dla_pustych =false;

if(zaznaczony !=0)zaznaczony->root->zaznaczony=true;

    



}
while(c!=27);
}

void menu()
{
	system("CLS");
	


int c=0;
string wiersz[4];
wiersz[0]="<-";
while(true)
{
cout<<"      ###      ##  ##   ##   ##     ###     ##  ##"<<endl;     
cout<<"      ####     ##  ##   ##   ##    ## ##    ### ##"<<endl;
cout<<"      ## ##    ##  ##   ##   ##   ##   ##   ### ##"<<endl;
cout<<"      ##  ##    ####    ## # ##   #######   ######"<<endl;
cout<<"      ##  ##     ##     #######   ##   ##   ## ###"<<endl;
cout<<"      ## ###     ##     ### ###   ##   ##   ## ###"<<endl;
cout<<"      ####       ##      #   #    ##   ##   ##  ##"<<endl<<endl;

cout<<" \t \t \t Menu glowne:"<<endl;
cout<<""<<endl;
cout<<" \t \t \t  1.Zagraj   "<<wiersz[0]<<endl;
cout<<" \t \t \t  2.Jak grac?"<<wiersz[1]<<endl;
cout<<" \t \t \t  3.Tworcy   "<<wiersz[2]<<endl;
cout<<" \t \t \t  4.Wyjdz    "<<wiersz[3]<<endl;


char a;
a=getch();
switch(a){


case 72:
	
	
	if(c>0)
	{
	
	wiersz[c]="";
	c=c-1;
	}
	break;

case 80:
	
	
	if(c<3)
	{
	
	wiersz[c]="";
	c=c+1;
	}
	break;

case 13:
if(c==0) 
{
system("CLS") ;
gra();
}
if(c==1)  
{
system("CLS") ;
instrukcja();
}
if(c==2)
{
 
system("CLS") ; 
autorzy();
}
if(c==3) exit(0);
break;
}




wiersz[c]="<-";
system("CLS");
};


}

void autorzy()
{
    string tekst = "Autorzy: \nMichal Sliwa\nMateusz Malysiak \nNacisnij esc aby wrocic do menu"; //wprowadŸ dowolny tekst
    for (int i = 0; i < tekst.length(); i++)  //pêtla wykonuje sie od 0 do d³ugosci tekstu wprowadzonego w zmiennej tekst
    {
        cout << tekst[i]; //wyœwietlanie na ekranie po kolei ka¿dej litery
        Sleep(25); //tym regulujesz szybkoœæ pisania, wartoœæ w ms
    }
        cout << endl; //znak koñca linii
	
	
	
	
	char x;
	while (true)
	{
		x=getch();
		if(x==27){ //powrót na ESC
		menu();
		}
	}
	
}

void instrukcja()
{
	
	
    string tekst1 = "Pasjans Dywan\nZasady:\nCelem gry jest ulozenie kart w kolejnosci od najmniejszej do najwiekszej od asa\n";
    string tekst2 ="Asy sa juz ulozone na 4 polach w gornej czesci planszy\n z prawej strony planszy znajduje sie talia z ktorej mozna dobierac karty na stos kart pomocniczych\n";
	string tekst3 =" raz dobranej karty nie mozna zwrocic do tali\n karty z stosu kart pomocniczych mozna przekladac na wolne miejsca na polu glownym\n\n ";
	string tekst4 = "Sterowanie:\nporuszanie sie po planszy za pomoca klawiszy strzalek\n podniesienie karty lub opuszczenie klawisz enter\n "; 
	string tekst5 = "Dobranie karty z tali do stosu kart pomocniczych - strzalka w dol\n tylko gdy znajdujemy sie na stosie pomocniczym\naby wrocic do menu nacisnij klawisz esc\n";
	string tekst = tekst1 +tekst2 +tekst3 +tekst4 +tekst5;
	for (int i = 0; i < tekst.length(); i++)  //pêtla wykonuje sie od 0 do d³ugosci tekstu wprowadzonego w zmiennej tekst
    {
        cout << tekst[i]; //wyœwietlanie na ekranie po kolei ka¿dej litery
        Sleep(1); //tym regulujesz szybkoœæ pisania, wartoœæ w ms
    }
        cout << endl; //znak koñca linii
  
		char x;
		while (true)
	{
		x=getch();
		if(x==27) // powrót na ESC
		menu();
	
	}
	
}
int main()
{
	menu();
	
	return 0;
	
}





