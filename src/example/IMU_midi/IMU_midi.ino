#include <MIDI.h>
#include <Wire.h>
#include <MadgwickAHRS.h>
Madgwick MadgwickFilter;


MIDI_CREATE_DEFAULT_INSTANCE();

#define cds_MIN0 -20
#define cds_MAX0 30
#define  pb_MIN0 127
#define  pb_MAX0 40

#define cds_MIN1 -25
#define cds_MAX1 25
#define  pb_MIN1 127
#define  pb_MAX1 0

#define cds_MIN2 0
#define cds_MAX2 50
#define  pb_MIN2 127
#define  pb_MAX2 0

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, temperature;
float degX, degY, degZ;

int cds0 = 0;
int cds1 = 0;
int cds2 = 0;


void setup() {

  MIDI.begin(1);  
  MIDI.turnThruOff();
  //Serial.begin(115200);
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
  MadgwickFilter.updateIMU(gxRaw / 131.0, gyRaw / 131.0, gzRaw / 131.0, axRaw / 16384.0, ayRaw / 16384.0, azRaw / 16384.0);
  degX = MadgwickFilter.getRoll();
  degY = MadgwickFilter.getPitch();
  degZ = MadgwickFilter.getYaw();
}

  {
  int nowcds0;
  nowcds0 = degX;   //analogRead(CDS0);
    cds0 = constrain(nowcds0, cds_MIN0, cds_MAX0);
    cds0 = map(cds0, cds_MIN0, cds_MAX0, pb_MAX0, pb_MIN0);
    MIDI.sendControlChange(74,cds0,1);     
    delay(5); //ぬるりとした感覚
  }   
  
  {
  int nowcds1;
  nowcds1 = degY;   //analogRead(CDS0);
    cds1 = constrain(nowcds1, cds_MIN1, cds_MAX1);
    cds1 = map(cds1, cds_MIN1, cds_MAX1, pb_MAX1, pb_MIN1);
    MIDI.sendControlChange(71,cds1,1);     
    delay(5);
  }   

{
  //Serial.print(degX); Serial.print(",");
  //Serial.print(degY); Serial.print(",");
  //Serial.println(degZ);
}
  
 
}


