import java.util.Scanner;

public class LSymSubstring {
    public static void main(String[] args) {
        String s;
        System.out.println("Enter a string:");
        Scanner scanner = new Scanner(System.in);
        s = scanner.nextLine();
        System.out.println("The longest symmetry substring's length is "
                + longestSymmetric(s));
    }

    public static int longestSymmetric(final String s) {
        int maxSymLen = 0;
        int fore, back, symLen;
        for (int i = 0; i < s.length(); i++) {
            // If the symmetry substring length is odd
            symLen = 1;
            fore = i - 1;
            back = i + 1;
            while (fore >= 0 && back < s.length()) {
                if (s.charAt(fore) == s.charAt(back)) {
                    symLen += 2;
                    fore--;
                    back++;
                }
                else {
                    break;
                }
            }
            if (symLen > maxSymLen) {
                maxSymLen = symLen;
            }

            // If the symmetry substring length is even
            symLen = 0;
            fore = i;
            back = i + 1;
            while (fore >= 0 && back < s.length()) {
                if (s.charAt(fore) == s.charAt(back)) {
                    symLen += 2;
                    fore--;
                    back++;
                }
                else {
                    break;
                }
            }
            if (symLen > maxSymLen) {
                maxSymLen = symLen;
            }
        }

        return maxSymLen;
    }
}
