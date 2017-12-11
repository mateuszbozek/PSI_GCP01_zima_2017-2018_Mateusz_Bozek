#include<stdio.h>
#include<ctime>
#include<stdlib.h>
#include<string>
#include<Eigen/Dense>
#include<fstream>
#include<iostream>

using namespace std;
using namespace Eigen;

#define ROZMIAR 15*15
#define N 10
#define norma sqrt(225)

#define FILENAME "out/test.xlsx"

#pragma once
class Hebbe {

public:
	int epoka;					/* liczba epok */
	double wspolczynnik_uczenia;		/* wspolczynnik uczenia */
	double wspolczynnik_zapominania;		/* wspolczynnik zapominania */
	double blad_globalny;
	double blad_lokalny;
	double MSE;
	double MAPE;

	double pom = 0;				// zmienne pomocnicze
	double pomt = 0;

	MatrixXf dane_uczace_emotikony= MatrixXf(225, 4); 				// dane uczace: 0,x - smiech, 1,x - calus, 2,x - milosc, 3,x - placz 
	MatrixXf dane_uczace_normalizacja = MatrixXf(225, 4);				// dane uczace znormalizowane: dane_uczace_emotikony/sqrt(255)
	MatrixXf wejscie= MatrixXf(225, 1);					// dane testowe 
	MatrixXf macierzSmiechu= MatrixXf(225, 1);
	MatrixXf macierzPocalunek= MatrixXf(225, 1);
	MatrixXf macierzMilosc= MatrixXf(225, 1);
	MatrixXf macierzPlacz = MatrixXf(225, 1);
	MatrixXf wagi = MatrixXf(225, 4);					// wagi 

	VectorXf suma_wag = VectorXf(255);					// suma wag
	VectorXf atest = VectorXf(255);					// wyniki dla danych testujacych 
	VectorXf deltaw= VectorXf(225);					// poprawka wag 

	Hebbe();   // konstruktor
	void zeruj();	 // funkcja do zerowania wag
	void losowanie_wag(); // funkcja do losowania wag
	void generuj_wejscie(); // funkcja do generowania wejscia
	void ustaw_wektor_uczenia(); // funkcja pobierajaca dane z pliku
	int fa(double); // funkcja aktywacyjna
	void test(); // funkcja testujaca
	void porownaj(); // funkcja z wynikami

};