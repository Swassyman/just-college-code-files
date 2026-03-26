import java.util.*;

class AffineCipher {
  public static String encrypt(String msg, int key1, int key2){
    String cipher = "";
    for(int i = 0; i<msg.length(); i++){
      if(msg.charAt(i) != ' '){
        cipher += (char)((((key1 * (msg.charAt(i) - 'a')) + key2) % 26) + 'a');
      } else {
        cipher += ' ';
      }
    }
    return cipher;
  }
  public static String decrypt(String cipher, int key1, int key2){
    String plain = "";
    int key1Inverse= 0;
    for(int i = 0; i<26; i++){
      if( (key1 * i) % 26 == 1) key1Inverse = i;
    }
    for(int i = 0; i<cipher.length(); i++){
      if(cipher.charAt(i)!=' '){
        plain += (char)(((key1Inverse * (cipher.charAt(i) - 'a' - key2 + 26)) % 26) + 'a');
      }
      else plain += ' ';
    }
    return plain;
  }
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    
    System.out.println("Enter a message: ");
    String msg = sc.nextLine();
    
    System.out.println("Enter key 1: ");
    int key1 = sc.nextInt();
    
    System.out.println("Enter key 2: ");
    int key2 = sc.nextInt();
    
    String cipher = encrypt(msg, key1, key2);
    System.out.println("Cipher text: " + cipher);
    
    System.out.println("Decrypted text: " + decrypt(cipher, key1, key2));
  }
}
