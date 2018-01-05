#include "Neuron.h"
#include <cmath>
#include <ctime>

Neuron::Neuron() {
	this->wejscia.resize(0);
	this->wagi.resize(0);
	this->sumowanie_wejsc = 0.0;
	this->wartosc_wyjscie = 0.0;
	this->wspolczynnik_uczenia = 0.0;
}

Neuron::Neuron(int liczba_wejsc, double wspolczynnik_uczenia) {
	stworz_wejscie(liczba_wejsc);
	normalizacja_wag_zaktualizowanych();
	this->wspolczynnik_uczenia = wspolczynnik_uczenia;
	this->sumowanie_wejsc = 0.0;
	this->wartosc_wyjscie = 0.0;
}

void Neuron::stworz_wejscie(int liczba_wejsc) { //stworzenie poczatkowych wejsc(ustawienie wejsc na 0, wykorzystanie metody losowanie_Wag())
	for (int i = 0; i < liczba_wejsc; i++) {
		wejscia.push_back(0);
		wagi.push_back(losowanie_Wag());
	}
}

double Neuron::oblicz_odleglosc_skalar() {
	sumowanie_wejsc = 0.0;
	for (int i = 0; i < getRozmiar_wejsc(); i++)
		sumowanie_wejsc += pow(wejscia[i] - wagi[i], 2);
	sumowanie_wejsc = sqrt(sumowanie_wejsc);

	return sumowanie_wejsc;
}

void Neuron::funkcja_aktywacji() {
	double beta = 1.0;
	this->wartosc_wyjscie = (1.0 / (1.0 + (exp(-beta * sumowanie_wejsc))));
}

void Neuron::nowa_waga() {
	for (int i = 0; i < getRozmiar_wag(); i++)
		this->wagi[i] += this->wspolczynnik_uczenia*this->wartosc_sasiedztwa*(this->wejscia[i] - this->wagi[i]);
	normalizacja_wag_zaktualizowanych();
}

void Neuron::normalizacja_wag_zaktualizowanych() {
	double vectorodl_euklides = 0.0;

	for (int i = 0; i < getRozmiar_wag(); i++)
		vectorodl_euklides += pow(wagi[i], 2);

	vectorodl_euklides = sqrt(vectorodl_euklides);

	for (int i = 0; i < getRozmiar_wag(); i++)
		wagi[i] /= vectorodl_euklides;
}

void Neuron::oblicz_odleglosc_od_zwycieskiego(double promien, double currentIteraton, double czasConstant) {
	this->odleglosc_od_zwycieskiego = promien * exp(-currentIteraton / czasConstant);
}

void Neuron::oblicz_odleglosc_od_zwycieskiego() {
	this->wartosc_sasiedztwa = exp(-pow(this->odl_euklides, 2) / (2 * pow(this->odleglosc_od_zwycieskiego, 2)));
}

double Neuron::losowanie_Wag() {
	double max = 1.0;
	double min = 0.0;
	double weight = ((double(rand()) / double(RAND_MAX))*(max - min)) + min;
	return weight;
}