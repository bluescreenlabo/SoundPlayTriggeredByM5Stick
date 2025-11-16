#include <M5StickCPlus2.h>
#include <BluetoothSerial.h>
#include <esp_mac.h>
#include "../MovingAve.cpp"

MovingAve accY;
MovingAve oldY;

BluetoothSerial bts;
unsigned long g_millis;

void setup() {
  M5.begin();
  M5.Imu.init();
  M5.Lcd.setRotation(0);
  M5.Lcd.setTextSize(3);
//  M5.Lcd.fillScreen(ORANGE);
  
  bts.begin("M5Stick");
  
  uint8_t macBT[10];
  esp_read_mac(macBT, ESP_MAC_BT);  // 要esp_mac.h
  M5.Lcd.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", macBT[0], macBT[1], macBT[2], macBT[3], macBT[4], macBT[5]);

  Serial.begin(115200);
  
  accY.init();
  oldY.init();

//  disp.printUp();
  g_millis = millis() + 10;
}

void loop() {
  float tmp;
  float tmpY;
  static char pushBak = 0;
  static char pushBakB = 0;
  static bool waitOneG = false;

  if (g_millis >= millis()) {
    return;
  }
  g_millis = millis() + 10;
  M5.update();

  char push = M5.BtnA.isPressed();
  if (push != pushBak) {
    pushBak = push;
    if (push == 1) {
      bts.println("A");
      M5.Lcd.print("A");
    }
  }

  char pushB = M5.BtnB.isPressed();
  if (pushB != pushBakB) {
    pushBakB = pushB;
    if (pushB == 1) {
      bts.println("B");
      M5.Lcd.print("B");
    }
  }

  M5.Imu.getAccelData(&tmp, &tmpY, &tmp);
  float old = accY.SetData(tmpY);
  oldY.SetData(old);
  float yAve = accY.Get();
  float oldAve = oldY.Get();

  if (waitOneG == false) {
    if ((0.9 < oldAve)&&(oldAve < 1.1)) {
      if (yAve > 1.3) {
        bts.println("J");
        M5.Lcd.print("J");
        waitOneG = true;
      }
    }
  }
  else {
    if ((0.9 < yAve)&&(yAve < 1.1)) {
      waitOneG = false;
    }
  }

  delay(1);
}
