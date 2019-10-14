#define SDRAM_BASE (0xA0000000)

/* SDRAM end address */
#define SDRAM_END  (0xA2000000)
extern void  HardWare_InitSDRAM( void );
extern void ClearMemory(void);
