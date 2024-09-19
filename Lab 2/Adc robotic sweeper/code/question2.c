/*
 * GccApplication8.c
 *
 * Created: 25-Mar-24 4:02:21 AM
 * Author : Mr karkinopoulos
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int aristera=0;
int brosta=1;
int deksia=0;

int end=0;

#define ped 10
#define limit 10

int main(){
	PORTD.DIR = PIN0_bm|PIN1_bm|PIN2_bm; // 2=aristera 1=brosta 0=deksia
	PORTD.OUT |= (PIN0_bm|PIN2_bm); //ksekinaei eutheia 

	ADC0.CTRLA |= ADC_RESSEL_10BIT_gc; // 10-bit kvadisths
	ADC0.CTRLA |= ADC_ENABLE_bm; // enable adc  
	ADC0.MUXPOS |= ADC_MUXPOS_AIN7_gc; //bit eisodou adc
	ADC0.DBGCTRL |= ADC_DBGRUN_bm; 
	
	
	ADC0.CTRLA |= ADC_FREERUN_bm; // enable free run
	ADC0.WINLT |= limit; // katofli
	ADC0.INTCTRL |= ADC_WCMP_bm; // enable interrupt 
	ADC0.CTRLE |= ADC_WINCM0_bm; // interrupt otan result <winlt
	
	ADC0.COMMAND |= ADC_STCONV_bm;
	sei();

	while(1){

		ADC0.CTRLA |= 0x05; // kleisto free run
		ADC0.CTRLE |= 0x00; // mi sigrinis

		if (ADC0.RES>limit) {

			PORTD.OUT |= (PIN0_bm|PIN1_bm|PIN2_bm); //stamata
			PORTD.OUTCLR |= PIN0_bm; //stripse deksia
			brosta=0;
			deksia=1;
		}

		ADC0.CTRLA |= ADC_FREERUN_bm; // anoixto free run
		ADC0.WINLT |= limit; 
		ADC0.INTCTRL |= ADC_WCMP_bm; 
		ADC0.CTRLE |= ADC_WINCM0_bm; 
		ADC0.COMMAND |= ADC_STCONV_bm;

		if (end==4) break;


		while (aristera)
		{
			end++;
			//timer
			TCA0.SINGLE.CNT = 0;  
			TCA0.SINGLE.CTRLB = 0; 
			TCA0.SINGLE.CMP0 = ped; 
			TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc; 
			TCA0.SINGLE.CTRLA |=1; 
			TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0_bm; 
			while (aristera){}
		}

		while (deksia)
		{
			end=end-1;
			
			TCA0.SINGLE.CNT = 0; 
			TCA0.SINGLE.CTRLB = 0; 
			TCA0.SINGLE.CMP0 = ped; 
			TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc; 
			TCA0.SINGLE.CTRLA |=1; 
			TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0_bm; 
			while (deksia){}

		}

	}
	return 0;
}

ISR(ADC0_WCOMP_vect){
	
	int intflags = ADC0.INTFLAGS;
	ADC0.INTFLAGS = intflags;

	PORTD.OUT |= (PIN0_bm|PIN1_bm|PIN2_bm); //stamata
	PORTD.OUTCLR |= PIN2_bm; //stripse aristera
	brosta=0;
	aristera=1;

}

ISR(TCA0_CMP0_vect)
{
	TCA0.SINGLE.CTRLA = 0; 
	//clear 
	int intflags = TCA0.SINGLE.INTFLAGS;
	TCA0.SINGLE.INTFLAGS=intflags;

	aristera=0;
	deksia=0;
	brosta=1;

	PORTD.OUT |= (PIN0_bm|PIN1_bm|PIN2_bm); //stamata
	PORTD.OUTCLR |= PIN1_bm; //eutheia
}











