#include <esp_now.h>
#include <WiFi.h>

uint8_t LED[2];            //送信データ(LEDのON=1,OFF=0）
char buf[2];
int num = 0;

//受信データ完了した時の処理11
void OnDataRecv(const esp_now_recv_info_t *mac_addr, const uint8_t *recvData, int len) {
  memcpy(&buf[0], recvData, len);
  buf[len]='\0';          //文字列の最後にNULL。
  //Serial.print("buf : ");
  //Serial.println(buf);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin();
  WiFi.mode(WIFI_STA);      // Wi-FiをStationモードに設定

  //ESP-NOWの初期化
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);   //ESP-NOWでデータ受信した時のコールバック関数を登録
}

void loop() {
  Serial.print(buf); Serial.print(",");
  Serial.println(num);
}