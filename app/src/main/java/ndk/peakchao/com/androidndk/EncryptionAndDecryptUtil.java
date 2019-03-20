package ndk.peakchao.com.androidndk;

import android.util.Base64;
import android.util.Log;

import java.io.UnsupportedEncodingException;

/**
 * 加密解密工具类
 */
public class EncryptionAndDecryptUtil {

    static {
        System.loadLibrary("cc");
    }


    /**
     * 解密
     *
     * @param content
     * @return
     */
    public static native String Encryption(String content);

    /**
     * 解密
     *
     * @param content
     * @return
     */
    public static native String Decrypt(String content);


    public static String encrypt(String key, String content) {
        Log.e("TAG:encrypt", content);
        String encode = Base64.encodeToString((content + key).getBytes(), Base64.DEFAULT);
        return encode;
    }

    public static String decrypt(String key, String content) {
        Log.e("TAG:decrypt", content);
        byte[] encrypted = Base64.decode(content.getBytes(), Base64.DEFAULT);
        try {
            String str = new String(encrypted, "UTF-8");
            return str.substring(0, str.length() - key.length());
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return "";
    }

}
