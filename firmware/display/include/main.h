#pragma once

#include <stdio.h>
#include "common.h"

//#define DEVELOPMENT

#ifdef DEVELOPMENT
  #define DISPLAY_SSD1306
  #define DISPLAY_SPI
#endif

#ifdef DISPLAY_SPI
  #define DISPLAY_USE_RESET_PIN
  // #define DISPLAY_USE_SELECT_PIN
#endif


/* Typedef of unions for handy access of single bytes */
/* Access bytewise: U16 var; var.byte[x] = z; */
/* Access value: U32 var; var.u32 = 0xFFFFFFFF; */
typedef union
{
  uint16_t u16;
  uint8_t byte[2];
} U16;

typedef union
{
  uint32_t u32;
  uint8_t byte[4];
} U32;

#define  MAIN_SCREEN_FIELD_LABELS_COLOR C_WHITE_SMOKE

// void system_power(bool state);

// uint32_t get_seconds(); // how many seconds since boot
// uint32_t get_time_base_counter_1ms();

void SW102_rt_processing_stop(void);
void SW102_rt_processing_start(void);
void walk_assist_state(void);
void system_power_off(uint8_t updateDistanceOdo);
uint32_t get_seconds();

// extern Button buttonM, buttonDWN, buttonUP, buttonPWR;

