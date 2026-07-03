#include <M5StickCPlus2.h>
#include <BluetoothSerial.h>
#include <esp_mac.h>
#include <cmath>             // sqrt を使うために追加
#include "../MovingAve.cpp"

// 変数名をY軸限定から、合成加速度（Total）用に変更
MovingAve accTotal;
MovingAve oldTotal;

BluetoothSerial bts;
unsigned long g_millis;

void setup() {
  M5.begin();
  M5.Imu.init();
  M5.Lcd.setRotation(0);
  M5.Lcd.setTextSize(3);
  
  bts.begin("M5Stick");
  
  uint8_t macBT[10];
  esp_read_mac(macBT, ESP_MAC_BT);
  M5.Lcd.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", macBT[0], macBT[1], macBT[2], macBT[3], macBT[4], macBT[5]);

  Serial.begin(115200);
  
  accTotal.init();
  oldTotal.init();

  g_millis = millis() + 10;
}

void loop() {
  float ax, ay, az; // X, Y, Z 各軸の加速度を格納する変数
  static char pushBak = 0;
  static char pushBakB = 0;
  static bool waitOneG = false;

  if (g_millis >= millis()) {
    return;
  }
  g_millis = millis() + 10;
  M5.update();

  // --- ボタンA処理 ---
  char push = M5.BtnA.isPressed();
  if (push != pushBak) {
    pushBak = push;
    if (push == 1) {
      bts.println("A");
      M5.Lcd.print("A");
    }
  }

  // --- ボタンB処理 ---
  char pushB = M5.BtnB.isPressed();
  if (pushB != pushBakB) {
    pushBakB = pushB;
    if (pushB == 1) {
      bts.println("B");
      M5.Lcd.print("B");
    }
  }

  // --- ジャンプ検出処理 ---
  M5.Imu.getAccelData(&ax, &ay, &az);
  float totalAccel = sqrt(ax * ax + ay * ay + az * az);

  float old = accTotal.SetData(totalAccel);
  oldTotal.SetData(old);
  float totalAve = accTotal.Get();
  // float oldTotalAve = oldTotal.Get(); // 不要になったため削除可能

  if (waitOneG == false) {
    // 1G付近に戻っている状態から、しきい値（1.3G）を超えたら即ジャンプ判定
    if (totalAve > 1.3) {
      bts.println("J");
      M5.Lcd.print("J");
      waitOneG = true; // 次の着地（1G復帰）を待つモードへ
    }
  }
  else {
    // 着地して加速度が 1G 付近に落ち着くのを待つ
    if ((0.9 < totalAve) && (totalAve < 1.1)) {
      waitOneG = false; // 再びジャンプを検知できる状態に戻す
    }
  }

  delay(1);
}