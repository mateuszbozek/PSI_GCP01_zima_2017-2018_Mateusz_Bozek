#include "Neuron.h"
#include <ctime>
#include <cmath>

Neuron::Neuron() {
	this->wejscia.resize(0);
	this->wagi.resize(0);
	this->sumOfAllwejscia = 0.0;
	this->wartosc_wyjsciowa = 0.0;
	this->wspolczynnik_uczenia = 0.0;
}

Neuron::Neuron(int liczba_wejsc, double wspolczynnik_uczenia) {
	createwejscia(liczba_wejsc);
	normalizacja_wag();
	this->wspolczynnik_uczenia = wspolczynnik_uczenia;
	this->sumOfAllwejscia = 0.0;
	this->wartosc_wyjsciowa = 0.0;
}

//stworzenie poczatkowych wejsc (ustawienie wejsc na 0, wykorzystanie metody losowanie_wag())
void Neuron::createwejscia(int liczba_wejsc) {
	for (int j = 0; j < liczba_wejsc; j++) {
		this->wejscia.push_back(0);
		this->wagi.push_back(losowanie_wag());
	}
}

//obliczenie sumy wszystkich wejsc
double Neuron::calculateSumOfAllwejscia() {
	this->sumOfAllwejscia = 0.0;
	for (int i = 0; i < getliczba_wejsc(); i++)
		this->sumOfAllwejscia += wejscia[i] * wagi[i];
	return sumOfAllwejscia;
}

//funkcja sigmoidalna obliczajaca wyjscie
void Neuron::funkcja_aktywacji() {
	double beta = 1.0;
	this->wartosc_wyjsciowa = (1.0 / (1.0 + (exp(-beta * this->sumOfAllwejscia))));
}

//obliczenie nowych wag
void Neuron::calculateNewWeight() {
	for (int i = 0; i < getRozmiar_wagi(); i++)
		this->wagi[i] += this->wspolczynnik_uczenia*(this->wejscia[i] - this->wagi[i]);
	normalizacja_wag();
}

//ustalenie poczatkowych wag dla wszystkich wejsc - zakres <0;1)
double Neuron::losowanie_wag() {
	double max = 1.0;
	double min = 0.0;
	double weight = ((double(rand()) / double(RAND_MAX))*(max - min)) + min;
	return weight;
}

//znormalizowanie nowo obliczonej wagi zwycieskiego neuronu
void Neuron::normalizacja_wag() {
	double vectordlugosc = 0.0;

	for (int i = 0; i < getRozmiar_wagi(); i++)
		vectordlugosc += pow(this->wagi[i], 2);

	vectordlugosc = sqrt(vectordlugosc);
	for (int i = 0; i < getRozmiar_wagi(); i++)
		this->wagi[i] /= vectordlugosc;
}