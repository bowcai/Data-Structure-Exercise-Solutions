
public class StringToInteger {
    public static void main(String[] args) {
        String s = "-1231904";
        System.out.println("Origin string: " + s);
        int num = myAtoi(s);
        System.out.println("Translated integer: " + num);
    }

    public static int myAtoi(String s) {
        if (s == null) {
            throw new NullPointerException();
        }
        int rslt = 0;
        int sign = 1;
        int i = 0;
        while (s.charAt(i) == '-') {
            sign *= -1;
            i++;
        }
        while (i < s.length() && s.charAt(i) >= '0'
                && s.charAt(i) <= '9') {
            rslt *= 10;
            rslt += s.charAt(i) - '0';
            i++;
        }
        return rslt * sign;
    }
}
