import java.util.*;
class Columnar{
	static int[] generateKey(char[] key){
		char[] sortedKey = Arrays.copyOf(key, key.length);
		Arrays.sort(sortedKey);
		int[] keyValue = new int[key.length];
		
		for(int i = 0; i<sortedKey.length; i++){
			for(int j = 0; j<key.length; j++){
				if(key[j] == sortedKey[i]){
					keyValue[j] = i+1;
				}
			}
		}
		
		return keyValue;
	}
	static int findPos(int[] key, int num){
		for(int i = 0; i<key.length; i++){
			if(num == key[i]) return i+1;
		}
		return 0;
	}
	static String encrypt(String plaintext, String keyed){
		int[] key = generateKey(keyed.toCharArray());
		int k = key.length;
		int n = plaintext.length();
		
		while(n%k != 0){
			plaintext += "x";
			n++;
		}
		
		int rows = n/k;
		
		String[][] M  = new String[rows][k];
		int index = 0;
		
		for(int i = 0; i<rows; i++){
			for(int j = 0; j<k; j++){
				M[i][j] = "" + plaintext.charAt(index);
				index++;
			}
		}
		
		StringBuilder ciphertext = new StringBuilder();
		
		for(int num = 1; num<=k; num++){
			int col = findPos(key, num);
			for(int i = 0; i<rows; i++){
				ciphertext.append(M[i][col-1]);
			}
		}
		
		return ciphertext.toString();
	}
	static String decrypt(String ciphertext, String keyed){
		int[] key = generateKey(keyed.toCharArray());
		int k = key.length;
		int n = ciphertext.length();
		int rows = n/k;
		
		String[][] M = new String[rows][k];
		int index = 0;
		
		for(int num = 1; num <= k; num++){
			int col = findPos(key, num);
			for(int i = 0; i<rows; i++){
				M[i][col-1] = "" + ciphertext.charAt(index);
				index++;
			}
		}
		
		StringBuilder plaintext = new StringBuilder();
		for(int i = 0; i<rows; i++){
			for(int j = 0; j<k; j++){
				if(M[i][j].equals("x")) plaintext.append("");
				else plaintext.append(M[i][j]);
			}
		}
		
		return plaintext.toString();
	}
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter message: ");
		String plaintext = sc.next();
		
		System.out.println("Enter key: ");
		String key = sc.next();
		
		String cipher = encrypt(plaintext, key);
		System.out.println("Encrypted text: " + cipher);
		
		String plain = decrypt(cipher, key);
		System.out.println("Decrypted text: " + plain);
	}
}
