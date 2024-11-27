/*
 * AtmelUART.c
 *
 * Author : Ana Beatriz Marinho
 */ 

#define F_CPU 16000000UL  
#include <avr/io.h>
#include <util/delay.h>

void UART_init(unsigned int baud) {
	unsigned int ubrr = F_CPU / 16 / baud - 1;  // Calcula o valor do baud rate
	UBRR0H = (ubrr >> 8);    // Configura a parte alta do baud rate
	UBRR0L = ubrr;           // Configura a parte baixa do baud rate
	UCSR0B = (1 << TXEN0);   // Habilita a transmissão
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Modo 8 bits
}

void UART_transmit(char data) {
	while (!(UCSR0A & (1 << UDRE0)));  // Espera o buffer ficar vazio
	UDR0 = data;  // Envia o dado
}

void UART_send_string(const char *str) {
	while (*str) {
		UART_transmit(*str++);  // Envia cada caractere da string
	}
}

int main(void) {
	UART_init(9600);  // Inicializa a UART com baud rate 9600

	while (1) {
		UART_send_string("Ola jovens\n");  // Envia a mensagem no monitor serial
		_delay_ms(1000);  // Aguarda 1 segundo antes de enviar novamente
	}

	return 0;
}


