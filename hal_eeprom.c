#include "hal_eeprom.h"

extern int_flags intF;
static volatile unsigned char EEPROM_data[64] __attribute__ ((at(0x280)));

void eeprom_init()
{
	EEPROM_WR_CTR() = 0;
	_mp1h = 0;
}

void eeprom_write(u8 addrC, u8 byteValue)
{

    #if 0
	
	_emi = 0;		//disable global interrupt

	EEPROM_MP_LOW(); //mp1l = 40H
	EEPROM_MP_HIGH(); //mp1h = 01H

	EEPROM_MODE_BYTE();		//set byte mode

	EEPROM_EEA() = addrC;	   //address register
	EEPROM_EED() = byteValue;	//data register

	EEPROM_WR_EN();           //enable write mode
    EEPROM_WR_CTR() = 1;      

	 while(EEPROM_ER_CTR() == 1); //wait till write process is done

	EEPROM_EEC_CLR();   //clearing IAR1 registers
	_mp1h = 0;         //clearing the memory pointer high

	_emi = 1;		//enable global interrupt			
	return;
    #endif 

	#if 1

	u8 buffer = 0;

	buffer = _emi;
	_emi = 0;
	
	EEPROM_EEA() = addrC;
	EEPROM_EED() = byteValue;
	EEPROM_MP_LOW();
	EEPROM_MP_HIGH();
	
	EEPROM_IAR1() |= 0b00000000; //set to byte mode
	EEPROM_IAR1() |= 0b00001000;
	EEPROM_IAR1() |= 0b00000100;

	while((EEPROM_IAR1() & 0b00000100));
	_emi = buffer;
	EEPROM_IAR1() = 0x00;
	EEPROM_MP_HIGH_CLR();

	#endif

}

u8 eeprom_read(u8 addrV)
{
    #if 0
   
	EEPROM_MP_LOW();   //mp1l = 40H
	EEPROM_MP_HIGH();  //mp1h = 01H
 
	EEPROM_MODE_BYTE();  //set to byte mode

	EEPROM_EEA() = addrV; //address register
	
	_rd = 1;             //read control reg
    EEPROM_RD_EN();     //enable read mode

    while(EEPROM_RD_CTR() == 1); //wait till the read preocess complete

	EEPROM_EEC_CLR();    //clearing IAR1 reg
	_mp1h = 0;
			//Read data
    return EEPROM_EED();
    #endif

	#if 1
	u8 buffer = 0;
	buffer = _emi;
	_emi = 0;

	EEPROM_EEA() = addrV;
	EEPROM_MP_LOW();
	EEPROM_MP_HIGH();
	delay(10);

	EEPROM_IAR1() |= 0b00000000; //set to byte mode

	EEPROM_IAR1() |= 0b00000010;
	EEPROM_IAR1() |= 0b00000001; 
	while((EEPROM_IAR1() & 0b00000001));
	_emi = buffer;
	EEPROM_IAR1() = 0x00;
	EEPROM_MP_HIGH_CLR();
	return EEPROM_EED();


	#endif
}

void eepromP1Write()
{
	u8 i = 0;
	for(i=0; i<4; i++)	
		intF.p1DeviceID[i] = intF.rxPayload[i+1];
	
	for(i = EEPROM_PAIR_DEVICE_ID_ADDR; i<EEPROM_PAIR_DEVICE_ID_ADDR+4; i++)
		eeprom_write(i, intF.p1DeviceID[i-EEPROM_PAIR_DEVICE_ID_ADDR]);
}

void eepromP1Read()
{
	u8 i = 0;
	for(i = EEPROM_PAIR_DEVICE_ID_ADDR; i<EEPROM_PAIR_DEVICE_ID_ADDR+4; i++)
		intF.p1DeviceID[i-EEPROM_PAIR_DEVICE_ID_ADDR] = eeprom_read(i);
}

void eepromPstatusCheck()
{
	intF.p1Status = eeprom_read(EEPROM_PAIRED_STATUS_ADDR);
}

void eepromPstatusWrite(u8 payloadByte)
{
	eeprom_write(EEPROM_PAIRED_STATUS_ADDR, payloadByte);
}

void eepromUnpairDevice()
{
	u8 i = 0;
	for(i = EEPROM_PAIR_DEVICE_ID_ADDR; i < EEPROM_PAIR_DEVICE_ID_ADDR+10; i++)
		eeprom_write(i, 0);
}


void eepromDeviceAddrCpyCheck(void)
{
	intF.deviceAddCpyAck = eeprom_read(EEPROM_DEVICE_ADDR_CPY_ACK);

	if(EEPROM_DEVICE_ADDR_CPY_ACK_VALUE == intF.deviceAddCpyAck)
	{
		uart_printf("Address is stored in the EEPROM already\n");
	}
	else
	{
		u8 i = 0;
		for (i = EEPROM_DEVICE_ADDR_CPY; i<EEPROM_DEVICE_ADDR_CPY+4; i++)
			eeprom_write(i, intF.eepromAddr[i - EEPROM_DEVICE_ADDR_CPY]);
		delay(1);
		eeprom_write(EEPROM_DEVICE_ADDR_CPY_ACK, EEPROM_DEVICE_ADDR_CPY_ACK_VALUE);
		uart_printf("EEPROM Device Address Copy Write is Done\n");
	}
}

void eepromDeviceAddrCpyRead(void)
{
	u8 i = 0;
	for (i = EEPROM_DEVICE_ADDR_CPY; i < EEPROM_DEVICE_ADDR_CPY+4; i++)
		intF.deviceAddrCpy[i - EEPROM_DEVICE_ADDR_CPY] = eeprom_read(i);
	uart_printf("EEPROM Device Address copy Read Done\n");
}