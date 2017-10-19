#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Perceptron {
	unsigned numInputs_;
	double *weights_;
	double threshold_, trainingRate_;
} Perceptron;

Perceptron *Perceptron_new(unsigned numOfInputs, double trainingRate);
void ucz(Perceptron *perceptron, const double inputs[], int expectedResult);
int uzyskajWynik(const Perceptron *perceptron, const double inputs[]);
double uzyskajWartosc(const Perceptron *perceptron, const double inputs[]);
void ustawWage(Perceptron *perceptron, const double *weights);
const double *uzyskajWage(const Perceptron *perceptron);
double losowaWartosc();
void zmianaWagi(Perceptron *perceptron, int actualResult, int desiredResult, const double inputs[]);

#ifdef __cplusplus
}
#endif

#endif

