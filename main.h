#ifndef MAIN_H
#define MAIN_H

#include "BC66F3652.h"
#include "hal_i2c.h"
#include "hal_ktd.h"
#include "hal_adc.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_rf.h"
#include "hal_eeprom.h"
#include "app.h"

#define WDTC()                                  (_wdtc=0xa8)
#define NULL()									'\0'

#define SEC_30                                  5//30
#define SEC_60                                  10//60
#define SEC_90                                  15//90

#define BRIGHT_LAYER							3

#define DOOR_BELL                               0x01

#define BATT_HIGH                               0x08
#define BATT_AVG1                               0x09
#define BATT_AVG2                               0x10
#define BATT_LOW                                0x11

//typedef unsigned char u8;
//typedef unsigned short u16;




typedef struct int_flags
{
    unsigned char int0_isr_flag;  // this flag is for pb0 pin -> assigned for SW2 blink interval change
    unsigned char int1_isr_flag;  // this flag is for pb1 pin -> Assigned for SW2 blink interval change
    
    unsigned char int2_isr_flag;  // this flag is for pb1 pin -> Assigned for SW2 blink interval change
    
    unsigned char sw0_status_flag;
    unsigned char battStatusValue;
    unsigned char notifiType;

    unsigned char deviceAddr[5];

    unsigned char rxPayload[10];
    unsigned char p1DeviceID[5];
    unsigned char p1Status;

    unsigned char waitingFlag;
    unsigned char rxAck;

    unsigned char ProcessType;

    unsigned char pairingMode;

    unsigned char lvdF;

    unsigned char deviceAddCpyAck;
    unsigned char deviceAddrCpy[5];
    unsigned char deviceAddrCmprF;
}int_flags;


//int_flags intF;
//struct define_flag Mflag;


#endif