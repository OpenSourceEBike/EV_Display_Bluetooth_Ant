/*
 * OpenSource DIY EV display
 * Copyright (C) Casainho, 2021
 *
 * Released under the GPL License, Version 3
 */

#include "nrf_saadc.h"

uint32_t adc_read_on_off_button_volts() {
  volatile int16_t result = 0;
  volatile float precise_result = 0;

  // first disable all channels
  for (uint8_t i = 0; i < 8; i++) {
    NRF_SAADC->CH[i].PSELP = 0;
    NRF_SAADC->CH[i].PSELN = 0;
  }

  // Configure SAADC singled-ended channel, Internal reference (0.6V) and 1/6 gain.
  NRF_SAADC->CH[7].CONFIG = (SAADC_CH_CONFIG_GAIN_Gain1_6    << SAADC_CH_CONFIG_GAIN_Pos) |
                            (SAADC_CH_CONFIG_MODE_SE         << SAADC_CH_CONFIG_MODE_Pos) |
                            (SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) |
                            (SAADC_CH_CONFIG_RESN_Bypass     << SAADC_CH_CONFIG_RESN_Pos) |
                            (SAADC_CH_CONFIG_RESP_Bypass     << SAADC_CH_CONFIG_RESP_Pos) |
                            (SAADC_CH_CONFIG_TACQ_3us        << SAADC_CH_CONFIG_TACQ_Pos);

  // Configure the SAADC channel with VDD as positive input, no negative input(single ended).
  NRF_SAADC->CH[7].PSELP = SAADC_CH_PSELP_PSELP_AnalogInput7;
  NRF_SAADC->CH[7].PSELN = 0;

  // Configure the SAADC resolution.
  NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_14bit << SAADC_RESOLUTION_VAL_Pos;

  // Configure result to be put in RAM at the location of "result" variable.
  NRF_SAADC->RESULT.MAXCNT = 1;
  NRF_SAADC->RESULT.PTR = (uint32_t)&result;

  // No automatic sampling, will trigger with TASKS_SAMPLE.
  NRF_SAADC->SAMPLERATE = SAADC_SAMPLERATE_MODE_Task << SAADC_SAMPLERATE_MODE_Pos;

  // Enable SAADC (would capture analog pins if they were used in CH[0].PSELP)
  NRF_SAADC->ENABLE = SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos;

  // Calibrate the SAADC (only needs to be done once in a while)
  NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;
  while (NRF_SAADC->EVENTS_CALIBRATEDONE == 0);
  NRF_SAADC->EVENTS_CALIBRATEDONE = 0;
  while (NRF_SAADC->STATUS == (SAADC_STATUS_STATUS_Busy <<SAADC_STATUS_STATUS_Pos));

  // Start the SAADC and wait for the started event.
  NRF_SAADC->TASKS_START = 1;
  while (NRF_SAADC->EVENTS_STARTED == 0);
  NRF_SAADC->EVENTS_STARTED = 0;

  // Do a SAADC sample, will put the result in the configured RAM buffer.
  NRF_SAADC->TASKS_SAMPLE = 1;
  while (NRF_SAADC->EVENTS_END == 0);
  NRF_SAADC->EVENTS_END = 0;

  // Convert the result to voltage
  // Result = [V(p) - V(n)] * GAIN/REFERENCE * 2^(RESOLUTION)
  // Result = (VDD - 0) * ((1/6) / 0.6) * 2^14
  // VDD = Result / 4551.1
  precise_result = (result * 10000) / 45511; // integer, precise result in mv

  // Stop the SAADC, since it's not used anymore.
  NRF_SAADC->TASKS_STOP = 1;
  while (NRF_SAADC->EVENTS_STOPPED == 0);
  NRF_SAADC->EVENTS_STOPPED = 0;

  return precise_result;
}