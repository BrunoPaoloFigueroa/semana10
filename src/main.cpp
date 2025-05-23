#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

/*
void display(float valor){

  int val = (int)(valor * 100); // Convierte, ej: 0.73 -> 73
  if (val > 999) val = 999;

  int c = val / 100;        // Centenas
  int d = (val / 10) % 10;  // Decenas
  int u = val % 10;         // Unidades

  // Mostrar centenas
  PORTB |= 0x07;           // Apaga todos los displays
  PORTD = (PORTD & 0x0F) | (c << 4); // Envia BCD al 74LS48
  PORTB &= ~(1 << 2);        // Enciende display 1
  _delay_ms(1);

  // Mostrar decenas
  PORTB |= 0x07;
  PORTD = (PORTD & 0x0F) | (d << 4);
  PORTB &= ~(1 << 1);        // Enciende display 2
  _delay_ms(1);

  // Mostrar unidades
  PORTB |= 0x07;
  PORTD = (PORTD & 0x0F) | (u << 4);
  PORTB &= ~(1 << 0);        // Enciende display 3
  _delay_ms(1);
}
*/
unsigned char z = 0;

char recive_char(void){
        while(!(UCSR0A&(1<<RXC0)));
      
        return UDR0;

}
/*
void config_ADC(void){

    ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2);
    ADMUX|=(1<<REFS0);
}
float valve=0;
ISR(ADC_vect){
    valve=ADC*4.99/1023.0;
    UCSR0B|=(1<<UDRIE0);

}
void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
    UBRR0=103;
}
unsigned char dato=0;
unsigned char flag=0;
ISR(USART_UDRE_vect){
   


      unsigned int val = (int)(valve * 100);  
  unsigned int d = (val / 100);  
  unsigned int u = (val / 10)%10;    
  unsigned int de=(val % 10);

    switch (z) {
      case 0:
          UDR0 = d + '0';  // Convertir a ASCII
          z = 1;
          break;
      case 1:
          UDR0 = 46;      // Separador
          z = 2;
          break;
      case 2:
          UDR0 = u + '0';  // Convertir a ASCII
          z = 3;
          break;
      case 3:
          UDR0 = de + '0';  // Convertir a ASCII
          z = 4;
          break;    
      case 4:
          UDR0 =  10;  // Convertir a ASCII
          z = 0;
          UCSR0B&=~(1<<UDRIE0);
          ADCSRA|=(1<<ADSC);
          break;
            
  }

    _delay_ms(100);
}
int main(void){
    DDRD|=0x02;
    config_ADC();
    config_USART();
    sei();
    ADCSRA|=(1<<ADSC);
    while(1){

    }
  return 0;
}
*/
/*
void config_ADC(void){

    ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2);
    ADMUX|=(1<<REFS0);
}
float valve=0;
ISR(ADC_vect){
    valve=ADC*4.99/1023.0;
    UCSR0B|=(1<<UDRIE0);

}

void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
    UBRR0=103;
}

ISR(USART_UDRE_vect){
   


    unsigned int val = (int)(valve * 100);  
  unsigned int d = (val / 100);  
  unsigned int u = (val / 10)%10;    
  unsigned int de=(val % 10);

    switch (z) {
      case 0:
          UDR0 = d + '0';  // Convertir a ASCII
          z = 1;
          break;
      case 1:
          UDR0 = 46;      // Separador
          z = 2;
          break;
      case 2:
          UDR0 = u + '0';  // Convertir a ASCII
          z = 3;
          break;
      case 3:
          UDR0 = de + '0';  // Convertir a ASCII
          z = 4;
          break;    
      case 4:
          UDR0 =  10;  // Convertir a ASCII
          z = 0;
          UCSR0B&=~(1<<UDRIE0);
          
          break;
            
  }

    _delay_ms(100);
}
unsigned char doto=0;
ISR(USART_UDRIE_vect){
    UDR0=doto;
    
    UCSR0B&=~(1<<UDRIE0);
}

int main(void){
    config_USART();
    config_ADC();   
    sei();
    while(1){
        doto=recive_char();
       
        if(doto=='A'){
        ADCSRA|=(1<<ADSC);
        doto=0;
    }
    }
}
*/
unsigned char doto=0;
void config_ADC(void){

    ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2);
    ADMUX|=(1<<REFS0);
}
float valve=0;
ISR(ADC_vect){
    valve=ADC*4.99/1023.0;
    UCSR0B|=(1<<UDRIE0);

}

void config_USART(void){
    UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
    UCSR0B|=(1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
    UBRR0=103;
}
ISR(USART_UDRE_vect){
   


    unsigned int val = (int)(valve * 100);  
  unsigned int d = (val / 100);  
  unsigned int u = (val / 10)%10;    
  unsigned int de=(val % 10);

    switch (z) {
      case 0:
          UDR0 = d + '0';  // Convertir a ASCII
          z = 1;
          break;
      case 1:
          UDR0 = 46;      // Separador
          z = 2;
          break;
      case 2:
          UDR0 = u + '0';  // Convertir a ASCII
          z = 3;
          break;
      case 3:
          UDR0 = de + '0';  // Convertir a ASCII
          z = 4;
          break;    
      case 4:
          UDR0 =  10;  // Convertir a ASCII
          z = 0;
          UCSR0B&=~(1<<UDRIE0);
          
          break;
            
  }

    _delay_ms(100);
}
ISR(USART_RX_vect){
    
   doto=UDR0;
    if(doto=='A'){
        ADCSRA|=(1<<ADSC);
        doto=0;
    }
    
}
int main(void){

  config_USART();
    config_ADC();   
    sei();
    while(1){

    }

}
