uint16_t tmp_subida, tmp_descida;
uint32_t dif, dist;

void led_distance(){
	if(dist <= 25){ // caso perto demais, ativa os três LEDs
		PORTC = 0b0111000;
	}else if(dist > 25 && dist < 40){ // caso distancia media, ativa dois LEDs
		PORTC = 0b0011000;
	}else if (dist < 60) { // caso distancia longa, ativa um LED
		PORTC = 0b0001000;
	}
  else PORTC = 0x00;
}

ISR(TIMER1_CAPT_vect) { //mudança de estado no pino PB0 (ICP1)
	if (TCCR1B & (1 << ICES1)) { // verifica se é borda de subida
		TCCR1B &= ~(1 << ICES1); // próxima verificação feita na borda de descida
		tmp_subida = ICR1; // salva tempo de borda de subida
	}
	else {
		TCCR1B |= (1 << ICES1); // próxima verificação feita na borda de descida
		tmp_descida = ICR1; //salva tempo de borda de descida
		dif = (uint32_t)tmp_descida - (uint32_t)tmp_subida;
		dist =  dif * 10 / 58; // distancia em mm
		led_distance();
		Serial.print("disnatncia (milimetros): ");
		Serial.println(dist);
	}
}

ISR(TIMER1_COMPA_vect) { //igualdade de comparação com OCR1A
	cpl_bit(PORTB, PIN5);
	_delay_us(15); // gera pulso de 15us pro trigger
	cpl_bit(PORTB, PIN5);
}
