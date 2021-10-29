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
#include "buttons.h"
#include "pins.h"

void pins_init(void)
{
  nrf_gpio_pin_clear(MOTOR_POWER_ENABLE__PIN);
  nrf_gpio_cfg_output(MOTOR_POWER_ENABLE__PIN);

    /* Buttons */
  InitButton(&buttonPWR, ONOFF__PIN, NRF_GPIO_PIN_NOPULL, BUTTON_ACTIVE_HIGH);
  InitButton(&buttonUP, UP__PIN, NRF_GPIO_PIN_PULLUP, BUTTON_ACTIVE_LOW);
  InitButton(&buttonDWN, DOWN__PIN, NRF_GPIO_PIN_PULLUP, BUTTON_ACTIVE_LOW);

  // this will enable wakeup from ultra low power mode (any button press)
  nrf_gpio_cfg_sense_input(ONOFF__PIN, GPIO_PIN_CNF_PULL_Pullup, GPIO_PIN_CNF_SENSE_Low);
}

void motor_power_enable(bool state)
{
  if (state)
    nrf_gpio_pin_set(MOTOR_POWER_ENABLE__PIN);
  else
    nrf_gpio_pin_clear(MOTOR_POWER_ENABLE__PIN);
}
