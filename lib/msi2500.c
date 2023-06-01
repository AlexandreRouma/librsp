#include "msi2500.h"

int msi2500_command(rsp_dev_t* dev, msi2500_cmd_t cmd, enum libusb_endpoint_direction dir, uint16_t val, uint16_t ind, uint8_t* data, size_t len) {
    return libusb_control_transfer(dev->usb, LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE | dir, cmd, val, ind, data, len, MSI2500_TIMEOUT_MS);
}

int msi2500_reg_read(rsp_dev_t* dev, msi2500_reg_t reg, uint32_t* val) {
    // TODO
    return -1;
}

int msi2500_reg_write(rsp_dev_t* dev, msi2500_reg_t reg, uint32_t val) {
    return msi2500_command(dev, MSI2500_CMD_REG_WRITE, LIBUSB_ENDPOINT_OUT, ((val & 0xFF) << 8) | reg, (val >> 8) & 0xFFFF, NULL, 0);
}

int msi2500_eeprom_read(rsp_dev_t* dev, uint16_t addr, uint8_t* data, size_t len) {
    return msi2500_command(dev, MSI2500_CMD_EEPROM_READ, LIBUSB_ENDPOINT_IN, 0, addr, data, len);;
}

int msi2500_eeprom_write(rsp_dev_t* dev, uint16_t addr, uint8_t* data, size_t len) {
    // TODO
    return -1;
}