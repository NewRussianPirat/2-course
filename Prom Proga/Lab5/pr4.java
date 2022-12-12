import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.*;

public class pr4 {
    public static void main(String[] args) throws IOException {
        FileReader fin = new FileReader("input.txt");
        FileWriter fout = new FileWriter("output.txt");
        ArrayList<String> arr = new ArrayList<>();
        Scanner scan = new Scanner(fin);
        while (scan.hasNextLine()) {
            arr.add(scan.nextLine());
        }
        fin.close();
        for (String s : arr) {
            if (isDate(s)) {
                System.out.println(s + " is time");
                fout.write(s + " is time\n");
            }
            else {
                System.out.println(s + " is not time");
                fout.write(s + " is not time\n");
            }
        }
        fout.close();
    }

    public static boolean isDate(String s) {
        Pattern pattern = Pattern.compile("([0-5][0-9])([/:-])([0-5][0-9])\\2(([0-1][0-9])|(2[0-4]))");
        Matcher matcher = pattern.matcher(s);
        return matcher.matches();
    }
}
