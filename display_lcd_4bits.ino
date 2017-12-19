#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))

#define DADOS_LCD PORTD
#define nibble_dados 1

#define CONTR_LCD PORTB
#define RS PB0
#define E PB1

#define tam_vector 5
#define conv_ascii 48

#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD, E); _delay_us(1); clr_bit(CONTR_LCD, E); _delay_us(45);

void cmd_LCD (unsigned char c, char cd) {
  if (cd == 0) {
    clr_bit(CONTR_LCD, RS);
  }
  else {
    set_bit(CONTR_LCD, RS);
  }

  #if (nibble_dados)
    DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & c);
  #else
    DADOS_LCD = (DADOS_LCD & 0xF0) | (c >> 4);
  #endif

  pulso_enable();

  #if (nibble_dados)
    DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c << 4));
  #else
    DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
  #endif

  pulso_enable();

  if ((cd == 0) && (c < 4)) {
    _delay_ms(2);
  }
}

void init_LCD_4bits () {
  clr_bit(CONTR_LCD, RS);
  clr_bit(CONTR_LCD, E);

  _delay_ms(20);

  #if (nibble_dados)
    DADOS_LCD = (DADOS_LCD & 0x0F) | 0x30;
  #else
    DADOS_LCD = (DADOS_LCD & 0xF0) | 0x03;
  #endif

  pulso_enable();
  _delay_ms(5);
  pulso_enable();
  _delay_us(200);
  pulso_enable();

  #if (nibble_dados)
    DADOS_LCD = (DADOS_LCD & 0x0F) | 0x20;
  #else
    DADOS_LCD = (DADOS_LCD & 0xF0) | 0x02;
  #endif

  pulso_enable();
  cmd_LCD(0x28, 0);

  cmd_LCD(0x08, 0);
  cmd_LCD(0x01, 0);
  cmd_LCD(0x0c, 0);
  cmd_LCD(0x80, 0);
}

void escreve_LCD (char *c) {
  for (; *c != 0; c++) {
    cmd_LCD(*c, 1);
  }
}

void escreve_LCD_Flash (const char *c) {
  for (; pgm_read_byte(&(*c)) != 0; c++) {
    cmd_LCD(pgm_read_byte(&(*c)), 1);
  }
}

const char msg[] PROGMEM = " DADOS DE 4BITS!\0";

int main( ) {
  unsigned char i;

  DDRB = 0xFF;
  DDRD = 0xFF;

  init_LCD_4bits();
  escreve_LCD(" INTERFACE DE");
  cmd_LCD(0xc0, 0);
  escreve_LCD_Flash(msg);

  while(1){}
}
