package Rastrigin;

import org.neuroph.core.NeuralNetwork;
import org.neuroph.core.data.DataSet;
import org.neuroph.core.data.DataSetRow;
import org.neuroph.nnet.MultiLayerPerceptron;
import org.neuroph.nnet.learning.BackPropagation;
import org.neuroph.util.TransferFunctionType;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {

    private static double xyMin = -2.0;
    private static double xyMax = 2.0;
    private static double zMin = Double.MIN_VALUE;
    private static double zMax = Double.MAX_VALUE;


        public static void main(String[] args) throws IOException {

            System.out.println("0.02");

            //utworzeine danych
            DataSet daneUczace = new DataSet(2, 1); //trainingData

            //wczytanie danych wejściowcyh z pliku
            File newFile = new File("learning_data.txt");
            FileWriter zapis = new FileWriter(newFile);

            for (double i=-2.0 ; i<=2.0 ; i+=0.1)
                for(double j=-2.0 ; j<= 2.0 ; j+=0.1)
                {
                    double z = Rastrigin.funkcja_rastrigin(i,j); // obliczenie wartosci z

                    zapis.write(i + ";" + j + ";" + z + "\n"); // ?

                    if(z <= zMin)                   // obliczenie wartości minimum i maksimum na przedziale ( -2 , 2 )
                        zMin=z;
                    else if ( z >= zMax)
                        zMax=z;

                }
            zapis.close();

            // wczytywanie danych z pliku
            Scanner wejscie = new Scanner(newFile); //wejscie
            String[] wynik;
            do {
                String line = wejscie.nextLine();
                wynik = line.split(";");

                //dodanie rzędu danych uczących
                daneUczace.addRow(new DataSetRow(new double[]{Rastrigin.normalizacja_danych(Double.parseDouble(wynik[0]), xyMin, xyMax), // normalizacja danych - wejscie 1
                                                                Rastrigin.normalizacja_danych(Double.parseDouble(wynik[1]), xyMin, xyMax) // normalizacja danych wejscie 2
                }, new double[]{Rastrigin.normalizacja_danych(Double.parseDouble(wynik[2]), zMin, zMax)})); // normalizacja danych - wyjscie
            } while (wejscie.hasNext());

            //wybranie metody wstecznej propagacji ( backPropagation )  i ustawienie max błędu i współczynnika uczenia
            BackPropagation backPropagation = new BackPropagation();
            backPropagation.setMaxError(0.015);
            backPropagation.setLearningRate(0.03);

            //utworzenie sieci wielowarstwowej i ustalenie ilośći warstw wewnętrznych
            MultiLayerPerceptron multiLayerPerceptron = new MultiLayerPerceptron(TransferFunctionType.SIGMOID, 2, 20,15,10, 1); // między wejscie i wyjscie znajduja sie ukryte wartwy
            multiLayerPerceptron.setLearningRule(backPropagation);

            System.out.println("Rozpoczecie nauki sieci z parametrami : \n" + "Blad maksymalny : " +
                    backPropagation.getMaxError() +"\n"+"Wspolczynnik uczenia : "+backPropagation.getLearningRate());
            multiLayerPerceptron.learn(daneUczace); // rozpoczecie procesu nauki

            // Wyswietlenie liczby iteracji oraz całkowitego błędu uczenia w sieci neuronowej
            System.out.println("Liczba iteracji : " + backPropagation.getCurrentIteration()+"\n"+"Blad : "+ backPropagation.getErrorFunction().getTotalError());

            //zapisanie utworzonej sieci
           multiLayerPerceptron.save("my.nnet");



            //testowanie nauczonej sieci

            NeuralNetwork siec_wielowarstwowa = NeuralNetwork.createFromFile("my.nnet");

            int liczba_epok = 1;

            for (DataSetRow dataSetRow : daneUczace.getRows()) {
                double[] input = dataSetRow.getInput();
                System.out.println("Epoka : " + liczba_epok + ":  x = " + input[0] + "  y = " + input[1]);

                double[] desiredOutput = dataSetRow.getDesiredOutput();
                siec_wielowarstwowa.setInput(dataSetRow.getInput());
                siec_wielowarstwowa.calculate();
                double[] output = siec_wielowarstwowa.getOutput();
                System.out.println("Oczekiwana wartosc wyjsciowa : " + desiredOutput[0]);
                System.out.println("Wyjscie : " + output[0]);
                System.out.println();
                liczba_epok++;
            }
        }
    }