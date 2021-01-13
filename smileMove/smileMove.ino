// RGB Panel GFX Demo example for 64x32 panel

#include <RGBmatrixPanel.h>
#include "smileytongue24.h"

#include <Adafruit_GFX.h>   // Core graphics library
#include <P3RGB64x32MatrixPanel.h>

P3RGB64x32MatrixPanel *matrix = new P3RGB64x32MatrixPanel(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 16, 17, 4);

// Panel Matrix doesn't fully work like Neomatrix (which I originally
// wrote this demo for), so map a few calls to be compatible. The rest
// comes from Adafruit_GFX and works the same on both backends.
#define setBrightness(x) fillScreen(0) // no-op, no brightness on this board
#define clear()          fillScreen(0)
#define show()           swapBuffer()
#define Color(x,y,z)     color444(x/16,y/16,z/16)

// Define matrix width and height.
#define mw 64
#define mh 32

// This could also be defined as matrix->color(255,0,0) but those defines
// are meant to work for Adafruit::GFX backends that are lacking color()

static const uint16_t PROGMEM
    //multicolor smiley face RGB_bmp
    RGB_bmp[64] = {
        0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000,
        0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000,
        0x00F, 0x000, 0xF00, 0x000, 0x000, 0xF00, 0x000, 0x00F,
        0x00F, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x00F,
        0x00F, 0x000, 0x0F0, 0x000, 0x000, 0x0F0, 0x000, 0x00F,
        0x00F, 0x000, 0x000, 0x0F4, 0x0F3, 0x000, 0x000, 0x00F,
        0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000,
        0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000, 
};
// Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    uint16_t RGB_bmp_fixed[w * h];
    for (uint16_t pixel=0; pixel<w*h; pixel++) {
        uint8_t r,g,b;
        uint16_t color = pgm_read_word(bitmap + pixel);

        b = (color & 0xF00) >> 8;
        g = (color & 0x0F0) >> 4;
        r = color & 0x00F;

        // expand from 4/4/4 bits per color to 5/6/5
        b = map(b, 0, 15, 0, 31);
        g = map(g, 0, 15, 0, 63);
        r = map(r, 0, 15, 0, 31);

        RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
        //Serial.print(" -> ");
        //Serial.println(RGB_bmp_fixed[pixel], HEX);
    }
    matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
}

// Scroll within big bitmap so that all if it becomes visible or bounce a
// small one.  If the bitmap is bigger in one dimension and smaller in the
// other one, it will both pan and bounce in the appropriate dimensions.
void display_panOrBounceBitmap (uint8_t bitmapSize) {
    // keep integer math, deal with values 16 times too big
    // start by showing upper left of big bitmap or centering if big display
    int16_t xf = max(0, (mw-bitmapSize)/2) << 4;
    int16_t yf = max(0, (mh-bitmapSize)/2) << 4;
    // scroll speed in 1/16th
    int16_t xfc = 6;
    int16_t yfc = 3;
    // scroll down and right by moving upper left corner off screen
    // more up and left (which means negative numbers)
    int16_t xfdir = -1;
    int16_t yfdir = -1;

    for (uint16_t i=1; i<1000; i++) {
        bool updDir = false;

        // Get actual x/y by dividing by 16.
        int16_t x = xf >> 4;
        int16_t y = yf >> 4;

        matrix->clear();
        // bounce 8x8 tri color smiley face around the screen
        if (bitmapSize == 8) fixdrawRGBBitmap(x, y, RGB_bmp, 8, 8);
        // pan 24x24 pixmap
        if (bitmapSize == 24) matrix->drawRGBBitmap(x, y, (const uint16_t *)bitmap24, bitmapSize, bitmapSize);
        matrix->show();

        // Only pan if the display size is smaller than the pixmap
        if (mw<bitmapSize) {
            xf += xfc*xfdir;
            if (xf >= 0)                      { xfdir = -1; updDir = true ; };
            // we don't go negative past right corner, go back positive
            if (xf <= ((mw-bitmapSize) << 4)) { xfdir = 1;  updDir = true ; };
        }
        if (mh<bitmapSize) {
            yf += yfc*yfdir;
            // we shouldn't display past left corner, reverse direction.
            if (yf >= 0)                      { yfdir = -1; updDir = true ; };
            if (yf <= ((mh-bitmapSize) << 4)) { yfdir = 1;  updDir = true ; };
        }
        // only bounce a pixmap if it's smaller than the display size
        if (mw>bitmapSize) {
            xf += xfc*xfdir;
            // Deal with bouncing off the 'walls'
            if (xf >= (mw-bitmapSize) << 4) { xfdir = -1; updDir = true ; };
            if (xf <= 0)                    { xfdir =  1; updDir = true ; };
        }
        if (mh>bitmapSize) {
            yf += yfc*yfdir;
            if (yf >= (mh-bitmapSize) << 4) { yfdir = -1; updDir = true ; };
            if (yf <= 0)                    { yfdir =  1; updDir = true ; };
        }

       if (updDir) {
            // Add -1, 0 or 1 but bind result to 1 to 1.
            // Let's take 3 is a minimum speed, otherwise it's too slow.
            xfc = constrain(xfc + random(-1, 2), 3, 16);
            yfc = constrain(xfc + random(-1, 2), 3, 16);
        }
        delay(10);
    }
}

void loop() {
    // pan a big pixmap
    display_panOrBounceBitmap(24);
    // bounce around a small one
    display_panOrBounceBitmap(8);
}

void setup() {
    Serial.begin(115200);
    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(BRIGHTNESS);
    // Test full bright of all LEDs. If brightness is too high
    // for your current limit (i.e. USB), decrease it.
}
