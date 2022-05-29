#include <M5EPD.h>
#include <WiFi.h>
#include <esp_now.h>

M5EPD_Canvas canvas(&M5.EPD);

// グローバル変数
//無線LANのSSID
extern char *ssid ;
//無線LANのパスワード
extern char *password ;

extern char *jpegUrl ;


//esp-now送信先のmacアドレス
//廃止

//esp-now送信後の処理
// void onSend(const uint8_t* mac_addr, esp_now_send_status_t status) {
//     char macStr[18];
//     snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
//         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//    Serial.println("onSendTRIGGERED");
//    Serial.println(macStr);
//    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failed");
// }


void setup()
{

  // M5.begin(false, false, true, true, false);
  M5.begin();
  Serial.print("start");
  M5.SHT30.Begin();
  //void begin(bool touchEnable = true, bool SDEnable = true, bool SerialEnable = true, bool BatteryADCEnable = true, bool I2CEnable = false);
  M5.EPD.SetRotation(0); 
  M5.EPD.Clear(true);


  //ここからesp-now関係
//   WiFi.mode(WIFI_STA);
//   WiFi.disconnect();
//   if (esp_now_init() == ESP_OK) {
//       Serial.println("ESPNow Init Success");
//   }
// Serial.println("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
//   Serial.println("Wifi channel: "); Serial.println(WiFi.channel());

//   esp_now_peer_info_t peerInfo;
//   memcpy(peerInfo.peer_addr, slaveAddress, 6);
//   peerInfo.channel = 0;
//   peerInfo.encrypt = false;

//   if (esp_now_add_peer(&peerInfo) != ESP_OK) {
//       Serial.println("Failed to add peer");
//       return;
//   }

//   esp_now_register_send_cb(onSend);
}
int Chk_battery()
{
  char buf[20];
  uint32_t vol = M5.getBatteryVoltage();
  if (vol < 3300)
  {
    vol = 3300;
  }
  else if (vol > 4350)
  {
    vol = 4350;
  }
  float battery = (float)(vol - 3300) / (float)(4350 - 3300);
  if (battery <= 0.01)
  {
    battery = 0.01;
  }
  if (battery > 1)
  {
    battery = 1;
  }
  //uint8_t px = battery * 25;
  // sprintf(buf, "BATT%d%% ", (int)(battery * 100));
  // canvas.drawString(buf, 450, 0);

  return (int)(battery * 100);
}

void loop()
{
    // バッテリー残量取得
  int btLevel = Chk_battery();

  //充電中は画面更新しないようにする
  if(btLevel==1){
    //充電時の処理
      canvas.createCanvas(540, 960);
    canvas.setTextSize(6);
    canvas.drawString("Charging....", 45, 350);
    // canvas.drawString("Batt:" + String(btLevel) + "%",45,550 );
    canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
    delay(60000);
  }else{
  WiFi.begin(ssid, password);
  canvas.createCanvas(960, 540);
  canvas.setTextSize(2);
  canvas.drawString("Connecting to the internet!", 45, 350);
  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
  //WiFi接続
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  //画像出力
  canvas.createCanvas(960, 540);
  Serial.print("writing image");
  canvas.setTextSize(3);
  //pngでも出力できるが10秒程度待たされるのでjpgが良い。
  // canvas.drawPngUrl(jpegUrl);
  canvas.drawJpgUrl(jpegUrl);



  // 気温取得
  M5.SHT30.UpdateData();
  float tem = M5.SHT30.GetTemperature();
  float hum = M5.SHT30.GetRelHumidity();
  char temStr[10];
  char humStr[10];
  dtostrf(tem, 2, 2, temStr); //小数点を含む数値を文字列に変換
  dtostrf(hum, 2, 2, humStr);
  canvas.setTextSize(2);
  canvas.drawString("Batt:" + String(btLevel) + "%   " + "Temp:" + String(temStr) + "*C  " + "Humi:" + String(humStr) + "%", 0, 0);

  // 描画
  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);

  Serial.print("written");



  //esp-nowでATOMMatrixに送信
  // uint8_t data[2] = { tem, hum }; // 送信データ
  // esp_err_t result = esp_now_send(slaveAddress, data, sizeof(data));

  // Serial.println("");
  // Serial.println(data[0]);
  // Serial.println(data[1]);
  // Serial.println("Send Status: ");
  // switch (result)
  // {
  // case ESP_OK:
  //     Serial.println("Success");
  //     break;
  // case ESP_ERR_ESPNOW_NOT_INIT:
  //     Serial.println("ESPNOW not Init.");
  //     break;
  // case ESP_ERR_ESPNOW_ARG:
  //     Serial.println("Invalid Argument");
  //     break;
  // case ESP_ERR_ESPNOW_INTERNAL:
  //     Serial.println("Internal Error");
  //     break;
  // case ESP_ERR_ESPNOW_NO_MEM:
  //     Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  //     break;
  // case ESP_ERR_ESPNOW_NOT_FOUND:
  //     Serial.println("Peer not found.");
  //     break;

  // default:
  //     Serial.println("Not sure what happened");
  //     break;
  // }

  delay(2000);
  M5.shutdown(3600);
  }
}
