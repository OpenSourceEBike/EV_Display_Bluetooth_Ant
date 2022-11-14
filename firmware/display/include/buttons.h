/*
 * LCD3 firmware
 *
 * Copyright (C) Casainho, 2018.
 *
 * Released under the GPL License, Version 3
 */

#pragma once

#include "nrf_gpio.h"

typedef enum
{
    BUTTON_ACTIVE_LOW = 0,
    BUTTON_ACTIVE_HIGH = 1
} button_active_state;

typedef struct
{
  button_active_state ActiveState;
  uint32_t PinNumber;
} Button;

typedef enum {
	ONOFF_CLICK = 1,
	ONOFF_CLICK_LONG_CLICK = 2,
	ONOFF_LONG_CLICK = 4,
	ONOFFUP_LONG_CLICK = 8,
	ONOFFDOWN_LONG_CLICK = 16,
	UP_CLICK = 32,
	UP_LONG_CLICK = 64,
  	UPDOWN_LONG_CLICK = 128,
	DOWN_CLICK = 256,
	DOWN_LONG_CLICK = 512,
	M_CLICK = 1024,
	M_CLICK_LONG_CLICK = 2048,
	M_LONG_CLICK = 4096,
	ONOFFUPDOWN_LONG_CLICK = 8192,
} buttons_events_t;

extern Button buttonDWN, buttonUP, buttonPWR, buttonM;

void InitButton(Button* button, uint32_t pin_number, nrf_gpio_pin_pull_t pull_config, button_active_state active_state);
bool PollButton(Button* button);

uint32_t buttons_get_m_state(void);
uint32_t buttons_get_up_state(void);
uint32_t buttons_get_up_click_event(void);
uint32_t buttons_get_up_click_long_click_event(void);
uint32_t buttons_get_up_long_click_event(void);
void buttons_clear_up_click_event(void);
void buttons_clear_up_click_long_click_event(void);
void buttons_clear_up_long_click_event(void);
uint32_t buttons_get_down_state(void);
uint32_t buttons_get_down_click_event(void);
uint32_t buttons_get_down_click_long_click_event(void);
uint32_t buttons_get_down_long_click_event(void);
void buttons_clear_down_click_event(void);
void buttons_clear_down_click_long_click_event(void);
void buttons_clear_down_long_click_event(void);
uint32_t buttons_get_onoff_state(void);
uint32_t buttons_get_onoff_click_event(void);
uint32_t buttons_get_onoff_click_long_click_event(void);
uint32_t buttons_get_onoff_long_click_event(void);
void buttons_clear_onoff_click_event(void);
void buttons_clear_onoff_click_long_click_event(void);
void buttons_clear_onoff_long_click_event(void);
uint32_t buttons_get_up_down_click_event(void);
void buttons_clear_up_down_click_event(void);
void buttons_clock(void);
buttons_events_t buttons_get_events(void);
void buttons_clear_all_events(void);
void buttons_set_events(buttons_events_t events);
void buttons_init(void);

extern buttons_events_t buttons_events;

