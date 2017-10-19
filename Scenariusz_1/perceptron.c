#include <stdlib.h>
#include <time.h>

#include "perceptron.h"

#ifdef __cplusplus
extern "C" {
#endif

Perceptron *Perceptron_new(unsigned numOfInputs, double trainingRate) {
	unsigned i;
	static int initializedRandomization_ = 0;
	
	Perceptron *perc = (Perceptron*)malloc(sizeof(Perceptron));
	perc->numInputs_ = numOfInputs;
	if (perc->numInputs_ <= 0) {
		perc->numInputs_ = 1;
	}
	perc->trainingRate_ = trainingRate;
	perc->weights_ = (double*)malloc(perc->numInputs_ * sizeof(double));
	if (! initializedRandomization_) {
		srand(time(NULL));
		initializedRandomization_ = 1;
	}	
	for (i = 0 ; i < perc->numInputs_ ; i++) {
		perc->weights_[i] = losowaWartosc();
	}
	perc->threshold_ = losowaWartosc();
	
	return perc;	
}

void ucz(Perceptron *perceptron, const double inputs[], int expectedResult) {
	int result = uzyskajWynik(perceptron, inputs);
	if (result == expectedResult) {
		return;
	}
	zmianaWagi(perceptron, result, expectedResult, inputs);
}

void zmianaWagi(Perceptron *perceptron, int actualResult, int desiredResult, const double inputs[]) {
	unsigned i;

	for (i = 0; i < perceptron->numInputs_; i++) {
		perceptron->weights_[i] += perceptron->trainingRate_ * (desiredResult - actualResult) * inputs[i];
	}
	perceptron->threshold_ -= perceptron->trainingRate_ * (desiredResult - actualResult);
}

double uzyskajWartosc(const Perceptron *perceptron, const double inputs[]) {
	unsigned i;
	double ans = 0;
	
	for (i = 0 ; i < perceptron->numInputs_ ; i++) {
		ans += perceptron->weights_[i] * inputs[i];
	}	
	return ans;
}

void ustawWage(Perceptron *perceptron, const double *weights) {
	unsigned i;
	for (i = 0; i < perceptron->numInputs_; i++) {
		perceptron->weights_[i] = weights[i];
	}
}

int uzyskajWynik(const Perceptron *perceptron, const double inputs[]) {
	return (uzyskajWartosc(perceptron, inputs) >= perceptron->threshold_);
}

double losowaWartosc() {
	double randValue = ((double)rand() / (double)RAND_MAX);
	double negativeRand = ((double)rand() / (double)RAND_MAX);
	if (negativeRand < 0.5) {
		randValue *= -1.0;
	}
	return randValue;
}

const double *uzyskajWage(const Perceptron *perceptron) {
	return perceptron->weights_;
}

#ifdef __cplusplus
}
#endif

