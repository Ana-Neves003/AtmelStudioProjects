/*
 * AtmelLedButton.c
 * Author : Ana Beatriz Marinho
 */ 

#define F_CPU 16000000UL  // Frequ�ncia do cristal do Arduino Uno (16 MHz)
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	// Configura o pino PB5 (pino do LED) como sa�da
	DDRB |= (1 << DDB5);

	// Configura o pino PD2 (bot�o) como entrada com pull-up habilitado
	DDRD &= ~(1 << DDD2);  // Configura PD2 como entrada
	PORTD |= (1 << PORTD2);  // Habilita o resistor de pull-up interno no PD2

	while (1) {
		// Verifica o estado do bot�o
		if (!(PIND & (1 << PIND2))) {  // Se o bot�o estiver pressionado (n�vel l�gico baixo)
			PORTB |= (1 << PORTB5);   // Liga o LED
			} else {
			PORTB &= ~(1 << PORTB5);  // Desliga o LED
		}
	}

	return 0;
}


