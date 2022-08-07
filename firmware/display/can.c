/*
 * OpenSource DIY EV display
 * Copyright (C) Casainho, 2021, 2022
 *
 * Released under the GPL License, Version 3
 */

#include <stdio.h>
#include <string.h>
#include "nrf_delay.h"
#include "can.h"
#include "CANSPI.h"
#include "buttons.h"
#include "state.h"

#ifdef MOTOR_TSDZ2

#elif defined(MOTOR_BAFANG)

static rt_vars_t *mp_rt_vars = NULL;
static ui_vars_t *mp_ui_vars = NULL;

void can_processing(uint32_t ui32_time_now) {
  static uint32_t ui32_can_last_run_time = 0;
  uCAN_MSG canMessage;

  if (mp_rt_vars == NULL) {
    mp_ui_vars = get_ui_vars();
    mp_rt_vars = get_rt_vars();
  }

  // every 100ms
  // CAN ID 0x03106300 needs to be sent periodically every 100ms or so, so the motor controller will turn off after a timeout
  if ((ui32_time_now - ui32_can_last_run_time) >= 100)
  {
    memset(canMessage.array, 0, sizeof(canMessage.array));
    canMessage.frame.idType = dEXTENDED_CAN_MSG_ID_2_0B;
    canMessage.frame.id = 0x03106300;
    canMessage.frame.dlc = 4;
    canMessage.frame.data0 = mp_ui_vars->ui8_number_of_assist_levels; // number of assist level: 3, 5 or 9 (seems M600 only supports up to 5)

    // assist level has some code scheme, implement it
    uint8_t assist_level_coded = 0;
    switch (mp_ui_vars->ui8_number_of_assist_levels) {
      case 3:
        switch (mp_ui_vars->ui8_assist_level) {
          case 0:
            assist_level_coded = 0x00;
          break;

          case 1:
            assist_level_coded = 0x0C;
          break;

          case 2:
            assist_level_coded = 0x02;
          break;

          case 3:
            assist_level_coded = 0x03;
          break;

          default:
            assist_level_coded = 0x00;
          break;
        }
      break;

      case 5:
        switch (mp_ui_vars->ui8_assist_level) {
          case 0:
            assist_level_coded = 0x00;
          break;

          case 1:
            assist_level_coded = 0x0B;
          break;

          case 2:
            assist_level_coded = 0x0D;
          break;

          case 3:
            assist_level_coded = 0x15;
          break;

          case 4:
            assist_level_coded = 0x17;
          break;

          case 5:
            assist_level_coded = 0x03;
          break;

          default:
            assist_level_coded = 0x00;
          break;
        }
      break;

      case 9:
        switch (mp_ui_vars->ui8_assist_level) {
          case 0:
            assist_level_coded = 0x00;
          break;

          case 1:
            assist_level_coded = 0x01;
          break;

          case 2:
            assist_level_coded = 0x0B;
          break;

          case 3:
            assist_level_coded = 0x0C;
          break;

          case 4:
            assist_level_coded = 0x0D;
          break;

          case 5:
            assist_level_coded = 0x02;
          break;

          case 6:
            assist_level_coded = 0x15;
          break;

          case 7:
            assist_level_coded = 0x16;
          break;

          case 8:
            assist_level_coded = 0x17;
          break;

          case 9:
            assist_level_coded = 0x03;
          break;

          default:
            assist_level_coded = 0x00;
          break;
        }
      break;

      default:
        assist_level_coded = 0x00;
      break;
    }

    // if walk assist is enabled, assist level coded is always 0x06
    if (mp_ui_vars->ui8_walk_assist_feature_enabled &&
        mp_ui_vars->ui8_walk_assist) {
      assist_level_coded = 0x06;
    }
    
    // finally use the assist_level_coded
    canMessage.frame.data1 = assist_level_coded;
 
    uint8_t up_down_button_state;
    up_down_button_state = buttons_get_up_long_click_event() | buttons_get_up_long_click_event();
    up_down_button_state |= buttons_get_down_long_click_event() | buttons_get_down_long_click_event();
    canMessage.frame.data2 = mp_ui_vars->ui8_lights | (up_down_button_state << 1); // bit 0 for light state; bit 1 for for UP or DOWN state

    canMessage.frame.data3 = (buttons_get_onoff_click_event() | buttons_get_onoff_long_click_event() | buttons_get_onoff_click_long_click_event()) ? 0: 1; // bit 0 for ON/OFF state
    // CANSPI_Transmit(&canMessage);
    // Not sending 'keep alive' if configured as second display!!! 
  }

  // process CAN messages
  if (CANSPI_Receive(&canMessage))
  {
    uint32_t temp;

    switch (canMessage.frame.id) {
      // torque sensor
      case 0x01F83100:
        temp = canMessage.frame.data1;
        temp = temp << 8;
        temp = temp + canMessage.frame.data0;
        mp_rt_vars->ui16_adc_pedal_torque_sensor = temp;

        mp_rt_vars->ui8_pedal_cadence = canMessage.frame.data2;
      break;

      // battery SOC
      case 0x02F83200:
        ui8_g_battery_soc = canMessage.frame.data0;
      break;

      // wheel speed; battery current; battery voltage; motor temperature
      case 0x02F83201:
        // as soon we receive this CAN package, the motor is ready
        g_motor_init_state = MOTOR_INIT_READY;

        temp = canMessage.frame.data1;
        temp = temp << 8;
        temp = temp + canMessage.frame.data0;
        mp_rt_vars->ui16_wheel_speed_x10 = temp / 10;

        temp = canMessage.frame.data3;
        temp = temp << 8;
        temp = temp + canMessage.frame.data2;
        mp_rt_vars->ui8_battery_current_div5 = temp / 20;

        temp = canMessage.frame.data5;
        temp = temp << 8;
        temp = temp + canMessage.frame.data4;
        mp_rt_vars->ui16_adc_battery_voltage = temp;

        mp_rt_vars->ui8_motor_temperature = canMessage.frame.data7 - 40;
      break;

      // wheel speed limit; wheel circunference
      case 0x02F83203:
        temp = canMessage.frame.data1;
        temp = temp << 8;
        temp = temp + canMessage.frame.data0;
        mp_ui_vars->ui16_wheel_max_speed_x100 = temp;

        temp = canMessage.frame.data3;
        temp = temp << 8;
        temp = temp + canMessage.frame.data2;
        temp = temp >> 4;
        temp = temp * 10;
        temp = temp + (canMessage.frame.data2 & 15);
        mp_ui_vars->ui16_wheel_size = temp;

        temp = canMessage.frame.data5;
        temp = temp << 8;
        temp = temp + canMessage.frame.data4;
        mp_ui_vars->ui16_wheel_perimeter = temp;
      break;

      // brakes state
      case 0x02FF1200:
        mp_rt_vars->ui8_braking = canMessage.frame.data0 & 0x01;
      break;    
    }
  }
}

void can_set_max_wheel_speed(uint16_t value) {

  static uCAN_MSG canMessage;
  memset(&canMessage.frame, 0, sizeof(canMessage.frame));
  
  canMessage.frame.idType = dEXTENDED_CAN_MSG_ID_2_0B;
  canMessage.frame.id = 0x05103203; // must be 0x05xxxxx, if is 0x03xxxx, the motor controller will instead set the value to 25km/h
  canMessage.frame.dlc = 6;

  // Max wheel speed limit Byte 0/1: 60.00km/h(1770Hex) = 70 17 / 25.00km/h(9C4Hex) = C4 09
  canMessage.frame.data0 = (value & 0xff);
  canMessage.frame.data1 = (value >> 8) & 0xff;

  // Wheel Size Byte 2/3: 29.0(1DHex) = D0 01 / 27.5(1B5Hex) = B5 01
  canMessage.frame.data2 = 0xC0; // TODO 28.0 inch
  canMessage.frame.data3 = 0x01; // TODO

  // Wheel perimeter Byte 4/5: 2280(8E8Hex) = E8 08 / 2240mm(8C0Hex) = C0 08
  canMessage.frame.data4 = 0x9D; // TODO 
  canMessage.frame.data5 = 0x08; // TODO

  // don´t know why but if sending only once the canMessage, sometimes the motor controller does not assume it
  // sending 5x and with the 100ms delay makes it works "always"
  CANSPI_Transmit(&canMessage);
  nrf_delay_ms(100);
  CANSPI_Transmit(&canMessage);
  nrf_delay_ms(100);
  CANSPI_Transmit(&canMessage);
  nrf_delay_ms(100);
  CANSPI_Transmit(&canMessage);
  nrf_delay_ms(100);
  CANSPI_Transmit(&canMessage);
  nrf_delay_ms(100);
}
#endif