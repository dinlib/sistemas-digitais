#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))

#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD, E); _delay_us(1); clr_bit(CONTR_LCD, E); _delay_us(45);

#define DADOS_LCD PORTD // 8 bits de dado
#define CONTR_LCD PORTB // pinos de controle
#define RS PB1 // pino de instrução ou dado
#define E PB0 //pino de enable

const unsigned char msg[] PROGMEM = "ABCDEFGHIJKLMNOPQ";

void cmd_LCD(unsigned char c, char cd) {
  DADOS_LCD = c;

  if (cd == 0) {
    clr_bit(CONTR_LCD, RS);
  }
  else {
    set_bit(CONTR_LCD, RS);
  }

  pulso_enable();

  if ((cd == 0) && (c < 4)) {
    _delay_ms(2);
  }
}

void init_LCD_8bits() {
  clr_bit(CONTR_LCD, RS);

  _delay_ms(15);

  DADOS_LCD = 0x38;

  pulso_enable();
  _delay_ms(5);
  pulso_enable();
  _delay_us(200);

  pulso_enable();
  pulso_enable();

  cmd_LCD(0x08, 0);
  cmd_LCD(0x01, 0);
  cmd_LCD(0x0c, 0);
  cmd_LCD(0x80, 0);
}

void escreve_LCD(char *c) {
  for (; *c != 0; c++) {
    cmd_LCD(*c, 1);
  }
}

int main( ) {
  unsigned char i;

  DDRB = 0xFF;
  DDRD = 0xFF;
  UCSR0B = 0x00;

  init_LCD_8bits();

  for (size_t i = 0; i < 16; i++) {
    cmd_LCD(pgm_read_byte(&msg[i]), 1);
  }

  cmd_LCD(0xc0, 0);
  escreve_LCD("QRSTUVWXYZ 123456");

  while(1){};
}
