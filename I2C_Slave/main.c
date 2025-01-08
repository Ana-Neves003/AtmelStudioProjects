#include <avr/io.h>
#include <util/delay.h>

// Inicializa o I2C como escravo
void I2C_slave_init(uint8_t address) {
	TWAR = (address << 1); // Configura endereço do escravo
	TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT); // Habilita o TWI
}

// Inicializa a UART
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

// Aguarda dado do mestre via I2C
uint8_t I2C_receive() {
	while (!(TWCR & (1 << TWINT))); // Aguarda a operação
	return TWDR; // Retorna o dado recebido
}

int main() {
	uint8_t data;

	I2C_slave_init(0x10); // Endereço do escravo: 0x10
	UART_init(); // Inicializa a UART

	while (1) {
		TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT); // Prepara o escravo para receber
		data = I2C_receive(); // Recebe o dado do mestre
		UART_transmit(data); // Envia o dado recebido ao terminal via UART
	}
}
