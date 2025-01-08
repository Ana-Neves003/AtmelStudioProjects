#include <avr/io.h>
#include <util/delay.h>

// Inicializa UART
void UART_init() {
	uint16_t ubrr = 103; // Para 16 MHz e 9600 baud
	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;

	UCSR0B = (1 << TXEN0); // Habilita transmissão
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits de dados
}

// Envia um caractere via UART
void UART_transmit(char data) {
	while (!(UCSR0A & (1 << UDRE0))); // Aguarda registrador estar vazio
	UDR0 = data;
}

// Envia uma string via UART
void UART_transmit_string(const char *str) {
	while (*str) {
		UART_transmit(*str++);
	}
}

int main() {
	UART_init();
	while (1) {
		UART_transmit_string("Hello, UART!\r\n");
		_delay_ms(1000);
	}
}
