#include <stdio.h>
#include <fstream>

// TODO: Should be automatic in the headers
extern "C" {
    #include "rsp.h"
    #include "msi2500.h"
    #include "msi001.h"
}


int main() {
    //putenv("LIBUSB_DEBUG=4");

    // List devices
    rsp_dev_info_t* devList;
    rsp_get_device_list(&devList);

    for (rsp_dev_info_t* inf = devList; inf; inf = inf->next) {
        printf("Found: %s\n", inf->serial);
    }

    // Open the device
    rsp_dev_t* dev;
    if (rsp_open(&dev, &devList[0])) {
        printf("Could not open device");
    }

    // If no serial, init device
    if (!strcmp(devList->serial, "NO SERIAL")) {
        printf("init\n");
        // Load firmware into ROM
        std::ifstream file("../rsp1fw", std::ios::in | std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            printf("Could not open firmware\n");
            return -1;
        }
        int size = file.tellg();
        file.seekg(file.beg);
        uint8_t* fw = new uint8_t[size];
        file.read((char*)fw, size);
        file.close();

        // Write firmware rom
        for (int i = 0; i < size; i += 0x1000) {
            printf("%02X\n", (int)fw[i]);
            msi2500_command(dev, MSI2500_CMD_MCU_RAM_WRITE, LIBUSB_ENDPOINT_OUT, i, 0, &fw[i], 0x1000);
        }

        // Set weird register
        msi2500_reg_write(dev, MSI2500_REG_UNKNOWN0, 0);

        // Issue start command
        msi2500_command(dev, MSI2500_CMD_MCU_RESET, LIBUSB_ENDPOINT_OUT, 1, 0, NULL, 0);
    }
    else {
        
    }

    

    return 0;
}