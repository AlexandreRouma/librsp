#pragma once
#include <libusb.h>
#include "msi001.h"

enum rsp_model {
    RSP_MODEL_RSP1,
    RSP_MODEL_RSP2,
    RSP_MODEL_RSP2Pro,
    RSP_MODEL_RSP1A,
    RSP_MODEL_RSPDX,
    RSP_MODEL_RSPDuo
};
typedef enum rsp_model rsp_model_t;

struct rsp_dev_info {
    struct rsp_dev_info* next;
    libusb_device* usbDev;
    rsp_model_t model;
    char* serial;
};
typedef struct rsp_dev_info rsp_dev_info_t;

struct rsp_dev {
    libusb_device_handle* usb;
    rsp_model_t model;
    msi001_dev_t* tuner;
};
typedef struct rsp_dev rsp_dev_t;

int rsp_get_device_list(rsp_dev_info_t** list);
void rsp_free_device_list(rsp_dev_info_t* list);

int rsp_open(rsp_dev_t** dev, rsp_dev_info_t* info);
void rsp_close(rsp_dev_t* dev);