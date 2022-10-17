#ifndef HAL_GPIO_H
#define HAL_GPIO_H
#include "main.h"

typedef unsigned char u8;
typedef unsigned short u16;

#define SW2_PB0                         _pb0
#define SW2_PB1                         _pb1
#define SW2_PB0_CTR                     _pbc0
#define SW2_PB1_CTE                     _pbc1

#define BUZZER_PIN                      _pb3
#define BUZZER_PIN_CTR                  _pbc3

#define MOTOR_PIN                       _pb5
#define MOTOR_PIN_CTR                   _pbc5

#define RGB_R                           _pd0
#define RGB_G                           _pd1
#define RGB_B                           _pd2

#define RGB_INIT()                      {_pdc0 = 0; _pdc1 = 0; _pdc2 = 0;}

#define STOP_BTN_PIN                    _pb4
#define STOP_BTN_PIN_INIT()             {_pbc4 = 1; _pbpu4 = 1;}

#define UNPAIR_BUTTON                   _pa6
#define UNPAIR_BTT_INIT()               {_pac6 = 1; _papu6 = 1; _pawu6 = 1;}

#define INT1_EDGE_RISING_CTR()          {_int1s1 = 0; _int1s0 = 1;}
#define INT1_EDGE_FALLING_CTR()         {_int1s1 = 1; _int1s0 = 0;}
#define INT1_EDGE_BOTH_CTR()            {_int1s1 = 1; _int1s0 = 1;}
#define INT1_EDGE_DISABLE_CTR()         {_int1s1 = 0; _int1s0 = 0;}

#define INT0_EDGE_RISING_CTR()          {_int0s1 = 0; _int0s0 = 1;}
#define INT0_EDGE_FALLING_CTR()         {_int0s1 = 1; _int0s0 = 0;}
#define INT0_EDGE_BOTH_CTR()            {_int0s1 = 1; _int0s0 = 1;}
#define INT0_EDGE_DISABLE_CTR()         {_int0s1 = 0; _int0s0 = 0;}

#define INT0_REG_FLAG_NOREQ()           (_int0f = 0)        //NO interrupt flag request
#define INT0_REF_FLAG_ISR_REQ()         (_int0f = 1)        //Interrupt flag request set

#define INT1_REG_FLAG_NOREQ()           (_int1f = 0)        //NO interrupt flag request
#define INT1_REF_FLAG_ISR_REQ()         (_int1f = 1)        //Interrupt flag request set

#define INT0_ISR_CTR_EN()               (_int0e = 1)
#define INT0_ISR_CTR_DIS()              (_int0e = 0)

#define INT1_ISR_CTR_EN()               (_int1e = 1)
#define INT1_ISR_CTR_DIS()              (_int1e = 0)

#define ISR_CTR_EN()                    (_emi = 1)
#define IST_CTR_DIS()                   (_emi = 0)

#define INT0_EN                         1
#define INT1_EN                         1



extern void gpio_init(void);
extern void int_init(void);
extern void buzzer_ctrl(unsigned char);
extern void motor_ctrl(unsigned char);
extern void led_clear(void);
#endif