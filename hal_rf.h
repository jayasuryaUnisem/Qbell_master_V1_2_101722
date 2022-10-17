#ifndef HAL_RF_H
#define HAL_RF_H
#include "main.h"

// typedef unsigned char u8;
// typedef unsigned short u16;

#include "RF_API.h"
#include "SYS_API.h"
#include "Configuration.h"
#include "hal_ktd.h"

#define NOTIFI_REQ                                      0x01
#define PAIR_REQ                                        0x02
#define UNPAIR_REQ                                      0x03
#define PAIR_CONF_REQ                                   0x04
#define UNPAIR_CONF_REQ                                 0x05

#define MODE_FLASHING                                   0 //0 for E-Writer //1 for E-Link

#define DOORBELL                                        0x30
#define MASTER_1                                        0x40
#define MASTER_2                                        0x50

extern void Sys_init(void);
extern void fun_RamInit();
extern void KEY_Process(unsigned char key_status);
extern void RF_Finished_Process(_BC3602_device_ *BC3602_T);
extern void DATA_Process(unsigned char *FIFO);
extern void RF_Process(void);
extern void RF_Process_Inint(void);


struct define_flag
{
    unsigned char Key_Stas;
    unsigned char LED_Stas;
    unsigned char fRFINT:1;
    unsigned char f8ms:1;
    unsigned char fm;
    unsigned char fs;
    unsigned char count;
    unsigned char adcFs;
    unsigned char adcFm;
    unsigned char lvdF;
};

#endif