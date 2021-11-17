#include "screen.h"
#include "mainscreen.h"
#include "configscreen.h"
#include "eeprom.h"

// static Field tripMenus[] =
// 		{
//             FIELD_EDITABLE_ENUM(_S("Reset trip A", "Rst trip A"), &ui8_g_configuration_trip_a_reset, "no", "yes"),
//             FIELD_EDITABLE_ENUM(_S("Reset trip B", "Rst trip B"), &ui8_g_configuration_trip_b_reset, "no", "yes"),
// 				FIELD_END };

static Field wheelMenus[] =
		{
						FIELD_EDITABLE_UINT("Max speed", &ui_vars.ui8_wheel_max_speed, "kph", 1, 99, .div_digits = 0, .inc_step = 1, .hide_fraction = true),
						FIELD_EDITABLE_UINT(_S("Circumference", "Circumfere"), &ui_vars.ui16_wheel_perimeter, "mm", 750, 3000, .inc_step = 10),
				FIELD_END };

static Field batterySOCMenus[] =
    {
            FIELD_EDITABLE_ENUM("Text", &ui_vars.ui8_battery_soc_enable, "disable", "SOC %", "volts"),
            FIELD_EDITABLE_UINT(_S("Reset at voltage", "Reset at"), &ui_vars.ui16_battery_voltage_reset_wh_counter_x10, "volts", 160, 630, .div_digits = 1),
            FIELD_EDITABLE_UINT(_S("Battery total Wh", "Batt total"), &ui_vars.ui32_wh_x10_100_percent, "whr", 0, 9990, .div_digits = 1, .inc_step = 100),
            FIELD_EDITABLE_UINT("Used Wh", &ui_vars.ui32_wh_x10, "whr", 0, 99900, .div_digits = 1, .inc_step = 100, .onSetEditable = onSetConfigurationBatterySOCUsedWh),
        FIELD_END };

static Field batteryMenus[] =
		{
						FIELD_EDITABLE_UINT(_S("Max current", "Max curren"), &ui_vars.ui8_battery_max_current, "amps", 1, 20),
						FIELD_EDITABLE_UINT(_S("Low cut-off", "Lo cut-off"), &ui_vars.ui16_battery_low_voltage_cut_off_x10, "volts", 160, 630, .div_digits = 1),
            FIELD_EDITABLE_UINT(_S("Resistance", "Resistance"), &ui_vars.ui16_battery_pack_resistance_x1000, "mohm", 0, 1000),
            FIELD_READONLY_UINT(_S("Voltage est", "Voltag est"), &ui_vars.ui16_battery_voltage_soc_x10, "volts", false, .div_digits = 1),
            FIELD_READONLY_UINT(_S("Resistance est", "Resist est"), &ui_vars.ui16_battery_pack_resistance_estimated_x1000, "mohm", 0, 1000),
						FIELD_READONLY_UINT(_S("Power loss est", "Power loss"), &ui_vars.ui16_battery_power_loss, "watts", false, .div_digits = 0),
				FIELD_END };

static Field motorMenus[] = {
            FIELD_EDITABLE_ENUM(_S("Motor voltage", "Motor volt"), &ui_vars.ui8_motor_type, "48V", "36V"),
            FIELD_EDITABLE_UINT(_S("Max current", "Max curren"), &ui_vars.ui8_motor_max_current, "amps", 1, 30),
            FIELD_EDITABLE_UINT(_S("Current ramp", "Curre ramp"), &ui_vars.ui8_ramp_up_amps_per_second_x10, "amps", 4, 100, .div_digits = 1),
            FIELD_EDITABLE_ENUM(_S("Motor control", "Motor ctrl"), &ui_vars.ui8_motor_current_control_mode, "power", "torque"),
            FIELD_EDITABLE_UINT(_S("Min current ADC step", "Min ADC st"), &ui_vars.ui8_motor_current_min_adc, "amps", 0, 13), // 13 ADC steps = 2 amps
            FIELD_EDITABLE_ENUM(_S("Field weakening", "Field weak"), &ui_vars.ui8_field_weakening, "disable", "enable"),
        FIELD_END };

static Field torqueSensorMenus[] =
    {
            FIELD_EDITABLE_UINT(_S("Torque s ADC thresho", "Torq s thr"), &ui_vars.ui8_torque_sensor_adc_threshold, "", 5, 100),
            FIELD_EDITABLE_ENUM(_S("Assist w/o pedal rot", "A w/o ped"), &ui_vars.ui8_motor_assistance_startup_without_pedal_rotation, "disable", "enable"), // FIXME, share one array of disable/enable strings
            FIELD_EDITABLE_ENUM(_S("Coast brake", "Coast brak"), &ui_vars.ui8_coast_brake_enable, "disable", "enable"),
            FIELD_EDITABLE_UINT(_S("Coast brake ADC", "Coa bk ADC"), &ui_vars.ui8_coast_brake_adc, "", 5, 255),
            FIELD_EDITABLE_ENUM(_S("Calibration", "Calibrat"), &ui_vars.ui8_torque_sensor_calibration_feature_enabled, "disable", "enable"),
            FIELD_EDITABLE_UINT(_S("Torque sensor filter", "Torq s fil"), &ui_vars.ui8_torque_sensor_filter, "", 0, 100),
            FIELD_EDITABLE_ENUM(_S("Start pedal ground", "Pedal grou"), &ui_vars.ui8_torque_sensor_calibration_pedal_ground, "left", "right"),
            FIELD_EDITABLE_UINT(_S("Left weight 1", "L weight 1"), &ui_vars.ui16_torque_sensor_calibration_table_left[0][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 1", &ui_vars.ui16_torque_sensor_calibration_table_left[0][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Left weight 2", "L weight 2"), &ui_vars.ui16_torque_sensor_calibration_table_left[1][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 2", &ui_vars.ui16_torque_sensor_calibration_table_left[1][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Left weight 3", "L weight 3"), &ui_vars.ui16_torque_sensor_calibration_table_left[2][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 3", &ui_vars.ui16_torque_sensor_calibration_table_left[2][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Left weight 4", "L weight 4"), &ui_vars.ui16_torque_sensor_calibration_table_left[3][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 4", &ui_vars.ui16_torque_sensor_calibration_table_left[3][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Left weight 5", "L weight 5"), &ui_vars.ui16_torque_sensor_calibration_table_left[4][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 5", &ui_vars.ui16_torque_sensor_calibration_table_left[4][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Left weight 6", "L weight 6"), &ui_vars.ui16_torque_sensor_calibration_table_left[5][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 6", &ui_vars.ui16_torque_sensor_calibration_table_left[5][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Left weight 7", "L weight 7"), &ui_vars.ui16_torque_sensor_calibration_table_left[6][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 7", &ui_vars.ui16_torque_sensor_calibration_table_left[6][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Left weight 8", "L weight 8"), &ui_vars.ui16_torque_sensor_calibration_table_left[7][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Left ADC 8", &ui_vars.ui16_torque_sensor_calibration_table_left[7][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 1", "R weight 1"), &ui_vars.ui16_torque_sensor_calibration_table_right[0][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 1", &ui_vars.ui16_torque_sensor_calibration_table_right[0][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 2", "R weight 2"), &ui_vars.ui16_torque_sensor_calibration_table_right[1][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 2", &ui_vars.ui16_torque_sensor_calibration_table_right[1][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 3", "R weight 3"), &ui_vars.ui16_torque_sensor_calibration_table_right[2][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 3", &ui_vars.ui16_torque_sensor_calibration_table_right[2][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 4", "R weight 4"), &ui_vars.ui16_torque_sensor_calibration_table_right[3][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 4", &ui_vars.ui16_torque_sensor_calibration_table_right[3][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 5", "R weight 5"), &ui_vars.ui16_torque_sensor_calibration_table_right[4][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 5", &ui_vars.ui16_torque_sensor_calibration_table_right[4][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 6", "R weight 6"), &ui_vars.ui16_torque_sensor_calibration_table_right[5][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 6", &ui_vars.ui16_torque_sensor_calibration_table_right[5][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 7", "R weight 7"), &ui_vars.ui16_torque_sensor_calibration_table_right[6][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 7", &ui_vars.ui16_torque_sensor_calibration_table_right[6][1], "", 0, 1023),
            FIELD_EDITABLE_UINT(_S("Right weight 8", "R weight 8"), &ui_vars.ui16_torque_sensor_calibration_table_right[7][0], "kg", 0, 200),
            FIELD_EDITABLE_UINT("Right ADC 8", &ui_vars.ui16_torque_sensor_calibration_table_right[7][1], "", 0, 1023),
        FIELD_END };

static Field assistMenus[] =
		{
						// FIELD_EDITABLE_UINT(_S("Num assist levels", "Num Levels"), &ui_vars.ui8_number_of_assist_levels, "", 1, 20),
						FIELD_EDITABLE_UINT("Level 1", &ui_vars.ui16_assist_level_factor[0], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 2", &ui_vars.ui16_assist_level_factor[1], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 3", &ui_vars.ui16_assist_level_factor[2], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 4", &ui_vars.ui16_assist_level_factor[3], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 5", &ui_vars.ui16_assist_level_factor[4], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 6", &ui_vars.ui16_assist_level_factor[5], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 7", &ui_vars.ui16_assist_level_factor[6], "", 1, 65535, .div_digits = 3),
						// FIELD_EDITABLE_UINT("Level 8", &ui_vars.ui16_assist_level_factor[7], "", 1, 65535, .div_digits = 3),
						// FIELD_EDITABLE_UINT("Level 9", &ui_vars.ui16_assist_level_factor[8], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 10", &ui_vars.ui16_assist_level_factor[9], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 11", &ui_vars.ui16_assist_level_factor[10], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 12", &ui_vars.ui16_assist_level_factor[11], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 13", &ui_vars.ui16_assist_level_factor[12], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 14", &ui_vars.ui16_assist_level_factor[13], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 15", &ui_vars.ui16_assist_level_factor[14], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 16", &ui_vars.ui16_assist_level_factor[15], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 17", &ui_vars.ui16_assist_level_factor[16], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 18", &ui_vars.ui16_assist_level_factor[17], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 19", &ui_vars.ui16_assist_level_factor[18], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 20", &ui_vars.ui16_assist_level_factor[19], "", 1, 65535, .div_digits = 3),
				FIELD_END };

static Field walkAssistMenus[] =
		{
						FIELD_EDITABLE_ENUM("Feature", &ui_vars.ui8_walk_assist_feature_enabled, "disable", "enable"), // FIXME, share one array of disable/enable strings
						FIELD_EDITABLE_UINT("Level 1", &ui_vars.ui8_walk_assist_level_factor[0], "", 0, 100),
						FIELD_EDITABLE_UINT("Level 2", &ui_vars.ui8_walk_assist_level_factor[1], "", 0, 100),
						FIELD_EDITABLE_UINT("Level 3", &ui_vars.ui8_walk_assist_level_factor[2], "", 0, 100),
						FIELD_EDITABLE_UINT("Level 4", &ui_vars.ui8_walk_assist_level_factor[3], "", 0, 100),
						FIELD_EDITABLE_UINT("Level 5", &ui_vars.ui8_walk_assist_level_factor[4], "", 0, 100),
						FIELD_EDITABLE_UINT("Level 6", &ui_vars.ui8_walk_assist_level_factor[5], "", 0, 100),
						FIELD_EDITABLE_UINT("Level 7", &ui_vars.ui8_walk_assist_level_factor[6], "", 0, 100),
						// FIELD_EDITABLE_UINT("Level 8", &ui_vars.ui8_walk_assist_level_factor[7], "", 0, 100),
						// FIELD_EDITABLE_UINT("Level 9", &ui_vars.ui8_walk_assist_level_factor[8], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 10", &ui_vars.ui8_walk_assist_level_factor[9], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 11", &ui_vars.ui8_walk_assist_level_factor[10], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 12", &ui_vars.ui8_walk_assist_level_factor[11], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 13", &ui_vars.ui8_walk_assist_level_factor[12], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 14", &ui_vars.ui8_walk_assist_level_factor[13], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 15", &ui_vars.ui8_walk_assist_level_factor[14], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 16", &ui_vars.ui8_walk_assist_level_factor[15], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 17", &ui_vars.ui8_walk_assist_level_factor[16], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 18", &ui_vars.ui8_walk_assist_level_factor[17], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 19", &ui_vars.ui8_walk_assist_level_factor[18], "", 0, 100),
            // FIELD_EDITABLE_UINT("Level 20", &ui_vars.ui8_walk_assist_level_factor[19], "", 0, 100),
				FIELD_END };

static Field startupPowerMenus[] =
		{
						FIELD_EDITABLE_ENUM("Feature", &ui_vars.ui8_startup_motor_power_boost_feature_enabled, "disable", "enable"), // FIXME, share one array of disable/enable strings
						FIELD_EDITABLE_ENUM("Active on", &ui_vars.ui8_startup_motor_power_boost_always, "startup", "always"),
						FIELD_EDITABLE_ENUM(_S("Limit to max-power", "Lim to max"), &ui_vars.ui8_startup_motor_power_boost_limit_power, "no", "yes"),
						FIELD_EDITABLE_UINT("Duration", &ui_vars.ui8_startup_motor_power_boost_time, "secs", 0, 255, .div_digits = 1),
						FIELD_EDITABLE_UINT("Fade", &ui_vars.ui8_startup_motor_power_boost_fade_time, "secs", 0, 255, .div_digits = 1),
						FIELD_EDITABLE_UINT("Level 1", &ui_vars.ui16_startup_motor_power_boost_factor[0], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 2", &ui_vars.ui16_startup_motor_power_boost_factor[1], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 3", &ui_vars.ui16_startup_motor_power_boost_factor[2], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 4", &ui_vars.ui16_startup_motor_power_boost_factor[3], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 5", &ui_vars.ui16_startup_motor_power_boost_factor[4], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 6", &ui_vars.ui16_startup_motor_power_boost_factor[5], "", 1, 65535, .div_digits = 3),
						FIELD_EDITABLE_UINT("Level 7", &ui_vars.ui16_startup_motor_power_boost_factor[6], "", 1, 65535, .div_digits = 3),
						// FIELD_EDITABLE_UINT("Level 8", &ui_vars.ui16_startup_motor_power_boost_factor[7], "", 1, 65535, .div_digits = 3),
						// FIELD_EDITABLE_UINT("Level 9", &ui_vars.ui16_startup_motor_power_boost_factor[8], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 10", &ui_vars.ui16_startup_motor_power_boost_factor[9], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 11", &ui_vars.ui16_startup_motor_power_boost_factor[10], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 12", &ui_vars.ui16_startup_motor_power_boost_factor[11], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 13", &ui_vars.ui16_startup_motor_power_boost_factor[12], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 14", &ui_vars.ui16_startup_motor_power_boost_factor[13], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 15", &ui_vars.ui16_startup_motor_power_boost_factor[14], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 16", &ui_vars.ui16_startup_motor_power_boost_factor[15], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 17", &ui_vars.ui16_startup_motor_power_boost_factor[16], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 18", &ui_vars.ui16_startup_motor_power_boost_factor[17], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 19", &ui_vars.ui16_startup_motor_power_boost_factor[18], "", 1, 65535, .div_digits = 3),
            // FIELD_EDITABLE_UINT("Level 20", &ui_vars.ui16_startup_motor_power_boost_factor[19], "", 1, 65535, .div_digits = 3),
				FIELD_END };

static Field motorTempMenus[] =
		{
						FIELD_EDITABLE_ENUM("Feature", &ui_vars.ui8_temperature_limit_feature_enabled, "disable", "temperature", "throttle"),
						FIELD_EDITABLE_UINT("Min limit", &ui_vars.ui8_motor_temperature_min_value_to_limit, "C", 0, 255),
						FIELD_EDITABLE_UINT("Max limit", &ui_vars.ui8_motor_temperature_max_value_to_limit, "C", 0, 255),
				FIELD_END };

// static Field streetModeMenus[] =
//     {
//       FIELD_EDITABLE_ENUM("Feature", &ui_vars.ui8_street_mode_function_enabled, "disable", "enable"),
//       FIELD_EDITABLE_ENUM(_S("Enable Mode", "Enabl Mode"), &ui_vars.ui8_street_mode_enabled, "no", "yes"),
//       FIELD_EDITABLE_ENUM(_S("Enable at startup", "Enabl stup"), &ui_vars.ui8_street_mode_enabled_on_startup, "no", "yes"),
//       FIELD_EDITABLE_UINT(_S("Speed limit", "Speed limt"), &ui_vars.ui8_street_mode_speed_limit, "kph", 1, 99, .div_digits = 0, .inc_step = 1, .hide_fraction = true),
//       FIELD_EDITABLE_UINT(_S("Motor power limit", "Power limt"), &ui_vars.ui16_street_mode_power_limit, "watts", 25, 2500, .div_digits = 0, .inc_step = 25, .hide_fraction = true),
//       FIELD_EDITABLE_ENUM(_S("Throttle enable", "Throt enab"), &ui_vars.ui8_street_mode_throttle_enabled, "no", "yes"),
//       FIELD_EDITABLE_ENUM(_S("Hotkey enable", "HotKy enab"), &ui_vars.ui8_street_mode_hotkey_enabled, "no", "yes"),
//     FIELD_END };

static Field displayMenus[] =
		{
  FIELD_EDITABLE_UINT(_S("Auto power off", "Auto p off"), &ui_vars.ui8_system_power_off_time_minutes, "mins", 0, 255),
  FIELD_EDITABLE_ENUM("Units", &ui_vars.ui8_units_type, "SI", "Imperial"),
  // FIELD_EDITABLE_ENUM(_S("Reset BLE connections", "Reset BLE"), &ui8_g_configuration_display_reset_bluetooth_peers, "no", "yes"),
  FIELD_EDITABLE_ENUM(_S("Reset to defaults", "Reset def"), &ui8_g_configuration_display_reset_to_defaults, "no", "yes"),
  FIELD_END };

static Field variousMenus[] = {
    FIELD_EDITABLE_ENUM(_S("Cadence fast stop", "Cadenc stp"), &ui_vars.ui8_pedal_cadence_fast_stop, "no", "yes"),
    // FIELD_EDITABLE_UINT(_S("ADC lights offset", "ADC lights"), &ui_vars.ui8_adc_lights_current_offset, "", 0, 4),
    // FIELD_EDITABLE_UINT(_S("Virtual throttle step", "V thr step"), &ui_vars.ui8_throttle_virtual_step, "", 1, 100),
    FIELD_EDITABLE_UINT("Odometer", &ui_vars.ui32_odometer_x10, "km", 0, UINT32_MAX, .div_digits = 1, .inc_step = 100, .onSetEditable = onSetConfigurationWheelOdometer),
  FIELD_END };

static Field technicalMenus[] = {
  FIELD_READONLY_UINT(_S("ADC battery current", "ADC bat cu"), &ui_vars.ui16_adc_battery_current, ""),
  FIELD_READONLY_UINT(_S("ADC throttle sensor", "ADC thrott"), &ui_vars.ui8_adc_throttle, ""),
  FIELD_READONLY_UINT(_S("Throttle sensor", "Throttle s"), &ui_vars.ui8_throttle, ""),
  FIELD_READONLY_UINT(_S("ADC torque sensor", "ADC torque"), &ui_vars.ui16_adc_pedal_torque_sensor, ""),
  FIELD_READONLY_ENUM(_S("Pedal side", "Pedal side"), &ui_vars.ui8_pas_pedal_right, "left", "right"),
  FIELD_READONLY_UINT(_S("Weight with offset", "Weight off"), &ui_vars.ui8_pedal_weight_with_offset, "kg"),
  FIELD_READONLY_UINT(_S("Weight without offset", "Weight"), &ui_vars.ui8_pedal_weight, "kg"),
  FIELD_READONLY_UINT(_S("Pedal cadence", "Cadence"), &ui_vars.ui8_pedal_cadence, "rpm"),
  FIELD_READONLY_UINT(_S("PWM duty-cycle", "PWM duty"), &ui_vars.ui8_duty_cycle, ""),
  FIELD_READONLY_UINT(_S("Motor speed", "Mot speed"), &ui_vars.ui16_motor_speed_erps, ""),
  FIELD_READONLY_UINT("Motor FOC", &ui_vars.ui8_foc_angle, ""),
  FIELD_READONLY_UINT(_S("Hall sensors", "Hall sens"), &ui_vars.ui8_motor_hall_sensors, ""),
  FIELD_END };

static Field topMenus[] = {
  // FIELD_SCROLLABLE("Trip memories", tripMenus),
  FIELD_SCROLLABLE("Wheel", wheelMenus),
  FIELD_SCROLLABLE("Battery", batteryMenus),
  FIELD_SCROLLABLE("SOC", batterySOCMenus),
  FIELD_SCROLLABLE(_S("Motor", "Motor"), motorMenus),
  FIELD_SCROLLABLE(_S("Torque sensor", "Torque sen"), torqueSensorMenus),
  FIELD_SCROLLABLE(_S("Assist level", "Assist"), assistMenus),
  FIELD_SCROLLABLE(_S("Walk assist", "Walk"), walkAssistMenus),
  // FIELD_SCROLLABLE(_S("Startup BOOST", "Star BOOST"), startupPowerMenus),
  FIELD_SCROLLABLE(_S("Motor temperature", "Motor temp"), motorTempMenus),
  // FIELD_SCROLLABLE(_S("Street mode", "Street mod"), streetModeMenus),
  FIELD_SCROLLABLE("Various", variousMenus),
  FIELD_SCROLLABLE("Display", displayMenus),
  FIELD_SCROLLABLE("Technical", technicalMenus),
  FIELD_END };

static Field configRoot = FIELD_SCROLLABLE(_S("Configurations", "Config"), topMenus);

uint8_t ui8_g_configuration_display_reset_to_defaults = 0;
uint8_t ui8_g_configuration_display_reset_bluetooth_peers = 0;
uint8_t ui8_g_configuration_trip_a_reset = 0;
uint8_t ui8_g_configuration_trip_b_reset = 0;

static void configScreenOnEnter() {
	// Set the font preference for this screen
	editable_label_font = &CONFIGURATIONS_TEXT_FONT;
	editable_value_font = &CONFIGURATIONS_TEXT_FONT;
	editable_units_font = &CONFIGURATIONS_TEXT_FONT;
}

static void configExit() {
  prepare_torque_sensor_calibration_table();

	// save the variables on EEPROM
	eeprom_write_variables();
	set_conversions(); // we just changed units

  update_battery_power_usage_label();

	// send the configurations to TSDZ2
  if (g_motor_init_state == MOTOR_INIT_READY)
    g_motor_init_state = MOTOR_INIT_SET_CONFIGURATIONS;
}

static void configPreUpdate() {
  set_conversions(); // while in the config menu we might change units at any time - keep the display looking correct

//  updateReadOnlyStr(&displayMenus[7], VERSION_STRING);

//  static char firmware_version[11]; // 123.123.123
//  sprintf(firmware_version, "%d.%d.%d",
//          g_tsdz2_firmware_version.major,
//          g_tsdz2_firmware_version.minor,
//          g_tsdz2_firmware_version.patch);
//  updateReadOnlyStr(&displayMenus[7], firmware_version);
}

//
// Screens
//
Screen configScreen = {
    .onExit = configExit,
    .onEnter = configScreenOnEnter,
    .onPreUpdate = configPreUpdate,

    .fields = {
		  { .color = ColorNormal, .field = &configRoot },
		  { .field = NULL }
    }
};
