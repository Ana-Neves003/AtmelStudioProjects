#include <avr/io.h>
#include <util/delay.h>

// Inicializa o I2C como mestre
void I2C_master_init() {
	TWSR = 0x00; // Sem prescaler
	TWBR = 0x48; // Configura SCL para 100kHz com F_CPU = 16MHz
	TWCR = (1 << TWEN); // Habilita o TWI
}

// Inicia uma comunica��o I2C
void I2C_start() {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT))); // Aguarda a opera��o
}

// Envia um dado via I2C
void I2C_write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT))); // Aguarda a opera��o
}

// Encerra a comunica��o I2C
void I2C_stop() {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	while (TWCR & (1 << TWSTO)); // Aguarda a finaliza��o
}

int main() {
	I2C_master_init();
	while (1) {
		I2C_start();
		I2C_write(0x20); // Endere�o do escravo (0x10) com bit de escrita
		I2C_write('H');
		I2C_write('e');
		I2C_write('l');
		I2C_write('l');
		I2C_write('o');
		I2C_write('!');
		I2C_stop();
		_delay_ms(1000); // Aguarda 1 segundo
	}
}


