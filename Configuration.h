/*+----------------------------------+*/
/*?						I/O usage statistics					   ?*/
/*+----------------------------------?*/
/*?  GIO4 -- N/C		PA1 -- GIO1 	PA2  -- N/C		 PA3 -- N/C	   ?*/
/*?  PB6  -- LCMSCK	PB5 -- LCMNCS	PB4  -- LCMRES	 PB3 -- LCMRS  ?*/
/*?  PA7  -- KEY4		PA6 -- KEY3		PA5  -- KEY2	 PD0 -- N/C	   ?*/
/*?  PD1  -- N/C		PD2 -- N/C		PD3  -- N/C		 PA4 -- KEY1   ?*/
/*?  PB2  -- N/C		PB1 -- LED1		PB0  -- LED2	 PC0 -- LED3   ?*/
/*?  PC1  -- LED4		PC2 -- LCMSDA	GIO3 -- N/C		 	 		   ?*/
/*?  PC3  -- RFSDIO	PC4 -- GIO2		PC5  -- RFSCK	 PC6 -- RFCSN  ?*/
/*+----------------------------------?*/
/*?					  SYSTEM  usage statistics		   			   ?*/
/*+----------------------------------?*/
/*?  SIM        --  SPI for RF or LCM (select out of two)			   ?*/
/*?  TimeBase0	 --  8ms time-out									   ?*/
/*?  INT0	     --  RF IRQ for GIO1								   ?*/
/*?  																   ?*/
/*?  						    other out of the list are available... ?*/
/*+----------------------------------+*/

/*------------------------------------------------------------------*/
/*							Header									*/
/*------------------------------------------------------------------*/
#include "MCU.h"

/*------------------------------------------------------------------*/
/*						KEY I/O Config								*/
/*------------------------------------------------------------------*/
#define		KEY_PxSx		_pas1

#define		KEY1_prot		_pa4
#define		KEY1_ctr		_pac4
#define		KEY1_pu			_papu4
#define		KEY1_wake		_pawu4

#define		KEY2_prot		_pa5
#define		KEY2_ctr		_pac5
#define		KEY2_pu			_papu5
#define		KEY2_wake		_pawu5

#define		KEY3_prot		_pa6
#define		KEY3_ctr		_pac6
#define		KEY3_pu			_papu6
#define		KEY3_wake		_pawu6

#define		KEY4_prot		_pa7
#define		KEY4_ctr		_pac7
#define		KEY4_pu			_papu7
#define		KEY4_wake		_pawu7

/*------------------------------------------------------------------*/
/*						LED I/O Config								*/
/*------------------------------------------------------------------*/
#define		LED_PxSx_1		_pds0
#define		LED_PxSx_2		_pcs0

#define		LED1_prot		_pb1
#define		LED1_ctr		_pbc1

#define		LED2_prot		_pd3
#define		LED2_ctr		_pdc3

#define		LED3_prot		_pc0
#define		LED3_ctr		_pcc0

#define		LED4_prot		_pc1
#define		LED4_ctr		_pcc1

/*------------------------------------------------------------------*/
/*						UART I/O Config								*/
/*------------------------------------------------------------------*/
#define		Baud_rate		9600			// [4800/9600/182000/#]bps
#define		UART_HBaud_EN	0				// [1:High  0:low] baud rate

#define		UART_PREN		0				// [1:enable  0:disable] check bit
#define		UART_PRT		0				// [1:odd  0:even] numble check bit
#define		UART_Stop_len	0				// [1:two  0:one] stop bit

#define		UART_RX_prot	_pd1
#define		UART_RX_ctr		_pdc1
#define		UART_RX_pu		_pdpu1
#define		UART_TX_prot	_pd2
#define		UART_TX_ctr		_pdc2

#define		UART_PxSx		_pds0
#define		UART_IFS		_ifs

/*------------------------------------------------------------------*/
/*						ADC I/O Config								*/
/*					Only Support AN0 - AN1							*/
/*------------------------------------------------------------------*/
//#define		ADC_AN0			1				//1:ON	0:OFF
//#define		ADC_AN1			1				//1:ON	0:OFF
//
//#if ADC_AN0
//#define		ADC0_ctr_prot		_pc1
//#define		ADC0_ctr_prot_ctr	_pcc1
//#endif
//
//#if ADC_AN1
//#define		ADC1_ctr_prot		_pc0
//#define		ADC1_ctr_prot_ctr	_pcc0
//#endif
//
//#define		ADC_DATA_HI			_sadoh
//#define		ADC_DATA_LO			_sadol



/*------------------------------------------------------------------*/
/*						RF SPI I/O Config							*/
/*------------------------------------------------------------------*/
#define		RF_SPI_line		4				// [3/4]line SPI

#if (RF_SPI_line==3)
#define		RF_SDIO			_pc3
#define		RF_SDIO_CTR		_pcc3
#define		RF_SDIO_PU		_pcpu3

#define		RF_SCK			_pc5
#define		RF_SCK_CTR		_pcc5

#define		RF_CSN			_pc6
#define		RF_CSN_CTR		_pcc6

#else
#define		RF_PxSx_1		_pcs0
#define		RF_PxSx_2		_pcs1
#define		RF_IFS			_ifs
#define		RF_SPI_SIMC0	_simc0
#define		RF_SPI_SIMC2	_simc2

#define		RF_MOSI			_pc3
#define		RF_MOSI_CTR		_pcc3

#define		RF_MISO			_pc4
#define		RF_MISO_CTR		_pcc4
#define		RF_MISO_PU		_pcpu4

#define		RF_SCK			_pc5
#define		RF_SCK_CTR		_pcc5

#define		RF_CSN			_pc6
#define		RF_CSN_CTR		_pcc6
#endif

/*------------------------------------------------------------------*/
/*						RF IRQ I/O Config							*/
/*------------------------------------------------------------------*/
#define		RF_INT			_pa1
#define		RF_INT_CTR		_pac1
#define		RF_INT_PU		_papu1
#define		RF_intxS0		_int0s0
#define		RF_intxS1		_int0s1
#define		RF_intxPS		_int0ps
#define		RF_INT_EN		_int0e

/*------------------------------------------------------------------*/
/*							RF Config								*/
/*------------------------------------------------------------------*/
#define		RF_BAND						_433MHz_			// [315/433/470/868/915]MHz
#define		RF_TxPower					_13dBm_				// [0/5/10/13]dBm
#define		RF_Datarate					_50kbps_			// [2/10/50/125/250]kbps

#define		RF_Payload_Length			96//92//32					// [1-255]bytes
#define		RF_SYNC_Length				4					// [4/6/8]bytes
#define		RF_SYNC_BCHcoding			0					// [1:ON 0:OFF]		must be set same in BCH32.asm
#define		RF_SYNC_L					0x12345678			// SYNC[3-0]bytes
#define		RF_SYNC_H					0x87654321			// SYNC[7-5]bytes

#define		RF_Trailer_EN				0					// [1:ON 0:OFF]
#define		RF_TxPreamble_Length		7					// [0-255]+1 bytes
#define		RF_RxPreamble_Length		3					// [0/1/2/3]value for [0/1/2/4]bytes
#define		RF_PLLEN_EN					0					// [1:ON 0:OFF]
#define		RF_Header_EN				0					// [1:ON 0:OFF]
#define		RF_Header_Length			0					// [1:2bytes 0:1byte]

#define		RF_Manchester_EN			0					// [1:ON 0:OFF]
#define		RF_FEC_EN					0					// [1:ON 0:OFF]
#define		RF_CRC_EN					1					// [1:ON 0:OFF]
#define		RF_CRC_Format				0					// [1:IBC-16-CRC 0:CCITT-16-CRC]
#define		RF_whiteining_EN			0					// [1:ON 0:OFF]
#define		RF_whiteining_Seed			0x00				// [0-127]	

#define		RF_PLHAC_EN					0					// [1:ON 0:OFF]
#define		RF_PLHA_Address				0x00				// [bit5:bit0]

/*ATR MODE*/
#define		RF_ATR_Enable				0					// [1:ON 0:OFF]
#define		RF_ATR_Cycle				1000				// [1-8000]ms
#define		RF_ATR_RX_Window			2000				// [250-511000]us
#define		RF_ATR_RX_extra				10					// [1-16380]ms

/*ARK MODE*/
#define		RF_ARK_Enable				0					// [1:ON 0:OFF]		if ARK on,RF payload length must be set less than 64 .
#define		RF_ARK_Resen_Count			3					// [0-15]+1 count
#define		RF_ARK_RX_Window			10000				// [250-63750]us
