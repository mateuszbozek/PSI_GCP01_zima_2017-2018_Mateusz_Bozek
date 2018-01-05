#include "Neuron.h"
#include <vector>
using namespace std;

class Layer {
public:
	vector<Neuron> neuron;
	vector<double> scalarProducts; //odleglosci euklidesowych
	int liczba_neuronow;
	double promien; //promien wyznaczajacy obszar od zwycieskiego neuronu
	double czas;
	int zwycieski_neuron; //indeks 
	void zmiana_wag(double obecnaIteracja, bool testing); //przy aktualnej iteracji
	void minimum_odleglosc_euklidesowa();
	void getOdleglosc_euklidesowa(); //zwraca odleglosci euklidesowe

	Layer(int liczba_neuronow, int liczba_wejsc, double wspolczynnik_uczenia, double iterationsNumber);
};