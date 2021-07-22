package kr.co.dothome.sssoyoung.ex1;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    public void LoginBtn(View v){
        Intent intent = new Intent(getApplicationContext(),LoginActivity.class);
        startActivity(intent);
    }

    public void RegBtn(View v){
        Intent intent = new Intent(getApplicationContext(),JoinActivity.class);
        startActivity(intent);
    }
        //토스트 예제 -> Toast.makeText (액티비티.this, "메시지", Toast.LENGTH_SHORT(잠깐)/LONG(길게)).show();
        //Toast.makeText (MainActivity.this, "im toast", Toast.LENGTH_SHORT).show();

}
