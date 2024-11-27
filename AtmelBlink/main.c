#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void initPWM() {
	// Configura o Timer0 para Fast PWM (modo 3), saída não invertida em OC0B (PB5)
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0B1);  // Fast PWM, não invertido no OC0B
	TCCR0B |= (1 << CS02) | (1 << CS00);  // Prescaler = 1024

	// Configura PB5 (pino digital 13) como saída
	DDRB |= (1 << PB5);
}


void loop() {
	for (uint8_t dutyCycle = 0; dutyCycle < 255; dutyCycle++) {
		OCR0B = dutyCycle; // Set duty cycle
		_delay_ms(10); // Delay for visibility
	}
	for (uint8_t dutyCycle = 255; dutyCycle > 0; dutyCycle--) {
		OCR0B = dutyCycle; // Set duty cycle
		_delay_ms(10); // Delay for visibility
	}
}

int main() {
	initPWM();
	while (1) {
		loop();
	}
}
