import java.io.*;
import java.util.Scanner;

public class pr {
    public static void main(String[] args) throws IOException {
        FileReader fin = new FileReader("input.txt");
        FileWriter fout = new FileWriter("output.txt");
        Scanner scan = new Scanner(fin);
        int n = Integer.parseInt(scan.next());
        int[] arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = Integer.parseInt(scan.next());
        }
        fin.close();
        for (int j = (n - 1) / 2; j >= 0; --j) {
            if ((2 * j + 1 < n && arr[j] > arr[2 * j + 1]) || (2 * j + 2 < n && arr[j] > arr[2 * j + 2])) {
                fout.write("No");
                fout.close();
                return;
            }
        }
        fout.write("Yes");
        fout.close();
    }
}
