import java.io.*;
import java.util.Scanner;

public class pr {
    public static void main(String[] args) throws IOException {
        FileReader in = new FileReader("input.txt");
        FileWriter out = new FileWriter("output.txt");
        Scanner scan = new Scanner(in);
        int n;
        int m;
        n = scan.nextInt();
        m = scan.nextInt();
        int[][] arr = new int[n][n];
        for (int i = 0; i < m; ++i) {
            int k = scan.nextInt();
            int j = scan.nextInt();
            --k;
            --j;
            ++arr[k][j];
            ++arr[j][k];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                out.write(arr[i][j] + " ");
            }
            out.write("\n");
        }
        in.close();
        out.close();
    }
}
