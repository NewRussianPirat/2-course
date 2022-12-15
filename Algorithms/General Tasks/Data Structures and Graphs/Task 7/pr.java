import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class pr {
    public static void main(String[] args) throws IOException {
        FileReader in = new FileReader("input.txt");
        FileWriter out = new FileWriter("output.txt");
        Scanner scan = new Scanner(in);
        int n = scan.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int m = scan.nextInt();
                if (m == 1) {
                    arr[j] = i + 1;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            out.write(arr[i] + " ");
        }
        in.close();
        out.close();
    }
}
