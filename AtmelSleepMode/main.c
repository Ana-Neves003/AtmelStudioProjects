/*
 * AtmelSleepMode.c
 *
 * Author: Ana Beatriz Marinho
 */

#define F_CPU 16000000UL  // Configura a frequ�ncia do rel�gio para 16 MHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

volatile uint8_t buttonPressed = 0;  // Vari�vel para verificar o estado do bot�o (0 = false, 1 = true)

// Fun��o de interrup��o para INT0 (pino 2, bot�o pressionado)
ISR(INT0_vect) {
	// Acorda o microcontrolador (interrup��o gerada pela borda de descida do bot�o)
	buttonPressed = 1;  // Marca que o bot�o foi pressionado
}

void Sleep_init(void) {
	// Configura o pino 2 (PD2/INT0) para interrup��o externa (borda de descida)
	EIMSK |= (1 << INT0);           // Habilita a interrup��o INT0 (pino PD2)
	EICRA |= (1 << ISC01) | (1 << ISC00);  // Gera interrup��o na borda de descida (bot�o pressionado)

	// Configura o modo de sono para o modo mais profundo (PWR_DOWN)
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Modo de menor consumo
	sei();  // Habilita interrup��es globais
}

int main(void) {
	Sleep_init();  // Inicializa o modo de sono e interrup��es

	while (1) {
		sleep_mode();  // Entra no modo de dormir (PWR_DOWN)
		
		// O microcontrolador acorda aqui ap�s a interrup��o
		if (buttonPressed) {
			// Quando o bot�o � pressionado, a interrup��o � gerada e o microcontrolador acorda
			buttonPressed = 0;  // Limpa a flag de bot�o pressionado

			// Aqui voc� pode fazer algo ap�s o bot�o ser pressionado, como acender o LED
			PORTB |= (1 << PB5);  // Acende o LED (pino 13)
			_delay_ms(1000);  // Mant�m o LED aceso por 1 segundo
			PORTB &= ~(1 << PB5);  // Apaga o LED ap�s 1 segundo
		}
	}

	return 0;
}


