import java.util.Scanner;

class HillCipher{
	public static int gcd(int a, int b){
		if(a == b) return a;
		else if (a > b) return gcd(a-b, b);
		else return gcd(a, b-a);
	}
	public static boolean validateKey(int matrix[][]){
		int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
		return gcd(det, 26) == 1;
	}
	public static String prepareText(String plaintext){
		plaintext = plaintext.toUpperCase();
		if(plaintext.length() % 2 != 0) plaintext += 'X';
		return plaintext;
	}
	public static int[][] inverseKey(int K[][]){
		int det = (K[0][0] * K[1][1] - K[0][1] * K[1][0]) % 26;
		int detInv = 0;
		for(int i = 0; i<26; i++){
      			if( (det * i) % 26 == 1) {
      				detInv = i;
      				break;
      			}
    		}
    		int KInv[][] = new int[2][2];
    		KInv[1][1] = (K[0][0] * detInv) % 26;
    		KInv[0][1] = (-K[0][1] * detInv + 26) % 26;
    		KInv[1][0] = (-K[1][0] * detInv + 26) % 26;
    		KInv[0][0] = (K[1][1] * detInv) % 26;
    		
    		for(int i = 0; i<2; i++){
    			for(int j = 0; j<2; j++){
    				System.out.print(KInv[i][j] + " ");
    			}
    			System.out.println();
    		}
    		return KInv;
	}
	public static String encrypt(String plaintext, int K[][]){
		if(!validateKey(K)) return "INVALID KEY";
		plaintext = prepareText(plaintext);
		StringBuilder ciphertext = new StringBuilder();
		
		for(int i = 0; i<plaintext.length() - 1; i+=2){
			int p1 = plaintext.charAt(i) - 'A';
			int p2 = plaintext.charAt(i+1) - 'A';
			 
			int c1 = (K[0][0] * p1 + K[0][1] * p2) % 26;
			int c2 = (K[1][0] * p1 + K[1][1] * p2) % 26;
			
			ciphertext.append((char)(c1 + 'A'));
			ciphertext.append((char)(c2 + 'A'));
		}
		return ciphertext.toString();
	}
	public static String decrypt(String ciphertext, int K[][]){
		if(!validateKey(K)) return "INVALID KEY";
		int[][] KInv = inverseKey(K);
		StringBuilder plaintext = new StringBuilder();
		
		for(int i = 0; i<ciphertext.length() - 1; i+=2){
			int c1 = ciphertext.charAt(i) - 'A';
			int c2 = ciphertext.charAt(i+1) - 'A';
			
			int p1 = (KInv[0][0] * c1 + KInv[0][1] * c2) % 26;
			int p2 = (KInv[1][0] * c1 + KInv[1][1] * c2) % 26;
			
			plaintext.append((char)(p1 + 'A'));
			plaintext.append((char)(p2 + 'A'));
		}
		return plaintext.toString();
	}
	public static void main(String[] args){
		Scanner sc  = new Scanner(System.in);
		System.out.println("Enter plaintext: ");
		String plaintext = sc.next();
		
		int[][] K = new int[2][2];
		System.out.println("Enter key: ");
		for(int i = 0; i<2; i++){
			for(int j = 0; j<2; j++){
				K[i][j] = sc.nextInt();
			}
		}
		
		String cipher = encrypt(plaintext, K);
		System.out.println("Encrypted message: " + cipher);
		
		String plain = decrypt(cipher, K);
		System.out.println("Decrypted message: " + plain);
		
	}
}
