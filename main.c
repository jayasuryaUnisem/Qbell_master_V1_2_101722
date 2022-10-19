/*+---------------------------------------------------------------------+*/
/*?				Bestcomm document description					   		?*/
/*+---------------------------------------------------------------------?*/
/*?  Name    :  QBell Master Device Main Code   						?*/
/*?  Author  :  Jayasurya Ramasamy  									?*/
/*?  Date    :  2022/05/30	  										   	?*/
/*?  Version :  V1.2  											  	   	?*/
/*+---------------------------------------------------------------------?*/
/*?				    Function description		   			  	   		?*/
/*+---------------------------------------------------------------------?*/
/*?  1.																	?*/
/*?  2. 															 	?*/
/*?  3.																	?*/
/*?  4. 					   											?*/
/*?  5.					   												?*/
/*?  6.																   	?*/
/*?  7.																   	?*/
/*+---------------------------------------------------------------------|*/

/*----------------------------------------------------------------------*/
/*							Header								    	*/
/*----------------------------------------------------------------------*/


#include "main.h"
#include <string.h>

//struct define_flag Mflag;

extern int_flags intF;

void main()
{
    Sys_init();  //Init function for the RF mode
   	sysInit();   //Init function for the adc, rgb, gpio and watchdog timer control
	
	app_eeprom_check();
	while(1)
	{
		GCC_CLRWDT();		//Watchdog timer clear
		//_emi = 1;
		#if 0
		
		if(LVDO)
		{
			uart_printf("Low Voltage Detection\n");
		}
		else
		{
			uart_printf("Waiting for Low Voltage Detection\n");
		}

		// if(intF.lvdF)
		// {
		// 	uart_printf("LVD Flag triggered\n");
		// 	intF.lvdF = 0;
		// }
		delay(1000);
		#endif
		#if 1

		if(!intF.deviceAddrCmprF)
			app();
		
		else
		{
			ktd_ctrl(RGB_NORMAL_MODE, FADE_INT_1S);
			ktd_rgb_ctrl(0, 0, 255);
			delay(3000);
			ktd_clear();
			delay(3000);
		}
		#endif		
	}
}





