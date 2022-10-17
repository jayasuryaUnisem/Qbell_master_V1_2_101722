#include "hal_uart.h"

u8 ReceiveData;

char* temPtr;



/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	itoa
// input	:	int value -> interger for convert to string, char* result -> pointer for the store the string value
//              int base -> base value
// output	:	char* result -> will return the result (the converted value in char*)
// function :   this api will use for convert the intger to string (char*) data type. (data type convertion)
//*********************************************//
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}




/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	uart_prot_init
// input	:	none
// output	:	none
// function :   This function is using for init the uart registers
//*********************************************//
void uart_prot_init(void)
{
    UART_RX_PU = 1;
    UART_RX_CTR = 1;
    UART_TX_CTR = 0;

    UART_PxSx |= 0x14;
    UART_IFS &= 0xfe;

    _ucr1 = (0x80|(UART_PREN<<5)|(UART_PRT<<4)|(UART_STOP_LEN<<3));
 	_ucr2 = (0xC0|(UART_HBAUD_EN<<5));
 	_brg = BRG; 
 	
	uart_int_init();
}




/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	uart_int_init
// input	:	none
// output	:	none
// function :   function for init the uart port and registers
//*********************************************//
void uart_int_init(void)
{
    _rie = 1;
    _wake = 1;
    _tiie = 0;
    _teie = 0;
    _uarte = 1;
    _uartf = 0;
}





/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	uart_send
// input	:	u8 data -> byte to send (will not support string have to send byte by byte)
// output	:	none
// function :   This api will use for send value (uart write)
//*********************************************//
void uart_send(u8 data)
{
    #if UART_EN
    while(0 == _tidle);
    _txr_rxr = data;
    while(0 == _tidle);
    #endif
}




/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	uart_receive
// input	:	none
// output	:	u8 data -> will  return the value in byte format
// function :   uart value receive api.
//*********************************************//
u8 uart_receive()
{
    u8 data = 0;
    while(0 == _ridle);
        data = _txr_rxr;
    return data;
}




/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	uart_prinf
// input	:	char* payload -> payload (string) to uart_send (will support in sting format)
// output	:	none
// function :   This api will use the transmit the string via uart
//*********************************************//
void uart_printf(char* payload)
{
    #if UART_EN
    while(*payload)
        uart_send(*payload++);
    #endif
}



/*------------------------------------------------------------------*/
/*							 Function								*/
/*------------------------------------------------------------------*/
//*********************************************//
// name		:	uart_int
// input	:	u16 value -> int value 
// output	:	none
// function :   This will transmit the interger via uart
//*********************************************//
void uart_int(u16 value)
{
    #if UART_EN
    memcpy(temPtr, '\0', 10);
    itoa(value, temPtr, 10);
    uart_printf(temPtr);
    #endif
}



void uart_enable()
{
    uart_prot_init();
}

void uart_disable()
{
    _uarten = 0;
    _txen = 0;
    _rxen = 0;
    _txbrk = 0;
    _rxif = 0;
    _oerr = 0;
    _ferr = 0;
    _perr = 0;
    _nf = 0;
    UART_RX_PU = 0;
    UART_PxSx = 0x00;
}