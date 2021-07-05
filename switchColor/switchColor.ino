#include <Adafruit_GFX.h>   
#include <P3RGB64x32MatrixPanel.h>

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

int pin = 13;
int val = 0;

void setup(){
   Serial.begin(115200);
   matrix.begin();

   pinMode(pin, INPUT);
}
bool reversPin = false;
void loop()
{             
  
  val = digitalRead(pin);
  if(val == LOW && reversPin == false)  
  {
      reversPin = true;
      matrix.fillScreen(0);
      matrix.setCursor(18, 12);
      matrix.print("Color");
      matrix.setTextColor(random(0,255));
      Serial.println("low");
    return;
  } 
  if (val == HIGH) reversPin = false;
}
