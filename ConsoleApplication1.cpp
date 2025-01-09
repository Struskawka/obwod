#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

class wsp{
public:

	wsp() { x = 0; y = 0; }
	wsp(double xx, double yy) { x = xx; y = yy; }

	void set_x(double xx) { x = xx; }
	void set_y(double yy) { y = yy; }
	double  get_x() { return x; }
	double  get_y() { return y; }

private:
	double x, y;
};
int main()
{
	time_t begin, end;
	time(&begin);

	ifstream dane("dane.txt");
	if(!dane.is_open()) {cerr << "Error opening the file!";return 0;}

	int rozmiar;
	dane>>rozmiar;

	if(rozmiar<3) { cerr << "Error za mało punktów"; return 0; }

	wsp* w;
	w = (wsp*)malloc(rozmiar * sizeof(*w));
	double x, y;
	for(int i = 0; i < rozmiar; ++i) { dane >> x >> y; w[i].set_x(x); w[i].set_y(y); }//wczytanie z pliku
	dane.close();

	//sortowanie po osi y rosnąco, od dołu do góry
	for(int i = 0; i < rozmiar - 1; i++) {
		for(int j = 0; j < rozmiar - i - 1; j++) {
			if(w[j].get_y() > w[j + 1].get_y()) {swap(w[j], w[j + 1]);}
		}
	}

	for(int i = 0; i < rozmiar; i++) { cout << w[i].get_x() << "  " << w[i].get_y()<< endl; }//wyświetlanie

	//obwód dolny ułożony współzegarowo
	vector<wsp> obw_D;
	int bottom = 0;
	obw_D.push_back(w[0]);
	for(int i = 1; i < rozmiar; i++) {
		if(w[i].get_x() <= obw_D.back().get_x()) { obw_D.push_back(w[i]); }
		if(w[i].get_x() > obw_D.front().get_x()) { obw_D.insert(obw_D.begin(), w[i]); bottom++; }
	}

	cout << endl; for(int i = 0; i < obw_D.size(); i++) { cout << obw_D[i].get_x() << "  " << obw_D[i].get_y() << endl; }//wyświetlanie
	cout<<"bottom  "<<bottom<<"  "<< obw_D[bottom].get_x() << "  " << obw_D[bottom].get_y() << endl;

	//obwód górny ułożony współzegarowo
	vector<wsp> obw_G;
	int top = 0;
	obw_G.push_back(w[rozmiar - 1]);
	for(int i = rozmiar - 2; i > 0; i--) {
		if(w[i].get_x() >= obw_G.back().get_x()) { obw_G.push_back(w[i]); }
		if(w[i].get_x() < obw_G.front().get_x()) { obw_G.insert(obw_G.begin(), w[i]); top++; }
	}

	cout << endl; for(int i = 0; i < obw_G.size(); i++) { cout << obw_G[i].get_x() << "  " << obw_G[i].get_y() << endl; }//wyświetlanie
	cout <<"top  "<< top << "  " << obw_G[top].get_x() << "  " << obw_G[top].get_y() << endl;

	double a, b;
	bool spr1=1;
	int i;

	//sprawdzanie wklęsłości w górnym obwodzie
	do {
		spr1 = 0;
		i = 0;
		while(i <= obw_G.size() - 3) {
			a = (obw_G[i+2].get_y() - obw_G[i].get_y()) / (obw_G[i+2].get_x() - obw_G[i].get_x());
			b = obw_G[i].get_y() - obw_G[i].get_x() * a;
			if(obw_G[i + 1].get_y() < a * obw_G[i + 1].get_x() + b) { 
				obw_G.erase(obw_G.begin() + i + 1); spr1 = 1; }
			else i++;
		}
	} while(spr1==1);

	//sprawdzanie wklęsłości w dolnym obwodzie
	do {
		spr1 = 0;
		i = 0;
		while(i <= obw_D.size() - 3) {
			a = (obw_D[i + 2].get_y() - obw_D[i].get_y()) / (obw_D[i + 2].get_x() - obw_D[i].get_x());
			b = obw_D[i].get_y() - obw_D[i].get_x() * a;
			if(obw_D[i + 1].get_y() > a * obw_D[i + 1].get_x() + b) {
				obw_D.erase(obw_D.begin() + i + 1); spr1 = 1;
			}
			else i++;
		}
	} while(spr1 == 1);



	cout << endl; for(int i = 0; i < obw_G.size(); i++) { cout << obw_G[i].get_x() << "  " << obw_G[i].get_y() << endl; }
	cout << endl; for(int i = 0; i < obw_D.size(); i++) { cout << obw_D[i].get_x() << "  " << obw_D[i].get_y() << endl; }

	//zapisywanie wyników do plików
	ofstream wynik;
	wynik.open ("wynik.txt");
	wynik << "x\ty"<<endl;
	for(int i = 0; i < obw_G.size(); i++) { wynik << obw_G[i].get_x() << "\t" << obw_G[i].get_y() << endl; }
	for(int i = 1; i < obw_D.size(); i++) { wynik << obw_D[i].get_x() << "\t" << obw_D[i].get_y() << endl; }
	wynik.close();


	time(&end);
	time_t elapsed = end - begin;
	cout << endl << "czas: " << elapsed;

	free(w);
	return(0);
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
