/*
 * AtmelISR.c
 *
 * Author : Ana Beatriz Marinho
 */ 

#define F_CPU 16000000UL  
#include <avr/io.h>
#include <avr/interrupt.h>

void Timer1_init(void) {
	
	TCCR1B |= (1 << WGM12);  // Configura o Timer 1 no modo CTC (Clear Timer on Compare Match)
	TCCR1B |= (1 << CS12) | (1 << CS10);  // Prescaler 1024, ele é usado para reduzir a frequência base do timer

	// Valor de comparação para 1 segundo (16MHz / 1024 prescaler)
		OCR1A = 15624; //Gera uma interrupção a cada 1 segundo => 1*15624 = 15624 
					   // Para 0,5 segundos => 0,5*15624 = 7812	
					   // Para 2 segundos => 2*15624 = 31248
					   
	// Habilita interrupção para o comparador A
	TIMSK1 |= (1 << OCIE1A); 
}

//A interrupção é acionada toda vez que o Timer 1 atinge o valor definido em OCR1A
ISR(TIMER1_COMPA_vect) {
	PORTB ^= (1 << PORTB5); // Alterna o estado do LED
}

int main(void) {
	DDRB |= (1 << DDB5); // Pino PB5 (pino do LED) como saída
	Timer1_init(); // Inicialização do Timer 1

	// Habilita interrupções globais
	sei();

	while (1) {
		// O loop fica vazio. O LED é controlado pela interrupção
	}

	return 0;
}


