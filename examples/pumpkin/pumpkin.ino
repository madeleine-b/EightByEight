#include "Badge.h"
#include "Sketch.h" 

Badge badge;
Sketch pumpkin;

static char mac_buf[6*3+1];
static uint32_t last_draw_millis;
const unsigned brightnessDivisor = 4;
static unsigned brightness = 128 * brightnessDivisor - 1;

void nudgeBrightness() {
  //slowly growing brightness with some catch at the apex to easily stop
  unsigned x =  ((brightness++ / brightnessDivisor) % 288);
  badge.matrix.setBrightness(_min(200, x)); // for some reason min is undefined. Seems to be A Thing (https://github.com/esp8266/Arduino/issues/263)
}

void setup()
{
  Serial.begin(9600);

  badge.begin();
  badge.matrix.clear();
  badge.matrix.show();
  nudgeBrightness();

  pumpkin.begin();
  badge.matrix.show();
  delay(2);
}

void loop()
{
  const uint32_t now = millis();

  bool do_draw = pumpkin.step(badge.ax, badge.ay, badge.az);
  // only draw the LEDs at 30Hz
  if (!do_draw && now - last_draw_millis < 30)
    return;
  last_draw_millis = now;
  
  pumpkin.draw(badge.matrix);
  badge.matrix.show();
  
  if (badge.button()) {
    nudgeBrightness();
  }
  delay(2);
}

