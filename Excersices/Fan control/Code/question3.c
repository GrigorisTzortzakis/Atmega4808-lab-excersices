/*
 * GccApplication13.c
 *
 * Created: 05-Apr-24 2:04:18 AM
 * Author : Mr karkinopoulos
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
volatile  leitourgia_anemisthra = 0; // koitame to koubi tou anemisthra an patithike


int main() {
	// input
	PORTD.DIR |= PIN0_bm | PIN1_bm;

	// koubi
	PORTF.PIN5CTRL |= PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;

	// Enable split mode
	TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;
	
	// Enable PWM
	TCA0.SPLIT.CTRLB |= TCA_SPLIT_LCMP0EN_bm | TCA_SPLIT_HCMP0EN_bm;


	// low part gia tis lepides
	TCA0.SPLIT.LPER = 18;  // periodos lepidon
	TCA0.SPLIT.LCMP0 = 9;  // Duty cycle lepidon

	// high part gia tin vash
	TCA0.SPLIT.HPER = 38;  // Periodos gia thn vash
	TCA0.SPLIT.HCMP0 = 23; // Duty cycle gia thn vash

	// prescaler 1024
	TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV1024_gc;

	//  interrupts 
	TCA0.SPLIT.INTCTRL |= TCA_SPLIT_LUNF_bm | TCA_SPLIT_HUNF_bm;

	
	sei();

	while (1) {
		
	}

	return 0;
}

// ISR gia lepides
ISR(TCA0_LUNF_vect) {
	cli();
	PORTD.OUTTGL = PIN0_bm; // Anavosvinei to led me ton kathe kiklo
	sei();
	
}

// ISR gia vash
ISR(TCA0_HUNF_vect) {
	cli();
	PORTD.OUTTGL = PIN1_bm; // Anavosvinei to led me ton kathe kiklo
	sei();

}



ISR(PORTF_PORT_vect) {
	cli();
	// patithike to koubi
	leitourgia_anemisthra++;

	if (leitourgia_anemisthra == 1) {
		// Katastash 1= anoikse ton anemisthra
		TCA0.SPLIT.LPER = 18;
		TCA0.SPLIT.LCMP0 = 9;
		} else if (leitourgia_anemisthra == 2) {
		// katastash 2 =ipodiplasiase thn periodo lepidon
		TCA0.SPLIT.LPER = 9;
		TCA0.SPLIT.LCMP0 = 4;
		
		
	}  else if (leitourgia_anemisthra == 3) {
	// katastash 3 = kleise ton anemisthra
	TCA0.SPLIT.LCMP0 = 0; //kleinei
	leitourgia_anemisthra = 0; // midenise to koubi gia na boro na to ksanakano
}


	// o timer arxizei otan patithei to koubi
	TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm;

	
	// Clear flags
	int intflags = PORTF.INTFLAGS;
	PORTF.INTFLAGS = intflags;
	sei();
}

