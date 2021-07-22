// 송신

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF7, 0x47 };
EthernetClient client;
IPAddress server(3,17,141,68);
String str="";
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 1000;

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac);
}

void loop() {
  if(client.available()){
    char c=client.read();
    str+=c;

    if(str.indexOf("relay=on")!=-1){
      //Serial.println("relay=on");
      str="on";
      Serial.write("on");
    }else if(str.indexOf("relay=off")!=-1){
      //Serial.println("relay=off");
      str="off";
      Serial.write("off");
    }
  }

  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
}

void httpRequest() {
  client.stop();
  if (client.connect(server, 80)) {
    //Serial.println("connecting...");
    if(str=="on"){
      //delay(1000); //시간 조절을 통해서 물 오래 줄 수 있음
      client.println("GET /pages/relay_insert.php?state=off HTTP/1.1");
    }else{
      client.println("GET /pages/relay_final.php HTTP/1.1");
    }
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
  str="";
}
