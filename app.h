#ifndef APP_H
#define APP_H
#include "main.h"

#define IND_PAIRING_REQ                     1
#define IND_PAIRED_CONF                     2
#define IND_NOTIFI                          3
#define IND_UNPAIRING                       4
#define UART_EN                             0//0 - disable uart, 1 - enable uart

extern void app();
extern void sw0_status_check(void);
extern void app_eeprom_check(void);
extern void sysInit();
extern void delay(unsigned short);


#endif