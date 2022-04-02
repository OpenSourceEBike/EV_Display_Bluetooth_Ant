#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_ANT_ID_BLE_OBSERVER_PRIO 2

#define BLE_ANT_ID_DEF(_name)                                                                          \
static ble_ant_id_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_ANT_ID_BLE_OBSERVER_PRIO,                                                     \
                     ble_ant_id_on_ble_evt, &_name)                                   

#define ANT_ID_UUID_BASE                {0xf9, 0xAD, 0xE9, 0x68, 0x49, 0x08, 0x40, 0x5C, \
                                        0x9A, 0x0B, 0xD2, 0x4D, 0x31, 0x46, 0xf7, 0x97}
#define ANT_ID_UUID_SERVICE             0x1500
#define ANT_ID_UUID_CHAR                0x1501

typedef struct ble_ant_id_s ble_ant_id_t;

typedef void (*ble_ant_id_write_handler_t) (uint16_t conn_handle, ble_ant_id_t * p_ant_id, uint8_t value);

typedef struct
{
  ble_ant_id_write_handler_t ant_id_write_handler;
} ble_ant_id_init_t;

struct ble_ant_id_s
{
    uint16_t                    service_handle;      
    ble_gatts_char_handles_t    ant_id_char_handles;
    uint8_t                     uuid_type;
    ble_ant_id_write_handler_t  ant_id_write_handler;
};

uint32_t ble_service_ant_id_init(ble_ant_id_t * p_ant_id, const ble_ant_id_init_t * p_ant_id_init);
void ble_ant_id_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);
uint32_t ble_ant_id_on_change(uint16_t conn_handle, ble_ant_id_t * p_ant_id_t, uint8_t value);

#ifdef __cplusplus
}
#endif
