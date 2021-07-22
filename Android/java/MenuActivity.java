package kr.co.dothome.sssoyoung.ex1;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

public class MenuActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);
    }

    public void TopLogoBtn(View v){
        Intent intent = new Intent(getApplicationContext(),MainActivity.class);
        startActivity(intent);
    }
    public void GoRegister(View v){
        Intent intent = new Intent(getApplicationContext(),PotRegisterActivity.class);
        startActivity(intent);
    }
    public void GoManage(View v){
        Intent intent = new Intent(getApplicationContext(),PotManageActivity.class);
        startActivity(intent);
    }
    public void GoDelete(View v){
        Intent intent = new Intent(getApplicationContext(),PotDelActivity.class);
        startActivity(intent);
    }
}
