import java.util.*;
class Euclid{
	static long euclideanGCD(long a, long b){
		if(a == 0) return b;
		else if(a == b || b == 0) return a;
		
		return euclideanGCD(b, a%b);
	}
	static long extendedGCD(long a, long b, long s1, long s2, long t1, long t2){
		if(b == 0) return a;
		
		long q = (long)(a/b);
		long r = a%b;
		
		long s = s1 - (q * s2);
		
		long t = t1 - (q * t2); 
		
		System.out.printf("%d | %d | %d | %d | %d | %d | %d | %d | %d | %d\n", q, a, b, r, s1, s2, s, t1, t2, t);
		
		return extendedGCD(b, r, s2, s, t2, t);
		
	}
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		long a, b;
		System.out.println("Enter first number: ");
		a = sc.nextLong();
		
		System.out.println("Enter second number: ");
		b = sc.nextLong();
		
		int op;
		long GCD = 0;
		while(true){
			System.out.println("1 - Euclidean Method\n2- Extended Euclidean Method\n0 - Exit");
			op = sc.nextInt();
			switch(op){
			case 0: return;
			case 1:
				GCD = euclideanGCD(a, b);
				System.out.println("GCD: " + GCD);
				break;
			case 2:
				System.out.println("q | r1 | r2 | r | s1 | s2 | s | t1 | t2 | t");
				GCD = extendedGCD(a, b, 1, 0, 0, 1);
				System.out.println("GCD: " + GCD);
				break;
			default:
				System.out.println("INVALID INPUT");
			}
		}
	}
}

