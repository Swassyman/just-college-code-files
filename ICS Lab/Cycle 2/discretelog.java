import java.util.*;
class DiscreteLog{
	static long discretelog(int g, int h, int p){
		long n = (long)(Math.sqrt(p-1));
		HashMap<Long, Long> T = new HashMap<>();
		
		long value = 1;
		
		for(long i = 0; i<n; i++){
			T.put(value, i);
			value = (value * g) % p;
		} 
		
		long inv = 1;
		for(int i = 0; i<p; i++){
      if( (value * i) % p == 1) inv = i;
    }
    
    value = h;
      for(int i = 0; i<n; i++){
      if(T.containsKey(value)){
        long x = (i*n) + T.get(value);
        return x;
      }
      value = (value * inv) % p;
    }
    
    return 0;
	}
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		System.out.println("Enter a: ");
		int a = sc.nextInt();
		System.out.println("Enter b: ");
		int b = sc.nextInt();
		System.out.println("Enter c: ");
		int c = sc.nextInt();
    
    long log = discretelog(a, b, c);
		System.out.println("Discrete logarithm: " + (log == 0 ? "No solution" : log) );
	}
}
