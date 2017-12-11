#include "Hebbe.h"

Hebbe::Hebbe() {

	this->epoka = 0;					// liczba epok 
	this->wspolczynnik_uczenia = 0.1;		// wspolczynnik uczenia
	this->wspolczynnik_zapominania = 0.05;		// wspolczynnik zapominania
	this->blad_globalny = 0;
	this->blad_lokalny = 0;
	this->MSE = 0;
	this->MAPE = 0;

}

void Hebbe::losowanie_wag() {
	srand(time(NULL));
	for (int i = 0;i<ROZMIAR;i++) {
		wagi(i, 0) = (float)rand() / (float)RAND_MAX;				// losowanie wag
		wagi(i, 1) = (float)rand() / (float)RAND_MAX;				
		wagi(i, 2) = (float)rand() / (float)RAND_MAX;				
		wagi(i, 3) = (float)rand() / (float)RAND_MAX;				
	}
}

void Hebbe::generuj_wejscie() {
	int temp;

	srand(time(NULL));
	for (int i = 0;i<ROZMIAR;i++) {
		temp = rand() % 2 - 1;						// generowanie losowych danych uczacych
		if (temp == 0) wejscie(i) = 1;
		else wejscie(i) = -1;
	}

	for (int i = 0;i<ROZMIAR;i++) {							// generowanie zdeformowanych emotikon
		macierzSmiechu(i) = dane_uczace_emotikony(i, 0);
		macierzPocalunek(i) = dane_uczace_emotikony(i, 1);
		macierzMilosc(i) = dane_uczace_emotikony(i, 2);
		macierzPlacz(i) = dane_uczace_emotikony(i, 3);
	}

	for (int i = 0;i<45;i++) {
		temp = rand() % 225;
		macierzMilosc(temp) = !macierzMilosc(temp);
		temp = rand() % 225;
		macierzSmiechu(temp) = !macierzSmiechu(temp);
	}

	for (int i = 0;i<90;i++) {
		temp = rand() % 225;
		macierzPocalunek(temp) = !macierzPocalunek(temp);
		temp = rand() % 225;
		macierzPlacz(temp) = !macierzPlacz(temp);
	}

}

void Hebbe::ustaw_wektor_uczenia() { // wczytywanie danych z pliku 
	int d, j, tmp;
	fstream fd;
	fd.open("dane_do_uczenia.txt");
	if (fd.is_open()) {
		j = 0, d = 0;
		while (!fd.eof()) {
			if (j == 225) {
				j = 0; d++;
			}
			if (d == 4) break;

			fd >> tmp;
			dane_uczace_emotikony(j, d) = tmp;
			dane_uczace_normalizacja(j, d) = dane_uczace_emotikony(j, d) / norma;

			++j;
		}
		fd.close();
	}
}

void Hebbe::zeruj() {
	for (int i = 0;i<ROZMIAR;i++) {
		suma_wag(i) = 1;
	}
}


void Hebbe::test() {

	fstream fout;						// plik w formacie do excela z zapisywaniem wyników
	fout.open(FILENAME, ios::app);

	double blad_globalny = 0;
	double blad_lokalny = 0;
	double MSE = 0;
	double MAPE = 0;
	double pom = 0;
	int epoka = 0;

	generuj_wejscie();

	do {
		epoka++;
		for (int j = 0;j<ROZMIAR;++j) {
			pom = suma_wag(j);
			//suma_wag(j) = (wagi(j, 0)*macierzPlacz(j, 0));
			//suma_wag(j) = (wagi(j, 0)*macierzMilosc(j, 0));
			suma_wag(j) = (wagi(j, 0)*macierzPocalunek(j, 0));
			//suma_wag(j) = (wagi(j, 0)*macierzSmiechu(j, 0));
			

			atest(j) = fa(suma_wag(j));
			blad_lokalny = abs(pom - suma_wag(j));
			blad_globalny = blad_globalny + pow(blad_lokalny, 2);
		}

		MSE = pow(blad_globalny, 2) / (ROZMIAR);
		MAPE = (blad_globalny * 10 / ROZMIAR);
		fout << "MSE: " << MSE << "\tMAPE: " << MAPE << "%\n";
	} while (blad_globalny != 0 && epoka<1);

	fout.close();

	porownaj();
}

int Hebbe::fa(double a) { // funkcja aktywacji
	return (a >= 0) ? 1 : -1;
}

void Hebbe::porownaj() {
	int tmp[4];
	int result;

	fstream fout;						// plik w formacie do excela z zapisywaniem wynikow
	fout.open(FILENAME, ios::app);

	for (int i = 0;i<4;i++) tmp[i] = 0;

	for (int i = 0;i<ROZMIAR;++i) {
		if (atest(i) == dane_uczace_emotikony(i, 0)) tmp[0]++;
		if (atest(i) == dane_uczace_emotikony(i, 1)) tmp[1]++;
		if (atest(i) == dane_uczace_emotikony(i, 2)) tmp[2]++;
		if (atest(i) == dane_uczace_emotikony(i, 3)) tmp[3]++;
	}

	cout << "\nPlacz: " << (double(tmp[3]) / 225.)*100. << endl;
	cout << "\nCalus: " << (double(tmp[1]) / 225.)*100. << endl;
	cout << "\nSmiech: " << (double(tmp[0]) / 225.)*100. << endl;
	cout << "\nMilosc: " << (double(tmp[2]) / 225.)*100. << endl;

	fout.close();
}