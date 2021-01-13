// scrolltext demo for Adafruit P3RGB64x32MatrixPanel library.
// Demonstrates single-buffered animation on our 32x64 RGB LED matrix:


#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

#define BALL_COUNT 3

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 16, 17, 4);

const char str[] PROGMEM = "CHANGE THE WORLD, BRIGHT YOUR LIFE";

int16_t    textX         = matrix.width(),
           textMin       = sizeof(str) * -12,
           hue           = 0;
int8_t ball[BALL_COUNT][4] = {  
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 }
};
static const uint16_t PROGMEM ballcolor[BALL_COUNT] = {
  0x0080, // Green=1
  0x0002, // Blue=1
  0x1000  // Red=1
};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(2);
}

void loop() {
  byte i;

  // Clear background
  matrix.fillScreen(0);

  // Bounce three balls around
  for(i=0; i<BALL_COUNT; i++) {
    // Draw 'ball'
    matrix.fillCircle(ball[i][0], ball[i][1], 5, pgm_read_word(&ballcolor[i]));
    // Update X, Y position
    ball[i][0] += ball[i][2];
    ball[i][1] += ball[i][3];
    // Bounce off edges
    if((ball[i][0] == 0) || (ball[i][0] == (matrix.width() - 1)))
      ball[i][2] *= -1;
    if((ball[i][1] == 0) || (ball[i][1] == (matrix.height() - 1)))
      ball[i][3] *= -1;
  }

  // Draw big scrolly text on top
  matrix.setTextColor(matrix.colorHSV(hue, 255, 255));
  matrix.setCursor(textX, 5);
  matrix.print(str);

  // Move text left (w/wrap), increase hue
  if((--textX) < textMin) textX = matrix.width();
  hue += 7;
  if(hue >= 1536) hue -= 1536;

#if !defined(__AVR__)
  // On non-AVR boards, delay slightly so screen updates aren't too quick.
  delay(20);
#endif

}
