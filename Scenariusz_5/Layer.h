#include <vector>
#include "Neuron.h"
using namespace std;

class Layer {
public:

	vector<Neuron> neuron; //wektor neuronow
	vector<double> suma; //wektor sum wejsc
	int liczba_neuronow; //liczba neuronow
	int wygrany_index; //indeks zwyciezcy

	Layer(int liczba_neuronow, int liczba_wejsc, double wspolczynnik_uczenia); //konstruktor
	void wygrany_neuron(bool learning); //szukanie zwycieskiego neuronu
	void suma_wszystkich_wejsc(); //obliczenie sumy wszystkich wejsc
	void zmiana_wag(bool learning); //zmiana wag (learning = true dla procesu uczenia, = false dla procesu testowania)
};
