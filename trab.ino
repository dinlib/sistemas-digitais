#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))

void turn_on_display(int n){
  switch (n) {
    case 0:
      PORTB = 0b111110;
      PORTD = 0b00000011;
      break;
    case 1:
      PORTB = 0b111111;
      PORTD = 0b11001011;
      break;
    case 2:
      PORTB = 0b111101;
      PORTD = 0b00100011;
      break;
    case 3:
      PORTB = 0b111101;
      PORTD = 0b10000011;
      break;
    case 4:
      PORTB = 0b111100;
      PORTD = 0b11001011;
      break;
    case 5:
      PORTB = 0b111100;
      PORTD = 0b10010011;
      break;
    case 6:
      PORTB = 0b111100;
      PORTD = 0b00010011;
      break;
    case 7:
      PORTB = 0b111110;
      PORTD = 0b11000011;
      break;
    case 8:
      PORTB = 0b111100;
      PORTD = 0b00000011;
      break;
    case 9:
      PORTB = 0b111100;
      PORTD = 0b11000011;
      break;
    case 10:
      PORTB = 0b111100;
      PORTD = 0b01000011;
      break;
    case 11:
      PORTB = 0b111100;
      PORTD = 0b00011011;
      break;
    case 12:
      PORTB = 0b111110;
      PORTD = 0b00110011;
      break;
    case 13:
      PORTB = 0b111101;
      PORTD = 0b00001011;
      break;
    case 14:
      PORTB = 0b111100;
      PORTD = 0b00110011;
      break;
    case 15:
      PORTB = 0b111100;
      PORTD = 0b01110011;
      break;
  }
}

ISR(PCINT0_vect);

int count;

int main( ) {
  	count = 1;
    DDRB = 0xFF; // PB1 e PB0 são de saida
    PORTB = 0xFF; // ativa no 0

    DDRD = 0xFF;
    PORTD = 0xFF;


  	PCMSK0 |= (1 << PCINT2);
  	PCICR |= (1 << PCIE0);

    sei();


    while(1){
      	count++;
      	if (count + 1 == 7) count = 1;
    }
}

ISR(PCINT0_vect){
  turn_on_display(count);
  _delay_ms(200);
}
