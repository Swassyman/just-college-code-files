import java.util.*;

class AdditiveCipher {
	public static void main(String[] args){
		String ciphertext = "";
		
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a key");
		int key = sc.nextInt();
		sc.nextLine();
		
		System.out.println("Enter a message (in lowercase):");
		String plaintext = sc.nextLine();
		
		System.out.println("Enter an operation");
		String op = sc.next();
		
		switch(op) {
			case "+":
				for(int i = 0; i<plaintext.length(); i++){
					if(plaintext.charAt(i) == ' ') ciphertext += " ";
					else ciphertext += (char)((plaintext.charAt(i) + key - 97) % 26 + 97) ;
				}
				break;
			case "-":
				for(int i = 0; i<plaintext.length(); i++){
					if(plaintext.charAt(i) == ' ') ciphertext += " ";
					else ciphertext += (char)((plaintext.charAt(i) + (26 - key) - 97) % 26 + 97) ;
				}
				break;
		}
		System.out.println(ciphertext);
		
		// todo: Decryption
	}
}
