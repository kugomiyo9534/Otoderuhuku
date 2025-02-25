#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10); // シリアルポートの準備を待機
  }

  if (!mpu.begin()) {
    Serial.println("MPU6050の初期化に失敗しました！");
    while (1) {
      delay(10);
    }
  }

  // センサーの設定
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050初期化完了！");
}

void loop() {
  // センサーのデータを取得
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //Serial.print("@SENSOR:");
  Serial.print("x加速度:"); Serial.print(a.acceleration.x); Serial.print(",");
  Serial.print("y加速度:"); Serial.print(a.acceleration.y); Serial.print(",");
  Serial.print("z加速度:"); Serial.print(a.acceleration.z); Serial.print(",");
  Serial.print("x回転:");Serial.print(g.gyro.x); Serial.print(",");
  Serial.print("y回転:");Serial.print(g.gyro.y); Serial.print(",");
  Serial.print("z回転:");Serial.print(g.gyro.z); Serial.println("");

  delay(20); 
/*
  // 加速度のデータを表示 (m/s^2)
  Serial.print("加速度 (X, Y, Z): ");
  Serial.print(a.acceleration.x);
  Serial.print(", ");
  Serial.print(a.acceleration.y);
  Serial.print(", ");
  Serial.println(a.acceleration.z);

  // ジャイロのデータを表示 (度/秒)
  Serial.print("ジャイロ (X, Y, Z): ");
  Serial.print(g.gyro.x);
  Serial.print(", ");
  Serial.print(g.gyro.y);
  Serial.print(", ");
  Serial.println(g.gyro.z);

  // 温度データを表示 (°C)
  Serial.print("温度: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  delay(100); // 更新間隔
*/
}