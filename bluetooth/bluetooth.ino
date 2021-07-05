#include "BluetoothSerial.h"
#include <Adafruit_GFX.h>   
#include <P3RGB64x32MatrixPanel.h>

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() 
{
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
}

int flg = 0;
int btPacket = 0;

void loop() 
{
  matrix.begin();
  matrix.fillScreen(0);

  while (SerialBT.available()) 
  {
    Serial.println("connect");
    flg = 1;
    btPacket = SerialBT.read();
    Serial.printf("btPacket : %d \n", btPacket);
    matrix.setCursor(3, 8);
    matrix.print("Bluetooth OK!");
  }

  if (!SerialBT.hasClient() && flg == 1) 
  { 
    Serial.println("disconnect");
    flg = 0;
    matrix.fillScreen(0);
    matrix.setCursor(3, 8);
    matrix.print("Bluetooth Fail!");
  }
 delay(3000);
}
