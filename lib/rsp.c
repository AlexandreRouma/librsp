#include "rsp.h"
#include "msi2500.h"

libusb_context* usb = NULL;

void rsp_init() {
    if (usb) { return; }
    libusb_init(&usb);
}

int rsp_get_device_list(rsp_dev_info_t** list) {
    // Initialize the library if needed
    rsp_init();

    // Find all devices
    *list = NULL;
    libusb_device** devList;
    struct libusb_device_descriptor desc;
    int count = libusb_get_device_list(usb, &devList);
    for (int i = 0; i < count; i++) {
        // Skip if not a PicoSDR
        libusb_device* dev = devList[i];
        libusb_get_device_descriptor(dev, &desc);
        if (desc.idVendor != 0x1DF7 || desc.idProduct != 0x2500) { continue; }
        
        // Open and get serial number
        char serial[128];
        if (desc.iSerialNumber) {
            libusb_device_handle* hndl;
            libusb_open(dev, &hndl);
            libusb_get_string_descriptor_ascii(hndl, desc.iSerialNumber, (unsigned char*)serial, sizeof(serial));
            libusb_close(hndl);
        }
        else {
            strcpy(serial, "NO SERIAL");
        }

        // Save to list
        *list = (rsp_dev_info_t*)malloc(sizeof(rsp_dev_info_t));
        (*list)->next = NULL;
        (*list)->usbDev = dev;
        (*list)->model = RSP_MODEL_RSP1;
        (*list)->serial = (char*)malloc(strlen(serial)+1);
        strcpy((*list)->serial, serial);
        list = &(*list)->next;
    }
}

void rsp_free_device_list(rsp_dev_info_t* list) {
    while (list) {
        rsp_dev_info_t* next = list->next;
        free(list->serial);
        free(list);
        list = next;
    }
}

int rsp_open(rsp_dev_t** dev, rsp_dev_info_t* info) {
    // Allocate device structure
    *dev = (rsp_dev_t*)malloc(sizeof(rsp_dev_t));

    // Open USB device
    int err = libusb_open(info->usbDev, &(*dev)->usb);
    if (err) { return err; }

    // Initialize device
    //err = msi001_open(&(*dev)->tuner, *dev);
    //if (err) { return err; }
}

void rsp_close(rsp_dev_t* dev) {
    // Free tuner structure
    msi001_close(dev->tuner);

    // Close USB device
    libusb_close(dev->usb);
}