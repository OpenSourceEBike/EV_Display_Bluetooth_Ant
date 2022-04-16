#pragma once

#include <stdint.h>

void spi_init();
void spi_tx(uint8_t* tx_buf, uint32_t length);
void spi_tx_rx(uint8_t* tx_buffer, uint32_t tx_length, uint8_t* rx_buffer, uint32_t rx_length);


