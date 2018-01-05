#include <iostream>
#include <vector>

using namespace std;

class Neuron {
public:
	vector<double> wejscia;
	vector <double> wagi;
	double wartosc_wyjscie;
	double odl_euklides;
	double odleglosc_od_zwycieskiego;
	double wspolczynnik_uczenia;
	double wartosc_sasiedztwa; //wartosc funkcji sasiedztwa (Gaussian neighborhood function)
	double sumowanie_wejsc;

	void normalizacja_wag_zaktualizowanych();
	double losowanie_Wag();
	void oblicz_odleglosc_od_zwycieskiego(); //oblicza wartosc funkcji sasiedztwa (Gaussian neighborhood function)
	void nowa_waga();
	void stworz_wejscie(int liczba_wejsc);  //ustawienie wejsc na 0 i skorzystanie z metody :  losowanie_Wag())
	void funkcja_aktywacji(); //funkcja sigmoidalna 
	double oblicz_odleglosc_skalar(); 
	void oblicz_odleglosc_od_zwycieskiego(double promien, double obecna_iteracja, double czas);

	Neuron(); // konstruktory
	Neuron(int liczba_wejsc, double wspolczynnik_uczenia);

	int getRozmiar_wejsc() {	return wejscia.size();  }  //zwraca rozmiar wejsca
	int getRozmiar_wag() { return wagi.size();  } // podaje wage
};