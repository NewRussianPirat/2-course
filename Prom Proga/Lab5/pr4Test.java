import static org.junit.jupiter.api.Assertions.*;

class pr4Test {

    @org.junit.jupiter.api.Test
    void isDate() {
        assertTrue(pr4.isDate("01/01/12"));
        assertTrue(pr4.isDate("59:59:23"));
        assertTrue(pr4.isDate("00-00-24"));
        assertFalse(pr4.isDate("61/01/12"));
        assertFalse(pr4.isDate("01/61/12"));
        assertFalse(pr4.isDate("01/33/25"));
        assertFalse(pr4.isDate("1/33/22"));
        assertFalse(pr4.isDate("59/59-23"));
        assertFalse(pr4.isDate("19/09-23"));
        assertFalse(pr4.isDate("00-00-223"));
        assertFalse(pr4.isDate("00.00.00"));
        assertFalse(pr4.isDate("60/60/23"));
    }
}