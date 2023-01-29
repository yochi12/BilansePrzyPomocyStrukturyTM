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
bool czyRokJestPrzestepny(int rok);
int podajMaksymalnaIloscDniWMiesiacu(int miesiac, int rok);
int podajPoczatekKolejnegoMiesiaca(string poczatkowaData);//tu juz tez wszystklo dziala
int podajKoniecKolejnegoMiesiaca(string koniecMiesiaca);

///////////////////////Drugi sposob (z wykorzystaniem struktury tm)//////////////////////////////////////////////////////////////////////
int zwrocPoczatekNastepnegoMiesiacaTM(string poczatkowaDataString);
int zwrocKoniecNastepnegoMiesiacaTM(string koniecMiesiaca);

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
void rozdzielDateNaZmienne(string dateWithDashes);
int convertStringToInt(string stringNumber);
string convertIntToString(int intNumber);
string dwucyfrowyMiesiac(int miesiac);





int main(){
    wprowadzWydatki();

    cout<<"Przed posortowaniem:"<<endl;
    pokazWszystkieWydatki();

    //sort(wydatkiV.begin(), wydatkiV.end(), mniejsze);//sortowanie bec innych odrebnych klas
    sort(wydatkiV.begin(), wydatkiV.end( ), [ ](Wydatki a, Wydatki b)  {return a.date < b.date;} ); ///wyrazenie lambda


    cout<<endl<<"Po posortowaniu (po dacie):"<<endl;
    pokazWszystkieWydatki();

    cout<<endl<<"Bilans z biezacego miesiaca:";
    bilansZBiezacegoMiesiaca();

    cout<<endl<<"Bilans z poprzedniego miesiaca:";
    bilansZPoprzedniegoMiesiaca();

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

int podajMaksymalnaIloscDniWMiesiacu(int miesiac, int rok){
    int luty=2, lipiec=7;
    bool rokPrzestepny = czyRokJestPrzestepny(rok);

	if (miesiac == luty)
		return rokPrzestepny ? 29 : 28;

	if (miesiac <= lipiec)
		return miesiac % 2 == 0 ? 30 : 31;

	return miesiac % 2 == 0 ? 31 : 30;
}

bool czyRokJestPrzestepny(int rok){
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
    wydatkiC.date = 20221229;
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


////////////////Bilanse//////////////////////////////////////////////////////////
void bilansZBiezacegoMiesiaca(){
    int poczatkowaData, koncowaData;

    poczatkowaData = convertStringToInt(zwrocPoczatekMiesiacaTM());//"20230101"
    koncowaData = convertStringToInt(zwrocAktualnaDateTM());//np. "20230122"

    cout<<endl<<"ID    Date         amount"<<endl;

    for (vector <Wydatki> :: iterator itr = wydatkiV.begin(); itr != wydatkiV.end(); itr++){
        for(int i=poczatkowaData; i<=koncowaData; i++){
            if(itr -> date == i){
                pokazPojedynczyWydatek(*itr);
            }
        }
    }
}

void bilansZPoprzedniegoMiesiaca(){
    int poczatekMiesiaca, koniecMiesiaca, maksymalnaIloscDniWMiesiacu;
    string tymczasowaData, miesiac, rok;

    poczatekMiesiaca = convertStringToInt(zwrocPoczatekPoprzedniegoMiesiacaTM());//20221201
    tymczasowaData = zwrocPoczatekPoprzedniegoMiesiacaTM();//np. 20221201

    rok = tymczasowaData.substr(0,4);                    //2022
    miesiac = tymczasowaData.substr(4,2);                //12

    maksymalnaIloscDniWMiesiacu = podajMaksymalnaIloscDniWMiesiacu(convertStringToInt(miesiac), convertStringToInt(rok));//31
    tymczasowaData = rok + miesiac + convertIntToString(maksymalnaIloscDniWMiesiacu);//20221231
    koniecMiesiaca = convertStringToInt(tymczasowaData);//20221231

    cout<<endl<<"ID    Date         amount"<<endl;

    for (vector <Wydatki> :: iterator itr = wydatkiV.begin(); itr != wydatkiV.end(); itr++){
        for(int i=poczatekMiesiaca; i<=koniecMiesiaca; i++){
            if(itr -> date == i){
                pokazPojedynczyWydatek(*itr);
            }
        }
    }
}

void bilansZDwochDat(){
    int poczatkowaData, koncowaData, koniecMiesiaca, maksymalnaIloscDniWMiesiacu, koniecPrzedzialu;
    string wpisanaDataPierwsza ="2021-02-15", wpisanaDataDruga = "2022-12-20", miesiac, rok;

    //tutaj musimy jeszcze sprawdzic poprawnosc obu dat

    wpisanaDataPierwsza = replaceDateToTextWithoutDashes(wpisanaDataPierwsza);//"20210215"
    wpisanaDataDruga = replaceDateToTextWithoutDashes(wpisanaDataDruga);//"20221220"

    rok = wpisanaDataPierwsza.substr(0,4);                    //2021
    miesiac = wpisanaDataPierwsza.substr(4,2);                //02

    maksymalnaIloscDniWMiesiacu = podajMaksymalnaIloscDniWMiesiacu(convertStringToInt(miesiac), convertStringToInt(rok));//28

    poczatkowaData = convertStringToInt(wpisanaDataPierwsza);//"20210215"
    koncowaData = convertStringToInt(wpisanaDataDruga);//"20221220"
    koniecMiesiaca = convertStringToInt(rok + miesiac + convertIntToString(maksymalnaIloscDniWMiesiacu));//"20210228"

    koncowaData >= koniecMiesiaca ? koniecPrzedzialu = koniecMiesiaca : koniecPrzedzialu = koncowaData;

    cout<<endl<<"ID    Date         amount"<<endl;

    for (vector <Wydatki> :: iterator itr = wydatkiV.begin(); itr != wydatkiV.end(); itr++){
        for(int i=poczatkowaData; i<=koniecPrzedzialu; i++){
            if(itr -> date == i){
                pokazPojedynczyWydatek(*itr);
            }
            if(i==koniecMiesiaca){
                poczatkowaData = zwrocPoczatekNastepnegoMiesiacaTM(convertIntToString(poczatkowaData));
                koniecMiesiaca = zwrocKoniecNastepnegoMiesiacaTM(convertIntToString(poczatkowaData));
                koncowaData >= koniecMiesiaca ? koniecPrzedzialu = koniecMiesiaca : koniecPrzedzialu = koncowaData;
            }
        }
    }
}

int podajPoczatekKolejnegoMiesiaca(string poczatkowaData){
    string rok, miesiac, nastepnyMiesiac, nastepnyRok;

    rok = poczatkowaData.substr(0,4);
    miesiac = poczatkowaData.substr(4,2);

    if (miesiac != "12"){ //ten sam rok
        nastepnyMiesiac = convertIntToString(convertStringToInt(miesiac) + 1);//tutaj ogarniamy temat kiedy to "int" niszczy
        nastepnyMiesiac.length()==1 ? nastepnyMiesiac = "0" + nastepnyMiesiac : nastepnyMiesiac;//nam zero przed pojedyncza cyfra
        poczatkowaData = rok + nastepnyMiesiac + "01";
    }else{ //kolejny rok
        nastepnyRok = convertIntToString(convertStringToInt(rok) + 1);
        poczatkowaData = nastepnyRok + "01" + "01";
    }
    return convertStringToInt(poczatkowaData);
}

int podajKoniecKolejnegoMiesiaca(string koniecMiesiaca){
    string rok, miesiac;
    int maksymalnaIloscDniWMiesiacu;

    rok = koniecMiesiaca.substr(0,4);
    miesiac = koniecMiesiaca.substr(4,2);

    maksymalnaIloscDniWMiesiacu = podajMaksymalnaIloscDniWMiesiacu(convertStringToInt(miesiac), convertStringToInt(rok));
    koniecMiesiaca = koniecMiesiaca.replace(6,2,convertIntToString(maksymalnaIloscDniWMiesiacu));

    return convertStringToInt(koniecMiesiaca);
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

    return convertStringToInt(bufor);
}

int zwrocKoniecNastepnegoMiesiacaTM(string koniecMiesiaca){
    string rok, miesiac;

    char bufor[64];
    time_t czas;
    time(&czas);
    tm czasTM;

    rok = koniecMiesiaca.substr(0,4);
    miesiac = koniecMiesiaca.substr(4,2);

    czasTM.tm_mday = podajMaksymalnaIloscDniWMiesiacu(convertStringToInt(miesiac), convertStringToInt(rok));;
    czasTM.tm_mon = convertStringToInt(koniecMiesiaca.substr(4,2)) - 1;
    czasTM.tm_year = convertStringToInt(koniecMiesiaca.substr(0,4)) - 1900;

    strftime(bufor, sizeof(bufor), "%Y%m%d", &czasTM);

    return convertStringToInt(bufor);
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

void rozdzielDateNaZmienne(string dateWithDashes){
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

string dwucyfrowyMiesiac(int miesiac)
{
    string miesiacString = convertIntToString(miesiac);
    miesiacString.length()==1 ? miesiacString = "0" + miesiacString : miesiacString;
}










