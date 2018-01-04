#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Neuron {
public:
	vector<double> wagi;
	vector<double> wejscia;
	double wartosc_wyjsciowa; //wartosc wyjsciowa
	double wspolczynnik_uczenia; //wspolczynnik uczenia
	double sumOfAllwejscia; //suma wszystkich wejsc
	
	Neuron(); //konstruktor
	Neuron(int liczba_wejsc, double wspolczynnik_uczenia); //konstruktor

	double losowanie_wag(); //wylosowanie poczatkowych wag z zakresu <0;1)
	void normalizacja_wag(); //znormalizowanie wag (podczas procesu uczenia)
	void createwejscia(int liczba_wejsc); //stworzenie poczatkowych wejsc (ustawienie wejsc na 0, wykorzystanie metody losowanie_wag())
	void calculateNewWeight(); //obliczenie nowej wagi dla zwycieskiego neuronu
	double calculateSumOfAllwejscia(); //obliczenie sumy wszystkich wejsc
	void funkcja_aktywacji(); //funkcja sigmoidalna obliczajaca wyjscie

	int getRozmiar_wagi() { //zwraca rozmiar wag
		return wagi.size();
	}
	int getliczba_wejsc() { //zwraca rozmiar wejsc
		return wejscia.size();
	}

};