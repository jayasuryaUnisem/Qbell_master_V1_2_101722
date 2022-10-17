#ifndef HAL_KTD_H
#define HAL_KTD_H
#include "main.h"

#define KTD_DEVICE_ADDR                     0x68//0x74//0x68

#define FADE_SHUTDOW_MODE                   0x00
#define RGB_NIGHT_MODE                      0x40
#define RGB_NORMAL_MODE                     0x80
#define RESET_REG_KTD                       0xC0

#define SEL_LED_1                           0x80//0x87    //135
#define SEL_LED_2                           0x08//0x78    //120
#define SEL_LED_B                           0xFF    //136
#define OFF_LED_B                           0x00

#define FADE_INT_31MS                       0x20    //0xA0    //160
#define FADE_INT_63MS                       0x21    //0xA1    //161
#define FADE_INT_125MS                      0x22    //0xA2    //162
#define FADE_INT_250MS                      0x23    //0xA3    //163
#define FADE_INT_500MS                      0x24    //0xA4    //164
#define FADE_INT_1S                         0x25    //0xA5    //165
#define FADE_INT_2S                         0x26    //0xA6    //166
#define FADE_INT_3S                         0x27    //0xA7    //167

typedef unsigned char u8;

extern void ktd_en();
extern void ktd_ctrl(u8 mode, u8 fade);
extern void ktd_clear();
extern void ktd_rgb_ctrl(u8 g, u8 r, u8 b);
extern void ktd_ring(u8 g, u8 r, u8 b, 
                                u8 a12, u8 a34, 
                                u8 b12, u8 b34,
                                u8 c12, u8 c34);
extern void ktd_clockwise_ring(u8 g, u8 r, u8 b, int delay, u8 start, u8 end);
extern void ktd_anticlockwise_ring(u8 g, u8 r, u8 b, int delay, u8 start, u8 end);
extern void ktd_clockwise_ring_p1(u8 g, u8 r, u8 b, int delay, u8 start, u8 end);
extern void ktd_anticlockwise_ring_p1(u8 g, u8 r, u8 b, int delay, u8 start, u8 end);
extern void ktd_breath(u8 delayMs);
extern void ktd_breath_battery(u8 battValue,u8 delayMs);

#endif