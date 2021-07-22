#include <Ethernet.h>
#include <TFT.h>
#include <SPI.h>
#include <DHT.h>

#define cs 10
#define dc 9
#define rst 8

DHT dht(2, DHT11);
TFT TFTscreen = TFT(cs, dc, rst);

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF7, 0x47}; // pc와 연결된 아두이노의 mac address
char server[] = "sssoyoung.dothome.co.kr";
char ctem[5];
char chum[5];
char csoit[5];
char csoim[5];
char csoiw[5];

IPAddress ip(192,168,0,100);
EthernetClient client;

void setup(){
  Serial.begin(9600); // 시리얼 통신을 위한 초기화, 통신 포트 OPEN 대기
  pinMode(A2, INPUT);
  analogReference(INTERNAL);

  TFTscreen.begin();
  TFTscreen.background(0, 0, 0); 
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(2);
  
  while(!Serial){
    ; // 시리얼 포트 연결 대기(레오나르도 보드에서만 사용
  }
  if(Ethernet.begin(mac) == 0){ // 이더넷 연결 시작
    Serial.println("DHCP fail"); // DHCP를 이용하여 이더넷 구성하는데 실패하였습니다.
    Ethernet.begin(mac, ip); // ip 주소 할당 받고, 웹 서버 서비스 시작
  }

}

void loop(){
  analog();
  //tfts();
  //ether();
  Serial.println("");
  delay(3000); //3초 주기
}

void analog(){
  
  //int val = analogRead(A2);
  int tem = dht.readTemperature();
  int hum = dht.readHumidity();
  int soiw = analogRead(A0);
  soiw = map(soiw, 0, 1023, 0, 100);
  int soit = analogRead(A5)/9.31; //soil temp
  int soim1 = analogRead(A3); //토양수분센서 전하값
  int soim2 = map(soim1, 0, 1023, 0, 100); //100단위로 환산한 값
  
  //String light = ""; // string으로 바꿔줌
//  if(val<500){
//    light="suuuuuny";
//  }else{
//    light = "daaaark";
//  }

  tfts(tem, hum, soit, soim2, soiw);
  //ether(val, tem, hum, soit, soim1, soim2, light, soiw);
}
void tfts(int tem, int hum, int soit, int soim2, int soiw){ // tft screen code
  itoa(tem, ctem, 10);
  itoa(hum, chum, 10);
  itoa(soit, csoit, 10);
  itoa(soim2, csoim, 10);
  itoa(soiw, csoiw, 10);

  Serial.print("temperature: ");
  Serial.println(tem); // 온도 출력
  Serial.print("humidity: ");
  Serial.println(hum); // 습도 출력
  Serial.print("water: ");
  Serial.println(soiw); // 수위 출력
  Serial.print("soil temperature: ");
  Serial.println(soit); // 습도 출력
  Serial.print("soil moisture: ");
  Serial.println(soim2);
  Serial.print("now light: ");
  //Serial.println(val); // 습도 출력

  TFTscreen.stroke(255, 255, 255); 

  if(tem<19){ //밝을때
    TFTscreen.text("temp:", 0, 0);
    TFTscreen.text(ctem, 70, 0);
    TFTscreen.text("humi:", 0, 20);
    TFTscreen.text(chum, 70, 20);
    TFTscreen.text("soil tem:", 0, 40);
    TFTscreen.text(csoit, 120, 40);
    TFTscreen.text("soil moi:", 0, 60);
    TFTscreen.text(csoim, 120, 60);
    TFTscreen.text("water:", 0, 80);
    TFTscreen.text(csoiw, 70, 80);
    TFTscreen.text("Light", 0, 100);
    //Serial.println(light);
    delay(2000); // 스크린 표시 시간 2초
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text("temp:", 0, 0);
    TFTscreen.text(ctem, 70, 0);
    TFTscreen.text("humi:", 0, 20);
    TFTscreen.text(chum, 70, 20);
    TFTscreen.text("soil tem:", 0, 40);
    TFTscreen.text(csoit, 120, 40);
    TFTscreen.text("soil moi:", 0, 60);
    TFTscreen.text(csoim, 120, 60);
    TFTscreen.text("water:", 0, 80);
    TFTscreen.text(csoiw, 70, 80);
    TFTscreen.text("Light", 0, 100);
  }
  else{ //어두울 때
    TFTscreen.text("temp:", 0, 0);
    TFTscreen.text(ctem, 70, 0);
    TFTscreen.text("humi:", 0, 20);
    TFTscreen.text(chum, 70, 20);
    TFTscreen.text("soil tem:", 0, 40);
    TFTscreen.text(csoit, 120, 40);
    TFTscreen.text("soil moi:", 0, 60);
    TFTscreen.text(csoim, 120, 60);
    TFTscreen.text("water:", 0, 80);
    TFTscreen.text(csoiw, 70, 80);
    TFTscreen.text("Dark", 0, 100);
    //Serial.println(light);
    delay(2000);
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.text("temp:", 0, 0);
    TFTscreen.text(ctem, 70, 0);
    TFTscreen.text("humi:", 0, 20);
    TFTscreen.text(chum, 70, 20);
    TFTscreen.text("soil tem:", 0, 40);
    TFTscreen.text(csoit, 120, 40);
    TFTscreen.text("soil moi:", 0, 60);
    TFTscreen.text(csoim, 120, 60);
    TFTscreen.text("water:", 0, 80);
    TFTscreen.text(csoiw, 70, 80);
    TFTscreen.text("Dark", 0, 100);
  }
  //delay(2000);
}
//
//void ether(int val, int tem, int hum, int soit, int soim1, int soim2, String light, int soiw){
//  if(client.connect(server,80)){
//    Serial.println("connected");
//    client.print("GET /b.php?temp=");
//    client.print(tem);
//    client.print("&humi=");
//    client.print(hum);
//    client.print("&light=");
//    client.print(light);
//    client.print("&lightval=");
//    client.print(val);
//    client.print("&soit=");
//    client.print(soit);
//    client.print("&soim1=");
//    client.print(soim1);
//    client.print("&soim2=");
//    client.print(soim2);
//    client.print("&soiw=");
//    client.print(soiw);
//    client.println(" HTTP/1.1");
//    client.println("Host: sssoyoung.dothome.co.kr");
//    client.println("Connection: close");
//    client.println();
//  }
//}
