import static org.junit.jupiter.api.Assertions.*;

class pr2Test {

    @org.junit.jupiter.api.Test
    void createMatrix() {
        double[][] matrix1 = new double[2][2];
        matrix1[0][0] = 2;
        matrix1[0][1] = 3;
        matrix1[1][0] = 5;
        matrix1[1][1] = 1;
        double[][] matrix2 = new double[2][2];
        matrix2[0][0] = 8;
        matrix2[0][1] = 3;
        matrix2[1][0] = 4;
        matrix2[1][1] = 5;
        Double[][] matrix3 = new Double[2][2];
        matrix3[0][0] = 16d;
        matrix3[0][1] = 24d;
        matrix3[1][0] = 25d;
        matrix3[1][1] = 5d;
        assertArrayEquals(matrix3, pr2.createMatrix(matrix1, matrix2, 2));
    }

    @org.junit.jupiter.api.Test
    void sort() {
        Double[] line = new Double[5];
        line[0] = 23d;
        line[1] = 12d;
        line[2] = 56d;
        line[3] = 43d;
        line[4] = 100d;
        Double[] line1 = new Double[5];
        line1[0] = 100d;
        line1[1] = 56d;
        line1[2] = 43d;
        line1[3] = 23d;
        line1[4] = 12d;
        pr2.sort(line);
        assertArrayEquals(line, line1);
    }

    @org.junit.jupiter.api.Test
    void binarySearch() {
        Double[] line = new Double[5];
        line[0] = 23d;
        line[1] = 12d;
        line[2] = 56d;
        line[3] = 43d;
        line[4] = 100d;
        pr2.sort(line);
        assertTrue(pr2.binarySearch(line, 0));
        assertTrue(pr2.binarySearch(line, 1));
        assertTrue(pr2.binarySearch(line, 2));
        assertTrue(pr2.binarySearch(line, 3));
        assertTrue(pr2.binarySearch(line, 4));
    }
}