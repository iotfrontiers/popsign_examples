/* Derived from Adafruit RGB_matrix_Panel library */

#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

// constructor with default pin wiring

// use this constructor for custom pin wiring instead of the default above
// these pins are an example, you may modify this according to your needs
  P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

void setup() {
  matrix.begin();
  uint8_t r=0, g=0, b=0;

  // Draw top half
  for(uint8_t x=0; x<64; x++) {
    for(uint8_t y=0; y<16; y++) {
      matrix.drawPixel(x, y, matrix.color444(r, g, b));
      r++;
      if(r == 15) {
        r = 0;
        g++;
        if(g == 15) {
          g = 0;
          b++;
        }
      }
    }
  }

  // Draw bottom half
  for(uint8_t x=0; x<64; x++) {
    for(uint8_t y=16; y<32; y++) {
      matrix.drawPixel(x, y, matrix.color444(r, g, b));
      r++;
      if(r == 15) {
        r = 0;
        g++;
        if(g == 15) {
          g = 0;
          b++;
        }
      }
    }
  }
}

void loop() {
  // Do nothing -- image doesn't change
}
