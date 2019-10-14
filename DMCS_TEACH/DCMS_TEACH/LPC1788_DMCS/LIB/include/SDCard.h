#include "stdint.h"


int MMC_disk_initialize(void);
int MMC_disk_read(uint8_t* buff, uint32_t sector, uint32_t count);
int MMC_disk_write( uint8_t* buff, uint32_t sector, uint32_t count);

