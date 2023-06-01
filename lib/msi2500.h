#pragma once
#include <stdint.h>
#include "rsp.h"

#define MSI2500_TIMEOUT_MS      1000

enum msi2500_cmd {
    MSI2500_CMD_MCU_RESET       = 0x40, // Might just be run. Value is set to 1.
    MSI2500_CMD_REG_WRITE       = 0x41,
    MSI2500_CMD_REG_READ        = 0x42,
    MSI2500_CMD_STREAM_START    = 0x43,
    MSI2500_CMD_MCU_RAM_WRITE   = 0x44,
    MSI2500_CMD_STREAM_STOP     = 0x45,
    MSI2500_CMD_EEPROM_READ     = 0x46,
    MSI2500_CMD_EEPROM_WRITE    = 0x47
};
typedef enum msi2500_cmd msi2500_cmd_t;

enum msi2500_reg {
    MSI2500_REG_UNKNOWN0 = 0x08,
    MSI2500_REG_TUNER0  = 0x09
};
typedef enum msi2500_reg msi2500_reg_t;

int msi2500_command(rsp_dev_t* dev, msi2500_cmd_t cmd, enum libusb_endpoint_direction dir, uint16_t val, uint16_t ind, uint8_t* data, size_t len);

int msi2500_reg_read(rsp_dev_t* dev, msi2500_reg_t reg, uint32_t* val);
int msi2500_reg_write(rsp_dev_t* dev, msi2500_reg_t reg, uint32_t val);

int msi2500_eeprom_read(rsp_dev_t* dev, uint16_t addr, uint8_t* data, size_t len);
int msi2500_eeprom_write(rsp_dev_t* dev, uint16_t addr, uint8_t* data, size_t len);