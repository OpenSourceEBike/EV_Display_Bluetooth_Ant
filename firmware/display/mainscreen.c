/*
 * Bafang LCD 850C firmware
 *
 * Copyright (C) Casainho, 2018.
 *
 * Released under the GPL License, Version 3
 */

#include <math.h>
#include <string.h>
#include "stdio.h"
#include "main.h"
#include "utils.h"
#include "screen.h"
#include "rtc.h"
#include "fonts.h"
#include "uart.h"
#include "mainscreen.h"
#include "eeprom.h"
#include "buttons.h"
#include "display.h"
#include "ugui.h"
#include "state.h"
#include "timer.h"
#include "rtc.h"
#include "peer_manager.h"
#include "configscreen.h"

static uint16_t m_assist_level_change_timeout = 0;

uint8_t ui8_m_wheel_speed_integer;
uint8_t ui8_m_wheel_speed_decimal;

static uint8_t ui8_walk_assist_timeout = 0;

uint16_t ui16_m_battery_current_filtered_x10;
uint16_t ui16_m_motor_current_filtered_x10;
uint16_t ui16_m_pedal_power_filtered;

uint8_t g_showNextScreenIndex = 0;
uint8_t g_showNextScreenPreviousIndex = 0;
uint16_t ui16_m_alternate_field_value;
uint8_t ui8_m_alternate_field_state = 0;
uint8_t ui8_m_alternate_field_timeout_cnt = 0;
uint8_t ui8_m_vthrottle_can_increment_decrement = 0;

void lcd_main_screen(void);
void warnings(void);
void power(void);
void time(void);
void wheel_speed(void);
void battery_soc(void);
void up_time(void);
// void trip_time(void);
void updateTripTime(uint32_t tripTime, Field *field);
void wheel_speed(void);
void showNextScreen();
static bool renderWarning(FieldLayout *layout);
void DisplayResetToDefaults(void);
void TripMemoriesReset(void);
void DisplayResetBluetoothPeers(void);
void torqueSensorCalibration(void);
void positionSensorCalibration(void);
void updateAssistLevels();
void onSetConfigurationBatteryTotalWh(uint32_t v);
void batteryTotalWh(void);
void batteryCurrent(void);
void batteryResistance(void);
void motorCurrent(void);
void batteryPower(void);
void pedalPower(void);
void thresholds(void);

/// set to true if this boot was caused because we had a watchdog failure, used to show user the problem in the fault line
bool wd_failure_detected;

#define MAX_TIMESTR_LEN 8 // including nul terminator
#define MAX_BATTERY_POWER_USAGE_STR_LEN 6 // Wh/km or Wh/mi , including nul terminator
#define MAX_ALTERNATE_USAGE_STR_LEN 10 // "max power", "throttle"  including nul terminator

//
// Fields - these might be shared my multiple screens
//
Field socField = FIELD_DRAWTEXT_RW();
Field timeField = FIELD_DRAWTEXT_RW();
Field assistLevelField = FIELD_READONLY_UINT("ASSIST", &ui_vars.ui8_assist_level, "", false);
Field wheelSpeedIntegerField = FIELD_READONLY_UINT("SPEED", &ui8_m_wheel_speed_integer, "kph", false);
Field wheelSpeedDecimalField = FIELD_READONLY_UINT("", &ui8_m_wheel_speed_decimal, "kph", false);
Field wheelSpeedField = FIELD_READONLY_UINT("SPEED", &ui_vars.ui16_wheel_speed_x10, "kph", true, .div_digits = 1);

// Note: this field is special, the string it is pointing to must be in RAM so we can change it later
Field upTimeField = FIELD_READONLY_STRING(_S("up time", "UP TIME"), (char [MAX_TIMESTR_LEN]){ 0 });

// Field tripADistanceField = FIELD_READONLY_UINT(_S("A trip dist", "A trip dis"), &ui_vars.ui32_trip_a_distance_x100, "km", false, .div_digits = 2);
// // Note: this field is special, the string it is pointing to must be in RAM so we can change it later
// Field tripATimeField = FIELD_READONLY_STRING(_S("A trip time", "A trip tim"), (char [MAX_TIMESTR_LEN]){ 0 });
// Field tripAAvgSpeedField = FIELD_READONLY_UINT(_S("A avg speed", "A avgspeed"), &ui_vars.ui16_trip_a_avg_speed_x10, "kph", true, .div_digits = 1);
// Field tripAMaxSpeedField = FIELD_READONLY_UINT(_S("A max speed", "A maxspeed"), &ui_vars.ui16_trip_a_max_speed_x10, "kph", true, .div_digits = 1);

// Field tripBDistanceField = FIELD_READONLY_UINT(_S("B trip dist", "B trip dis"), &ui_vars.ui32_trip_b_distance_x100, "km", false, .div_digits = 2);
// // Note: this field is special, the string it is pointing to must be in RAM so we can change it later
// Field tripBTimeField = FIELD_READONLY_STRING(_S("B trip time", "B trip tim"), (char [MAX_TIMESTR_LEN]){ 0 });
// Field tripBAvgSpeedField = FIELD_READONLY_UINT(_S("B avg speed", "B avgspeed"), &ui_vars.ui16_trip_b_avg_speed_x10, "kph", true, .div_digits = 1);
// Field tripBMaxSpeedField = FIELD_READONLY_UINT(_S("B max speed", "B maxspeed"), &ui_vars.ui16_trip_b_max_speed_x10, "kph", true, .div_digits = 1);

Field odoField = FIELD_READONLY_UINT("ODOMETER", &ui_vars.ui32_odometer_x10, "km", false, .div_digits = 1);
Field cadenceField = FIELD_READONLY_UINT("CADENCE", &ui_vars.ui8_pedal_cadence_filtered, "rpm", true, .div_digits = 0);
Field humanPowerField = FIELD_READONLY_UINT(_S("human power", "HUMAN POWR"), &ui16_m_pedal_power_filtered, "W", true, .div_digits = 0);
Field batteryPowerField = FIELD_READONLY_UINT(_S("motor power", "MOTOR POWR"), &ui_vars.ui16_battery_power_filtered_ui, "W", true, .div_digits = 0);
Field batteryPowerUsedField = FIELD_READONLY_UINT("POWER USED", &ui_vars.ui32_wh_x10, "kWh", true, .div_digits = 1);
Field batteryPowerRemainField = FIELD_READONLY_UINT("POW REMAIN", &ui_vars.ui32_wh_x10_remain, "kWh", false, .div_digits = 1);
Field fieldAlternate = FIELD_READONLY_UINT((char [MAX_ALTERNATE_USAGE_STR_LEN]){ 0 }, &ui16_m_alternate_field_value, "", 0, 2500, .div_digits = 0,);
Field batteryVoltageField = FIELD_READONLY_UINT(_S("batt voltage", "BAT VOLTS"), &ui_vars.ui16_battery_voltage_filtered_x10, "", true, .div_digits = 1);
Field batteryCurrentField = FIELD_READONLY_UINT(_S("batt current", "BAT CURREN"), &ui16_m_battery_current_filtered_x10, "", true, .div_digits = 1);
Field motorCurrentField = FIELD_READONLY_UINT(_S("motor current", "MOT CURREN"), &ui16_m_motor_current_filtered_x10, "", true, .div_digits = 1);
Field batterySOCField = FIELD_READONLY_UINT(_S("battery SOC", "BAT SOC"), &ui8_g_battery_soc, "%", true, .div_digits = 0);
Field motorTempField = FIELD_READONLY_UINT(_S("motor temp", "MOT TEMP"), &ui_vars.ui8_motor_temperature, "C", true, .div_digits = 0);
Field motorErpsField = FIELD_READONLY_UINT(_S("motor speed", "MOT SPEED"), &ui_vars.ui16_motor_speed_erps, "", true, .div_digits = 0);
Field pwmDutyField = FIELD_READONLY_UINT(_S("motor pwm", "MOT PWM"), &ui_vars.ui8_duty_cycle, "", true, .div_digits = 0);
Field motorFOCField = FIELD_READONLY_UINT(_S("motor foc", "MOT FOC"), &ui_vars.ui8_foc_angle, "", true, .div_digits = 0);
Field batteryPowerPerKmField = FIELD_READONLY_UINT((char [MAX_BATTERY_POWER_USAGE_STR_LEN]){ 0 }, &ui_vars.battery_energy_km_value_x100, "kph", true, .div_digits = 2);
Field EscTempField = FIELD_READONLY_UINT(_S("esc temp", "ESC TEMP"), &ui_vars.ui8_esc_temperature, "C", true, .div_digits = 0);


Field warnField = FIELD_CUSTOM(renderWarning);

/**
 * NOTE: The indexes into this array are stored in EEPROM, to prevent user confusion add new options only at the end.
 * If you remove old values, either warn users or bump up eeprom version to force eeprom contents to be discarded.
 */
#ifdef MOTOR_TSDZ2
Field *customizables[] = {
    &upTimeField, // 0
    &odoField, // 1
    &wheelSpeedField, // 2
    &cadenceField, // 3
		&humanPowerField, // 4
		&batteryPowerField, // 5
    &batteryVoltageField, // 6
    &batteryCurrentField, // 7
    &motorCurrentField, // 8
    &batterySOCField, // 9
		&motorTempField, // 10
    &motorErpsField, // 11
		&pwmDutyField, // 12
		&motorFOCField, // 13
		&batteryPowerPerKmField, // 14
    &batteryPowerUsedField, // 15
    &batteryPowerRemainField, // 16
		NULL
};
#elif defined(MOTOR_BAFANG)
Field *customizables[] = {
    &upTimeField, // 0
    &odoField, // 1
    &wheelSpeedField, // 2
    &cadenceField, // 3
		&humanPowerField, // 4
		&batteryPowerField, // 5
    &batteryVoltageField, // 6
    &batteryCurrentField, // 7
    &batterySOCField, // 8
		&motorTempField, // 9
		&batteryPowerPerKmField, // 10
    &batteryPowerUsedField, // 11
    &batteryPowerRemainField, // 12
    &EscTempField, //13
		NULL
};
#endif

// Note: field_selectors[0] is used on the 850C for the graphs selector
Field custom1 = FIELD_CUSTOMIZABLE_PTR(&ui_vars.field_selectors[0], customizables),
  custom2 = FIELD_CUSTOMIZABLE_PTR(&ui_vars.field_selectors[1], customizables),
  custom3 = FIELD_CUSTOMIZABLE_PTR(&ui_vars.field_selectors[2], customizables),
  custom4 = FIELD_CUSTOMIZABLE_PTR(&ui_vars.field_selectors[3], customizables),
  custom5 = FIELD_CUSTOMIZABLE_PTR(&ui_vars.field_selectors[4], customizables),
  custom6 = FIELD_CUSTOMIZABLE_PTR(&ui_vars.field_selectors[5], customizables);


#ifdef MOTOR_TSDZ2
Field bootHeading = FIELD_DRAWTEXT_RO("EasyDIY"),
   bootURL_1 = FIELD_DRAWTEXT_RO("TSDZ2"),
   bootURL_2 = FIELD_DRAWTEXT_RO(""),
   bootVersion = FIELD_DRAWTEXT_RO(VERSION_STRING),
   bootStatus2 = FIELD_DRAWTEXT_RW(.msg = "");
#elif defined(MOTOR_BAFANG)
Field bootHeading = FIELD_DRAWTEXT_RO("EasyDIY"),
   bootURL_1 = FIELD_DRAWTEXT_RO("Bafang"),
   bootURL_2 = FIELD_DRAWTEXT_RO("M500/M600"),
   bootVersion = FIELD_DRAWTEXT_RO(VERSION_STRING);
#endif

static void bootScreenOnPreUpdate() {
  switch (g_motor_init_state) {
    case MOTOR_INIT_WAIT_GOT_CONFIGURATIONS_OK:
    case MOTOR_INIT_READY:
      if (buttons_get_onoff_state() == 0) {
        buttons_clear_all_events();
        showNextScreen();
      } else {
#ifdef MOTOR_TSDZ2
        if ((g_motor_init_state == MOTOR_INIT_WAIT_GOT_CONFIGURATIONS_OK) ||
            (g_motor_init_state == MOTOR_INIT_READY)) {
          fieldPrintf(&bootStatus2, "%u.%u.%u",
          g_tsdz2_firmware_version.major,
          g_tsdz2_firmware_version.minor,
          g_tsdz2_firmware_version.patch);
        }
#endif
      }

    // any error state will block here and avoid leave the boot screen
    default:
      break;
  }
}

void bootScreenOnExit(void) {
  // now that we are goind to main screen, start by showing the assist level for 5 seconds
  m_assist_level_change_timeout = 50;
}

Screen bootScreen = {
  .onPreUpdate = bootScreenOnPreUpdate,
  .onExit = bootScreenOnExit,

  .fields = {
    {
      .x = 0, .y = YbyEighths(0) + 2, .height = -1,
      .field = &bootHeading,
      .font = &REGULAR_TEXT_FONT,
    },
    {
      .x = 0, .y = -24, .height = -1,
      .field = &bootURL_1,
      .font = &SMALL_TEXT_FONT,
    },
    {
      .x = 0, .y = -6, .height = -1,
      .field = &bootURL_2,
      .font = &SMALL_TEXT_FONT,
    },
    {
      .x = 0, .y = -24, .height = -1,
      .field = &bootVersion,
      .font = &SMALL_TEXT_FONT,
    },
#ifdef MOTOR_TSDZ2
    {
      .x = 0, .y = YbyEighths(7), .height = -1,
      .field = &bootStatus2,
      .font = &SMALL_TEXT_FONT,
    },
#endif
    {
      .field = NULL
    }
  }
};

// Allow common operations (like walk assist and headlights) button presses to work on any page
bool anyscreen_onpress(buttons_events_t events) {
  if ((events & DOWN_LONG_CLICK) && ui_vars.ui8_walk_assist_feature_enabled) {
    ui_vars.ui8_walk_assist = 1;
    return true;
  }

  // long up to turn on headlights
  if (events & UP_LONG_CLICK) {
    ui_vars.ui8_lights = !ui_vars.ui8_lights;
    set_lcd_backlight();

    return true;
  }

  return false;
}

static bool onPressAlternateField(buttons_events_t events) {
  bool handled = false;

  // start increment throttle only with UP_LONG_CLICK
  if ((ui8_m_alternate_field_state == 7) &&
      (events & UP_LONG_CLICK) &&
      (ui8_m_vthrottle_can_increment_decrement == 0)) {
    ui8_m_vthrottle_can_increment_decrement = 1;
    events |= UP_CLICK; // let's increment, consider UP CLICK
    ui8_m_alternate_field_timeout_cnt = 50; // 50 * 20ms = 1 second
  }

  if (ui8_m_alternate_field_timeout_cnt == 0) {
    ui_vars.ui8_throttle_virtual = 0;
    ui8_m_vthrottle_can_increment_decrement = 0;
  }

  switch (ui8_m_alternate_field_state) {
    case 0:
      if (events & SCREENCLICK_ALTERNATE_FIELD_START) {
        ui8_m_alternate_field_state = 1;
        handled = true;
      }
      break;

    // max power
    case 3:
      if (
        (
          ui_vars.ui8_street_mode_function_enabled
          && ui_vars.ui8_street_mode_enabled
          && ui_vars.ui8_street_mode_throttle_enabled
          || !ui_vars.ui8_street_mode_function_enabled
          || !ui_vars.ui8_street_mode_enabled
        )
        && events & SCREENCLICK_ALTERNATE_FIELD_START
      ) {
        ui8_m_alternate_field_state = 6;
        handled = true;
        break;
      }

      if (events & SCREENCLICK_ALTERNATE_FIELD_STOP) {
        ui8_m_alternate_field_state = 4;
        handled = true;
        break;
      }

      if (events & UP_CLICK) {
        handled = true;

        if (ui_vars.ui8_target_max_battery_power_div25 < 10) {
          ui_vars.ui8_target_max_battery_power_div25++;
        } else {
          ui_vars.ui8_target_max_battery_power_div25 += 2;
        }

        // limit to 100 * 25 = 2500 Watts
        if(ui_vars.ui8_target_max_battery_power_div25 > 100) {
          ui_vars.ui8_target_max_battery_power_div25 = 100;
        }

        break;
      }

      if (events & DOWN_CLICK) {
        handled = true;

        if (ui_vars.ui8_target_max_battery_power_div25 <= 10 &&
            ui_vars.ui8_target_max_battery_power_div25 > 1) {
          ui_vars.ui8_target_max_battery_power_div25--;
        } else if (ui_vars.ui8_target_max_battery_power_div25 > 10) {
          ui_vars.ui8_target_max_battery_power_div25 -= 2;
        }

        break;
      }
    break;

    // virtual throttle
    case 7:
      if (events & SCREENCLICK_ALTERNATE_FIELD_START) {
        ui8_m_alternate_field_state = 1;
        handled = true;
        break;
      }

      if (events & SCREENCLICK_ALTERNATE_FIELD_STOP) {
        ui_vars.ui8_throttle_virtual = 0;
        ui8_m_alternate_field_timeout_cnt = 0;
        ui8_m_vthrottle_can_increment_decrement = 0;
        ui8_m_alternate_field_state = 4;
        handled = true;
        break;
      }

      if (events & UP_CLICK) {
        handled = true;

        if (ui8_m_vthrottle_can_increment_decrement &&
            ui_vars.ui8_assist_level) {
          if ((ui_vars.ui8_throttle_virtual + ui_vars.ui8_throttle_virtual_step) <= 100) {
            ui_vars.ui8_throttle_virtual += ui_vars.ui8_throttle_virtual_step;
          } else {
            ui_vars.ui8_throttle_virtual = 100;
          }

          ui8_m_alternate_field_timeout_cnt = 50;
        }

        break;
      }

      if (events & DOWN_CLICK) {
        handled = true;

        if (ui8_m_vthrottle_can_increment_decrement &&
            ui_vars.ui8_assist_level) {
          if (ui_vars.ui8_throttle_virtual >= ui_vars.ui8_throttle_virtual_step) {
            ui_vars.ui8_throttle_virtual -= ui_vars.ui8_throttle_virtual_step;
          } else {
            ui_vars.ui8_throttle_virtual = 0;
          }

          ui8_m_alternate_field_timeout_cnt = 50;
        }

        break;
      }
    break;
  }

  if (ui8_m_alternate_field_state == 7) {
    // user will keep UP DOWN LONG clicks on this state, so, clean them to not pass to next code
    if ((events & UP_LONG_CLICK) ||
        (events & DOWN_LONG_CLICK))
      handled = true;
  }

  return handled;
}

static bool onPressStreetMode(buttons_events_t events) {
  bool handled = false;

  if (events & SCREENCLICK_STREET_MODE)
  {
    if (ui_vars.ui8_street_mode_function_enabled && ui_vars.ui8_street_mode_hotkey_enabled)
    {
      if (ui_vars.ui8_street_mode_enabled)
        ui_vars.ui8_street_mode_enabled = 0;
      else
        ui_vars.ui8_street_mode_enabled = 1;

      mainScreenOnDirtyClean();
    }

    handled = true;
  }

  return handled;
}

bool mainScreenOnPress(buttons_events_t events) {
  bool handled = false;

  // handled = onPressAlternateField(events);

  if (handled == false)
    handled = anyscreen_onpress(events);

  // if (handled == false)
  //   handled = onPressStreetMode(events);

  if (handled == false &&
      ui8_m_alternate_field_state == 0) {
    
    if (events & UP_CLICK) {
      ui_vars.ui8_assist_level++;

      if (ui_vars.ui8_assist_level > ui_vars.ui8_number_of_assist_levels) {
        ui_vars.ui8_assist_level = ui_vars.ui8_number_of_assist_levels;
      }

      m_assist_level_change_timeout = 20; // 2 seconds
      handled = true;
    }

    if (events & DOWN_CLICK
      && !ui_vars.ui8_walk_assist // do not lower assist level if walk assist is active
    ) {
      if (ui_vars.ui8_assist_level > 0)
        ui_vars.ui8_assist_level--;

      m_assist_level_change_timeout = 20; // 2 seconds
      handled = true;
    }
  }

	return handled;
}


void set_conversions() {
  screenConvertMiles = ui_vars.ui8_units_type != 0; // Set initial value on unit conversions (FIXME, move this someplace better)
  screenConvertFarenheit = screenConvertMiles; // FIXME, should be based on a different eeprom config value
  screenConvertPounds = screenConvertMiles;
}

void lcd_main_screen(void) {
	walk_assist_state();
//  offroad_mode();
	battery_soc();
	battery_display();
	warnings();
  up_time();
	// trip_time();
	wheel_speed();
}

void wheel_speed(void)
{
  uint16_t ui16_wheel_speed = ui_vars.ui16_wheel_speed_x10;

  // reset otherwise at startup this value goes crazy
  if (ui8_g_motorVariablesStabilized == 0)
    ui16_wheel_speed = 0;

  ui8_m_wheel_speed_integer = (uint8_t) (ui16_wheel_speed / 10);
  ui8_m_wheel_speed_decimal = (uint8_t) (ui16_wheel_speed % 10);

  // if we are inside the timeout, override the wheel speed value so assist level is shown there
  if (m_assist_level_change_timeout > 0) {
    m_assist_level_change_timeout--;
    ui8_m_wheel_speed_integer = ui_vars.ui8_assist_level;
  }
}

void alternatField(void) {
  static const char str_max_power[] = "max power";
  static const char str_throttle[] = "throttle";

  switch (ui8_m_alternate_field_state) {
    case 1:
      wheelSpeedIntegerField.rw->visibility = FieldTransitionNotVisible;
      ui8_m_alternate_field_state = 2;
      break;

    case 2:
      updateReadOnlyLabelStr(&fieldAlternate, str_max_power);
      fieldAlternate.rw->visibility = FieldTransitionVisible;
      mainScreenOnDirtyClean();
      ui8_m_alternate_field_state = 3;
      break;

    case 3:
      // keep updating the variable to show on display
      ui16_m_alternate_field_value = ((uint16_t) ui_vars.ui8_target_max_battery_power_div25) * 25;
      break;

    case 4:
      fieldAlternate.rw->visibility = FieldTransitionNotVisible;
      ui8_m_alternate_field_state = 5;
      break;

    case 5:
      wheelSpeedIntegerField.rw->visibility = FieldTransitionVisible;
      mainScreenOnDirtyClean();
      ui8_m_alternate_field_state = 0;
      break;

    case 6:
      updateReadOnlyLabelStr(&fieldAlternate, str_throttle);
      mainScreenOnDirtyClean();
      ui8_m_alternate_field_state = 7;
      break;

    case 7:
      // keep updating the variable to show on display
      ui16_m_alternate_field_value = (uint16_t) ui_vars.ui8_throttle_virtual;
      break;
  }
}

void streetMode(void) {
  if (ui_vars.ui8_street_mode_function_enabled)
  {
    ui_vars.ui8_street_mode_power_limit_div25 = (ui_vars.ui16_street_mode_power_limit / 25);
  }
}

void mainscreen_clock(void) {
  lcd_main_screen();
  DisplayResetToDefaults();
  TripMemoriesReset();
  DisplayResetBluetoothPeers();
#ifdef MOTOR_TSDZ2
#elif defined(MOTOR_BAFANG)
  updateAssistLevels();
  torqueSensorCalibration();
  positionSensorCalibration();
#endif
  batteryCurrent();
  batteryResistance();
  motorCurrent();
  batteryPower();
  pedalPower();
  alternatField();
  streetMode();

  // finally, update the screen
  screenUpdate();
}

void up_time(void) {
	rtc_time_t *p_time = rtc_get_time_since_startup();
	static int oldmin = -1; // used to prevent unneeded updates
	char timestr[MAX_TIMESTR_LEN]; // 12:13

	if (p_time->ui8_minutes != oldmin) {
		oldmin = p_time->ui8_minutes;
		sprintf(timestr, "%d:%02d", p_time->ui8_hours, p_time->ui8_minutes);
		updateReadOnlyStr(&upTimeField, timestr);
	}
}

// void trip_time(void){
//   updateTripTime(ui_vars.ui32_trip_a_time, &tripATimeField);
//   updateTripTime(ui_vars.ui32_trip_b_time, &tripBTimeField);
// }

void updateTripTime(uint32_t tripTime, Field *field) {
  char timestr[MAX_TIMESTR_LEN]; // 12:13
  uint32_t ui32_temp = tripTime % 86399; // 86399 = seconds in 1 day minus 1s

  // Calculate trip time
  uint8_t hours = ui32_temp / 3600;
  uint8_t minutes = (ui32_temp % 3600) / 60;
  uint8_t seconds = (ui32_temp % 3600) % 60;

  if(hours > 0)  
    sprintf(timestr, "%d:%02d", hours, minutes);
  else
    sprintf(timestr, "%d:%02d", minutes, seconds);

  //sprintf(timestr, "%d:%02d:%02d", hours, minutes, seconds);

  if(strcmp(field->editable.target, timestr) != 0)
    updateReadOnlyStr(field, timestr);
}

static ColorOp warnColor = ColorNormal;
static char warningStr[MAX_FIELD_LEN];

// We use a custom callback so we can reuse the standard drawtext code, but with a dynamically changing color
static bool renderWarning(FieldLayout *layout) {
	layout->color = warnColor;
	return renderDrawTextCommon(layout, warningStr);
}

void setWarning(ColorOp color, const char *str) {
	warnColor = color;
	warnField.rw->blink = (color == ColorError);
	warnField.rw->dirty = (strcmp(str, warningStr) != 0);
	if(warnField.rw->dirty)
		strncpy(warningStr, str, sizeof(warningStr));
}

static const char *motorErrors[] = { _S("None", "None"), _S("Motor init", "Motor init"), "Motor Blocked", "Torque Fault", "Brake Fault", "Throttle Fault", "Speed Fault", "Low Volt", "Comms"};

void warnings(void) {
  uint32_t motor_temp_limit = ui_vars.ui8_temperature_limit_feature_enabled & 1;
  uint8_t ui8_motorErrorsIndex;

  switch (g_motor_init_state) {
    case MOTOR_INIT_ERROR_SET_CONFIGURATIONS:
      setWarning(ColorError, _S("Error set config", "e: config"));
      return;

    case MOTOR_INIT_WAIT_CONFIGURATIONS_OK:
    case MOTOR_INIT_WAIT_GOT_CONFIGURATIONS_OK:
      setWarning(ColorWarning, _S("Motor init", "Motor init"));
      return;
  }

	// High priorty faults in red
  if (ui_vars.ui8_error_states) {
    if (ui_vars.ui8_error_states & 1)
      ui8_motorErrorsIndex = 1;
    else if (ui_vars.ui8_error_states & 2)
//      ui8_motorErrorsIndex = 2; // ignore this error for now
      return;
    else if (ui_vars.ui8_error_states & 4)
      ui8_motorErrorsIndex = 3;
    else if (ui_vars.ui8_error_states & 8)
      ui8_motorErrorsIndex = 4;
    else if (ui_vars.ui8_error_states & 16)
      ui8_motorErrorsIndex = 5;
    else if (ui_vars.ui8_error_states & 32)
      ui8_motorErrorsIndex = 6;
    else if (ui_vars.ui8_error_states & 64)
      ui8_motorErrorsIndex = 7;
    else if (ui_vars.ui8_error_states & 128)
      ui8_motorErrorsIndex = 8;

    char str[24];
    snprintf(str, sizeof(str), "%s%d%s%s", "e: ", ui8_motorErrorsIndex, " ", motorErrors[ui8_motorErrorsIndex]);
		setWarning(ColorError, str);
		return;
	}

	if (motor_temp_limit &&
	    ui_vars.ui8_motor_temperature >= ui_vars.ui8_motor_temperature_max_value_to_limit) {
		setWarning(ColorError, _S("Temp Shutdown", "Temp Shut"));
		return;
	}

	// If we had a watchdog failure, show it forever - so user will report a bug
	if (wd_failure_detected) {
    setWarning(ColorError, "Report Bug!");
    return;
	}

	// warn faults in yellow
  if (motor_temp_limit &&
      ui_vars.ui8_motor_temperature >= ui_vars.ui8_motor_temperature_min_value_to_limit) {
		setWarning(ColorWarning, _S("Temp Warning", "Temp Warn"));
		return;
	}

	// All of the following possible 'faults' are low priority

	if (ui_vars.ui8_braking) {
		setWarning(ColorNormal, "BRAKE");
		return;
	}

	if(ui_vars.ui8_walk_assist) {
		setWarning(ColorNormal, "WALK");
		return;
	}

	if (ui_vars.ui8_lights) {
		setWarning(ColorNormal, "LIGHT");
		return;
	}

	setWarning(ColorNormal, "");
}

void battery_soc(void) {
  switch (ui_vars.ui8_battery_soc_enable) {
    default:
    case 0:
      // clear the area
      fieldPrintf(&socField, "");
      break;

    case 1:
      fieldPrintf(&socField, "%3d%", ui8_g_battery_soc);
      break;

    case 2:
      fieldPrintf(&socField, "%u.%1u",
          ui_vars.ui16_battery_voltage_soc_x10 / 10,
          ui_vars.ui16_battery_voltage_soc_x10 % 10);
      break;
  }
}

// Screens in a loop, shown when the user short presses the power button
extern Screen *screens[];

void showNextScreen() {
  g_showNextScreenPreviousIndex = g_showNextScreenIndex;

  // increase to index of next screen
  if (screens[++g_showNextScreenIndex] == NULL) {
    g_showNextScreenIndex = 0;
  }

	screenShow(screens[g_showNextScreenIndex]);
}

bool appwide_onpress(buttons_events_t events)
{
// on Bafang M500/M600, at long press, the motor controller will turn off the display power
#ifdef MOTOR_TSDZ2
  if (events & ONOFF_LONG_CLICK)
  {
    system_power_off(1);
    return true;
  }
#endif

#ifdef DEVELOPMENT
  if ((events & SCREENCLICK_NEXT_SCREEN)) {
#else
  if ((events & SCREENCLICK_NEXT_SCREEN) &&
  (g_motor_init_state == MOTOR_INIT_READY)) {
#endif
    showNextScreen();
    return true;
  }

  if (events & SCREENCLICK_ENTER_CONFIGURATIONS) {
    screenShow(&configScreen);
    return true;
  }

  if (events & SCREENCLICK_ANT_CONTROLS_PAGE_MOVE_FORWARD) {
    buttons_send_pag73(&m_antplus_controls, 1);
    return true;
  } else if (events & SCREENCLICK_ANT_CONTROLS_PAGE_MOVE_BACKWARD) {
    buttons_send_pag73(&m_antplus_controls, 0);
    return true;
  }

	return false;
}

/// Called every 50ms
void handle_buttons() {

  static uint8_t firstTime = 1;

  // keep tracking of first time release of onoff button
  if(firstTime && buttons_get_onoff_state() == 0) {
    firstTime = 0;
    buttons_clear_onoff_click_event();
    buttons_clear_onoff_long_click_event();
    buttons_clear_onoff_click_long_click_event();
  }

  if (buttons_get_events() && firstTime == 0)
  {
    bool handled = false;

		if (!handled)
			handled |= screenOnPress(buttons_get_events());

		// Note: this must be after the screen/menu handlers have had their shot
		if (!handled)
			handled |= appwide_onpress(buttons_get_events());

		if (handled)
			buttons_clear_all_events();
	}

  // if (buttons_get_events() && firstTime == 0)
  // {
 	// 	if (wiredRemoteOnPress(buttons_get_events())) buttons_clear_all_events();
  // }

	buttons_clock(); // Note: this is done _after_ button events is checked to provide a 50ms debounce
}

void mainscreen_idle() {
 	automatic_power_off_management();
	handle_buttons();
	mainscreen_clock(); // This is _after_ handle_buttons so if a button was pressed this tick, we immediately update the GUI
}

void onSetConfigurationBatteryTotalWh(uint32_t v) {

  ui_vars.ui32_wh_x10_100_percent = v * 10;
}

void DisplayResetToDefaults(void) {
  if (ui8_g_configuration_display_reset_to_defaults) {
    ui8_g_configuration_display_reset_to_defaults = 0;
    eeprom_init_defaults();
  }
}

void TripMemoriesReset(void) {
//   if (ui8_g_configuration_trip_a_reset) {
//     ui8_g_configuration_trip_a_reset = 0;
//     rt_vars.ui32_trip_a_distance_x1000 = 0;
//     rt_vars.ui32_trip_a_time = 0;
//     rt_vars.ui16_trip_a_avg_speed_x10 = 0;
//     rt_vars.ui16_trip_a_max_speed_x10 = 0;
//   }

//   if (ui8_g_configuration_trip_b_reset) {
//     ui8_g_configuration_trip_b_reset = 0;
//     rt_vars.ui32_trip_b_distance_x1000 = 0;
//     rt_vars.ui32_trip_b_time = 0;
//     rt_vars.ui16_trip_b_avg_speed_x10 = 0;
//     rt_vars.ui16_trip_b_max_speed_x10 = 0;
//   }
}

void DisplayResetBluetoothPeers(void) {
  if (ui8_g_configuration_display_reset_bluetooth_peers) {
    ui8_g_configuration_display_reset_bluetooth_peers = 0;
    // TODO: fist disable any connection
    // Warning: Use this (pm_peers_delete) function only when not connected or connectable. If a peer is or becomes connected
    // or a PM_PEER_DATA_FUNCTIONS function is used during this procedure (until the success or failure event happens),
    // the behavior is undefined.
    pm_peers_delete();
  }
}

void torqueSensorCalibration(void) {
  if (ui8_g_configuration_torque_sensor_calibration) {
    ui8_g_configuration_torque_sensor_calibration = 0;
    
    // TODO: CAN send command
  }
}

void positionSensorCalibration(void) {
  if (ui8_g_configuration_position_sensor_calibration) {
    ui8_g_configuration_position_sensor_calibration = 0;
    
    // TODO: CAN send command
  }
}

void updateAssistLevels() {

  switch (ui8_g_configuration_assist_levels) {
    case 0:
      ui_vars.ui8_number_of_assist_levels = 3;
    break;

    case 1:
      ui_vars.ui8_number_of_assist_levels = 5;
    break;

    case 2:
      ui_vars.ui8_number_of_assist_levels = 9;
    break;
  }
}

void batteryCurrent(void) {

  ui16_m_battery_current_filtered_x10 = ui_vars.ui16_battery_current_filtered_x5 * 2;
}

void batteryResistance(void) {

#ifdef MOTOR_TSDZ2
  #define CALC_BATTERY_RESISTANCE_MIN_CURRENT 10
#elif defined(MOTOR_BAFANG)
  #define CALC_BATTERY_RESISTANCE_MIN_CURRENT 6
#endif

  typedef enum {
    WAIT_MOTOR_STOP = 0,
    STARTUP = 1,
    DELAY = 2,
    CALC_RESISTANCE = 3,
  } state_t;

  static state_t state = WAIT_MOTOR_STOP;
  static uint8_t ui8_counter;
  static uint16_t ui16_batt_voltage_init_x10;
  uint16_t ui16_batt_voltage_final_x10;
  uint16_t ui16_batt_voltage_delta_x10;
  uint16_t ui16_batt_current_final_x5;

  switch (state) {
    case WAIT_MOTOR_STOP:
      // wait for motor stop to measure battery initial voltage
      if (ui_vars.ui16_motor_current_filtered_x5 == 0) {
        ui16_batt_voltage_init_x10 = ui_vars.ui16_battery_voltage_filtered_x10;
        ui8_counter = 0;
        state = STARTUP;
      }
      break;

    case STARTUP:
      // wait for motor running and at high battery current
#ifdef MOTOR_TSDZ2
      if ((ui_vars.ui16_motor_speed_erps > 10) &&
          (ui_vars.ui16_battery_current_filtered_x5 > CALC_BATTERY_RESISTANCE_MIN_CURRENT)) {
#elif defined(MOTOR_BAFANG)
      if (ui_vars.ui16_battery_current_filtered_x5 > CALC_BATTERY_RESISTANCE_MIN_CURRENT) {
#endif
        ui8_counter = 0;
        state = DELAY;
      } else {

        if (++ui8_counter > 50) // wait 5 seconds on this state
          state = WAIT_MOTOR_STOP;
      }
      break;

    case DELAY:
      if (ui_vars.ui16_battery_current_filtered_x5 > CALC_BATTERY_RESISTANCE_MIN_CURRENT) {

        if (++ui8_counter > 40) // sample battery final voltage after 4 seconds
          state = CALC_RESISTANCE;

      } else {
        state = WAIT_MOTOR_STOP;
      }
      break;

    case CALC_RESISTANCE:
      ui16_batt_voltage_final_x10 = ui_vars.ui16_battery_voltage_filtered_x10;
      ui16_batt_current_final_x5 = ui_vars.ui16_battery_current_filtered_x5;

      if (ui16_batt_voltage_init_x10 > ui16_batt_voltage_final_x10) {
        ui16_batt_voltage_delta_x10 = ui16_batt_voltage_init_x10 - ui16_batt_voltage_final_x10;
      } else {
        ui16_batt_voltage_delta_x10 = 0;
      }

      // R = U / I
      ui_vars.ui16_battery_pack_resistance_estimated_x1000 =
          (ui16_batt_voltage_delta_x10 * 500) / ui16_batt_current_final_x5 ;

      state = WAIT_MOTOR_STOP;
      break;
  }
}

void motorCurrent(void) {

  ui16_m_motor_current_filtered_x10 = ui_vars.ui16_motor_current_filtered_x5 * 2;
}

void batteryPower(void) {

  uint16_t ui16_battery_power = ui_vars.ui16_battery_power;

  // loose resolution under 200W
  if (ui16_battery_power < 200) {
    ui16_battery_power /= 10;
    ui16_battery_power *= 10;
  }
  // loose resolution under 400W
  else if (ui16_battery_power < 500) {
    ui16_battery_power /= 20;
    ui16_battery_power *= 20;
  }

  ui_vars.ui16_battery_power_filtered_ui = ui16_battery_power;
}

void pedalPower(void) {

  ui16_m_pedal_power_filtered = ui_vars.ui16_pedal_power;

  if (ui16_m_pedal_power_filtered > 500) {
    ui16_m_pedal_power_filtered /= 20;
    ui16_m_pedal_power_filtered *= 20;
  } else if (ui16_m_pedal_power_filtered > 200) {
    ui16_m_pedal_power_filtered /= 10;
    ui16_m_pedal_power_filtered *= 10;
  } else if (ui16_m_pedal_power_filtered > 10) {
    ui16_m_pedal_power_filtered /= 5;
    ui16_m_pedal_power_filtered *= 5;
  }
}

void onSetConfigurationBatterySOCUsedWh(uint32_t v) {
  reset_wh();
  ui_vars.ui32_wh_x10_offset = v;
}

#ifdef MOTOR_TSDZ2
#elif defined(MOTOR_BAFANG)
void onSetConfigurationChangeMaxWheelSpeed(uint32_t v) {
  can_set_max_wheel_speed(v);
}
void onSetConfigurationChangeWheelSize(uint32_t v) {
  can_set_wheel_size(v);
}
void onSetConfigurationChangeWheelPerimeter(uint32_t v) {
  can_set_wheel_perimeter(v);
}
#endif
