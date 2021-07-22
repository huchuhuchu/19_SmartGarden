package kr.co.dothome.sssoyoung.ex1;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;

public class FindActivity extends AppCompatActivity {

    //변수 선언
    Button btn_idfind;
    Button btn_pwfind;
    LinearLayout layout4ID;
    LinearLayout layout4PW;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_find);
        setup();
    }

    //메인로고버튼
    public void TopLogoBtn(View v){
        Intent intent = new Intent(getApplicationContext(),MainActivity.class);
        startActivity(intent);
    }

    //셋팅
    private void setup() {
        btn_idfind = (Button) findViewById(R.id.btn_idfind);
        btn_pwfind = (Button) findViewById(R.id.btn_pwfind);
        layout4ID = (LinearLayout) findViewById(R.id.layout4ID);
        layout4PW = (LinearLayout) findViewById(R.id.layout4PW);


        btn_idfind.setOnClickListener(myListener);
        btn_pwfind.setOnClickListener(myListener);
    }

    //함수
    View.OnClickListener myListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.btn_idfind:  //idfind버튼 클릭시 id 보이고 pw 사라짐
                    layout4ID.setVisibility(View.VISIBLE);
                    layout4PW.setVisibility(View.GONE);
                    break;

                case R.id.btn_pwfind:  //pwfind버튼 클릭시 id 사라지고 pw 보임
                    layout4ID.setVisibility(View.GONE);
                    layout4PW.setVisibility(View.VISIBLE);
                    break;
            }
        }
    };

}
