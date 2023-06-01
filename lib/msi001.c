#include "msi001.h"

int msi001_write_reg(msi001_reg_t reg, uint32_t val) {
    //msi2500_write_reg(dev, MSI2500_REG_TUNER0, (val << 8) | reg);
}

int msi001_open(msi001_dev_t** dev) {
    *dev = (msi001_dev_t*)malloc(sizeof(msi001_dev_t));
    //(*dev)->rsp = rsp;
    return msi001_reset(*dev);
}

int msi001_close(msi001_dev_t* dev) {
    free(dev);
}

int msi001_reset(msi001_dev_t* dev) {
    // See datasheet for reset value
    dev->regs[MSI001_REG_MODESEL]       = 0b00000110001100000000;
    dev->regs[MSI001_REG_GAIN_CTRL]     = 0b01010000000000;
    dev->regs[MSI001_REG_SYNTH_PROG]    = 0b0100000000110011000;
    dev->regs[MSI001_REG_LO_TRIM]       = 0;
    dev->regs[MSI001_REG_AUX_CTRL]      = 0;
    dev->regs[MSI001_REG_SYNTH_CONF]    = 0b101000000000100000;
    dev->regs[MSI001_REG_DC_CALIB]      = 0b100000000000000001;

    // Sync all registers
    for (int i = 0; i < _MSI001_REG_COUNT; i++) {
        int err = msi001_sync_reg(dev, i);
        if (err) { return err; }
    }
}

int msi001_sync_reg(msi001_dev_t* dev, msi001_reg_t reg) {
    //msi001_write_reg(dev->rsp, reg, dev->regs[reg]);
}

uint32_t msi001_get_reg_bits(msi001_dev_t* dev, msi001_reg_t reg, int count, int offset) {
    uint32_t mask = (1 << count) - 1;
    return (dev->regs[reg] >> offset) & mask;
}

void msi001_set_reg_bits(msi001_dev_t* dev, msi001_reg_t reg, uint32_t val, int count, int offset) {
    uint32_t mask = (1 << count) - 1;
    val &= mask;
    dev->regs[reg] &= ~(mask << offset);
    dev->regs[reg] |= val << offset;
}

int msi001_set_am_port(msi001_dev_t* dev, msi001_am_port_t port) {
    msi001_set_reg_bits(dev, MSI001_REG_MODESEL, port, 1, 11);
    msi001_sync_reg(dev, MSI001_REG_MODESEL);
}

int msi001_set_if_filter(msi001_dev_t* dev, msi001_if_filter_t filter) {
    msi001_set_reg_bits(dev, MSI001_REG_MODESEL, filter, 2, 12);
    msi001_sync_reg(dev, MSI001_REG_MODESEL);
}

int msi001_set_rf_bandwidth(msi001_dev_t* dev, msi001_rf_bandwidth_t bw) {
    msi001_set_reg_bits(dev, MSI001_REG_MODESEL, bw, 3, 14);
    msi001_sync_reg(dev, MSI001_REG_MODESEL);
}

int msi001_set_xtal(msi001_dev_t* dev, msi001_xtal_t xtal) {
    msi001_set_reg_bits(dev, MSI001_REG_MODESEL, xtal, 3, 17);
    msi001_sync_reg(dev, MSI001_REG_MODESEL);
}