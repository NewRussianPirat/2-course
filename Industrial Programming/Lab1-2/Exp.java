import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;

public class Exp {
    public static BigDecimal exp(BigDecimal x, BigInteger k) {
        BigDecimal e = new BigDecimal(1);
        for(int i = 0; i < k.intValue(); ++i) {
            e = e.divide(BigDecimal.valueOf(10), RoundingMode.DOWN);
        }

        BigDecimal res = new BigDecimal(1);
        BigDecimal slag = x;
        BigDecimal i = new BigDecimal(2);
        while (slag.abs().compareTo(e) > 0) {
            res = res.add(slag);
            slag = slag.multiply(x);
            slag = slag.divide(i, 10, RoundingMode.DOWN);
            i = i.add(BigDecimal.valueOf(1));
        }

        return res;
    }
}
