import java.util.Arrays;

public class DES {
    static int[] IP = {1, 5, 2, 0, 3, 7, 4, 6};
    static int[] FP = {3, 0, 2, 4, 6, 1, 7, 5};
    static int[] KEY = {1, 0, 1, 1};

    static int[][] generateSubkeys() {
        int[][] subkeys = new int[16][4];

        for (int i = 0; i < 16; i++) {
            subkeys[i] = new int[4];
            for (int j = 0; j < 4; j++) {
                subkeys[i][j] = (KEY[(j + i) % 4]);
            }
        }
        return subkeys;
    }

    static int[] charToBits(char c) {
        int[] bits = new int[8];
        int val = (int) c;

        for (int i = 7; i >= 0; i--) {
            bits[i] = val % 2;
            val /= 2;
        }
        return bits;
    }

    static String bitsToHex(int[] bits) {
        int value = 0;
        for (int i = 0; i < 8; i++) {
            value = value * 2 + bits[i];
        }
        return String.format("%02X", value);
    }

    static int[] permute(int[] input, int[] table) {
        int[] output = new int[table.length];
        for (int i = 0; i < table.length; i++) {
            output[i] = input[table[i]];
        }
        return output;
    }

    static int[] xor(int[] a, int[] b) {
        int[] result = new int[a.length];
        for (int i = 0; i < a.length; i++) {
            result[i] = a[i] ^ b[i];
        }
        return result;
    }

    static int[] f(int[] right, int[] key) {
        return xor(right, key);
    }

    static int[] encrypt(int[] plaintext) {
        plaintext = permute(plaintext, IP);

        int[] left = Arrays.copyOfRange(plaintext, 0, 4);
        int[] right = Arrays.copyOfRange(plaintext, 4, 8);

        int[][] subkeys = generateSubkeys();

        for (int i = 0; i < 16; i++) {
            int[] temp = right;
            right = xor(left, f(right, subkeys[i]));
            left = temp;
        }

        int[] combined = new int[8];
        System.arraycopy(left, 0, combined, 0, 4);
        System.arraycopy(right, 0, combined, 4, 4);

        return permute(combined, FP);
    }

    static String encryptString(String text) {
        StringBuilder result = new StringBuilder();

        for (char c : text.toCharArray()) {
            int[] bits = charToBits(c);
            int[] encrypted = encrypt(bits);
            result.append(bitsToHex(encrypted)).append("");
        }
        return result.toString();
    }

    public static void main(String[] args) {
        String text = "Hello, World!";

        String encrypted = encryptString(text);

        System.out.println("Original : " + text);
        System.out.println("Encrypted: " + encrypted);
    }
}