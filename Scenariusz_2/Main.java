public class Main {
    public static void main(String[] args) {
        System.out.println("ANALINE");
        Adaline adaline = new Adaline();
        adaline.uczenie();
        adaline.testAdaline();

        System.out.println("DELTA SIGNOIDAL");
        DeltaSigmoidal deltasigmoidal = new DeltaSigmoidal();
        deltasigmoidal.uczenie();
        deltasigmoidal.testDelta();

    }

}