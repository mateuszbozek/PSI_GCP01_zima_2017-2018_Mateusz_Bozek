#include "Layer.h"

Layer::Layer(int liczba_neuronow, int liczba_wejsc, double wspolczynnik_uczenia, double iterationsNumber) {
	this->liczba_neuronow = liczba_neuronow;
	neuron.resize(liczba_neuronow);
	this->czas = iterationsNumber / this->promien;
	this->promien = 5;
	for (int i = 0; i < liczba_neuronow; i++)
		neuron[i].Neuron::Neuron(liczba_wejsc, wspolczynnik_uczenia);
}

void Layer::minimum_odleglosc_euklidesowa() {  //szuka najmniejszej odleglosci euklidesowej
	double tmp = scalarProducts[0];
	this->zwycieski_neuron = 0;
	for (int i = 1; i < scalarProducts.size(); i++) {
		if (tmp < scalarProducts[i]) {
			this->zwycieski_neuron = i;
			tmp = scalarProducts[i];
		}
	}
}

void Layer::zmiana_wag(double obecna_iteracja, bool uczing) {
	minimum_odleglosc_euklidesowa();
	getOdleglosc_euklidesowa();
	neuron[zwycieski_neuron].funkcja_aktywacji();

	if (uczing) {
		 
		neuron[zwycieski_neuron].oblicz_odleglosc_od_zwycieskiego(promien, obecna_iteracja, czas);// szukanie neuronow w otoczeniu wygraneno neuronu 
		int promien = neuron[zwycieski_neuron].odleglosc_od_zwycieskiego;
		int leftBorderNeuronIndex = 0;
		int rightBorderNeuronIndex = 0;

		if (zwycieski_neuron - promien < 0) //sprawdzenie czy dany neuron miesci sie w siatce
			leftBorderNeuronIndex = 0;
		else
			leftBorderNeuronIndex = zwycieski_neuron - promien;

		if (zwycieski_neuron + promien >= liczba_neuronow)
			rightBorderNeuronIndex = liczba_neuronow - 1;
		else
			rightBorderNeuronIndex = zwycieski_neuron + promien;

		promien = (promien <= 0) ? 0 : --promien;

		for (int i = leftBorderNeuronIndex; i < rightBorderNeuronIndex; i++) {
			neuron[i].odl_euklides = (i < zwycieski_neuron) ? (zwycieski_neuron - i) : (i - zwycieski_neuron); //zmiana wag dla neuronow z otoczenia
			neuron[i].odleglosc_od_zwycieskiego = neuron[zwycieski_neuron].odleglosc_od_zwycieskiego;
			neuron[i].nowa_waga();
		}
	}
}

void Layer::getOdleglosc_euklidesowa() {
	scalarProducts.clear();
	for (int i = 0; i < liczba_neuronow; i++)
		scalarProducts.push_back(neuron[i].oblicz_odleglosc_skalar());
}