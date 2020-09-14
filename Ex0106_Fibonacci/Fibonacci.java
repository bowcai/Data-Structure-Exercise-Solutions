public class Fibonacci {
    public static void main(String[] args) {
        final int testTimes = 100000;
        final int nFibonacci = 25;

        long time1Start = System.currentTimeMillis();
        for (int i = 1; i <= testTimes; i++) {
            fibonacci1(nFibonacci);
        }
        long time1End = System.currentTimeMillis();
        System.out.println("Total run time for algorithm 1 is " 
            + (time1End - time1Start) + " ms");

        long time2Start = System.currentTimeMillis();
        for (int i = 1; i <= testTimes; i++) {
            fibonacci2(nFibonacci);
        }
        long time2End = System.currentTimeMillis();
        System.out.println("Total run time for algorithm 1 is " 
            + (time2End - time2Start) + " ms");

        long time3Start = System.currentTimeMillis();
        for (int i = 1; i <= testTimes; i++) {
            fibonacci3(nFibonacci);
        }
        long time3End = System.currentTimeMillis();
        System.out.println("Total run time for algorithm 1 is " 
            + (time3End - time3Start) + " ms");

    }

    // The first algorithm with complexity O(N^2)
    public static void fibonacci1(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException(
                "The input must be a positive integer.");
        }
        
        // System.out.println("Fibonacci number 1: 1");
        // System.out.println("Fibonacci number 2: 1");
        
        for (int i = 3; i <= n; i++) {
            long current = 1;
            long previous = 1;
            long temp;
            for (int j = 3; j <= i; j++) {
                temp = current;
                current += previous;
                previous = temp;
            }

            // System.out.println("Fibonacci number " 
            //     + i + ": " + current);
        }
    }

    // The second algorithm with complexity O(N)
    public static void fibonacci2(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException(
                    "The input must be a positive integer.");
        }
        
        // System.out.println("Fibonacci number 1: 1");
        // System.out.println("Fibonacci number 2: 1");

        long current = 1;
        long previous = 1;
        long temp;

        for (int i = 3; i <= n; i++) {
            temp = current;
            current += previous;
            previous = temp;
            // System.out.println("Fibonacci number " 
            //     + i + ": " + current);
        }
    }

    // The third algorithm that use recursion with complexity O(2^n)
    public static int fibonacci3(int n) {
        if (n > 2) {
            return fibonacci3(n - 1) + fibonacci3(n - 2);
        }
        else if (n == 1) {
            return 1;
        }
        else if (n == 2) {
            return 1;
        }
        else {
            throw new IllegalArgumentException(
                    "The input must be a positive integer.");
        }
    }
}
