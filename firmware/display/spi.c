/*
 * OpenSource DIY EV display
 * Copyright (C) Casainho, 2021
 *
 * Released under the GPL License, Version 3
 */

#include "nrf_drv_spi.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "main.h"

#define SPI_INSTANCE 1 /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */

volatile bool spi_xfer_done = true;

/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{
  spi_xfer_done = true;
  // NRF_LOG_INFO("Transfer completed.");
  // if (m_rx_buf[0] != 0)
  // {
  //   NRF_LOG_INFO(" Received:");
  //   NRF_LOG_HEXDUMP_INFO(m_rx_buf, strlen((const char *)m_rx_buf));
  // }
}

void spi_init() {
  nrf_gpio_cfg_output(DISPLAY_DC_PIN);
  nrf_gpio_pin_set(DISPLAY_DC_PIN);

#ifdef DISPLAY_USE_RESET_PIN
  nrf_gpio_cfg_output(DISPLAY_RS_PIN);
  nrf_gpio_pin_clear(DISPLAY_RS_PIN); // hold in reset until initialization
  nrf_delay_ms(1);
#endif

#ifdef DISPLAY_USE_SELECT_PIN
  nrf_gpio_cfg_output(DISPLAY_CS_PIN);
  nrf_gpio_pin_set(DISPLAY_CS_PIN);
#endif

  nrf_gpio_cfg_output(CAN_MODULE_CS_PIN);
  nrf_gpio_pin_set(CAN_MODULE_CS_PIN);

  nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
  spi_config.ss_pin   = NRF_DRV_SPI_PIN_NOT_USED;
  spi_config.miso_pin = DISPLAY_MISO_PIN;
  spi_config.mosi_pin = DISPLAY_MOSI_PIN;
  spi_config.sck_pin  = DISPLAY_CLK_PIN;
  spi_config.frequency = NRF_SPIM_FREQ_2M;
  spi_config.mode = NRF_SPI_MODE_0;
  spi_config.bit_order = NRF_SPI_BIT_ORDER_MSB_FIRST;
  APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));
}

void spi_tx(uint8_t* m_tx_buf, uint32_t m_tx_length) {
  static uint8_t m_rx_buf[1]; // we are not receiving anything
  
  // wait for SPI transfer finish
  while (spi_xfer_done == false) ;
  
  spi_xfer_done = false;
  APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_tx_buf, m_tx_length, m_rx_buf, 1));

  // wait for SPI transfer finish
  while (spi_xfer_done == false) ;
}

void spi_tx_rx(uint8_t* m_tx_buf, uint32_t m_tx_length, uint8_t* m_rx_buf, uint32_t m_rx_length) {

  // wait for SPI transfer finish
  while (spi_xfer_done == false) ;
  
  spi_xfer_done = false;
  APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_tx_buf, m_tx_length, m_rx_buf, m_rx_length));

  // wait for SPI transfer finish
  while (spi_xfer_done == false) ;
}
