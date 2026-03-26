import java.util.*;
class RailFence{
	static String encrypt(String plaintext, int key){
		if(key == 1) return plaintext;
		
		String[] rail = new String[key];
		
		for(int i = 0; i<key; i++){
			rail[i] = "";
		}
		
		int row = 0;
		int dir = 1;
		StringBuilder ciphertext = new StringBuilder();
		
		for(int i = 0; i<plaintext.length(); i++){
			rail[row] += plaintext.charAt(i);
			if(row == 0) dir = 1;
			else if (row == key-1) dir = -1;
			row += dir; 
		}
		
		for(int i = 0; i<key; i++){
			ciphertext.append(rail[i]);
		}
		return ciphertext.toString();
	}
	static String decrypt(String ciphertext, int key){
		if(key == 1) return ciphertext;
		
		int n = ciphertext.length();
		String[][] rail = new String[key][n];
		
		for(int i = 0; i<key; i++)
			for(int j = 0; j<n; j++)
				rail[i][j] = "*";
		
		int row = 0;
		int dir = 1;
		
		for(int col = 0; col<n; col++){
			rail[row][col] = "#";
			if(row == 0) dir = 1;
			else if(row == key-1) dir = -1;
			row += dir;
		}
		
		int index = 0;
		for(int i = 0; i<key; i++){
			for(int j = 0; j<n; j++){
				if(rail[i][j] == "#"){
					rail[i][j] = "" + ciphertext.charAt(index);
					index++;
				}
			}
		}
		
		row = 0;
		dir = 1;
		StringBuilder plaintext = new StringBuilder();
		
		for(int col = 0; col<n; col++){
			plaintext.append(rail[row][col]);
			if(row == 0) dir = 1;
			else if(row == key-1) dir = -1;
			row += dir;
		}
		
		return plaintext.toString();
	}
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter message: ");
		String plaintext = sc.next();
		
		System.out.println("Enter key: ");
		int key = sc.nextInt();
		
		String cipher = encrypt(plaintext, key);
		System.out.println("Encrypted text: " + cipher);
		
		String plain = decrypt(cipher, key);
		System.out.println("Decrypted text: " + plain);
	}
}
