#include <stdio.h>
#include "perceptron.h"

const int iteration = 16, numberOfImputs = 2;
const double learnRate = 0.2;

int main() {
	
	const double ZERO_ZERO[] = {0, 0};
	const double ZERO_ONE[]  = {0, 1};
	const double ONE_ZERO[]  = {1, 0};
	const double ONE_ONE[]   = {1, 1};

	int i;
	Perceptron *pOR  = Perceptron_new(numberOfImputs, learnRate);
	
	printf("Wyniki 'AND' przed nauka :\n");
	printf("Wejscie : 0,0 wynik: %d\n", uzyskajWynik(pOR, ZERO_ZERO));
	printf("Wejscie : 0,1 wynik: %d\n", uzyskajWynik(pOR, ZERO_ONE));
	printf("Wejscie : 1,0 wynik: %d\n", uzyskajWynik(pOR, ONE_ZERO));
	printf("Wejscie : 1,1 wynik: %d\n", uzyskajWynik(pOR, ONE_ONE));

	printf("\nUcze sie \n\n");
	
	for (i = 0 ; i < iteration; i++) {
		ucz(pOR, ZERO_ZERO,  0);
		ucz(pOR, ZERO_ONE,   0);
		ucz(pOR, ONE_ZERO,   0);
		ucz(pOR, ONE_ONE,    1);
	}
	printf("Wynik'AND' po nauce :\n");
	printf("Wejscie : 0,0 wynik: %d\n", uzyskajWynik(pOR, ZERO_ZERO));
	printf("Wejscie : 0,1 wynik: %d\n", uzyskajWynik(pOR, ZERO_ONE));
	printf("Wejscie : 1,0 wynik: %d\n", uzyskajWynik(pOR, ONE_ZERO));
	printf("Wejscie : 1,1 wynik: %d\n", uzyskajWynik(pOR, ONE_ONE));

	system("pause");
	return 0;
}

