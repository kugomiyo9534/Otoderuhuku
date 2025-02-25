#define LED 16
 
void setup(){
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop(){
  while(Serial1.available()){
    byte inChar = (byte)Serial1.read();
    delay(10);
    Serial.println(inChar);
  }
}