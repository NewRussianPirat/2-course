import java.util.ArrayList;
import java.util.TreeMap;

import static org.junit.jupiter.api.Assertions.*;

class pr5Test {

    @org.junit.jupiter.api.Test
    void func() {
        ArrayList<ArrayList<Integer>> matr = new ArrayList<>();
        matr.add(new ArrayList<>());
        matr.get(0).add(1);
        assertEquals(new Pair(0, 0), pr5.Func(0, 0, matr, new TreeMap<>()));
        matr.get(0).add(1);
        matr.add(new ArrayList<>());
        matr.get(1).add(1);
        matr.get(1).add(1);
        assertEquals(new Pair(1, 1), pr5.Func(0, 0, matr, new TreeMap<>()));
        matr.get(0).add(0);
        matr.get(1).add(0);
        assertEquals(new Pair(1, 1), pr5.Func(0, 0, matr, new TreeMap<>()));
        assertEquals(new Pair(1, 2), pr5.Func(0, 2, matr, new TreeMap<>()));
        assertEquals(new Pair(1, 2), pr5.Func(1, 2, matr, new TreeMap<>()));
        matr.add(new ArrayList<>());
        matr.get(2).add(1);
        matr.get(2).add(1);
        matr.get(2).add(1);
        assertEquals(new Pair(2, 1), pr5.Func(0, 0, matr, new TreeMap<>()));
        assertEquals(new Pair(2, 2), pr5.Func(2, 0, matr, new TreeMap<>()));
        matr.add(new ArrayList<>());
        matr.get(3).add(0);
        matr.get(3).add(0);
        matr.get(3).add(0);
        assertEquals(new Pair(3, 2), pr5.Func(3, 0, matr, new TreeMap<>()));
        assertEquals(new Pair(2, 1), pr5.Func(0, 0, matr, new TreeMap<>()));
    }
}