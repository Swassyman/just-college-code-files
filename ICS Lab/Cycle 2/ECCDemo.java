import java.math.BigInteger;

class ECPoint {
    BigInteger x, y;
    boolean isInfinity;

    public ECPoint(){
        this.isInfinity = true;
    }

    public ECPoint(BigInteger x, BigInteger y){
        this.x = x;
        this.y = y;
        this.isInfinity = false;
    }
}

class EllipticCurve {
    BigInteger a, b, p;

    public EllipticCurve(BigInteger a, BigInteger b, BigInteger p){
        this.a = a;
        this.b = b;
        this.p = p;
    }

    private BigInteger modInverse(BigInteger k){
        return k.modInverse(p);
    }

    public ECPoint add(ECPoint P, ECPoint Q){
        if(P.isInfinity) return Q;
        if(Q.isInfinity) return P;

        if(P.x.equals(Q.x) && P.y.add(Q.y).mod(p).equals(BigInteger.ZERO)){
            return new ECPoint();
        }

        BigInteger numerator = Q.y.subtract(P.y);
        BigInteger denominator = Q.x.subtract(P.x).modInverse(p);
        BigInteger lambda = numerator.multiply(denominator).mod(p);

        BigInteger xr = lambda.pow(2).subtract(P.x).subtract(Q.x).mod(p);
        BigInteger yr = lambda.multiply(P.x.subtract(xr)).subtract(P.y).mod(p);

        return new ECPoint(xr, yr);
    }
}

public class ECCDemo {
    public static void main(String[] args) {

        BigInteger a = BigInteger.valueOf(2);
        BigInteger b = BigInteger.valueOf(3);
        BigInteger p = BigInteger.valueOf(97);

        EllipticCurve curve = new EllipticCurve(a, b, p);

        ECPoint P = new ECPoint(BigInteger.valueOf(3), BigInteger.valueOf(6));
        ECPoint Q = new ECPoint(BigInteger.valueOf(80), BigInteger.valueOf(10));

        ECPoint R = curve.add(P, Q);

        System.out.println("R = (" + R.x + ", " + R.y + ")");
    }
}
