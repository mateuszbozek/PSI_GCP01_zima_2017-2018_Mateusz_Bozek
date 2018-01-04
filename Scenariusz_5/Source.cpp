#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>
#include "Layer.h"

using namespace std;

fstream OUTPUT_FILE_LEARNING, OUTPUT_FILE_TESTING_SUM, OUTPUT_FILE_TESTING_WINNER;  //strumienie do plikow sluzace do wczytania danych uczacych oraz zapisu wynikow
fstream Dane_do_nauki, Dane_do_testu;

void uczenie(Layer& layer, vector<vector<double>> inputData); //uczenie sieci
void test(Layer& layer, vector<vector<double>> inputData); //testowanie sieci
void wczytanie_danych_ucz¹cych(vector<vector<double>>&learnData, int liczba_wejsc); //wczytanie danych potrzebnych do nauki 
void wczytanie_danych_testowych(vector<vector<double>>&testData, int numberOfInpus); //wczytaniee danych testowych
void wczytanie_danych_wejsciowych(Neuron& neuron, vector<vector<double>> inputData, int liczba_wejsc, int inputDataRow); //wczytanie do tablic danych wejsciowych

int main() {
	srand(time(NULL));

	//wektory z danymi uczacymi oraz testujacymi
	vector<vector<double>> trainData;
	vector<vector<double>> testData;
	int liczba_neuronow = 10;
	int liczba_wejsc = 4;
	double wspolczynnik_uczenia = 0.5;

	Layer siecKohonena(liczba_neuronow, liczba_wejsc, wspolczynnik_uczenia); //stworzenie sieci Kohonena
	wczytanie_danych_ucz¹cych(trainData, liczba_wejsc); //wczytanie danych uczacych
	wczytanie_danych_testowych(testData, liczba_wejsc); //wczytaniee danych testowych


			OUTPUT_FILE_LEARNING.open("output_learning_data.txt", ios::out);

			for (int Epoka = 1, i = 0; i < 2; i++, Epoka++) {
				//uczenie
				OUTPUT_FILE_LEARNING << "Epoka: " << Epoka << endl;
				cout << "Epoka: " << Epoka << endl;
				uczenie(siecKohonena, trainData);
			}
			OUTPUT_FILE_LEARNING.close();
			
		
			OUTPUT_FILE_TESTING_SUM.open("output_Dane_do_testu.txt", ios::out);
			OUTPUT_FILE_TESTING_WINNER.open("output_testing_neuron.txt", ios::out);
			
			test(siecKohonena, testData);
		
			OUTPUT_FILE_LEARNING.close();
			OUTPUT_FILE_TESTING_SUM.close();
			OUTPUT_FILE_TESTING_WINNER.close();
			system("pasue");
			return 0;
}

void uczenie(Layer& layer, vector<vector<double>> inputData)
{
	int licznik = 0;
	for (int rowOfData = 0; rowOfData < inputData.size(); rowOfData++) {
		for (int i = 0; i < layer.liczba_neuronow; i++) {
			wczytanie_danych_wejsciowych(layer.neuron[i], inputData, layer.neuron[i].getliczba_wejsc(), rowOfData); //wczytanie danych do tablic
			layer.neuron[i].calculateSumOfAllwejscia();	//wyliczenie sumy wejscia
		}
	
		layer.zmiana_wag(true);	//zmiana wag
		//przeskoczenie na kolejny rodzaj kwiatka (wyzerowanie licznika)
		if (licznik == 50) {
			licznik = 0;
			OUTPUT_FILE_LEARNING << "Next flower" << endl;
			cout << "Next flower" << endl;
		}
		OUTPUT_FILE_LEARNING << layer.wygrany_index << endl;
		cout << "Winner: " << layer.wygrany_index << endl;
		licznik++;
	}
}

void wczytanie_danych_wejsciowych(Neuron& neuron, vector<vector<double>> inputData, int liczba_wejsc, int row)
{
	for (int i = 0; i < liczba_wejsc; i++) {
		neuron.wejscia[i] = inputData[row][i];
	}
}


void test(Layer& layer, vector<vector<double>> inputData) {
	int licznik = 0;
	for (int wierszDanych = 0; wierszDanych < inputData.size(); wierszDanych++) {
		for (int i = 0; i < layer.liczba_neuronow; i++) {
			wczytanie_danych_wejsciowych(layer.neuron[i], inputData, layer.neuron[i].getliczba_wejsc(), wierszDanych);//wczytanie danych do tablic
			layer.neuron[i].calculateSumOfAllwejscia(); //wyliczenia sumy wejscia
		}
		//przeskoczenie na kolejny rodzaj kwiatka (wyzerowanie licznika)
		if (licznik == 15) {
			licznik = 0;
			OUTPUT_FILE_TESTING_WINNER << "Next flower" << endl;
			cout << "Next flower" << endl;
		}
	
		layer.zmiana_wag(false);   //wagi nie beda zaktualiowane dla zwyciezcy
		OUTPUT_FILE_TESTING_SUM << layer.neuron[layer.wygrany_index].sumOfAllwejscia << endl;
		OUTPUT_FILE_TESTING_WINNER << layer.wygrany_index << endl;
		cout << "Which neuron: " << layer.wygrany_index << endl;
		licznik++;
	}
}

void wczytanie_danych_testowych(vector<vector<double>> &testData, int liczba_wejsc) {
	Dane_do_testu.open("datatest.txt", ios::in);
	vector<double> row;

	while (!Dane_do_testu.eof()) {
		row.clear();

		for (int i = 0; i < liczba_wejsc; i++) {
			double inputTmp = 0.0;
			Dane_do_testu >> inputTmp;
			row.push_back(inputTmp);
			if (i == liczba_wejsc - 1) {
				Dane_do_nauki >> inputTmp;
			}
		}
		double dlugosc = 0.0; //znormalizowanie danych uczacych

		for (int i = 0; i < liczba_wejsc; i++)
			dlugosc += pow(row[i], 2);
		dlugosc = sqrt(dlugosc);
		for (int i = 0; i < liczba_wejsc; i++)
			row[i] /= dlugosc;

		testData.push_back(row);
	}
	Dane_do_testu.close();
}

void wczytanie_danych_ucz¹cych(vector<vector<double>> &trainData, int liczba_wejsc) {
	Dane_do_nauki.open("data.txt", ios::in);
	vector<double> row;

	do {
		row.clear();
		for (int i = 0; i < liczba_wejsc; i++) {
			double inputTmp = 0.0;
			Dane_do_nauki >> inputTmp;
			row.push_back(inputTmp);
			if (i == liczba_wejsc - 1) {
				Dane_do_nauki >> inputTmp;
			}
		}

		//znormalizowanie danych uczacych
		double dlugosc = 0.0;

		for (int i = 0; i < liczba_wejsc; i++)
			dlugosc += pow(row[i], 2);

		dlugosc = sqrt(dlugosc);

		for (int i = 0; i < liczba_wejsc; i++)
			row[i] /= dlugosc;

		trainData.push_back(row);

	} while (!Dane_do_nauki.eof());

	Dane_do_nauki.close();
}