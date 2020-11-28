

#include "hal.h"
#include "out.h"
#include "vm.h"
#define F_CPU 16000000UL
#include <avr/io.h>

unsigned int UBRR0_value = 103;
bool toggle = false;

char UART_receive() {
  char readChar;

  // Wait until unread data received
  while ( !(UCSR0A & (1 << RXC0)) ) {
    PORTB |= 1 << 5;
  };

  PORTB ^= (1 << 5);
  // Read data
  readChar = (char)UDR0;

  return readChar;
}

void UART_transmit(char data) {
  while ( !(UCSR0A & (1 << UDRE0)) );
  UDR0 = data;
}




int main(void) {
  
  // Set PIN 13 (PB5) as output to control LED
  DDRB = 1 << 5;

  // Set BAUD rate
  UBRR0H = UBRR0_value >> 8; 
  UBRR0L = UBRR0_value;

  // Enable receiver and transmitter
  UCSR0B |= (1 << RXEN0) | (1 << TXCIE0);
  
  /*  Using default frame format:
   *  Async
   *  No parity
   *  8-bit character size
   *  1-bit stop bit
  */
  char mem[3] = { };
  int count = 0;
  while(1) {
    char readChar = UART_receive();
    
    if (readChar == 1) {
      break;
    }
    else {
      mem[count++] = readChar;
    }

  }

  // Run program
  Hal_Init();
  VMOut_PutS("Test pre-compiled program:\n");
  VMOut_PutS("1\n");
  VM_Init(mem);
  VM_execute(mem);
}
