#ifndef USER_USB_RAM
#error "Require USB RAM. Select the 266B USB RAM option in the CH55xDuino Tools menu"
#endif

#include "src/neo/neo.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

#include "src/buttons.h"
#include "src/encoder.h"
#include "src/keyboard.h"
#include "src/led.h"
#include "src/util.h"

#define PIN_BTN_1 11
#define PIN_BTN_2 17
#define PIN_BTN_3 16
#define PIN_BTN_ENC 33

#define ENCODER_A 31
#define ENCODER_B 30

#define LED_PIN 34

void setup()
{
  NEO_init();
  delay(10);
  NEO_clearAll();

  if (!digitalRead(PIN_BTN_ENC))
  {
    NEO_writeHue(0, NEO_CYAN, NEO_BRIGHT_KEYS);
    NEO_writeHue(1, NEO_BLUE, NEO_BRIGHT_KEYS);
    NEO_writeHue(2, NEO_MAG, NEO_BRIGHT_KEYS);
    NEO_update();
    BOOT_now();
  }

  buttons_setup(PIN_BTN_1, PIN_BTN_2, PIN_BTN_3, PIN_BTN_ENC);
  encoder_setup(ENCODER_A, ENCODER_B);
  led_set_color_hue(NEO_OFF_KEYS, NEO_OFF_KEYS, NEO_OFF_KEYS, NEO_BRIGHT_KEYS);
  USBInit();
}

void loop()
{
  buttons_update();
  encoder_update();
  led_serial_update();
  led_update();
  delay(5);
}
