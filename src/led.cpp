#include <Arduino.h>
#include "neo/neo.h"
#include "led.h"

// ===================================================================================
// Color section
// ============================================================================

static int color_hue_s[3] = {0, 0, 0}; // hue value: 0..191 color map
static bool color_rgb_s[3] = {false, false, false};
static uint8_t color_red_s[3] = {0, 0, 0};
static uint8_t color_green_s[3] = {0, 0, 0};
static uint8_t color_blue_s[3] = {0, 0, 0};
static int curretn_key_s = -1;         // current press key
static int led_brightness_s = NEO_DIM_KEYS; // brightness of keys

void led_set_color_hue(uint8_t led0, uint8_t led1, uint8_t led2, int led_brightness)
{
  color_hue_s[0] = led0;
  color_hue_s[1] = led1;
  color_hue_s[2] = led2;
  color_rgb_s[0] = false;
  color_rgb_s[1] = false;
  color_rgb_s[2] = false;
  led_brightness_s = led_brightness;
}

void led_set_color_rgb(uint8_t led, uint8_t red, uint8_t green, uint8_t blue)
{
  if (led >= 3)
  {
    return;
  }

  color_rgb_s[led] = true;
  color_red_s[led] = red;
  color_green_s[led] = green;
  color_blue_s[led] = blue;
}

void led_presskey(int key)
{
  curretn_key_s = key;
}

void led_update() {
  for (int led = 0; led < 3; led++) {
    if (curretn_key_s == led) {
      NEO_writeColor(led, 255, 255, 255);
    } else if (color_rgb_s[led]) {
      NEO_writeColor(led, color_red_s[led], color_green_s[led], color_blue_s[led]);
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