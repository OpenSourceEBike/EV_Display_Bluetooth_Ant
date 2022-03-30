#pragma once

#include <stdint.h>

void spi_init(uint32_t clk, uint32_t mosi);
void spi_transfer(uint8_t* m_tx_buf, uint32_t m_length);


