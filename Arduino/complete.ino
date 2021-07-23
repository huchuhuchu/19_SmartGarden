#include <Ethernet.h>
#include <DHT.h>
// #include <TFT.h>
// #include <SPI.h>
//
   #define DHTPIN 5
   #define DHTTYPE DHT11
   DHT dht(5, DHT11);

// #define cs 10
// #define dc 9
// #define rst 8

// TFT TFTscreen = TFT(cs, dc, rst);
//
// char ctemp[5];
// char chumi[5];
// char csoim[5];

byte mac[] = {0x18, 0x56, 0x80, 0x20, 0xF7, 0xDD};
char server[] = "#";    //서버 도메인
IPAddress ip(192, 168, 0, 101);
EthernetClient client;

void setup(){
  Serial.begin(9600);

  // TFTscreen.begin();
  // TFTscreen.background(0,0,0);  //검은배경
  // TFTscreen.stroke(255,255,255);  //흰글씨
  // TFTscreen.setTextSize(2);
  // TFTscreen.text("start\n", 0, 0);

  if(Ethernet.begin(mac)==0){
    Serial.println("DHCP fail");
    Ethernet.begin(mac, ip);
  }
}

void loop(){  //변수 주루ㅈㄹ루루륵
  int temp = dht.readTemperature();
  int humi = dht.readHumidity();

  int light_val = analogRead(A0);
  String light ="";
  if(light_val<500){light = "light";}else{light = "dark";}

  int wlevel = map(analogRead(A1), 0, 500, 1, 5);
  int soim1 = analogRead(A2);
  int soim2 = map(soim1, 0, 500, 0, 100);

  serial_print(temp, humi, light_val, light, wlevel, soim1, soim2);
  // tfts(temp, humi, light_val, wlevel, soim2);
  ethernet(temp, humi, light_val, light, wlevel, soim1, soim2);
  delay(1000);
}

void serial_print(int temp, int humi, int light_val, String light, int wlevel, int soim1, int soim2){
  Serial.println("----------");
  Serial.print("temp: ");
  Serial.print(temp);
  Serial.print("'C | humi: ");
  Serial.print(humi);
  Serial.print("% | light state: ");
  Serial.print(light);
  Serial.print("(");
  Serial.print(light_val);
  Serial.print(")");
  Serial.print(" | soil moisture: ");
  Serial.print(soim2);
  Serial.print("%(");
  Serial.print(soim1);
  Serial.print(") | water level: ");
  Serial.print(wlevel);
  Serial.print("/5\n");

}

// lcd 고장남~~~ 새로사자
// void tfts(int temp, int humi, int light_val, int wlevel, int soim2){
//   itoa(temp, ctemp, 10);
//   itoa(humi, chumi, 10);
//   itoa(soim2, csoim, 10);
//
//   TFTscreen.text("temp: ", 0, 0);
//   TFTscreen.text(ctemp, 70, 0);
//   TFTscreen.text("humi: ", 0, 20);
//   TFTscreen.text(chumi, 70, 20);
//   TFTscreen.text("soil mois: ", 0, 40);
//   TFTscreen.text(csoim, 120, 40);
//
//   if(wlevel<2){
//     TFTscreen.text("water level: no water", 0, 60);
//   }else if(wlevel>4){
//     TFTscreen.text("water level: much water", 0, 60);
//   }else{
//     TFTscreen.text("water level: water tank ok", 0, 60);
//   }
//
//   if(light_val<500){
//     TFTscreen.text("light state: light", 0, 80);
//   }else{
//     TFTscreen.text("light state: dark", 0, 80);
//   }
// }

void ethernet(int temp, int humi, int light_val, String light, int wlevel, int soim1, int soim2){
  if(client.connect(server,80)){
    Serial.println("connected");
    client.print("GET /b.php?temp=");
    client.print(temp);
    client.print("&humi=");
    client.print(humi);
    client.print("&light=");
    client.print(light);
    client.print("&lightval=");
    client.print(light_val);
    client.print("&soim1=");
    client.print(soim1);
    client.print("&soim2=");
    client.print(soim2);
    client.print("&water=");
    client.print(wlevel);
    client.println(" HTTP/1.1");
    client.println("Host: sssoyoung.dothome.co.kr");
    client.println("Connection: close");
    client.println();
  }
}
