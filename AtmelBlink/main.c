#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define LED_PIN PB5 // pino do LED 

void init() {
	DDRB |= (1 << LED_PIN); // Configura o pino PB5 como saída
}

int main(void) {
	init();
	while (1) {
		PORTB ^= (1 << LED_PIN); // Alterna o estado do LED
		_delay_ms(500); // Espera 500 ms
	}
}
