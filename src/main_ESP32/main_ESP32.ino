struct MPUData {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
};

void setup() {
    Serial.begin(9600);
}

void loop(){
  while(Serial.available()){
    byte inChar = (byte)Serial.read();
    Serial.println(inChar);
    delay(10);
  }
}

