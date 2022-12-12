import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;

import static org.junit.jupiter.api.Assertions.*;

class pr1Test {
    @org.junit.jupiter.api.Test
    void exp() {
        assertEquals(new BigDecimal(6), Exp.exp(new BigDecimal(2), new BigInteger("0")).setScale(0, RoundingMode.DOWN));
        assertEquals(new BigDecimal("6.3"), Exp.exp(new BigDecimal(2), new BigInteger("0")).setScale(1, RoundingMode.DOWN));
        assertEquals(new BigDecimal(1), Exp.exp(new BigDecimal(0), new BigInteger("5")).setScale(0, RoundingMode.DOWN));
        assertEquals(new BigDecimal("20.085"), Exp.exp(new BigDecimal(3), new BigInteger("2")).setScale(3, RoundingMode.DOWN));
        assertEquals(new BigDecimal("2.1"), Exp.exp(new BigDecimal("1.1"), new BigInteger("0")).setScale(1, RoundingMode.DOWN));
    }
}