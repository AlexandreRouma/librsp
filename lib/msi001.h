#pragma once
#include <stdint.h>

enum msi001_reg {
    MSI001_REG_MODESEL      = 0x0,
    MSI001_REG_GAIN_CTRL    = 0x1,
    MSI001_REG_SYNTH_PROG   = 0x2,
    MSI001_REG_LO_TRIM      = 0x3,
    MSI001_REG_AUX_CTRL     = 0x4,
    MSI001_REG_SYNTH_CONF   = 0x5,
    MSI001_REG_DC_CALIB     = 0x6,
    _MSI001_REG_COUNT
};
typedef enum msi001_reg msi001_reg_t;

struct msi001_dev {
    uint32_t regs[_MSI001_REG_COUNT];
};
typedef struct msi001_dev msi001_dev_t;

int msi001_write_reg(msi001_reg_t reg, uint32_t val);

int msi001_open(msi001_dev_t** dev);
int msi001_close(msi001_dev_t* dev);

int msi001_reset(msi001_dev_t* dev);
int msi001_sync_reg(msi001_dev_t* dev, msi001_reg_t reg);

uint32_t msi001_get_reg_bits(msi001_dev_t* dev, msi001_reg_t reg, int count, int offset);
void msi001_set_reg_bits(msi001_dev_t* dev, msi001_reg_t reg, uint32_t val, int count, int offset);

enum msi001_am_port {
    MSI001_AM_PORT_1    = 0,
    MSI001_AM_PORT_2    = 1,
};
typedef enum msi001_am_port msi001_am_port_t;

enum msi001_if_filter {
    MSI001_IF_FILTER_2048KHZ_IF   = 0,
    MSI001_IF_FILTER_1620KHZ_IF   = 1,
    MSI001_IF_FILTER_450KHZ_IF    = 2,
    MSI001_IF_FILTER_ZERO_IF      = 3
};
typedef enum msi001_if_filter msi001_if_filter_t;

enum msi001_rf_bandwidth {
    MSI001_RF_BANDWIDTH_200KHZ  = 0,
    MSI001_RF_BANDWIDTH_300KHZ  = 1,
    MSI001_RF_BANDWIDTH_600KHZ  = 2,
    MSI001_RF_BANDWIDTH_1536KHZ = 3,
    MSI001_RF_BANDWIDTH_5000KHZ = 4,
    MSI001_RF_BANDWIDTH_6000KHZ = 5,
    MSI001_RF_BANDWIDTH_7000KHZ = 6,
    MSI001_RF_BANDWIDTH_8000KHZ = 7
};
typedef enum msi001_rf_bandwidth msi001_rf_bandwidth_t;

enum msi001_xtal {
    MSI001_XTAL_19_2MHZ     = 0,
    MSI001_XTAL_22MHZ       = 1,
    MSI001_XTAL_24_576MHZ   = 2,
    MSI001_XTAL_26MHZ       = 3,
    MSI001_XTAL_38_4MHZ     = 4
};
typedef enum msi001_xtal msi001_xtal_t;

#define MSI001_MIN_IF_ATT   0
#define MSI001_MAX_IF_ATT   59

// TODO: Modesel

int msi001_set_am_port(msi001_dev_t* dev, msi001_am_port_t port);

int msi001_set_if_filter(msi001_dev_t* dev, msi001_if_filter_t filter);

int msi001_set_rf_bandwidth(msi001_dev_t* dev, msi001_rf_bandwidth_t bw);

int msi001_set_xtal(msi001_dev_t* dev, msi001_xtal_t xtal);

// TODO: LP Config

int msi001_set_if_att(msi001_dev_t* dev, uint8_t attDb);

