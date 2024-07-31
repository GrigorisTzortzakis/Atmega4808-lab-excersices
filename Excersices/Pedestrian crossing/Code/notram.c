#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PEZOS_PRASINO 800   // diarkeia pezofanarou T2
#define COOLDOWN_Koubiou 1000 // T3


volatile int Button_pezou  = 0;
volatile int Cooldown = 0;

int main() {
	// Set up
	PORTD.DIR = PIN0_bm | PIN2_bm |PIN1_bm ; // 0 dromos me ta autokinhta , 2 to pezofanaro , 1 to tram
	PORTD.OUT |= PIN2_bm | PIN1_bm ; // arxikh katastash prasino gia autokinhta kokkino gia pezous 


	// koubi pezon
	PORTF.PIN5CTRL |= PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;

	// timer split
	TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm; // Enable split mode
	TCA0.SPLIT.LCMP0 = PEZOS_PRASINO; // Compare gia tous pezous
	TCA0.SPLIT.LCMP1 = COOLDOWN_Koubiou; // Compare gia to cooldown
	TCA0.SPLIT.HCMP0 = TRAM_INTERVAL; // compare gia to tram
	TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV1024_gc | TCA_SPLIT_ENABLE_bm; // Enable 
	TCA0.SPLIT.CTRLB = TCA_SPLIT_LCMP0EN_bm | TCA_SPLIT_LCMP1EN_bm | TCA_SPLIT_HCMP0EN_bm ; // Enable   interrupts
	
	sei(); 

	while (1) {
		if (Button_pezou  && !Cooldown) {
			// pezos pernaei
			PORTD.OUT  = PIN0_bm; // kokkino gia ta amaksia , kanoume to bit 1 
			PORTD.OUTCLR = PIN2_bm;  //prasino gia tous pezous , kanoume to bit 0
			TCA0.SPLIT.LCNT = 0; // arxizei o timer
			Button_pezou  = 0; //reset koubi pezon
			Cooldown = 1; //arxh cooldown
		}
	
	}
}

// ISR otan patiete to koubi pezon
ISR(PORTF_PORT_vect){
	PORTF.INTFLAGS = PORTF.INTFLAGS; // Clear interrupt 
	Button_pezou  = 1; // energopoihsh koubiou
}

// ISR gia timer pezon
ISR(TCA0_LCMP0_vect){
	TCA0.SPLIT.INTFLAGS = TCA_SPLIT_LCMP0_bm; // Clear 

	// piso stin default katastash
	PORTD.OUTCLR = PIN0_bm;  
	PORTD.OUT  = PIN2_bm; 
}

// ISR gia cooldown
ISR(TCA0_LCMP1_vect){
	TCA0.SPLIT.INTFLAGS = TCA_SPLIT_LCMP1_bm; 
	Cooldown = 0; // Cooldown telos
}

