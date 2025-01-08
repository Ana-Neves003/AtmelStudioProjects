/*
 * AtmelPWM.c
 *
 * Author : Ana Beatriz Marinho 
 */ 

#define F_CPU 16000000UL  // Frequência do cristal do Arduino Uno (16 MHz)
#include <avr/io.h>
#include <util/delay.h>

void PWM_init() {
	// Configura o Timer0 para gerar PWM no pino 6 (OC0A)
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);  // Modo Fast PWM, Clear OC0A on Compare Match
	TCCR0B = (1 << CS00);  // Sem prescaler, clock direto
	DDRD |= (1 << DDD6);    // Configura o pino 6 (PD6) como saída (LED externo)
}

void set_PWM_duty_cycle(uint8_t duty) {
	OCR0A = duty;  // Define o valor do duty cycle (0-255)
}

int main(void) {
	PWM_init();  // Inicializa o PWM no pino 6

	while (1) {
		set_PWM_duty_cycle(128);  // Define um brilho de 50% (OCR0A = 128)
		_delay_ms(1000);          // Espera 1 segundo
	}

	return 0;
}




