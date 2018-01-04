#include "Layer.h"

Layer::Layer(int liczba_neuronow, int liczba_wejsc, double wspolczynnik_uczenia) {
	this->liczba_neuronow = liczba_neuronow;
	this->neuron.resize(liczba_neuronow);
	for (int i = 0; i < liczba_neuronow; i++)
		this->neuron[i].Neuron::Neuron(liczba_wejsc, wspolczynnik_uczenia);
}
void Layer::wygrany_neuron(bool learning) { //poszukiwanie wejscia o najwiekszej sumie
	double tmp = this->suma[0];
	this->wygrany_index = 0;
	for (int i = 1; i < this->suma.size(); i++) {
		if (tmp < this->suma[i]) {
			this->wygrany_index = i;
			tmp = this->suma[i];
		}
	}
	this->neuron[this->wygrany_index].funkcja_aktywacji();
	if (learning)
		this->neuron[this->wygrany_index].calculateNewWeight();  //aktualizacja wag
}
void Layer::zmiana_wag(bool learning) { //obliczenie sum wszystkich wejsc, poszukiwanie tego o najwiekszej sumie i aktualizacja jego wag
	suma_wszystkich_wejsc();
	wygrany_neuron(learning);
}
void Layer::suma_wszystkich_wejsc() { //obliczenie sumy wszystkich wejsc
	this->suma.clear();
	for (int i = 0; i < this->liczba_neuronow; i++)
		this->suma.push_back(neuron[i].calculateSumOfAllwejscia());
}
