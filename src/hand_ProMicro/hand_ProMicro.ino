#include <Wire.h>
#include <MadgwickAHRS.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // RX, TX

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, temperature;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); // ソフトウェアシリアルの初期化

  Wire.setClock(400000);
  Wire.begin();
  
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();

  MadgwickFilter.begin(100);//Hz感度を調節
}

void loop() {

{  
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 14);
  while (Wire.available() < 14);
  axRaw = Wire.read() << 8 | Wire.read();
  ayRaw = Wire.read() << 8 | Wire.read();
  azRaw = Wire.read() << 8 | Wire.read();
  temperature = Wire.read() << 8 | Wire.read();
  gxRaw = Wire.read() << 8 | Wire.read();
  gyRaw = Wire.read() << 8 | Wire.read();
  gzRaw = Wire.read() << 8 | Wire.read();
}

{
  Serial.print(axRaw); Serial.print(",");
  Serial.print(ayRaw); Serial.print(",");
  Serial.println(azRaw);
}

{
  mySerial.listen();
  mySerial.write(count);
 
  delay(10);
 
  if (mySerial.available()) {
    Serial.print(mySerial.readString());
  }

}
 
}