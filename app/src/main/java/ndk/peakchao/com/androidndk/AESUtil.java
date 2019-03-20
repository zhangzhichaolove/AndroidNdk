package ndk.peakchao.com.androidndk;

public class AESUtil {

    static {
        System.loadLibrary("cc");
    }

    public native String encrypt(String plainText, String key);
    public native String decrypt(String cipherText, String key);

}
