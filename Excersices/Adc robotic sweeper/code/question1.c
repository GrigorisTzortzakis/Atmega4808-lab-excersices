/*
 * GccApplication7.c
 *
 * Created: 25-Mar-24 3:12:28 AM
 * Author : Mr karkinopoulos
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int aristera=0;
int brosta=1;


int telos=0;

#define ped 10

int main(){
	PORTD.DIR = PIN1_bm|PIN2_bm; // 2=aristera 1=brosta
	PORTD.OUT |= (PIN2_bm); //ksekinaei eutheia


	//adc ftiaksimo
	ADC0.CTRLA |= ADC_RESSEL_10BIT_gc; //10-bit kvadistis
	ADC0.CTRLA |= ADC_FREERUN_bm; //enable free run
	ADC0.CTRLA |= ADC_ENABLE_bm; //Enable adc
	ADC0.MUXPOS |= ADC_MUXPOS_AIN7_gc; //bit eisodou adc
	
	ADC0.DBGCTRL |= ADC_DBGRUN_bm;//enable debug
	
	ADC0.WINLT |= 10; //katoflh sigrisis
	ADC0.INTCTRL |= ADC_WCMP_bm; //Enable Interrupts f
	ADC0.CTRLE |= ADC_WINCM0_bm; //Interrupt otan result < winlt
	sei();
	ADC0.COMMAND |= ADC_STCONV_bm;



	while(1){
		if (telos==4) break;

		while (aristera)
		{
			// timer
			TCA0.SINGLE.CNT = 0;
			TCA0.SINGLE.CTRLB = 0;
			TCA0.SINGLE.CMP0 = ped;
			TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc;
			TCA0.SINGLE.CTRLA |=1;
			TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0_bm;
			while (aristera){}

		}
		

	}
	return 0;
}

ISR(ADC0_WCOMP_vect){
	
	int intflags = ADC0.INTFLAGS;
	ADC0.INTFLAGS = intflags;

	PORTD.OUT |= (PIN1_bm|PIN2_bm); //stamata
	PORTD.OUTCLR |= PIN2_bm; //strofi aristera
	brosta=0;
	aristera=1;

}

ISR(TCA0_CMP0_vect)
{
	TCA0.SINGLE.CTRLA = 0;
	
	int intflags = TCA0.SINGLE.INTFLAGS;
	TCA0.SINGLE.INTFLAGS=intflags;

	aristera=0;
	brosta=1;

	PORTD.OUT |= (PIN1_bm|PIN2_bm); //stamata
	PORTD.OUTCLR |= PIN1_bm; //proxora eutheia


	telos++;
}

