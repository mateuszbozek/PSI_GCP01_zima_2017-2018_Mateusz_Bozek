#include "Hebbe.h"

int main() {
	
	Hebbe hebbe;

	cout << "Rozpoczecie nauki wedlug reguly Hebba." << endl;
	hebbe.zeruj();					/* ustawienie wartosci domyslnych dla wektora a  */
	hebbe.losowanie_wag();				/* wygenerowanie wag */
	hebbe.ustaw_wektor_uczenia();				/* ustawienie wektorow uczacych */

	do {
		cout << "epoka: " << hebbe.epoka << endl;

		// BEZ WSPOLCZYNNIKA ZAPOMINANIA
		
		for (int i = 0;i<4;++i) {    
			hebbe.blad_globalny = 0;

			for (int j = 0;j<ROZMIAR;++j) {
				hebbe.pom = hebbe.suma_wag(j); // ustalenie wag
				hebbe.suma_wag(j) = (hebbe.wagi(j, i)*hebbe.dane_uczace_emotikony(j, i)); // ustalenie sumy wag = waga * dana wejsciowa
				hebbe.wagi(j, i) = hebbe.wagi(j, i) + hebbe.wspolczynnik_uczenia*hebbe.suma_wag(j)*hebbe.dane_uczace_emotikony(j, i); //zmiana wagi 

				if (hebbe.blad_lokalny == abs(hebbe.pom - hebbe.suma_wag(j))) break; //
				hebbe.blad_lokalny = abs(hebbe.pom - hebbe.suma_wag(j));	// ustalenie bledu lokalnego
				hebbe.blad_globalny = hebbe.blad_globalny + pow(hebbe.blad_lokalny, 2); // ustalenie bledu globalnego

			}

			hebbe.MSE = pow(hebbe.blad_globalny, 2) / ROZMIAR;
			hebbe.MAPE = (hebbe.blad_globalny * 10) / ROZMIAR;
			cout << " MSE: " << hebbe.MSE << "\tMAPE: " << hebbe.MAPE << "%\n";
		}
		
		// ZE WSPOLCZYNNIKIEM ZAPOMINANIA
		
		for( int i=0;i<4;++i){
			hebbe.blad_globalny = 0;

			for( int j=0;j<ROZMIAR;++j){
				hebbe.pom = hebbe.suma_wag(j);
				hebbe.suma_wag(j) = (hebbe.wagi(j,i)*hebbe.dane_uczace_emotikony(j,i));
				hebbe.wagi(j,i) = hebbe.wagi(j,i)*hebbe.wspolczynnik_zapominania + hebbe.wspolczynnik_uczenia*hebbe.suma_wag(j)*hebbe.dane_uczace_emotikony(j,i); // zmiana wag

				if(hebbe.blad_lokalny==abs(hebbe.pom- hebbe.suma_wag(j))) break;
				hebbe.blad_lokalny = abs(hebbe.pom - hebbe.suma_wag(j));
				hebbe.blad_globalny = hebbe.blad_globalny + pow(hebbe.blad_lokalny,2);

			}

			hebbe.MSE = pow(hebbe.blad_globalny,2)/(ROZMIAR);
			hebbe.MAPE = (hebbe.blad_globalny*10/ROZMIAR);
			cout << "i:" << i << " MSE: " << hebbe.MSE << "\tMAPE: " << hebbe.MAPE << "%\n";
		}
		
		
		hebbe.epoka++;
	} while (hebbe.blad_globalny != 0 && hebbe.epoka<1000);

	cout << "\nliczba epok: " << hebbe.epoka << endl;

	hebbe.test();

	system("pause");
	return 0;
}












