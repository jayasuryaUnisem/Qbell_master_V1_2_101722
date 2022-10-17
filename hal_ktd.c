#include "hal_ktd.h"



/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		  :	ktd_en
// input	  :	none
// output	  :	none
// function : this function is for enable the KTD Chip and setting the
//            fade interval. (fade interval is defined in macros)
//*********************************************//
void ktd_en()
{
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x02, 0x00);
  delay(1);
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x02, RGB_NORMAL_MODE | FADE_INT_63MS);
  delay(1);
}

void ktd_ctrl(u8 mode, u8 fade)
{
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x02, mode | fade);
  delay(1);
}


/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		  :	ktd_clear
// input	  :	none
// output	  :	none
// function : This API is for clearing the LED and set it to down or off
//*********************************************//
void ktd_clear()
{
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x03, 0x00);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x04, 0x00);

  WriteI2C_Int(KTD_DEVICE_ADDR, 0x05, 0x00);
  
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x06, 0x00);
  
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x07, 0x00);
  
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x08, 0x00);
 

  WriteI2C_Int(KTD_DEVICE_ADDR, 0x09, 0x00);
  
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0A, 0x00);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0B, 0x00);

  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0C, 0x00);

  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0D, 0x00);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0E, 0x00);
 
}



/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		  :	ktd_rgb_ctrl
// input	  :	u8, ur, ub -> this 8bit RGB color code (it can be either in bytes of int (0-255))
// output	  :	none
// function : This API will be use for set the RGB color
//*********************************************//
void ktd_rgb_ctrl(u8 r, u8 g, u8 b)
{
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x03, r);
  
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x04, g);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x05, b);
 

  WriteI2C_Int(KTD_DEVICE_ADDR, 0x06, r);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x07, g);
  
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x08, b);
  

  WriteI2C_Int(KTD_DEVICE_ADDR, 0x09, SEL_LED_B);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0A, SEL_LED_B);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0B, SEL_LED_B);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0x0C, SEL_LED_B);
  
  WriteI2C_Int(KTD_DEVICE_ADDR, 0X0D, SEL_LED_B);
 
  WriteI2C_Int(KTD_DEVICE_ADDR, 0X0E, SEL_LED_B);
  

}




/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		  :	ktd_ring
// input	  :	r, b, g -> 8 bit color code selection, 
//            a12, a34, b12, b34, c12, c34 -> selecting the led 
// output	  :	none
// function : this function will used for create ring pantern. 
//*********************************************//
void ktd_ring(u8 g, u8 r, u8 b, 
                                u8 a12, u8 a34, 
                                u8 b12, u8 b34,
                                u8 c12, u8 c34)
{
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x03, r);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x04, g);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x05, b);
    //delay(1);

    WriteI2C_Int(KTD_DEVICE_ADDR, 0x06, r);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x07, g);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x08, b);
    //delay(1);

    WriteI2C_Int(KTD_DEVICE_ADDR, 0x09, a12);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x0A, a34);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x0B, b12);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x0C, b34);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x0D, c12);
    //delay(1);
    WriteI2C_Int(KTD_DEVICE_ADDR, 0x0E, c34);
    //delay(1);
}


/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	ktd_clockwise_ring
// input	: r, g, b -> RGB color 8 bit selection, msDelay -> ring running delay
// output	:	none
//*********************************************//
void ktd_clockwise_ring(u8 g, u8 r, u8 b, int msDelay, u8 start, u8 end)
{
	int i = 0;
    for (i = start; i<=end; i++)
    {
      switch(i)
      {
        case 1:
          ktd_ring(r, g, b, 
                    SEL_LED_1, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;

        case 2:
          ktd_ring(r, g, b, 
                    SEL_LED_2, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 3:
          ktd_ring(r, g, b, 
                    OFF_LED_B, SEL_LED_1, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 4:
          ktd_ring(r, g, b, 
                    OFF_LED_B, SEL_LED_2, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        case 5:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    SEL_LED_1, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 6:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    SEL_LED_2, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;

        case 7:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, SEL_LED_1,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 8:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, SEL_LED_2,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 9:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    SEL_LED_1, OFF_LED_B);
          break;
        
        case 10:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    SEL_LED_2, OFF_LED_B);
          break;
        
        case 11:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, SEL_LED_1);
          break;
        
        case 12:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, SEL_LED_2);
          break;
      }
      delay(msDelay);
    }
}


/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	Sys_init
// input	:	none
// output	:	none
//*********************************************//
void ktd_anticlockwise_ring(u8 g, u8 r, u8 b, int msDelay, u8 start, u8 end)
{
	int i = 0;
    for (i = start; i<=end; i++)
    {
      switch(i)
      {
        case 12:
          ktd_ring(r, g, b, 
                    SEL_LED_1, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 11:
          ktd_ring(r, g, b, 
                    SEL_LED_2, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 10:
          ktd_ring(r, g, b, 
                    OFF_LED_B, SEL_LED_1, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 9:
          ktd_ring(r, g, b, 
                    OFF_LED_B, SEL_LED_2, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 8:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    SEL_LED_1, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 7:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    SEL_LED_2, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;

        case 6:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, SEL_LED_1,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 5:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, SEL_LED_2,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 4:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    SEL_LED_1, OFF_LED_B);
          break;
        
        case 3:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    SEL_LED_2, OFF_LED_B);
          break;

        case 2:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, SEL_LED_1);
          break;
       
        case 1:
          ktd_ring(r, g, b, 
                    OFF_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, SEL_LED_2);
          break;
      }
      delay(msDelay);
    }
}



/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	ktd_clockwise_ring
// input	: r, g, b -> RGB color 8 bit selection, msDelay -> ring running delay
// output	:	none
//*********************************************//
void ktd_clockwise_ring_p1(u8 g, u8 r, u8 b, int msDelay, u8 start, u8 end)
{
	int i = 0;
    for (i = start; i<=end; i++)
    {
      switch(i)
      {
        case 1:
          ktd_ring(r, g, b, 
                    SEL_LED_1, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;

        case 2:
          ktd_ring(r, g, b, 
                    SEL_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 3:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_1, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 4:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        case 5:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_1, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 6:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;

        case 7:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_1,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 8:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 9:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_1, OFF_LED_B);
          break;
        
        case 10:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_B, OFF_LED_B);
          break;
        
        case 11:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_B, SEL_LED_1);
          break;
        
        case 12:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_B, SEL_LED_B);
          break;
      }
      delay(msDelay);
    }
}


/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	Sys_init
// input	:	none
// output	:	none
//*********************************************//
void ktd_anticlockwise_ring_p1(u8 g, u8 r, u8 b, int msDelay, u8 start, u8 end)
{
	int i = 0;
    for (i = start; i<=end; i++)
    {
      switch(i)
      {
        case 12:
          ktd_ring(r, g, b, 
                    SEL_LED_1, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 11:
          ktd_ring(r, g, b, 
                    SEL_LED_B, OFF_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 10:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_1, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 9:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    OFF_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 8:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_1, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 7:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, OFF_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;

        case 6:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_1,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 5:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    OFF_LED_B, OFF_LED_B);
          break;
        
        case 4:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_1, OFF_LED_B);
          break;
        
        case 3:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_B, OFF_LED_B);
          break;

        case 2:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_B, SEL_LED_1);
          break;
       
        case 1:
          ktd_ring(r, g, b, 
                    SEL_LED_B, SEL_LED_B, 
                    SEL_LED_B, SEL_LED_B,
                    SEL_LED_B, SEL_LED_B);
          break;
      }
      delay(msDelay);
    }
}



void ktd_breath(u8 delayMs)
{

  ktd_ctrl(RGB_NORMAL_MODE, delayMs);
  delay(1);
  ktd_ring(0, 255, 0, SEL_LED_B, SEL_LED_B,
                            SEL_LED_B, SEL_LED_B,
                            OFF_LED_B, SEL_LED_1);
}

void ktd_breath_battery(u8 battValue,u8 delayMs)
{
  switch (battValue)
  {
  case BATT_HIGH:
    ktd_ring(0, 255, 0, OFF_LED_B, OFF_LED_B,
                            OFF_LED_B, OFF_LED_B,
                            SEL_LED_B, SEL_LED_2);
    break;

  case BATT_AVG1:
    ktd_ring(0, 0, 255, OFF_LED_B, OFF_LED_B,
                            OFF_LED_B, OFF_LED_B,
                            SEL_LED_1, SEL_LED_B);

    break;

  case BATT_AVG2:
    ktd_ring(0, 0, 255, OFF_LED_B, OFF_LED_B,
                            OFF_LED_B, OFF_LED_B,
                            SEL_LED_1, SEL_LED_B);
    break;

  case BATT_LOW:
    #if 0
    ktd_ring(0, 0, 255,     OFF_LED_B, OFF_LED_B,
                            OFF_LED_B, OFF_LED_B,
                            SEL_LED_1, SEL_LED_B);
    #endif
    #if 1
    ktd_ring(255, 0, 0,     OFF_LED_B, OFF_LED_B,
                            OFF_LED_B, OFF_LED_B,
                            SEL_LED_B, SEL_LED_1);
    #endif
    break;                 
  
  default:
    ktd_ring(0, 0, 255, OFF_LED_B, OFF_LED_B,
                            OFF_LED_B, OFF_LED_B,
                            SEL_LED_1, SEL_LED_B);
    break;
  }
}