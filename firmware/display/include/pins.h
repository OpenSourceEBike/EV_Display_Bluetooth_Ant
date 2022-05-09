/*
 * EV display
 *
 * Copyright (C) Casainho, 2020, 201
 *
 * Released under the GPL License, Version 3
 */

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "boards.h"

#ifdef DISPLAY_SPI
  #define DISPLAY_USE_RESET_PIN
  #define DISPLAY_USE_SELECT_PIN
#endif

// I2C pins
#define DISPLAY_SCL_PIN NRF_GPIO_PIN_MAP(1, 10) 
#define DISPLAY_SDA_PIN NRF_GPIO_PIN_MAP(1, 13)

// SPI pins
#define DISPLAY_CLK_PIN NRF_GPIO_PIN_MAP(1, 10)
#define DISPLAY_MOSI_PIN NRF_GPIO_PIN_MAP(1, 13)
#define DISPLAY_MISO_PIN NRF_GPIO_PIN_MAP(1, 15)
#define DISPLAY_RS_PIN NRF_GPIO_PIN_MAP(0, 10)
#define DISPLAY_DC_PIN NRF_GPIO_PIN_MAP(0, 2)
#define DISPLAY_CS_PIN NRF_GPIO_PIN_MAP(0, 29)
#define CAN_MODULE_CS_PIN NRF_GPIO_PIN_MAP(0, 31)

// UART pins
#define RX_PIN_NUMBER 24
#define TX_PIN_NUMBER 22
#define RTS_PIN_NUMBER 0xFFFFFFFF  // UART_PIN_DISCONNECTED
#define CTS_PIN_NUMBER 0xFFFFFFFF  // UART_PIN_DISCONNECTED

#ifdef TSDZ2
#define MOTOR_POWER_ENABLE__PIN   NRF_GPIO_PIN_MAP(1,0)
#endif

void pins_init(void);
void motor_power_enable(bool state);

typedef enum {
    UP__PIN  = 13,
    DOWN__PIN  = 15,
    ONOFF__PIN = 20,
    M__PIN = 17,
    BUTTON_PIN_ELEMENTS = 4 // must be updated when added or removed an element
} button_pins_t;

typedef enum {
    LED_R__PIN  = 1,
    LED_G__PIN  = 2,
    LED_B__PIN  = 3,
    LED_PWR__PIN = 0,
} LED_pins_t;

