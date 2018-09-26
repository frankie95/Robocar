/*
* robocar_ll.cpp
*
* robocar low level board support drivers
*
* Created: 1/18/2015 11:54:25 AM
* Author: ensylam
*/


#include <avr/io.h>

#include "robocar_ll.h"

void __attribute__((noinline, naked)) delay(void) {
    __asm__("ret"::);
}
//8 clk = 723 ns (11.0592 MHz)

void delayU(unsigned char t) {
    while (t--) {
        delay();
    }
}

char mirror(char c) {			// abcdefgh -> hgfedcba
    __asm__ __volatile__(\
                         "mov __tmp_reg__, %0" "\n\t"\
                         "ldi %0, 0xfe" "\n\t"\
                         "1: lsr __tmp_reg__" "\n\t"\
                         "rol %0" "\n\t"\
                         "brcs 1b" "\n\t"\
                         :"=a" (c)\
                         :"0" (c)\
                        );
    return c;
}

#define LCDSTROBE() PORTA |= _BV(7); delay(); PORTA &= ~_BV(7)
#define BREAD		0x0F
#define BWRITE		0xFF
#define BUS(X)		DDRC = X
#define BUSREAD(X)	X = PINC
#define BUSWRITE(X)	PORTC = X
#define BGATEH()	PORTB |= _BV(2)
#define BGATEL()	PORTB &= ~_BV(2)

#define SPICLKH()	UCSR1C |= _BV(0)
#define SPICLKL()	UCSR1C &= ~_BV(0)

#define POWERUP() PORTA |= _BV(1)
#define POWEROFF() PORTA &= ~_BV(1)

#define LEDON() PORTA |= _BV(2)
#define LEDOFF() PORTA &= ~_BV(2)


void __attribute__((section(".init3"), naked)) __hardwareInit(void) {
    DDRA |= _BV(1);		// POWER
    DDRA |= _BV(2);		// LED
    DDRA |= _BV(7);		// LCD strobe
    DDRB |= _BV(2);		// HC138 GATE

    //SPI init (USART1 in MSPIM)
    DDRD |= _BV(3);			// TXD1 output
    DDRD |= _BV(4);			// XCLK1 output
    UBRR1 = 0;
    UCSR1C = 0b11000011;	// MSPIM, MSB first, idle high (write)
    UCSR1B = 0x18;			// enable transmitter and receiver
    UBRR1 = 0;				// set clock to fosc/2

    LL::write574(LL::U4, 0);
    LL::write574(LL::U5, 0);
}

void __attribute__((section(".init8"), naked)) __power(void) {
    POWERUP();
}


namespace {

    char u4, u5;

    char SPI(char c) {
        while (!(UCSR1A & _BV(UDRE1)));		// wait for empty transmit buffer
        UDR1 = c;
        while (!(UCSR1A & _BV(RXC1)));		// wait for data to be received
        return UDR1;							// dummy read
    }

} //namespace


namespace LL {

    void lcdWriteNibble(unsigned char n, unsigned char c) {
        // require lower nibble of n = 0
        BGATEL();
        BUS(BWRITE);
        BUSWRITE(n | c << 2);
        LCDSTROBE();
    }

    void lcdWriteByte(unsigned char b, unsigned char c) {
        lcdWriteNibble(b & 0xf0, c);		// high nibble first
        lcdWriteNibble(b << 4, c);
    }

    char lcdReadByte(unsigned char c) {
        unsigned char lownibble;
        BGATEL();
        BUS(BREAD);
        BUSWRITE((c | 2) << 2);
        LCDSTROBE();
        BUSREAD(c);
        c &= 0xf0;	// high nibble first
        LCDSTROBE();
        BUSREAD(lownibble);
        return c | lownibble >> 4;
    }

    char read541(HC541 address, unsigned char t) {
        SPICLKL();
        BGATEL();
        BUS(BWRITE);
        BUSWRITE(address);
        BGATEH();
        delayU(t);
        SPICLKH();
        BGATEL();
        PORTC &= 0xf3;
        return SPI(0);
    }

    void write574(HC574 address, char c) {
        BGATEL();
        BUS(BWRITE);
        BUSWRITE(address);
        BGATEH();
        SPI(c);
        BGATEL();
    }

    void servoSetAddress(char c) {
        u4 = (u4 & 0x1F) | mirror(c & 7);
        write574(U4, u4);
    }

    void backMotorControl(char c) {
        u5 = (u5 & 0x78) | (c & 0x87);
        write574(U5, u5);
    }

    void power(char c) {
        if (c) POWERUP();
        else POWEROFF();
    }

    void LED(char c) {
        if (c) LEDON();
        else LEDOFF();
    }

} //namespace LL
