#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  WiFi.begin();
  Serial.print("MACWIfi: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
}