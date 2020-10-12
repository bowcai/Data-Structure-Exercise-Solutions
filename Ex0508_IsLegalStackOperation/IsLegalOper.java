import java.util.Scanner;

public class IsLegalOper {
    public static void main(String[] args) {
        int n, m;
        Scanner scanner = new Scanner(System.in);

        n = scanner.nextInt();
        m = scanner.nextInt();


        // Clean the buffer
        scanner.nextLine();

        String[] strings = new String[n];
        for (int i = 0; i < n; i++) {
            strings[i] = scanner.nextLine();
        }

        for (String s: strings) {
            if (isLegal(s, m)) {
                System.out.println("YES");
            }
            else {
                System.out.println("NO");
            }
        }
    }

    public static boolean isLegal(final String s, int m) {
        int currentSize = 0;
        for (int i = 0; i < s.length(); i++) {
            switch (s.charAt(i)) {
                case 'S':
                    currentSize++;
                    break;
                case 'X':
                    currentSize--;
                    break;
                default:
                    return false;
            }
            if (currentSize < 0 || currentSize > m) {
                return false;
            }
        }

        return currentSize == 0;
    }
}
