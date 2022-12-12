import java.io.*;
import java.util.*;
import java.text.*;

class descendingComparator implements Comparator<Double> {
    @Override
    public int compare(Double d1, Double d2) {
        return Double.compare(d2, d1);
    }
}

public class pr2 {
    public static void main(String[] args) throws IOException {
        Locale locale = new Locale("be", "BY");
        String pattern = "###.##";
        DecimalFormat decimalFormat = (DecimalFormat) NumberFormat.getNumberInstance(locale);
        decimalFormat.applyPattern(pattern);
        DecimalFormat decimalFormat2 = (DecimalFormat) NumberFormat.getCurrencyInstance(locale);
        DecimalFormat decimalFormat3 = (DecimalFormat) NumberFormat.getPercentInstance(locale);

        String s;
        System.out.print("Enter n: ");
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        s = in.readLine();
        int n = Integer.parseInt(s);
        double[][] matrix1 = new double[n][n];
        double[][] matrix2 = new double[n][n];
        Random rand = new Random();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix1[i][j] = (double) Math.round(rand.nextDouble() * 1_000) / 100;
                matrix2[i][j] = (double) Math.round(rand.nextDouble() * 1_000) / 100;
            }
        }

        System.out.println("\nmatrix1");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                System.out.printf("%.2f ", matrix1[i][j]);
            }
            System.out.println();
        }

        System.out.println("\nmatrix2");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                System.out.printf("%.2f ", matrix2[i][j]);
            }
            System.out.println();
        }

        Double[][] matrix3 = createMatrix(matrix1, matrix2, n);
        sort(matrix3[n - 1]);
        System.out.println("\nmatrix3");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                System.out.printf("%.2f ", matrix3[i][j]);
            }
            System.out.println();
        }

        if (binarySearch(matrix3[n - 1], 0)) {
            System.out.printf("%.2f was found", matrix3[n - 1][0]);
        } else {
            System.out.printf("%.2f was not found", matrix3[n - 1][0]);
        }

        System.out.println("\n");
        for (int i = 0; i < n; ++i) {
            System.out.print(decimalFormat.format(matrix3[n-1][i]) + " ");
        }
        System.out.println("\n");
        for (int i = 0; i < n; ++i) {
            System.out.print(decimalFormat2.format(matrix3[n-1][i]) + " ");
        }
        System.out.println("\n");
        for (int i = 0; i < n; ++i) {
            System.out.print(decimalFormat3.format(matrix3[n-1][i]) + " ");
        }
    }

    public static Double[][] createMatrix(double[][] matrix1, double[][] matrix2, int n) {
        Double[][] matrix = new Double[n][n];
        for (int i = 0; i < n; ++i) {
            double biggest = matrix2[i][0];
            for (int j = 1; j < n; ++j) {
                if (matrix2[i][j] > biggest) {
                    biggest = matrix2[i][j];
                }
            }
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = (double) Math.round(matrix1[i][j] * biggest * 100) / 100;
            }
        }

        return matrix;
    }

    public static void sort(Double[] line) {
        Arrays.sort(line, new descendingComparator());
    }

    public static boolean binarySearch(Double[] line, int k) {
        return Arrays.binarySearch(line, line[k], new descendingComparator()) >= 0;
    }
}