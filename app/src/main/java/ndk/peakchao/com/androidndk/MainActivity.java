package ndk.peakchao.com.androidndk;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(JniUtil.getToastString());

        Toast.makeText(this, JniUtil.getToastString(), Toast.LENGTH_LONG).show();
        String content = "这是待加密的字符串哦, i love you !";
//        Log.e("TAG", content);
        Log.e("TAG", EncryptionAndDecryptUtil.Encryption(content));
        Log.e("TAG", EncryptionAndDecryptUtil.Decrypt(EncryptionAndDecryptUtil.Encryption(content)));
    }


}
