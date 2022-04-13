/*
 * TSDZ2 EBike wireless firmware
 *
 * Copyright (C) Casainho, 2020
 *
 * Released under the GPL License, Version 3
 */

#include <stdio.h>
#include <stdbool.h>
#include "nrf_gpio.h"
#include "pins.h"
#include "SSD1306.h"
#include "ugui.h"

/* uGUI instance from main */
extern UG_GUI gui;

static UG_RESULT accel_fill_frame(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c) {
  if(c == C_TRANSPARENT) // This happens a lot when drawing fonts and we don't need to bother drawing the background
    return UG_RESULT_OK;

  int16_t w;
  if(x1 <= x2) {
    w = x2 - x1 + 1;
  }
  else {
    w = x1 - x2 + 1; // swap around so we always draw left to right
    ssd1306_swap(x1, x2);
  }

  if(y2 < y1)
    ssd1306_swap(y1, y2); // Always draw top to bottom

  while(y1 <= y2) {
    ssd1306_draw_fast_hline(x1, y1, w, c);
    y1++;
  }

  return UG_RESULT_OK;
}

static UG_RESULT accel_draw_line(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c) {
  if(c == C_TRANSPARENT) // Probably won't happen but a cheap optimization
    return UG_RESULT_OK;

  if(y1 == y2)  {
    if(x1 <= x2)
      ssd1306_draw_fast_hline(x1, y1, x2 - x1 + 1, c);
    else
      ssd1306_draw_fast_hline(x2, y1, x1 - x2 + 1, c);

    return UG_RESULT_OK;
  }
  return UG_RESULT_FAIL;
}

void display_show() {
  // if(lcdBacklight != oldBacklight) {
  //   oldBacklight = lcdBacklight;

  //   uint8_t level = 255 * (100 - lcdBacklight);
  //   uint8_t cmd[] = { 0x81, level };

  //   send_cmd(cmd, sizeof(cmd));
  // }

  ssd1306_display();
}

void display_off() {
  ssd1306_dim(1);
  ssd1306_power_off();
}

void display_init(void)
{
#ifdef DISPLAY_I2C
  ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS, false);
#elif defined(DISPLAY_SPI)
  ssd1306_begin(SSD1306_SWITCHCAPVCC, 0, true);
#else
#error MUST define DISPLAY_I2C or DISPLAY_SPI
#endif

  ssd1306_clear_display();
  ssd1306_display();
  set_rotation(3); // makes vertical

  // Setup uGUI library
  UG_Init(&gui, ssd1306_draw_pixel, display_show, 64, 128); // Pixel set function

  UG_DriverRegister(DRIVER_DRAW_LINE, (void *) accel_draw_line);
  UG_DriverRegister(DRIVER_FILL_FRAME, (void *) accel_fill_frame);
}

static int lcdBacklight = -1; // -1 means unset
static int oldBacklight = -1;

// We are an oled so if the user asks for lots of backlight we really want to dim instead
// Note: This routine might be called from an ISR, so do not do slow SPI operations (especially because
// you might muck up other threads).  Instead just change the desired intensity and wait until the next
// screen redraw.
void display_set_backlight_intensity(uint8_t pct) {
  lcdBacklight = pct;
}
