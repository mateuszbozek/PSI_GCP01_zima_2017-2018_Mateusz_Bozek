#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

#include "Layer.h"

using namespace std;

void dane_wejsciowe(Neuron& neuron, vector<vector<double>> inputData, int liczba_wejsc, int row);  //wczytanie do tablic danych wejsciowych
void ucz(Layer& layer, vector<vector<double>> inputData); // uczenie sieci
void test(Layer& layer, vector<vector<double>> inputData);
void wczytaj_dane_uczace(vector<vector<double>>&uczingInputData, int liczba_wejsc);
void wczytaj_dane_testujace(vector<vector<double>>&testingInputData, int liczba_wejsc);

fstream OUTPUT_FILE_uczING, OUTPUT_FILE_strumien_danych_testujacych, OUTPUT_FILE_TESTING_NEURON;
fstream strumie_danych_uczacych, strumien_danych_testujacych;

int main() {
	srand(time(NULL));

	vector<vector<double>> dane_testujace;
	vector<vector<double>> dane_uczace;
	int liczba_neuronow = 20;
	int liczba_wejsc = 35;
	double wspolczynnik_uczenia = 0.05;
	int epoka = 50;

	Layer siec_Kohonena(liczba_neuronow, liczba_wejsc, wspolczynnik_uczenia, epoka);
	wczytaj_dane_uczace(dane_uczace, liczba_wejsc);
	wczytaj_dane_testujace(dane_testujace, liczba_wejsc);

			OUTPUT_FILE_uczING.open("output_uczing_data.txt", ios::out);

			for (int epokaNumber = 1, i = 0; i < epoka; i++, epokaNumber++) {
				ucz(siec_Kohonena, dane_uczace); // ropoczynanie procesu uczenia
				OUTPUT_FILE_uczING << "epoka: " << epokaNumber << endl;
				cout << "epoka: " << epokaNumber << endl;
			}
			OUTPUT_FILE_uczING.close();
		
			OUTPUT_FILE_strumien_danych_testujacych.open("output_strumien_danych_testujacych.txt", ios::out);
			OUTPUT_FILE_TESTING_NEURON.open("output_testing_neuron.txt", ios::out);
			test(siec_Kohonena, dane_testujace);
			
			OUTPUT_FILE_uczING.close();
			OUTPUT_FILE_strumien_danych_testujacych.close();
			system("pause");
	return 0;
}

void dane_wejsciowe(Neuron& neuron, vector<vector<double>> inputData, int liczba_wejsc, int row)
{
	for (int i = 0; i < liczba_wejsc; i++)
		neuron.wejscia[i] = inputData[row][i];
}

void ucz(Layer& layer, vector<vector<double>> inputData)
{
	static int obecna_iteracja = 0;
	for (int rowOfData = 0; rowOfData < inputData.size(); rowOfData++) {
		for (int i = 0; i < layer.liczba_neuronow; i++) {
			dane_wejsciowe(layer.neuron[i], inputData, layer.neuron[i].getRozmiar_wejsc(), rowOfData);
			layer.neuron[i].oblicz_odleglosc_skalar();
		}
		
		layer.zmiana_wag(obecna_iteracja, true);

		OUTPUT_FILE_uczING << layer.zwycieski_neuron << endl;
		cout << "Winner: " << layer.zwycieski_neuron << endl;
		obecna_iteracja++;
	}
}

void test(Layer& layer, vector<vector<double>> inputData) {
	for (int rowOfData = 0; rowOfData < inputData.size(); rowOfData++) {
		for (int i = 0; i < layer.liczba_neuronow; i++) {
			dane_wejsciowe(layer.neuron[i], inputData, layer.neuron[i].getRozmiar_wejsc(), rowOfData);
			layer.neuron[i].oblicz_odleglosc_skalar();
		}
		char letter = 'A';
		layer.zmiana_wag(0, false);
		OUTPUT_FILE_strumien_danych_testujacych << layer.neuron[layer.zwycieski_neuron].getRozmiar_wejsc() << endl;
		OUTPUT_FILE_TESTING_NEURON << (char)(letter + rowOfData) << " " << layer.zwycieski_neuron << endl;
		cout << (char)(letter + rowOfData) << " " << layer.zwycieski_neuron << endl;
	}
}

void wczytaj_dane_testujace(vector<vector<double>> &dane_testujace, int liczba_wejsc) {
	strumien_danych_testujacych.open("datatest.txt", ios::in);
	vector<double> row;
	double odl_euklides = 0;

	while (!strumien_danych_testujacych.eof()) {
		row.clear();

		for (int i = 0; i < liczba_wejsc; i++) {
			double inputTmp = 0.0;
			strumien_danych_testujacych >> inputTmp;
			row.push_back(inputTmp);
		}

		for (int i = 0; i < liczba_wejsc; i++) //znormalizowanie danych uczacych
			odl_euklides += pow(row[i], 2);
		odl_euklides = sqrt(odl_euklides);

		for (int i = 0; i < liczba_wejsc; i++)
			row[i] /= odl_euklides;
		dane_testujace.push_back(row);
	}
	strumien_danych_testujacych.close();
}

void wczytaj_dane_uczace(vector<vector<double>> &inputData, int liczba_wejsc) {
	strumie_danych_uczacych.open("data.txt", ios::in);
	double odl_euklides = 0;
	vector<double> row;
	do {
		row.clear();

		for (int i = 0; i < liczba_wejsc; i++) {
			double inputTmp = 0.0;
			strumie_danych_uczacych >> inputTmp;
			row.push_back(inputTmp);
		}
	
		for (int i = 0; i < liczba_wejsc; i++)//znormalizowanie danych uczacych
			odl_euklides += pow(row[i], 2);

		odl_euklides = sqrt(odl_euklides);

		for (int i = 0; i < liczba_wejsc; i++)
			row[i] /= odl_euklides;

		inputData.push_back(row);

	} while (!strumie_danych_uczacych.eof());

	strumie_danych_uczacych.close();
}