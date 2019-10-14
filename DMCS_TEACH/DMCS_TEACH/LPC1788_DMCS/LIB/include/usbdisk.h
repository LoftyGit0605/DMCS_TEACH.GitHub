#include "stdint.h"

int USB_disk_initialize(void);
int USB_disk_read(uint8_t* buff, uint32_t sector, uint32_t count);
int USB_disk_write(uint8_t* buff, uint32_t sector, uint32_t count);
