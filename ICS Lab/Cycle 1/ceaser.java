import java.util.*;

class CeaserCipher {
  public static String encrypt(String plaintext, int key){
    String ciphertext = "";
    for(int i = 0; i<plaintext.length(); i++){
			  if(plaintext.charAt(i) == ' ') ciphertext += " ";
			  else ciphertext += (char)((plaintext.charAt(i) + key - 97) % 26 + 97) ;
		  }
		return ciphertext;
  }
  public static String decrypt(String cipher, int key){
    String plaintext = "";
    for(int i = 0; i<cipher.length(); i++){
			  if(cipher.charAt(i) == ' ') plaintext += " ";
			  else plaintext += (char)((cipher.charAt(i) + (26 - key) - 97) % 26 + 97) ;
		  }
		return plaintext;
  }
  
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a message (in lowercase):");
		
		String plaintext = sc.nextLine();
		
		String cipher = encrypt(plaintext, 3);
		System.out.println("Cipher text: " + cipher);
    
    System.out.println("Decrypted text: " + decrypt(cipher, 3));
	}
}
