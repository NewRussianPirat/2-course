import java.util.Comparator;

public class Pair implements Comparable<Pair>, Comparator<Pair> {
    int i;
    int j;

    public Pair(int i1, int j1) {
        i = i1;
        j = j1;
    }

    @Override
    public int compareTo(Pair p) {
        if (i == p.i && j == p.j) return 0;
        else if (i > p.i) return 1;
        else if (i == p.i) return j - p.j;
        else return -1;
    }

    @Override
    public boolean equals(Object o) {
        Pair pair = (Pair) o;
        return i == pair.i && j == pair.j;
    }

    @Override
    public String toString() {
        return new String("[" + i + ", " + j + "]");
    }

    @Override
    public int compare(Pair pair1, Pair pair2) {
        if (pair1.i == pair2.i && pair1.j == pair2.j) return 0;
        else if (pair1.i > pair2.i) return 1;
        else if (pair1.i == pair2.i) return pair1.j - pair2.j;
        else return -1;
    }
}
