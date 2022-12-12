import java.io.*;
import java.util.*;
import java.util.regex.*;

public class pr3 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter first str (string): ");
        String str1 = in.readLine();
        System.out.print("Enter second str (separators): ");
        String str2 = in.readLine();
        System.out.print("Enter number P: ");
        int P = Integer.parseInt(in.readLine());
        int[] arr = new int[100];
        StringBuilder StringOfNumbers = new StringBuilder("String of Numbers: ");
        StringBuilder StringOfPalindromes = new StringBuilder("String of Palindromes: ");
        StringBuilder StringOfNumberP = new StringBuilder();
        StringBuilder StringOfModified_str1;
        Random rand = new Random();

        ArrayList<String> StringOfLexemes = findLexemes(str1, str2, arr, P, StringOfNumberP, StringOfPalindromes, StringOfNumbers);
        StringOfModified_str1 = deleteParentheses("Modified first str: " + str1);
        sort(StringOfLexemes);

        System.out.print("String of Lexemes: ");
        StringOfLexemes.forEach(pr3::PrintString);
        System.out.println("\n" + String.format(StringOfNumbers.toString()));
        System.out.println(String.format(StringOfPalindromes.toString()));
        if (StringOfNumberP.length() == 0) {
            StringOfNumberP.append("Number P hadn't found");
            StringOfModified_str1.insert(20, rand.nextInt(1000) + " ");
        }
        System.out.println(String.format(StringOfNumberP.toString()));
        System.out.println(String.format(StringOfModified_str1.toString()));
    }

    public static ArrayList<String> findLexemes(String str1, String str2, int[] arr, int P,
                                    StringBuilder StringOfNumberP, StringBuilder StringOfPalindromes, StringBuilder StringOfNumbers) {
        int k = 0;
        ArrayList<String> StringOfLexemes = new ArrayList<>();
        StringTokenizer s = new StringTokenizer(str1, str2);
        while (s.hasMoreTokens()) {
            String str = s.nextToken();
            StringOfLexemes.add(str);
            if (isNumber(str)) {
                arr[k] = Integer.parseInt(str);
                if (P == arr[k] && StringOfNumberP.length() == 0) {
                    StringOfNumberP.append("Position of number P: ").append(str1.indexOf(Integer.toString(P)));
                }
                ++k;
            }
            else {
                if (isPalindrome(str) && ! isNumber(str)) {
                    StringOfPalindromes.append(str).append(" ");
                }
            }
        }

        for (int i = 0; i < k; ++i) {
            StringOfNumbers.append(arr[i]).append(" ");
        }

        return StringOfLexemes;
    }

    public static StringBuilder deleteParentheses(String str1) {
        StringBuilder StringOfModified_str1 = new StringBuilder(str1);
        if(str1.contains("(") && str1.contains(")")) {
            int index = StringOfModified_str1.indexOf("(");
            int index1 = index;
            while (index1 < StringOfModified_str1.indexOf(")") && index1 != -1) {
                index = index1;
                index1 = StringOfModified_str1.indexOf("(", index + 1);
            }
            if (index < StringOfModified_str1.indexOf(")")) {
                StringOfModified_str1.delete(index, StringOfModified_str1.indexOf(")") + 1);
                StringOfModified_str1 = deleteParentheses(StringOfModified_str1.toString());
            }
        }
        return StringOfModified_str1;
    }

    public static void sort(ArrayList<String> StringOfLexemes) {
        StringOfLexemes.sort((ss1, ss2) -> {
            if (isPalindrome(ss1) && isPalindrome(ss2)) {
                if (ss1.length() % 2 == 1 && ss2.length() % 2 == 1) {
                    return ss1.length() - ss2.length();
                } else if (ss1.length() % 2 == 1) {
                    return -1;
                } else if (ss2.length() % 2 == 1) {
                    return 1;
                }
                else return 1;
            }
            else if (isPalindrome(ss1)) return -1;
            else if (isPalindrome(ss2)) return 1;
            else return 1;
        });
    }

    public static boolean isNumber(String str) {
        Pattern pattern = Pattern.compile("-?\\d+");
        Matcher matcher = pattern.matcher(str);
        return matcher.matches();
    }

    public static boolean isPalindrome(String str) {
        StringBuilder s1 = new StringBuilder(str);
        StringBuilder s2 = new StringBuilder(str);
        s2.reverse();
        return s1.compareTo(s2) == 0;
    }

    public static void PrintString(String ss) {
        System.out.print(ss + " ");
    }
}