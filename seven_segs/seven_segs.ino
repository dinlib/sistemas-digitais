#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) 
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) 
#define tst_bit(Y,bit_x) (Y&(1<<bit_x))
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x))

int main( ) {

    byte seven_segments_table[16][7]{ {0, 1, 1, 1, 0, 0, 0},
                                      {0, 1, 1, 0, 0, 0, 0}, 
                                      {1, 0, 0, 0, 0, 1, 0},
                                      {0, 1, 1, 0, 0, 0, 1},
                                      {1, 1, 0, 0, 0, 0, 0}, 
                                      {0, 0, 0, 1, 0, 0, 0}, 
                                      {0, 0, 0, 1, 1, 0, 0}, 
                                      {0, 0, 0, 0, 0, 0, 0}, 
                                      {0, 0, 0, 1, 1, 1, 1}, 
                                      {0, 1, 0, 0, 0, 0, 0}, 
                                      {0, 1, 0, 0, 1, 0, 0}, 
                                      {1, 0, 0, 1, 1, 0, 0}, 
                                      {0, 0, 0, 0, 1, 1, 0}, 
                                      {0, 0, 1, 0, 0, 1, 0}, 
                                      {1, 0, 0, 1, 1, 1, 1}, 
                                      {0, 0, 0, 0, 0, 0, 0}
    };
    
    unsigned char value = 0;
    
    DDRB = 0b11111111;
    PORTB = 0b11111111;
    
    DDRD = 0b11111111;
    PORTD = 0b11111111;

//    PORTD = 0b0000000;
//    PORTB= 0b0000000;
    

//    PORTD = seven_segments_table[7];
    while(1){
        if(value == 0x0F) value = 0;
          else value++;
          PORTB = pgm_read_byte(&seven_segments_table[value]);
          PORTD = pgm_read_byte(&seven_segments_table[value]);
          _delay_ms(1000);
    }
}


