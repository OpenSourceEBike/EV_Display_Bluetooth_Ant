/*
 * TSDZ2 EBike wireless firmware
 *
 * Copyright (C) Casainho, 2020
 *
 * Released under the GPL License, Version 3
 */

#ifndef ANT_LEV_PAGE_2_H__
#define ANT_LEV_PAGE_2_H__

#include <stdint.h>
#include "antplus_lev_common_data.h"

typedef struct
{
    uint16_t remaining_range;
} antplus_lev_page_2_data_t;

#define DEFAULT_ANT_LEV_PAGE2() \
    (antplus_lev_page_2_data_t)      \
    {                           \
        .remaining_range = 0,    \
    }

void antplus_lev_page_2_encode(uint8_t * p_page_buffer,
                            antplus_lev_page_2_data_t const * p_page_data,
                            antplus_lev_common_data_t const * p_common_data);

#endif