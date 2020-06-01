#ifndef __USART__
#define __USART__

#ifdef __AVR__
#include <avr/interrupt.h>
#endif

#include "scheduler.h"
#include <string.h>
#include "NEXTION.h"

#define USART_BAUDRATE 12
#define USART_RX_BUFFER_SIZE 32
#define USART_TX_BUFFER_SIZE 32
#define USART_EOT 0xff//End of transmission
#define USART_EOT_COUNT 3//EOT must appear EOT_COUNT times in a row to be valid.

//#define USART_PARSING_FINISHED 0
//#define USART_PARSING_INWORK 1
//#define USART_TEMPERATURE 3
//#define USART_RTC 4
/*
    PARSING STARTS WITH /r
    ENDS WITH RESULTING TX
*/
char USART_RX_buffer[USART_RX_BUFFER_SIZE];
char USART_TX_buffer[USART_TX_BUFFER_SIZE];
uint8_t USART_TX_message_length;
uint8_t USART_RX_buffer_index;
uint8_t USART_TX_buffer_index;
//note: indexes work as status flags too I.E: TX index at TX_BUFFER_SIZE means "TX is ready to go" 
int8_t USART_eot_counter;

//USARTcallbacks
int8_t NEXTION_touch();

#ifndef __AVR__
uint8_t UDR;
#endif

void USART_transmit()
{
    /*if(USART_eot_counter == USART_EOT_COUNT)//Message is done nothing to send, if statement is true its probably IRQ after sending last EOT. 
    {
		USART_outcome_buffer_index = USART_TX_BUFFER_SIZE;//set index beyond buffer so its marked as "free"
		return;
	}*/

	if(USART_TX_buffer_index == USART_TX_message_length)
		return;
		
    char buffer = USART_TX_buffer[USART_TX_buffer_index];
    UDR = buffer;
    
    /*if(buffer == USART_EOT)
    {
		if(USART_eot_counter < USART_EOT_COUNT)
			USART_eot_counter++;
        else
			return;
    }*/
	USART_TX_buffer_index++;
}

int8_t USART_register()
{
	switch(USART_RX_buffer[0])
	{
		case 0x65:
			NEXTION_touch();
		break;
	}
	USART_RX_buffer_index = 0;//unlock
	
	return 0;
}

void USART_TX_clear()
{
		USART_TX_buffer_index = USART_TX_BUFFER_SIZE;//Mark as finished
		USART_TX_message_length = 0;
}

uint8_t USART_send(char data[],uint8_t flush)
{
	if(USART_TX_buffer_index != USART_TX_BUFFER_SIZE)//Check if there is no pending transmission
		return 0;
		
	uint8_t size = strlen(data);
	if(size+USART_TX_message_length > USART_TX_BUFFER_SIZE)
		return 0;

	memcpy(&USART_TX_buffer[USART_TX_message_length],data,size);
	USART_TX_message_length = USART_TX_message_length + size;
	
	if(flush)
	{
		USART_TX_buffer_index = 1;//set index at 2nd byte for further IRQ callback
		UDR = USART_TX_buffer[0];//First byte is send here, rest is handled on IRQ
	}
	
	return 1;
}

void initializeUSART()
{
    //USART_parsing_function = USARTonUSART;
	if(USART_TX_buffer_index == USART_TX_BUFFER_SIZE)//just a guard
		return;
    
	USART_TX_buffer_index = USART_TX_BUFFER_SIZE;
	#ifdef __AVR__
    uint8_t baud = USART_BAUDRATE;
    UBRRH = (uint8_t)(baud>>8);
    UBRRL = (uint8_t)baud;
    UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE);
    UCSRC = (1<<URSEL)|(3<<UCSZ0);//frame format: 8data, 1stop bit
	sei();//enable global interrupts
    #endif
}
#ifdef __AVR__
ISR(USART_RXC_vect)
{
	uint8_t buffer = UDR;
	if(USART_RX_buffer_index < USART_RX_BUFFER_SIZE)
	{
		USART_RX_buffer[USART_RX_buffer_index] = buffer;
		USART_RX_buffer_index++;
	}

	if(buffer == USART_EOT)
		USART_eot_counter++;
	else
		USART_eot_counter = 0;
	
	if(USART_eot_counter == USART_EOT_COUNT)
	{	
		USART_RX_buffer_index = USART_RX_BUFFER_SIZE;//Lock buffer
		SCHEDULER_addLowPriorityTask(USART_register);
	}
}
ISR(USART_TXC_vect)
{
    if(USART_TX_buffer_index == USART_TX_message_length)
	{
		USART_TX_clear();
		return;
	}
	
    char buffer = USART_TX_buffer[USART_TX_buffer_index];
	USART_TX_buffer_index++;
	UDR = buffer;
}
#endif
#endif