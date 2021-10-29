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

#define MOTOR_POWER_ENABLE__PIN   NRF_GPIO_PIN_MAP(1,0)

// UART pins
#define RX_PIN_NUMBER 24
#define TX_PIN_NUMBER 22
#define RTS_PIN_NUMBER 0xFFFFFFFF  // UART_PIN_DISCONNECTED
#define CTS_PIN_NUMBER 0xFFFFFFFF  // UART_PIN_DISCONNECTED

void pins_init(void);
void motor_power_enable(bool state);

typedef enum {
    UP__PIN  = 13,
    DOWN__PIN  = 15,
    ONOFF__PIN = 20,
    BUTTON_PIN_ELEMENTS = 3 // must be updated when added or removed an element
} button_pins_t;

typedef enum {
    LED_R__PIN  = 1,
    LED_G__PIN  = 2,
    LED_B__PIN  = 3,
    LED_PWR__PIN = 0,
} LED_pins_t;

