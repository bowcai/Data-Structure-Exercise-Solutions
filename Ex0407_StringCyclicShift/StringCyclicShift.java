
public class StringCyclicShift {
    public static void main(String[] args) {
        String s = "asdf";
        String t = "sdfa";

        System.out.println("Origin string 1: " + s);
        System.out.println("Origin string 2: " + t);
        System.out.println();

        System.out.println("Check with self-written KMP method");
        if (isShift(s, t)) {
            System.out.println("They are shift strings.");
        }
        else {
            System.out.println("They are not shift strings.");
        }

        System.out.println();
        System.out.println("Or use method contains() of String");
        if (isShiftUsingContains(s, t)) {
            System.out.println("They are shift strings.");
        }
        else {
            System.out.println("They are not shift strings.");
        }
    }

    public static int[] getNext(String t) {
        if (t == null) {
            throw new NullPointerException();
        }
        int[] next = new int[t.length()];
        next[0] = -1;

        for (int i = 1; i < t.length(); i++) {
            int j = next[i - 1];

            while (j >= 0 && t.charAt(i-1) != t.charAt(j)) {
                j = next[j];
            }

            if (j >= 0 && t.charAt(i-1) == t.charAt(j)) {
                next[i] = j + 1;
            }
            else {
                next[i] = 0;
            }
        }

        return next;
    }


    public static int kmp(String s, String t) {
        if (s == null || t == null) {
            throw new NullPointerException();
        }

        // find number of string t in string s
        int[] next = getNext(t);

        int index, count = 0;
        for (index = 0; index < s.length(); ++index) {
            int pos = 0;
            int iter = index;
            while (pos < t.length() && iter < s.length()) {
                if (s.charAt(iter) == t.charAt(pos)) {
                    ++iter; ++pos;
                }
                else {
                    if (pos == 0) {
                        ++iter;
                    }
                    else {
                        pos = next[pos - 1] + 1;
                    }
                }
            }

            if (pos == t.length() && (iter - index) == t.length()) {
                ++count;
            }
        }

        return count;
    }


    public static boolean isShift(String s, String t) {
        if (s == null || t == null) {
            throw new NullPointerException();
        }

        if (s.length() == 0 || s.length() != t.length()) {
            return false;
        }

        String s_copy = s + s;

        return kmp(s_copy, t) >= 1;
    }

    public static boolean isShiftUsingContains(
            String s, String t) {
        if (s == null || t == null) {
            throw new NullPointerException();
        }
        if (s.length() == 0 || s.length() != t.length()) {
            return false;
        }

        String s_copy = s + s;
        return s_copy.contains(t);
    }
}
