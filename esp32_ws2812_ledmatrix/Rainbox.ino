#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "buffer_serial.h"
#include "BluetoothSerial.h"
#include "bluetooth.h"
#include "Rainbow.h"

#define LEDS_COUNT  256
#define LEDS_PIN	25
#define CHANNEL		0

#define LED_VAL 2
#define LED_DELAY delay(1000)
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

BluetoothSerial SerialBT;

BufferSerial bufferSerial = BufferSerial(&SerialBT);
Bluetooth bluetooth(&SerialBT);
int modeStep = 0;
void bluetoothMode();

void setup() {
  strip.begin();
  Serial.begin(115200);
  Serial.println("setup!!!");
}
int red = 0;
int green = 0;
int blue = 0;

void loop() 
{
  bluetoothMode();

}

void bluetoothMode() // 0 ~ 1 Logo Setion, 2 ~ 3 bluetooth init, 4 is bt ongoing
{
  if (modeStep == 0) {
    Serial.println("BLUETOOTH MODE!");
    Serial.println("BLUETOOTH Set Up!");
    bluetooth.setup();
    modeStep = 1;
  }

  else if (modeStep == 1) {
    if(bluetooth.check())
    {
      Serial.println("BLUETOOTH Connection OK!");
      modeStep = 2;
    } 
  }
  else if (modeStep == 2) 
  {
    bufferSerial.process();
  } 
}

void scr_all_red()
{
  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, LED_VAL, 0, 0);
  }
  strip.show();
  LED_DELAY;
}



void scr_all_green()
{
  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, 0, LED_VAL, 0);
  }
  strip.show();
  LED_DELAY;
}


void scr_all_blue()
{
  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, 0, 0, LED_VAL);
  }
  strip.show();
  LED_DELAY;
}

void scr_all_white()
{
  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, LED_VAL, LED_VAL, LED_VAL);
  }
  strip.show();
  LED_DELAY;
}

void scr_clear()
{
 
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, 0);
    }
    strip.show();
    LED_DELAY;
}

void functionTest(char* data, int len) {

  if((data[0] > 0) && (data[1] == 0) && (data[2] == 0)){
    scr_all_red();
    //scr_clear();
  }
  else if((data[0] == 0) && (data[1] > 0) && (data[2] == 0)){
    scr_all_green();
    //scr_clear();
  }
  else if((data[0] == 0) && (data[1] == 0) && (data[2] > 0)){
    scr_all_blue();
    //scr_clear();
  }
  else if((data[0] > 0) && (data[1] > 0) && (data[2] > 0)){
    scr_all_white();
    //scr_clear();
  }

}
