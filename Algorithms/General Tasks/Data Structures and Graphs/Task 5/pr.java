import java.io.*;
import java.util.Scanner;

public class pr {
    public static void main(String[] args) throws IOException {
        FileReader in = new FileReader("input.txt");
        FileWriter out = new FileWriter("output.txt");
        Scanner scan = new Scanner(in);
        int n;
        n = scan.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n - 1; ++i) {
            int k = scan.nextInt();
            int m = scan.nextInt();
            --m;
            arr[m] = k;
        }
        for (int i = 0; i < n; ++i) {
            out.write(arr[i] + " ");
        }
        in.close();
        out.close();
    }
}
