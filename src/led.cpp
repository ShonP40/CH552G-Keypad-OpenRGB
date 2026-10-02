#include <Arduino.h>
#include "neo/neo.h"
#include "led.h"

// ===================================================================================
// Color section
// ============================================================================

static int color_hue_s[3] = {0, 0, 0}; // hue value: 0..191 color map
static int curretn_key_s = -1;         // current press key
static int led_brightness_s = NEO_DIM_KEYS; // brightness of keys

void led_set_color_hue(uint8_t led0, uint8_t led1, uint8_t led2, int led_brightness)
{
  color_hue_s[0] = led0;
  color_hue_s[1] = led1;
  color_hue_s[2] = led2;
  led_brightness_s = led_brightness;
}

void led_presskey(int key)
{
  curretn_key_s = key;
}

void led_update() {
  for (int led = 0; led < 3; led++) {
    if (curretn_key_s == led) {
      NEO_writeColor(led, 255, 255, 255);
    } else if (color_hue_s[led] == NEO_OFF_KEYS) {
        NEO_writeColor(led, 0, 0, 0); // full black
    } else if (color_hue_s[led] == NEO_WHITE) {
        NEO_writeColor(led, 255, 255, 255); // full white
    } else {
      NEO_writeHue(led, color_hue_s[led], led_brightness_s);
    }
  }

  NEO_update();
}