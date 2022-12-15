import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class pr {
    public static void main(String[] args) throws IOException {
        FileReader in = new FileReader("input.txt");
        FileWriter out = new FileWriter("output.txt");
        Scanner scan = new Scanner(in);
        int n = scan.nextInt();
        int m = scan.nextInt();
        ArrayList<ArrayList<Integer>> arr = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < n; ++i) {
            arr.add(new ArrayList<Integer>());
        }
        for (int i = 0; i < m; ++i) {
            int k = scan.nextInt();
            int j = scan.nextInt();
            arr.get(k - 1).add(j);
            arr.get(j - 1).add(k);
        }
        for (int i = 0; i < n; ++i) {
            out.write(arr.get(i).size() + " ");
            for (int j = 0; j < arr.get(i).size(); ++j) {
                out.write(arr.get(i).get(j) + " ");
            }
            out.write("\n");
        }
        in.close();
        out.close();
    }
}
