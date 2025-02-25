#include <esp_now.h>
#include <WiFi.h>

//調べた受信側のMACアドレスを設定8
uint8_t broadcastAddress[] = {0xE4, 0xB0, 0x63, 0xB2, 0x4E, 0x18};

uint8_t LED[2];            //送信データ(LEDのON=1,OFF=0）
char buf[2];
int tact_data;          //タクトボタンが押された時のデータ（LOW）
boolean flag = false;   //タクトボタンの押下フラグ（押すごとにtrue,falseを繰り返す）

esp_now_peer_info_t peerInfo;   //受信側情報のパラメータオブジェクト

//送信が完了した時の処理
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Deli_Success" : "Deli_Fail");
}
 
void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  WiFi.begin();
  WiFi.mode(WIFI_STA);            // Wi-FiをStationモードに設定

  //ESP-NOWの初期化
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  //ペア情報（受信側のアドレスとチャネルと暗号化の設定）
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  //受信側の情報追加      
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_send_cb(OnDataSent);   //ESP-NOWでデータ送信した時のコールバック関数を登録
}
 
void loop() {
  // 送信データ
    byte temp=(byte)Serial1.read();;               //LED消灯信号をセット

    sprintf(buf,"%d",temp);//数値型を文字型に変換
    memcpy(LED,buf,strlen(buf));  //uint8_tのLED変数に値をコピー
    //ESP-NOWのデータ送信処理
    esp_err_t result = esp_now_send(broadcastAddress, LED, sizeof(buf));
   
    if (result == ESP_OK) {//送信が成功したら
      Serial.println("success");
      Serial.print("temp : ");
      Serial.println(temp);
    }
    else {
      Serial.println("Error");
    }
    delay(10);
  }
