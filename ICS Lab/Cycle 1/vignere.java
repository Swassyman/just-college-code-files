import java.util.Scanner;
class VignereCipher {
	static String GenerateKey(String plaintext, String key){
		key = key.toUpperCase();
		plaintext = plaintext.toUpperCase();
		StringBuilder fullkey = new StringBuilder();
		int j = 0;
		
		for(int i = 0; i<plaintext.length(); i++){
			fullkey.append(key.charAt(j % key.length()));
			j++;
		}
		return fullkey.toString();
	}
	static String encrypt(String plaintext, String key){
		plaintext = plaintext.toUpperCase();
		String keyStream = GenerateKey(plaintext, key);
		StringBuilder ciphertext = new StringBuilder();
		
		for(int i = 0; i<plaintext.length(); i++){
			int p = plaintext.charAt(i) - 'A';
			int k = keyStream.charAt(i) - 'A';
			int c = (p + k) % 26;
			
			ciphertext.append((char)(c + 'A'));
		}
		return ciphertext.toString();
	}
	static String decrypt(String ciphertext, String key){
		ciphertext = ciphertext.toUpperCase();
		String keyStream = GenerateKey(ciphertext, key);
		StringBuilder plaintext = new StringBuilder();
		
		for(int i = 0; i<ciphertext.length(); i++){
			int c = ciphertext.charAt(i) - 'A';
			int k = keyStream.charAt(i) - 'A';
			int p = (c - k + 26) % 26;
			
			plaintext.append((char)(p + 'A'));
		}
		return plaintext.toString();
	}
	public static void main(String[] args){
		Scanner sc  = new Scanner(System.in);
		System.out.println("Enter plaintext: ");
		String plaintext = sc.next();
		
		System.out.println("Enter key: ");
		String key = sc.next();
		
		String cipher = encrypt(plaintext, key);
		System.out.println("Encrypted message: " + cipher);
		
		String plain = decrypt(cipher, key);
		System.out.println("Decrypted message: " + plain);
	}
}
