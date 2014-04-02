#include<avr/io.h>
#define FOSC 16000000 // Clock Speed
#define BAUD 31250// baud rate
#define MYUBRR FOSC/16/BAUD-1
void USART_Init(unsigned int ubrr);
//unsigned char USART_Receive( void );

int main(void)
{
  USART_Init(MYUBRR);
  DDRB |= 1 << PORTB5;
  PORTB ^= 1 << PORTB5;
  
  while(1)
  {
    while ( !(UCSR0A & (1<<RXC0)) );
    {
      if (UDR0 == 60) PORTB ^= 1 << PORTB5;  
    }
  }
}

void USART_Init(unsigned int ubrr)
{
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

/*
To compile with GCC
avr-gcc -mmcu=atmega328p -Wall -Os -o usart_basic_rx.elf USART_BASIC_RX.C

Create .hex
avr-objcopy -j .text -j .data -O ihex usart_basic_rx.elf usart_basic_rx.hex

Upload using AVRdude
sudo avrdude -p m328p -c usbtiny -e -U flash:w:usart_basic_rx.hex
*/
