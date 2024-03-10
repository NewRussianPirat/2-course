import java.io.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.text.*;
class pr1 {
    public static void main(String[] args) throws IOException {
        System.out.print("Enter x: ");
        String s;
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        s = in.readLine();
        BigDecimal x = new BigDecimal(s);
        System.out.print("Enter k: ");
        s = in.readLine();
        BigInteger k = new BigInteger(s);

        BigInteger decimal_places = k.add(new BigInteger("1"));
        BigDecimal res = Exp.exp(x, k);

        NumberFormat formatter = NumberFormat.getNumberInstance();
        formatter.setMaximumFractionDigits(decimal_places.intValue());
        System.out.println("exp(x) = " + formatter.format(res));
        System.out.println("exp(x) = " + formatter.format(Math.exp(x.doubleValue())));
    }
}
