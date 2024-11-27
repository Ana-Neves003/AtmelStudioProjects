#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void initPWM() {
	// Configura o Timer2 para Fast PWM (modo 3) em 8 bits
	TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1);  // Fast PWM, non-inverted output on OC2A (PB3)
	TCCR2B |= (1 << CS21);  // Prescaler = 8
	
	// Configura o pino PB3 (OC2A) como saída
	DDRB |= (1 << PB3);
}

void SetPWMOutput(int duty) {
	// Define o valor de OCR2A para controlar o ciclo de trabalho do PWM
	OCR2A = duty;
}

void Wait(){
	_delay_loop_2(3200);  // Delay ajustado para uma mudança suave no brilho
}

int main(void) {
	int brilho = 0;
	initPWM();
	
	while(1){
		// Aumenta o brilho do LED
		for (brilho = 0; brilho < 255; brilho++) {
			SetPWMOutput(brilho);
			Wait();
		}
		
		// Diminui o brilho do LED
		for (brilho = 255; brilho > 0; brilho--) {
			SetPWMOutput(brilho);
			Wait();
		}
	}
}
