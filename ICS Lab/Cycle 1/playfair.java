import java.util.*;
class Playfair{
  static char[][] matrix = new char[5][5];
  public static String cleanKey(String msg, String key){
    LinkedHashSet<Character> set = new LinkedHashSet<>();
    String newKey = "";
    for(int i = 0; i<key.length(); i++){
      set.add(key.charAt(i));
    }
    for(char element: set){
      newKey += element;
    }
    return newKey;
  }
  public static void generateCipherKey(String key){
    Set<Character> set = new HashSet<>();
    for(int i = 0; i<key.length(); i++){
      if(key.charAt(i)=='J') continue;
      set.add(key.charAt(i));
    }
    String tempkey = new String(key);
    for(int i = 0; i<26; i++){
      char ch = (char)(i+65);
      if(ch=='J') continue;
      if(!set.contains(ch)) tempkey += ch;
    }
    int index = 0;
    for(int i = 0; i<5; i++){
      for(int j = 0; j<5; j++){
        matrix[i][j] = tempkey.charAt(index++);
      }
    }
  }
  public static String formatPlainText(String msg){
    String tempmsg = "";
    for(int i = 0; i<msg.length(); i++){
      if(msg.charAt(i) == 'J') tempmsg += 'i';
      else tempmsg += msg.charAt(i);
    }
    for(int i = 0; i<tempmsg.length(); i+=2){
      if(tempmsg.charAt(i) == tempmsg.charAt(i+1)){
        tempmsg = tempmsg.substring(0, i+1) + 'X' + tempmsg.substring(i+1);
      }
    }
    if(tempmsg.length() % 2 != 0) tempmsg += 'X';
    return tempmsg;
  }
  public static String[] formPairs(String msg){
    int len = msg.length()/2;
    String[] pairs = new String[len];
    int count = 0;
    for(int i = 0; i<len; i++){
      pairs[i] = msg.substring(count, count+=2);
    }
    return pairs;
  }
  public static int[] getCharPos(char ch){
    int[] pos = new int[2];
    for(int i = 0; i<5; i++){
      for(int j = 0; j<5; j++){
        if(matrix[i][j] == ch){
          pos[0] = i;
          pos[1] = j;
        }
      }
    }
    return pos;
  }
  public static String encrypt(String msg){
    String formattedMessage = formatPlainText(msg);
    String[] msgPairs = formPairs(formattedMessage);
    String cipher = "";
    
    for(int i = 0; i<msgPairs.length; i++){
      char ch1 = msgPairs[i].charAt(0);
      char ch2 = msgPairs[i].charAt(1);
      int[] pos1 = getCharPos(ch1);
      int[] pos2 = getCharPos(ch2);
      
      if(pos1[0] == pos2[0]) {
        pos1[1] = (pos1[1] + 1) % 5;
        pos2[1] = (pos2[1] + 1) % 5;
      }
      else if(pos1[1] == pos2[1]){
        pos1[0] = (pos1[0] + 1) % 5;
        pos2[0] = (pos2[0] + 1) % 5;
      }
      else {
        int temp = pos1[1];
        pos1[1] = pos2[1];
        pos2[1] = temp;
      }
      cipher += matrix[pos1[0]][pos1[1]] + "" + matrix[pos2[0]][pos2[1]];
    }
    return cipher;
  }
  public static String decrypt(String cipher){
    String[] msgPairs = formPairs(cipher);
    String message = "";
    
    for(int i = 0; i<msgPairs.length; i++){
      char ch1 = msgPairs[i].charAt(0);
      char ch2 = msgPairs[i].charAt(1);
      int[] pos1 = getCharPos(ch1);
      int[] pos2 = getCharPos(ch2);
      
      if(pos1[0] == pos2[0]) {
        pos1[1] = (pos1[1] - 1) % 5;
        pos2[1] = (pos2[1] - 1) % 5;
      }
      else if(pos1[1] == pos2[1]){
        pos1[0] = (pos1[0] - 1) % 5;
        pos2[0] = (pos2[0] - 1) % 5;
      }
      else {
        int temp = pos1[1];
        pos1[1] = pos2[1];
        pos2[1] = temp;
      }
      message += matrix[pos1[0]][pos1[1]] + "" + matrix[pos2[0]][pos2[1]];
    }
    return message;
  }
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    System.out.println("Enter a message: ");
    String msg = sc.nextLine();
    System.out.println("Enter a key: ");
    String key = sc.next();
    
    key = cleanKey(msg, key);
    generateCipherKey(key);
    String cipher = encrypt(msg);
    System.out.println("Encrypted message: " + cipher);
    String plain = decrypt(cipher);
    System.out.println("Decrypted message: " + plain);
  }
}
