package ndk.peakchao.com.androidndk;

public class JniUtil {

    static {
        System.loadLibrary("cc");
    }

    public static native String getToastString();

}
