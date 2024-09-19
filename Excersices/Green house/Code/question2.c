/*
 * GccApplication15.c
 *
 * Created: 13-Apr-24 3:53:14 PM
 * Author : Mr karkinopoulos
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define kato_orio 5 //kato orio sigrisis adc
#define ano_orio 10 //ano orio sigrisis adc


volatile  teleftea_timi_adc;  // timh adc gia ton tipo tou timer potismatos
volatile  rising_edge = 0;  // To count gia na kleisi o anemisthras


int main(){
	PORTD.DIR = PIN0_bm|PIN1_bm|PIN2_bm; // pin0=potisma  pin1=anemisthres
	PORTD.OUT |= (PIN0_bm|PIN1_bm|PIN2_bm); //arxizoun kleista , tha aneiksoun otan xriastei
	
	
	PORTF.PIN5CTRL |= PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc; 
	PORTF.PIN6CTRL |= PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc; 
	
	
	// timer split
	TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;  // Enable split mode

	// anemisthras
	TCA0.SPLIT.LPER = 18;  // 1ms periodos
	TCA0.SPLIT.LCMP0 = 9;  // duty cycle

	// prescaler
	TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV1024_gc; 

		

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
		
		PORTD.OUTCLR = PIN1_bm; // anoiske to led 1 an egine interrupt gia to ano katofli
		
	}
	sei();
}



ISR(PORTF_PORT_vect) {
	cli();
	if ((PORTF.IN & PIN6_bm)) {  // anemisthras 
		TCA0.SPLIT.CTRLB |= TCA_SPLIT_LCMP0EN_bm; // Enable PWM
		TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm; // enable timer
		PORTD.OUTCLR |= PIN1_bm; // anoikse led1
	}
	if ((PORTF.IN & PIN5_bm)) {  // potisma
		int timh_adc = ADC0.RES;  // diavase tin timh adc
		teleftea_timi_adc= timh_adc; // vale tin sosti timh

		
		TCA0.SPLIT.HCMP0 = kato_orio-teleftea_timi_adc ; // Diarkeia tou timer
		TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm; // Enable timer

		PORTD.OUTCLR |= PIN0_bm; // anoikse led0
	}
	// Clear flags
	int intflags = PORTF.INTFLAGS;
	PORTF.INTFLAGS = intflags;
	sei();
}


ISR(TCA0_LUNF_vect) {
	cli();
	PORTD.OUTTGL = PIN2_bm; // anoigoklinei to led
	if (++rising_edge >= 4) {  // kleinei o anemisthras
		TCA0.SPLIT.CTRLB = ~TCA_SPLIT_LCMP0EN_bm; // Disable PWM ara kleinei o anemisthras
		TCA0.SPLIT.CTRLA = ~TCA_SPLIT_ENABLE_bm;
		PORTD.OUT |= (PIN1_bm|PIN2_bm); // kleise to led
		
		rising_edge = 0;  // Reset ton metrhth
	}
	sei();
}

// isr gia to potisma
ISR(TCA0_HCMP0_vect) {  
	cli();
	TCA0.SPLIT.CTRLA = ~TCA_SPLIT_ENABLE_bm; // kleise to timer
	PORTD.OUT |= PIN0_bm;  // kleise to led
	sei();
	
}