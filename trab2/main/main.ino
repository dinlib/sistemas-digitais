#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "lcd.h"
#include "ultrasonic.h"

int main(){
	Serial.begin(9600);
	char str[16]; // utilizado para converter distancia para string e mostrar no LCD
  char white[16] = "                ";

	//ECHO está no PB0
	DDRB |= (1 << PIN1) | (1 << PIN2) | (1 << PIN5); // 1 e 2 p/ o LCD e 5 p/ o TRIGGER
	DDRC = 0xFF; //habilita portas de saída para os leds
	PORTC = 0b0111000;
	DDRD = 0xFF; // dados do LCD


	TCCR1B |= (1 << ICNC1) | (1 << CS10) | (1 << CS11) | (1 << WGM12); // ativa ICNC1 para filtro de ruído
	// ativa CS10 e CS11 prescalar 64
	// ativa WGM12 para modo CTC - utilizar OCR1A
	TIMSK1 |= (1 << ICIE1) | (1 << OCIE1A); //ICIE1 ativa interrupção pra quando ocorre mudança de estado do
	//pino ICP1 (PB0, echo ligado).
	//OCIE1A ativa interrupção pra igualdade de comparação no OCR1A,
	//utilizado para disparar o trigger.

	TCCR1B |= (1 << ICES1); // habilita captura na borda de subida

	OCR1A = 10000; // quando contador atingir a igualdade de OCR1A, acontecerá uma interrupção que ativará o trigger
	sei();

	init_LCD_4bits();
  escreve_LCD("Distancia (mm): ");
	while(1){
		cmd_LCD(0xC0, 0);
		itoa(dist, str, 10);
		escreve_LCD(str);
    escreve_LCD(white);
	}
}
