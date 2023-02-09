#include <iostream>//trzeba ogarnac temat z "void rozdzielDateNaZmienne(string dateWithDashes);" gdzie rok czy miesiac jest jako int w naszym projekcie
#include <windows.h>
#include <winbase.h>
#include <time.h>
#include <conio.h>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class Wydatki{
public:
    int incomeId;
    int userId;
    int date;
    string item;
    float amount;
};

int rok, miesiac, dzien;

Wydatki wydatkiC;
vector <Wydatki> wydatkiV;

////////////////Daty (w tym struktury tm)//////////////////////////////////////////////////////////
string zwrocAktualnaDateTM();
string zwrocPoczatekMiesiacaTM();
string zwrocPoczatekPoprzedniegoMiesiacaTM();
bool czyRokJestPrzestepny();
int podajMaksymalnaIloscDniWMiesiacu();

///////////////////////Drugi sposob (z wykorzystaniem struktury tm)//////////////////////////////////////////////////////////////////////
int zwrocPoczatekNastepnegoMiesiacaTM(string poczatkowaDataString);
int zwrocKoniecMiesiacaTM(string koniecMiesiaca);

////////////////Wprowadzanie danych i dodatkowe//////////////////////////////////////////////////////////
Wydatki wprowadzWydatki();
bool mniejsze(Wydatki a, Wydatki b);
void pokazWszystkieWydatki();

////////////////Bilanse//////////////////////////////////////////////////////////
void bilansZBiezacegoMiesiaca();
void bilansZPoprzedniegoMiesiaca();
void bilansZDwochDat();

////////////////Pomicnicze//////////////////////////////////////////////////////////
string replaceDateToTextWithoutDashes(string dateWithDashes);
void rozdzielDateNaGlowneZmienne(string dateWithDashes);
string dwucyfrowyMiesiacLubDzien(int miesiac);
int podajDateZeZemiennychInt();
int convertStringToInt(string stringNumber);
string convertIntToString(int intNumber);

////////////////Pierwsza metoda, juz niekatualna//////////////////////////////////////////////////////////
//int podajPoczatekKolejnegoMiesiaca(string poczatkowaData);//tu juz tez wszystklo dziala
//int podajKoniecKolejnegoMiesiaca(string koniecMiesiaca);





int main(){
    wprowadzWydatki();

    cout<<"Przed posortowaniem:"<<endl;
    pokazWszystkieWydatki();

    //sort(wydatkiV.begin(), wydatkiV.end(), mniejsze);//sortowanie bec innych odrebnych klas
    sort(wydatkiV.begin(), wydatkiV.end( ), [ ](Wydatki a, Wydatki b)  {return a.date < b.date;} ); ///wyrazenie lambda


//    cout<<endl<<"Po posortowaniu (po dacie):"<<endl;
//    pokazWszystkieWydatki();
//
//    cout<<endl<<"Bilans z biezacego miesiaca:";
//    bilansZBiezacegoMiesiaca();
//
//    cout<<endl<<"Bilans z poprzedniego miesiaca:";
//    bilansZPoprzedniegoMiesiaca();

    cout<<endl<<"Bilans z dwoch dat:";
    bilansZDwochDat();
}

////////////////Daty (w tym struktury tm)//////////////////////////////////////////////////////////
string zwrocAktualnaDateTM(){

    char bufor[64];
    time_t czas;
    time(&czas);
    tm czasTM = *localtime(&czas);

    strftime(bufor, sizeof(bufor), "%Y%m%d", &czasTM);

    //cout<<"zwrocAktualnaDate: "<<czasString<<endl;
    return bufor; //np. "20230122"
}

string zwrocPoczatekMiesiacaTM(){

    char bufor[64];
    time_t czas;
    time(&czas);
    tm czasTM = *localtime(&czas);

    czasTM.tm_mday = 1;

    strftime(bufor, sizeof(bufor), "%Y%m%d", &czasTM);

    //cout<<"zwrocPoczatekMiesiaca: "<<czasString<<endl;
    return bufor;
}

string zwrocPoczatekPoprzedniegoMiesiacaTM(){

    char bufor[64];
    time_t czas;
    time(&czas);
    tm czasTM = *localtime(&czas);

    if (czasTM.tm_mon == 0) // "0" to styczen
    {
        czasTM.tm_mday = 1;
        czasTM.tm_mon = 11; // "11" to grudzien
        czasTM.tm_year -= 1;
    }else{
        czasTM.tm_mon -= 1;
        czasTM.tm_mday = 1;
    }

    strftime(bufor, sizeof(bufor), "%Y%m%d", &czasTM);

    //cout<<"zwrocPoczatekPoprzedniegoMiesiaca: "<<czasString<<endl;
    return bufor;
}

int podajMaksymalnaIloscDniWMiesiacu(){
    int luty=2, lipiec=7;
    bool rokPrzestepny = czyRokJestPrzestepny();

	if (miesiac == luty)
		return rokPrzestepny ? 29 : 28;

	if (miesiac <= lipiec)
		return miesiac % 2 == 0 ? 30 : 31;

	return miesiac % 2 == 0 ? 31 : 30;
}

bool czyRokJestPrzestepny(){
	if ((rok % 4 == 0 && rok % 100 != 0) && (rok % 400 == 0))
		return true;
	else
		return false;
}

////////////////Wprowadzanie danych i dodatkowe//////////////////////////////////////////////////////////
Wydatki wprowadzWydatki(){
    wydatkiC.incomeId = 4;
    wydatkiC.userId = 1;
    wydatkiC.date = 20230105;
    wydatkiC.item = "Krzeslo";
    wydatkiC.amount = 50;
    wydatkiV.push_back(wydatkiC);

    wydatkiC.incomeId = 8;
    wydatkiC.userId = 1;
    wydatkiC.date = 20230101;
    wydatkiC.item = "Stol";
    wydatkiC.amount = 300;
    wydatkiV.push_back(wydatkiC);

    wydatkiC.incomeId = 1;
    wydatkiC.userId = 1;
    wydatkiC.date = 20230115;
    wydatkiC.item = "Dzieciak";
    wydatkiC.amount = 500;
    wydatkiV.push_back(wydatkiC);

    wydatkiC.incomeId = 7;
    wydatkiC.userId = 1;
    wydatkiC.date = 20221220;
    wydatkiC.item = "Hajs co miesiac!";
    wydatkiC.amount = 1500;
    wydatkiV.push_back(wydatkiC);

    wydatkiC.incomeId = 5;
    wydatkiC.userId = 1;
    wydatkiC.date = 20221129;
    wydatkiC.item = "Glupoty";
    wydatkiC.amount = 1100;
    wydatkiV.push_back(wydatkiC);

    wydatkiC.incomeId = 2;
    wydatkiC.userId = 1;
    wydatkiC.date = 20221220;
    wydatkiC.item = "Benzyna";
    wydatkiC.amount = 1000;
    wydatkiV.push_back(wydatkiC);

    wydatkiC.incomeId = 3;
    wydatkiC.userId = 1;
    wydatkiC.date = 20221225;
    wydatkiC.item = "Benzyna2";
    wydatkiC.amount = 1550;
    wydatkiV.push_back(wydatkiC);

    return wydatkiC;
}

bool mniejsze(Wydatki a, Wydatki b){
    return a.date < b.date;
}

void pokazWszystkieWydatki(){
    cout<<"ID    Date         amount"<<endl;
    for (vector<Wydatki> :: iterator itr = wydatkiV.begin(); itr != wydatkiV.end(); itr++){
        cout<<itr -> incomeId<<"     ";
        cout<<itr -> date<<"     ";
        cout<<itr -> amount<<endl;
    }
}

void pokazPojedynczyWydatek(Wydatki wydatkiC){
        cout<<wydatkiC.incomeId<<"     ";
        cout<<wydatkiC.date<<"     ";
        cout<<wydatkiC.amount<<endl;
}


//////////////Bilanse//////////////////////////////////////////////////////////
void bilansZBiezacegoMiesiaca(){
    int poczatekMiesiaca, aktualnaData;

    poczatekMiesiaca = convertStringToInt(zwrocPoczatekMiesiacaTM());//"20230101"
    aktualnaData = convertStringToInt(zwrocAktualnaDateTM());//np. "20230122"

    cout<<endl<<"ID    Date         amount"<<endl;

    for (vector <Wydatki> :: iterator itr = wydatkiV.begin(); itr != wydatkiV.end(); itr++){
        for(int i=poczatekMiesiaca; i<=aktualnaData; i++){
            if(itr -> date == i){
                pokazPojedynczyWydatek(*itr);
            }
        }
    }
}

void bilansZPoprzedniegoMiesiaca(){
    int poczatekMiesiaca, koniecMiesiaca;

    poczatekMiesiaca = convertStringToInt(zwrocPoczatekPoprzedniegoMiesiacaTM());//20221201
    koniecMiesiaca = zwrocKoniecMiesiacaTM(convertIntToString(poczatekMiesiaca));

    cout<<endl<<"ID    Date         amount"<<endl;

    for (vector <Wydatki> :: iterator itr = wydatkiV.begin(); itr != wydatkiV.end(); itr++){
        for(int i=poczatekMiesiaca; i<=koniecMiesiaca; i++){
            if(itr -> date == i){
                pokazPojedynczyWydatek(*itr);
            }
        }
    }
}

void bilansZDwochDat(){//funkcja jest dluga i brzydka, ale dziala... trzeba by ja jakos upiekrzyc, albo czesc wywalic do innej funkcji
    int poczatkowaData, koncowaData, koniecMiesiaca, maksymalnaIloscDniWMiesiacu, koniecPrzedzialu, tymczasowePoczatkowaData, tymczasoweKoniecPrzedzialu, tymczasoweKoniecMiesiaca;
    string wpisanaDataPierwsza ="2021-11-30", wpisanaDataDruga = "2022-12-26";

    //tutaj musimy jeszcze sprawdzic poprawnosc obu dat, oraz dac warunek: wpisanaDataDruga>=wpisanaDataPierwsza

    rozdzielDateNaGlowneZmienne(wpisanaDataPierwsza);
    poczatkowaData = podajDateZeZemiennychInt();

    maksymalnaIloscDniWMiesiacu = podajMaksymalnaIloscDniWMiesiacu();
    koniecMiesiaca = zwrocKoniecMiesiacaTM(convertIntToString(poczatkowaData));

    rozdzielDateNaGlowneZmienne(wpisanaDataDruga);
    koncowaData = podajDateZeZemiennychInt();

    koncowaData >= koniecMiesiaca ? koniecPrzedzialu = koniecMiesiaca : koniecPrzedzialu = koncowaData;

    cout<<endl<<"ID    Date         amount"<<endl;
    for (vector <Wydatki> :: iterator itr = wydatkiV.begin(); itr != wydatkiV.end(); itr++){
        tymczasowePoczatkowaData = poczatkowaData;
        tymczasoweKoniecMiesiaca = koniecMiesiaca;
        tymczasoweKoniecPrzedzialu = koniecPrzedzialu;

        for(int i=poczatkowaData; i<=koniecPrzedzialu; i++){
            if(itr -> date == i){
                pokazPojedynczyWydatek(*itr);
            }
            if (i==koniecPrzedzialu && koniecPrzedzialu!=koniecMiesiaca)
                break;
//fajnie byloby nie angazowac zmiennych glownych int do "koniecMiesiaca"
            if(i==koniecPrzedzialu){
                poczatkowaData = zwrocPoczatekNastepnegoMiesiacaTM(convertIntToString(poczatkowaData));
                koniecMiesiaca = zwrocKoniecMiesiacaTM(convertIntToString(poczatkowaData));
                koncowaData >= koniecMiesiaca ? koniecPrzedzialu = koniecMiesiaca : koniecPrzedzialu = koncowaData;
                i = poczatkowaData - 1;
            }
        }
        poczatkowaData = tymczasowePoczatkowaData;
        koniecMiesiaca = tymczasoweKoniecMiesiaca;
        koniecPrzedzialu = tymczasoweKoniecPrzedzialu;
    }
}

///////////////////////Drugi sposob//////////////////////////////////////////////////////////////////////
int zwrocPoczatekNastepnegoMiesiacaTM(string poczatkowaDataString){//tutaj sprawdzamy czy szybciej/latwiej bedzie za pomoca struktury tm
    char bufor[64];
    time_t czas;
    time(&czas);
    tm czasTM;

    czasTM.tm_mday = convertStringToInt(poczatkowaDataString.substr(6,2)) - 1;
    czasTM.tm_mon = convertStringToInt(poczatkowaDataString.substr(4,2)) - 1;
    czasTM.tm_year = convertStringToInt(poczatkowaDataString.substr(0,4)) - 1900;

    if (czasTM.tm_mon == 11){ // "0" to styczen
        czasTM.tm_mon = 0; // "11" to grudzien
        czasTM.tm_year += 1;
    }else{
        czasTM.tm_mon += 1;
    }
    czasTM.tm_mday = 1;

    strftime(bufor, sizeof(bufor), "%Y%m%d", &czasTM);
//cout<<"bufor: "<<bufor<<endl;      system("pause");
    return convertStringToInt(bufor);
}

int zwrocKoniecMiesiacaTM(string poczatkowaData){//moze uda sie skrocic "insert"
    string poczatekMiesiaca;

    poczatekMiesiaca = poczatkowaData.insert(6, "-");
    poczatekMiesiaca = poczatekMiesiaca.insert(4, "-");

    rozdzielDateNaGlowneZmienne(poczatekMiesiaca);

    return convertStringToInt((convertIntToString(rok) + dwucyfrowyMiesiacLubDzien(miesiac) + convertIntToString(podajMaksymalnaIloscDniWMiesiacu())));
}


////////////////Pomicnicze//////////////////////////////////////////////////////////
string replaceDateToTextWithoutDashes(string dateWithDashes){
    string dateWithoutDashes;//"dataBezKresek"
    for (int charPosition=0; charPosition<(int)dateWithDashes.length(); charPosition++)
        if(dateWithDashes[charPosition]!='-'){
            dateWithoutDashes+=dateWithDashes[charPosition];
        }
    return dateWithoutDashes;
}

void rozdzielDateNaGlowneZmienne(string dateWithDashes){
    string dateElement = "";//"elementDaty"
    int dateElementNumber = 1;//"numerElementuDaty"

    dateWithDashes=dateWithDashes+'-';//dodajemy na koncu dodatkowa kreske do daty, aby petla nizej dzialala bez modyfikacji

    for (int charPosition=0; charPosition<(int)dateWithDashes.length(); charPosition++)
    {
        if(dateWithDashes[charPosition]!='-'){
            dateElement+=dateWithDashes[charPosition];
        }else{
            switch(dateElementNumber){
                case 1:
                    rok = atoi(dateElement.c_str());       break;
                case 2:
                    miesiac = atoi(dateElement.c_str());      break;
                case 3:
                    dzien = atoi(dateElement.c_str());        break;
            }
        dateElement = "";
        dateElementNumber++;
        }
    }
}

string dwucyfrowyMiesiacLubDzien(int miesiacLubDzien){
    string miesiacString = convertIntToString(miesiacLubDzien);
    miesiacString.length()==1 ? miesiacString = "0" + miesiacString : miesiacString;
    return miesiacString;
}

int podajDateZeZemiennychInt(){
    string rokString, miesiacString, dzienString;

    rokString = convertIntToString(rok);
    miesiacString = dwucyfrowyMiesiacLubDzien(miesiac);
    dzienString = dwucyfrowyMiesiacLubDzien(dzien);

    return convertStringToInt (rokString + miesiacString + dzienString);
}

int convertStringToInt(string stringNumber){
    int intNumber;
    istringstream iss(stringNumber);
    iss >> intNumber;

    return intNumber;
}

string convertIntToString(int intNumber){
    ostringstream ss;
    ss << intNumber;
    string stringNumber = ss.str();

    return stringNumber;
}


////////////////Pierwsza metoda, juz niekatualna//////////////////////////////////////////////////////////

//int podajPoczatekKolejnegoMiesiaca(string poczatkowaData){//"rok" i "miesiac" juz sa jako int, wiec nie dziala
//    string rok, miesiac, nastepnyMiesiac, nastepnyRok;
//
//    rok = poczatkowaData.substr(0,4);
//    miesiac = poczatkowaData.substr(4,2);
//
//    if (miesiac != "12"){ //ten sam rok
//        nastepnyMiesiac = convertIntToString(convertStringToInt(miesiac) + 1);//tutaj ogarniamy temat kiedy to "int" niszczy
//        nastepnyMiesiac.length()==1 ? nastepnyMiesiac = "0" + nastepnyMiesiac : nastepnyMiesiac;//nam zero przed pojedyncza cyfra
//        poczatkowaData = rok + nastepnyMiesiac + "01";
//    }else{ //kolejny rok
//        nastepnyRok = convertIntToString(convertStringToInt(rok) + 1);
//        poczatkowaData = nastepnyRok + "01" + "01";
//    }
//    return convertStringToInt(poczatkowaData);
//}
//
//int podajKoniecKolejnegoMiesiaca(string koniecMiesiaca){//"rok" i "miesiac" juz sa jako int, wiec nie dziala
//    string rok, miesiac;
//    int maksymalnaIloscDniWMiesiacu;
//
//    rok = koniecMiesiaca.substr(0,4);
//    miesiac = koniecMiesiaca.substr(4,2);
//
//    //maksymalnaIloscDniWMiesiacu = podajMaksymalnaIloscDniWMiesiacu(convertStringToInt(miesiac), convertStringToInt(rok));
//    //koniecMiesiaca = koniecMiesiaca.replace(6,2,convertIntToString(maksymalnaIloscDniWMiesiacu));
//
//    return convertStringToInt(koniecMiesiaca);
//}








