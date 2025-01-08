/*
 * AtmelSleepMode.c
 *
 * Author: Ana Beatriz Marinho
 */

#define F_CPU 16000000UL  // Configura a frequência do relógio para 16 MHz

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

volatile uint8_t buttonPressed = 0;  // Variável para verificar o estado do botão (0 = false, 1 = true)

// Função de interrupção para INT0 (pino 2, botão pressionado)
ISR(INT0_vect) {
	// Acorda o microcontrolador (interrupção gerada pela borda de descida do botão)
	buttonPressed = 1;  // Marca que o botão foi pressionado
}

void Sleep_init(void) {
	// Configura o pino 2 (PD2/INT0) para interrupção externa (borda de descida)
	EIMSK |= (1 << INT0);           // Habilita a interrupção INT0 (pino PD2)
	EICRA |= (1 << ISC01) | (1 << ISC00);  // Gera interrupção na borda de descida (botão pressionado)

	// Configura o modo de sono para o modo mais profundo (PWR_DOWN)
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Modo de menor consumo
	sei();  // Habilita interrupções globais
}

int main(void) {
	Sleep_init();  // Inicializa o modo de sono e interrupções

	while (1) {
		sleep_mode();  // Entra no modo de dormir (PWR_DOWN)
		
		// O microcontrolador acorda aqui após a interrupção
		if (buttonPressed) {
			// Quando o botão é pressionado, a interrupção é gerada e o microcontrolador acorda
			buttonPressed = 0;  // Limpa a flag de botão pressionado

			// Aqui você pode fazer algo após o botão ser pressionado, como acender o LED
			PORTB |= (1 << PB5);  // Acende o LED (pino 13)
			_delay_ms(1000);  // Mantém o LED aceso por 1 segundo
			PORTB &= ~(1 << PB5);  // Apaga o LED após 1 segundo
		}
	}

	return 0;
}


