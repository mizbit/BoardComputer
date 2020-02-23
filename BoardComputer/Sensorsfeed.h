/*
 * Sensorsfeed.h
 *
 * Created: 2019-12-23 00:27:41
 *  Author: pszczelaszkov
 */ 


#ifndef SENSORSFEED_H_
#define SENSORSFEED_H_
#include "bitwise.h"

#define SENSORSFEED_READY 0xff
#define SENSORSFEED_ADC_LAST_CHANNEL 0

uint8_t SENSORSFEED_status;
uint16_t SENSORSFEED_feed[1];//10 bit each
//ISR bedzie podbijac do last channel reszte sie wymysli
void SENSORSFEED_update()
{
	if(SENSORSFEED_status != SENSORSFEED_READY)
		return;
	
	SENSORSFEED_status = 0;
	CLEAR(ADMUX,0x0f);
	ADCSRA |= (1 << ADSC);
}

void SENSORSFEED_initialize()
{
	//ADC init
	ADMUX = (1<<REFS0);//Vcc ref
	ADCSRA = (1<<ADEN)|(1<<ADIE);
	SENSORSFEED_status = SENSORSFEED_READY;
}

ISR(ADC_vect)
{
	SENSORSFEED_feed[SENSORSFEED_status] = ADC;
	if(SENSORSFEED_status >= SENSORSFEED_ADC_LAST_CHANNEL)
	{
		SENSORSFEED_status = SENSORSFEED_READY;
		return;
	}
	ADMUX++;
	SENSORSFEED_status++;
}

#endif /* SENSORSFEED_H_ */