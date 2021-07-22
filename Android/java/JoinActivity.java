package kr.co.dothome.sssoyoung.ex1;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;

public class JoinActivity extends AppCompatActivity {

    //blog -> https://jake217.tistory.com/17
    private EditText inputID;
    private EditText inputPW;
    private EditText inputPW2;
    private EditText inputNAME;
    private EditText inputMAIL;



    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_join);

        //blog
        inputID = (EditText) findViewById(R.id.InputID);
        inputPW = (EditText) findViewById(R.id.InputPW);
        inputPW2 = (EditText) findViewById(R.id.InputPW2);
        inputNAME = (EditText) findViewById(R.id.InputNAME);
        inputMAIL = (EditText) findViewById(R.id.InputMAIL);
    }

    public void gologin(View v){
        Intent intent = new Intent(getApplicationContext(),LoginActivity.class);
        startActivity(intent);
    }

    //blog
    public void insert(View v){
        String ID = inputID.getText().toString();
        String PW = inputPW.getText().toString();
        String PW2 = inputPW2.getText().toString();
        String NAME = inputNAME.getText().toString();
        String MAIL = inputMAIL.getText().toString();

        //비밀번호 일치 여부 확인 후 db 삽입 실행
        if (PW.equals(PW2)) {
            insertToDatabase(ID, PW, NAME, MAIL);

            //버튼클릭 후 login 이동
            Intent intent = new Intent(getApplicationContext(),LoginActivity.class);
            startActivity(intent);
        }else{
            //중복 경고 문구
            Toast.makeText (JoinActivity.this, "wrong pw", Toast.LENGTH_SHORT).show();
            onStart();
        }
    }

    //blog
    private void insertToDatabase(String ID, String PW, String NAME, String MAIL){
        class InsertData extends AsyncTask<String, Void, String>{
            ProgressDialog loading;
            @Override
            protected void onPreExecute(){
                super.onPreExecute();
                loading = ProgressDialog.show(JoinActivity.this, "Please Wait", null, true, true);
            }

            @Override
            protected void onPostExecute(String s){
                super.onPostExecute(s);
                loading.dismiss();
                Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
            }

            @Override
            protected String doInBackground(String... params){
                try{
                    String ID = (String) params[0];
                    String PW = (String) params[1];
                    String NAME = (String) params[2];
                    String MAIL = (String) params[3];

                    String link = "http://sssoyoung.dothome.co.kr/abc_join.php";
                    String data = URLEncoder.encode("ID","UTF-8")+"="+URLEncoder.encode(ID, "UTF-8");
                    data += "&" + URLEncoder.encode("PW", "UTF-8")+"="+URLEncoder.encode(PW, "UTF-8");
                    data += "&" + URLEncoder.encode("NAME", "UTF-8")+"="+URLEncoder.encode(NAME, "UTF-8");
                    data += "&" + URLEncoder.encode("MAIL", "UTF-8")+"="+URLEncoder.encode(MAIL, "UTF-8");

                    URL url = new URL(link);
                    URLConnection conn = url.openConnection();

                    conn.setDoOutput(true);
                    OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());

                    wr.write(data);
                    wr.flush();

                    BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));


                    StringBuilder sb = new StringBuilder();
                    String line = null;

                    //read server response
                    while((line = reader.readLine()) != null){
                        sb.append(line);
                        break;
                    }

                    return sb.toString();
                }catch (Exception e){
                    return new String("Exception:"+e.getMessage());
                }
            }
        }
        InsertData task = new InsertData();
        task.execute(ID, PW, NAME, MAIL);
    }
}