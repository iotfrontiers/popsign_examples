#include <WiFi.h>
#include <Adafruit_GFX.h>   
#include <P3RGB64x32MatrixPanel.h>
#include <Fonts/FreeSans9pt7b.h>

P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 0, 15, 32, 33, 12, 5, 23, 4);

char ssid[] = "frontier";
char pass[] = "front1202^^";


void setup(){
  Serial.begin(115200);

  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);                   // print the network name (SSID);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  configTime(32400, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp"); // enable NTP
   matrix.begin();
}

int r = 0, g = 3 , b = 6;

void loop()
{             
  if (WiFi.status() != WL_CONNECTED)
    ESP.restart();

  time_t t;
  static time_t last_t;
  struct tm *tm;
  static const char* const wd[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};

  t = time(NULL);
  if (last_t == t) return;    // draw each second
  last_t = t;
  tm = localtime(&t);
  matrix.fillScreen(0);

  matrix.setFont(&FreeSans9pt7b);
  matrix.setCursor(0, 13);
  matrix.setTextColor(matrix.color444(15, 15, 15));

  matrix.printf("%02d:%02d", tm->tm_hour, tm->tm_min);

  matrix.setFont();
  matrix.printf(":%02d", tm->tm_sec);
 

  matrix.setCursor(2, 16);
  matrix.setTextColor(matrix.color444(b, r, g));

  matrix.printf("%s", wd[tm->tm_wday]);


  matrix.setCursor(2, 24);
  matrix.setTextColor(matrix.color444(g, r, b));

  r = (r + 3) % 31;
  g = (g + 3) % 31;
  b = (b + 3) % 31;

  matrix.printf("%04d/%02d/%02d\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);

}
