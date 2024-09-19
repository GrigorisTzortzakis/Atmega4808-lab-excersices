/*
 * GccApplication14.c
 *
 * Created: 10-Apr-24 3:55:58 AM
 * Author : Mr karkinopoulos
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define kato_orio 5 //kato orio sigrisis adc
#define ano_orio 10 //ano orio sigrisis adc

int main(){
	PORTD.DIR = PIN0_bm|PIN1_bm; // pin0=potisma  pin1=anemisthres
	PORTD.OUT |= (PIN0_bm|PIN1_bm); //arxizoun kleista , tha aneiksoun otan xriastei
	
	

	ADC0.CTRLA |= ADC_RESSEL_10BIT_gc; // 10-bit kvadisths
	ADC0.CTRLA |= ADC_ENABLE_bm; // enable adc
	ADC0.CTRLA |= ADC_FREERUN_bm ; // enable free run 
	ADC0.MUXPOS |= ADC_MUXPOS_AIN7_gc; //bit eisodou adc
	ADC0.DBGCTRL |= ADC_DBGRUN_bm; //debug
	
	
	ADC0.WINLT |= kato_orio; //kato katofli sigrisis
	ADC0.WINHT |= ano_orio; //ano katofli sigrisis
	ADC0.INTCTRL |= ADC_WCMP_bm; // enable interrupt
	ADC0.CTRLE |= ADC_WINCM2_bm; // interrupt otan perasoun ta oria
	
	ADC0.COMMAND |= ADC_STCONV_bm;
	sei();

	while(1){

	}
	return 0;
}


ISR(ADC0_WCOMP_vect){
	cli();
	int intflags = ADC0.INTFLAGS;
	ADC0.INTFLAGS = intflags;
	
	int timh_adc= ADC0.RES;
	
	if (timh_adc < kato_orio) {
		
		PORTD.OUTCLR = PIN0_bm; // anoikse to led 0 an egine interrupt gia to kato katofli
	}
	else if (timh_adc > ano_orio) {
		
		PORTD.OUTCLR = PIN1_bm; //anoiske to led 1 an egine interrupt gia to ano katofli
		
	}
	sei();
	}
	
	
