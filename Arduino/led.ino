int motion = 7;
int red = 9;
int green = 10;
int blue = 11;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensor = digitalRead(motion);
  if(sensor == HIGH){
   digitalWrite(red, HIGH);
   digitalWrite(red, LOW);
   digitalWrite(green, HIGH);
   digitalWrite(green, LOW);
   digitalWrite(blue, HIGH);
   digitalWrite(blue, LOW);
  }
}
