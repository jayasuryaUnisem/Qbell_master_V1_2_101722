#include "app.h"

extern struct define_flag Mflag;
extern _BC3602_device_ BC3602_T;
extern int_flags intF;

/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	delay
// input	:	unsigned short time -> in milliseconds
// output	:	none
// function : 	Blocking delay
//*********************************************//

void delay(unsigned short time)
{
	unsigned short a;
	unsigned char b, c;

	for (a = 0; a < time; a++)
	{
		for (b = 0; b < 5; b++)
		{
			for (c = 0; c < 102; c++)
				asm("nop");
		}
	}
}

/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	sw0_status_check
// input	:	none
// output	:	none
// function :	For checking the SW1 status for RGB blink interval
//				 -------------------------------------
//				|  PB0 |  PB1  |  Interval in Seconds |
//				 -------------------------------------
//				|	0  |   0   |		10			  |
//				|	0  |   1   |		10			  |
//				|	1  |   0   |        20			  |
//				|   1  |   1   |		15            |
//				 -------------------------------------
//*********************************************//
void sw0_status_check(void)
{
	if (1 == SW2_PB0 && 1 == SW2_PB1)
	{
		uart_printf("in 60 mode\n");
		intF.sw0_status_flag = SEC_60;
	}
	else if (1 == SW2_PB0 && 0 == SW2_PB1)
	{
		uart_printf("in 90 mode\n");
		intF.sw0_status_flag = SEC_90;
	}
	else if (0 == SW2_PB0 && 1 == SW2_PB1)
	{
		uart_printf("in 30 mode\n");
		intF.sw0_status_flag = SEC_30;
	}
	else
	{
		uart_printf("in 30 mode\n");
		intF.sw0_status_flag = SEC_30;
	}
	delay(1000);
}

/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	sysInit
// input	:	none
// output	:	none
// function :	which includes watchdog time clear, uart init, adc init,
//				i2c init, ktd rgb led driver init and other gpio inits
//*********************************************//
void sysInit()
{
	WDTC();
#if UART_EN
	uart_prot_init();
#endif
	delay(10);
	adc_init();
	IIC_Init();
	ktd_en();
	ktd_clear();
	delay(10);
	int_init();
	delay(10);
	RF_Init(); // RF Initialization
	RF_Parameter_loading();
	BC3602_WriteRegister(IO2_REGS, 0xcd); // debug use
	BC3602_T.mode = RF_RX;				  // set RF mode flag as RX mode
	BC3602_T.mode = RF_RX;
	delay(10);

	ktd_clear();
	ktd_clockwise_ring_p1(0, 200, 0, 50, 1, 12);
	ktd_anticlockwise_ring_p1(0, 200, 0, 50, 1, 12);
	ktd_clockwise_ring_p1(0, 0, 200, 50, 1, 12);
	ktd_anticlockwise_ring_p1(0, 0, 200, 50, 1, 12);
	delay(1000);
	ktd_clear();
}

void app_eeprom_check(void)
{
	/*
	u8 i = 0;
	char tempValue[10];
	uart_printf("Reading Device Address from EEPROM: ");
	for (i = 0; i < 4; i++)
	{
		intF.deviceAddr[i] = eeprom_read(i);
		GCC_CLRWDT();
		itoa(intF.deviceAddr[i], tempValue, 10);
		uart_printf(tempValue);
		uart_printf(" ");
	}
	uart_printf("\n");
	delay(100);
	*/
	uart_printf("Checking Device Address: ");
	eepromDeviceAddrRead();
	uart_printf(intF.deviceAddr);
	//eepromDeviceAddrCpyAckRead();
	// uart_printf("\nDevice Copy Address Ack: ");
	// uart_send(intF.deviceAddCpyAck);

	if(0x40 == intF.deviceAddr[0])
	{
		uart_printf("\nThis device address is copied already\n");
		eepromDeviceAddrCpyRead();
		uart_printf("Device Address Copy: ");
		uart_printf(intF.deviceAddrCpy);
		uart_printf("\nComparing the Address and Address Copy\n");

		if(!memcmp(intF.deviceAddr, intF.deviceAddrCpy, sizeof(intF.deviceAddr)))
		{
			uart_printf("Address Matching\n");
			intF.deviceAddrCmprF = 0;
		}
		else
		{
			uart_printf("Address Not Matching\n");
			intF.deviceAddrCmprF = 1;
		}
	}

	else
	{
		uart_printf("The Device address is not Copied yet\nChecking for the first boot: ");
		uart_send(intF.deviceAddr[0]);

		if(0x41 == intF.deviceAddr[0])
		{
			uart_printf("Device is boot for first time\n");
			eeprom_write(EEPROM_DEVICE_ID_ADDR, MASTER_1);
			delay(1);
			eepromDeviceAddrRead();
			delay(1);
			//eepromDeviceAddrCpyAckWrite(EEPROM_DEVICE_ADDR_CPY_ACK_VALUE);
			delay(1);
			eepromDeviceAddrCpyWrite();
			delay(1);
			intF.deviceAddrCmprF = 0;
		}
		else
		{
			uart_printf("This Device is not Booting for first time, some other issue\n");
			intF.deviceAddrCmprF = 1;
		}
	}

}

void app()
{
#if 0
	
	ktd_ctrl(RGB_NORMAL_MODE, FADE_INT_500MS);
	ktd_rgb_ctrl(255, 0, 0);
	delay(1000);
	ktd_rgb_ctrl(0, 255, 0);
	delay(1000);
	ktd_rgb_ctrl(0, 0, 255);
	delay(1000);
	ktd_clear();
	delay(2000);

#endif
#if 1

	if (intF.int0_isr_flag)
	{
		intF.int0_isr_flag = 0;
		u8 i = 0;
		u8 tempPacketAddr[5];
		for (i = 0; i < 4; i++)
			tempPacketAddr[i] = intF.rxPayload[i + 1];

#if !MODE_FLASHING
		if ((DOORBELL == tempPacketAddr[0]) && (intF.deviceAddr[1] == tempPacketAddr[1]) &&
			(intF.deviceAddr[2] == tempPacketAddr[2]) && (intF.deviceAddr[3] == tempPacketAddr[3]))
#elif MODE_FLASHING
		if ((DOORBELL == tempPacketAddr[0]) && (1 == tempPacketAddr[1]) &&
			(1 == tempPacketAddr[2]) && (1 == tempPacketAddr[3]))
#endif
		{
			uart_printf("Notification Received from Paired Device\n");
			sw0_status_check();
			u8 i = 0;
			MOTOR_PIN = 0;
			for (i = 0; i < intF.sw0_status_flag; i++)
			{
				if(i<10)
				{
					MOTOR_PIN = 1;
					if (!STOP_BTN_PIN)
						break;
					ktd_clockwise_ring_p1(140, 43, 151, 10, 1, 12);
					if (!STOP_BTN_PIN)
						break;
					ktd_anticlockwise_ring_p1(140, 43, 151, 10, 1, 12);

					if (!STOP_BTN_PIN)
						break;
					MOTOR_PIN = 0;
					ktd_clockwise_ring_p1(22, 39, 217, 10, 1, 12);
					if (!STOP_BTN_PIN)
						break;
					ktd_anticlockwise_ring_p1(22, 39, 217, 10, 1, 12);

					if (!STOP_BTN_PIN)
						break;
					MOTOR_PIN = 1;
					ktd_clockwise_ring_p1(17, 186, 20, 10, 1, 12);
					if (!STOP_BTN_PIN)
						break;
					ktd_anticlockwise_ring_p1(17, 186, 20, 10, 1, 12);

					if (!STOP_BTN_PIN)
						break;
					MOTOR_PIN = 0;
					delay(10);
				}
				else
				{
					ktd_ctrl(RGB_NORMAL_MODE, FADE_INT_500MS);
					MOTOR_PIN = 1;
					if (!STOP_BTN_PIN)
						break;
					ktd_rgb_ctrl(255, 0, 0);
					delay(1000);
					if (!STOP_BTN_PIN)
						break;
					ktd_rgb_ctrl(0, 255, 0);
					delay(1000);
					if (!STOP_BTN_PIN)
						break;
					ktd_rgb_ctrl(0, 0, 255);
					delay(1000);
					if (!STOP_BTN_PIN)
						break;
					MOTOR_PIN = 0;
					ktd_clear();
					if (!STOP_BTN_PIN)
						break;
					delay(2000);
				}
			}
			ktd_en();
			ktd_clear();
			MOTOR_PIN = 0;
#if !UART_EN
			rgb_mode(intF.battStatusValue);
			delay(5000);
			led_clear();
#elif UART_EN
			switch (intF.battStatusValue)
			{
			case BATT_HIGH:
				uart_printf("Node Battery Voltage Full\n");
				ktd_rgb_ctrl(0, 255, 0);
				break;
			case BATT_AVG1:
				uart_printf("Node Battery Voltage Average 1\n");
				ktd_rgb_ctrl(0, 0, 255);
				break;
			case BATT_AVG2:
				uart_printf("Node Battery Voltage Average 2\n");
				ktd_rgb_ctrl(0, 0, 255);
				break;
			case BATT_LOW:
				uart_printf("Node Battery Voltage Low\n");
				ktd_rgb_ctrl(255, 0, 0);
				break;
			default:
				break;
			}
			delay(5000);
			ktd_clear();
#endif
		}
	}

	lvd_read();

	if (intF.lvdF)
	{
		u8 tempCount = 0;
		tempCount = 11;
		while (intF.lvdF)
		{
			if (10 <= tempCount)
			{
				tempCount = 0;
				u8 i = 0;
				for (i = 0; i < 5; i++)
				{
#if !UART_EN
					rgb_mode(BATT_LOW);
					delay(1000);
					led_clear();
					delay(1000);
#elif UART_EN
					uart_printf("Low Voltage Detected\n");
					delay(1000);
#endif
				}
				ktd_clear();
			}
			tempCount++;
			lvd_read();
			uart_printf("Low Voltage Detected\n");
			delay(1000);
		}
	}

	if (BC3602_T.mode == RF_TX) // while RF mode flag = TX
		ExtendFIFO_TX_Process(&BC3602_T);

	if (BC3602_T.mode == RF_RX) // while RF mode flag = RX
		ExtendFIFO_RX_Process(&BC3602_T);

	RF_Finished_Process(&BC3602_T);

#endif
	/*
		- 	Checking the rgb blink flag tiggred or not
			blink timing will be set by PB0 and PB1 input.
	*/
}
