

#include "hal.h"
#include "out.h"
#include "vm.h"
#include "command_types.h"
#define F_CPU 16000000UL
#include <avr/io.h>

#define MemMax 300

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
  
  while(1) {
    Hal_Init();
    u8 program[MemMax]  = {};
    int count = 0;

    u8 programSize[2] = { };
    int sizeCount = 0;
    int size = 0;

    bool run = true;

    while(1) {
      char readChar = UART_receive();
      // Calculate program size using first 2 bytes
      if (sizeCount <= 1) {
        programSize[sizeCount++] = (u8)readChar;
        if (sizeCount == 2) {
          size = programSize[0] << 8 | programSize[1];
        }
      }
      // Load program
      else {
        if (size > MemMax ) {

          // Ignore rest of program
          count++;
          while (count < size) {
            count++;
            char garbo = UART_receive();
          }
          
          run = false;
          VMOut_PutS("Program is too big (max ");
          VMOut_PutI(MemMax);
          VMOut_PutS(" bytes)\n");
          break;
        }
        else {
          *(program + count) = readChar;
          count++;

          if (count == size) {
            break;
          }
        }
      }
    }

    if (run == true) {
      // Run program
      VM_Init(program);
      VM_execute(program);
    }
  }
}
