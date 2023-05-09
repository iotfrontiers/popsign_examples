#include <Adafruit_GFX.h>   
#include <P3RGB64x32MatrixPanel.h>
#include <Fonts/GodoM6pt8b.h>

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);
//P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 23, 15, 32, 33, 12, 16, 17, 18);

String InputString = "";

void setup()
{
  Serial.begin(115200);

  // matrix와 폰트 설정
  matrix.begin();
  matrix.setFont(&GodoM6pt8b);  
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setAttribute(UTF8_ENABLE , true);
  matrix.setTextColor(matrix.color444(15, 9, 12));
  matrix.fillScreen(0); // 화면 클리어
}

void loop() 
{
  matrix.setCursor(15, 10);
  matrix.print("고구마");
}
