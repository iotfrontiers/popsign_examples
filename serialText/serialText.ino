#include <Adafruit_GFX.h>   
#include <P3RGB64x32MatrixPanel.h>
#include <Fonts/GodoM6pt8b.h>
#include <Fonts/GodoM7pt8b.h>

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

String InputString = "";

void setup()
{
  Serial.begin(115200);
  matrix.begin();
  matrix.setFont(&GodoM6pt8b);
  matrix.setAttribute(UTF8_ENABLE , true);  
}

void loop() 
{

  if(Serial.available()) {
    char c = Serial.read();
    if ( c == NULL || c == '\n') {
      matrix.fillScreen(0);
      matrix.setCursor(15, 10);
      matrix.print(InputString);
      InputString = "";   
      return;
    }
    InputString += c;
  }
}
