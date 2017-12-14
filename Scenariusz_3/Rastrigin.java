package Rastrigin;

public class Rastrigin {

        //obliczenie wartości funkcji rastrigin na osi z

        static double funkcja_rastrigin(double x1, double x2)
        {
            return 10 * 2 + Math.pow(x1, 2) - 10 * Math.cos(2 * Math.PI * x1) + Math.pow(x2, 2) - 10 * Math.cos(2 * Math.PI * x2);
        }

        //normalizacja danych do przedziału < 0 , 1 >
        static double normalizacja_danych(double wart, double wart_pocz, double wart_konc)
        {
            return ((wart - wart_pocz) / (wart_konc - wart_pocz)) * (1.0 - (0.0)) + (0.0);
        }
}
