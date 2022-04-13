#include "MCP2515.h"
#include "spi.h"
#include "nrf_gpio.h"
#include "pins.h"

/* Modify below items for your SPI configurations */
#define MCP2515_CS_HIGH()   nrf_gpio_pin_set(CAN_MODULE_CS_PIN);
#define MCP2515_CS_LOW()    nrf_gpio_pin_clear(CAN_MODULE_CS_PIN);

/* Prototypes */
static void SPI_Tx(uint8_t data);
static void SPI_TxBuffer(uint8_t *buffer, uint8_t length);
static void SPI_TxRxBuffer(uint8_t *tx_buffer, uint8_t tx_length, uint8_t *rx_buffer, uint8_t rx_length);

bool MCP2515_SetLoopbackMode(void)
{
  /* CANCTRL Register Sleep 모드 설정 */  
  MCP2515_WriteByte(MCP2515_CANCTRL, 0x40);
  
  uint8_t loop = 10;
  
  do {    
    /* 모드전환 확인 */    
    if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x40)
      return true;
    
    loop--;
  } while(loop > 0);
  
  return false;
}

bool MCP2515_SetConfigMode(void)
{


  static uint8_t can_ctrl = 0, can_stat = 0;

  MCP2515_CS_LOW();

while (1) {

  can_ctrl = MCP2515_ReadByte(MCP2515_CANCTRL);
  can_stat = MCP2515_ReadByte(MCP2515_CANSTAT);

  // set config mode
  MCP2515_WriteByte(MCP2515_CANCTRL, 0x80);

  can_ctrl = MCP2515_ReadByte(MCP2515_CANCTRL);
  can_stat = MCP2515_ReadByte(MCP2515_CANSTAT);

  // set loopback mode
  MCP2515_SetLoopbackMode();
  
}

  uint8_t loop = 10;
  
  do {    
    /* Mode change confirmation */    
    if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x80)
      return true;
    
    loop--;
  } while(loop > 0); 
  
  return false;
}

bool MCP2515_SetNormalMode(void)
{
  /* CANCTRL Register Normal mode setting */  
  MCP2515_WriteByte(MCP2515_CANCTRL, 0x00);
  
  uint8_t loop = 10;
  
  do {    
    /* Mode change confirmation */    
    if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x00)
      return true;
    
    loop--;
  } while(loop > 0);
  
  return false;
}

bool MCP2515_SetSleepMode(void)
{
  /* CANCTRL Register Sleep 모드 설정 */  
  MCP2515_WriteByte(MCP2515_CANCTRL, 0x20);
  
  uint8_t loop = 10;
  
  do {    
    /* 모드전환 확인 */    
    if((MCP2515_ReadByte(MCP2515_CANSTAT) & 0xE0) == 0x20)
      return true;
    
    loop--;
  } while(loop > 0);
  
  return false;
}

void MCP2515_Reset(void)
{    
  MCP2515_CS_LOW();
      
  SPI_Tx(MCP2515_RESET);
      
  MCP2515_CS_HIGH();
}

uint8_t MCP2515_ReadByte (uint8_t address)
{
  uint8_t retVal[2];
  
  MCP2515_CS_LOW();
  
  SPI_Tx(MCP2515_READ);
  SPI_TxRxBuffer(&address, 1, retVal, 2);
      
  MCP2515_CS_HIGH();
  
  return retVal[1];
}

void MCP2515_ReadRxSequence(uint8_t instruction, uint8_t *data, uint8_t length)
{
  MCP2515_CS_LOW();
  
  SPI_TxRxBuffer(&instruction, 1, data, length);
    
  MCP2515_CS_HIGH();
}

void MCP2515_WriteByte(uint8_t address, uint8_t data)
{    
  MCP2515_CS_LOW();  
  
  SPI_Tx(MCP2515_WRITE);
  SPI_Tx(address);
  SPI_Tx(data);  
    
  MCP2515_CS_HIGH();
}

void MCP2515_WriteByteSequence(uint8_t startAddress, uint8_t endAddress, uint8_t *data)
{    
  MCP2515_CS_LOW();
  
  SPI_Tx(MCP2515_WRITE);
  SPI_Tx(startAddress);
  SPI_TxBuffer(data, (endAddress - startAddress + 1));
  
  MCP2515_CS_HIGH();
}

void MCP2515_LoadTxSequence(uint8_t instruction, uint8_t *idReg, uint8_t dlc, uint8_t *data)
{    
  MCP2515_CS_LOW();
  
  SPI_Tx(instruction);
  SPI_TxBuffer(idReg, 4);
  SPI_Tx(dlc);
  SPI_TxBuffer(data, dlc);
       
  MCP2515_CS_HIGH();
}

void MCP2515_LoadTxBuffer(uint8_t instruction, uint8_t data)
{
  MCP2515_CS_LOW();
  
  SPI_Tx(instruction);
  SPI_Tx(data);
        
  MCP2515_CS_HIGH();
}

void MCP2515_RequestToSend(uint8_t instruction)
{
  MCP2515_CS_LOW();
  
  SPI_Tx(instruction);
      
  MCP2515_CS_HIGH();
}

uint8_t MCP2515_ReadStatus(void)
{
  uint8_t retVal;
  uint8_t command;
  
  MCP2515_CS_LOW();
  
  command = MCP2515_READ_STATUS;
  SPI_TxRxBuffer(&command, 1, &retVal, 1);
        
  MCP2515_CS_HIGH();
  
  return retVal;
}

uint8_t MCP2515_GetRxStatus(void)
{
  uint8_t retVal;
  uint8_t command;
  
  MCP2515_CS_LOW();

  command = MCP2515_RX_STATUS;
  SPI_TxRxBuffer(&command, 1, &retVal, 1);
        
  MCP2515_CS_HIGH();
  
  return retVal;
}

void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data)
{    
  MCP2515_CS_LOW();
  
  SPI_Tx(MCP2515_BIT_MOD);
  SPI_Tx(address);
  SPI_Tx(mask);
  SPI_Tx(data);
        
  MCP2515_CS_HIGH();
}

static void SPI_Tx(uint8_t data)
{
  spi_tx(&data, 1);
}

static void SPI_TxBuffer(uint8_t *buffer, uint8_t length)
{
  spi_tx(buffer, length);
}

static void SPI_TxRxBuffer(uint8_t *tx_buffer, uint8_t tx_length, uint8_t *rx_buffer, uint8_t rx_length)
{
  spi_tx_rx(tx_buffer, tx_length, rx_buffer, rx_length);
}

