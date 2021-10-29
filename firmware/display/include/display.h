/*
 * TSDZ2 EBike wireless firmware
 *
 * Copyright (C) Casainho, 2020
 *
 * Released under the GPL License, Version 3
 */

#pragma once

#include "SSD1306.h"

void display_off();
void display_init();
void display_show(void); // Call to flush framebuffer
void display_set_backlight_intensity(uint8_t level);




