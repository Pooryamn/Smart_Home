/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 1/5/2020
Author  :
Company :
Comments:


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <delay.h>

// Declare your global variables here
char order;
char ch_color;
char ch_mode;

void get_mode(char mode);
void set_color(char color);

#define R PORTD.2
#define G PORTD.3
#define B PORTD.4

#define L1 PORTA.0
#define L2 PORTA.1
#define L3 PORTA.2
#define L4 PORTA.3
#define L5 PORTA.4
#define L6 PORTA.5
#define L7 PORTA.6
#define L8 PORTA.7

#define L9 PORTB.0
#define L10 PORTB.1
#define L11 PORTB.2
#define L12 PORTB.3
#define L13 PORTB.4
#define L14 PORTB.5
#define L15 PORTB.6
#define L16 PORTB.7

#define L17 PORTC.0
#define L18 PORTC.1
#define L19 PORTC.2
#define L20 PORTC.3
#define L21 PORTC.4
#define L22 PORTC.5
#define L23 PORTC.6
#define L24 PORTC.7

// Standard Input/Output functions
#include <stdio.h>

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=In Bit0=In
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=T Bit0=T
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: Off
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (0<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;

// Analog Comparator initialization
// Analog Comparator: Off
// The Analog Comparator's positive input is
// connected to the AIN0 pin
// The Analog Comparator's negative input is
// connected to the AIN1 pin
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
SFIOR=(0<<ACME);

// ADC initialization
// ADC disabled
ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

// SPI initialization
// SPI disabled
SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

// TWI initialization
// TWI disabled
TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

while (1)
    {

    order = getchar();

    ch_color = order & 0x0F;
    ch_mode = order & 0xF0;


    get_mode(ch_mode);
    set_color(ch_color);



    }
}


void set_color(char color){
    int i;

    if( color == 0x00){
        R = 0;
        G = 0;
        B = 0;
    }
    else if(color == 0x01){
        R = 0;
        G = 0;
        B = 1;
    }
    else if(color == 0x02){
        R = 0;
        G = 1;
        B = 0;
    }
    else if(color == 0x03){
        R = 0;
        G = 1;
        B = 1;
    }
    else if(color == 0x04){
        R = 1;
        G = 0;
        B = 0;
    }
    else if(color == 0x05){
        R = 1;
        G = 0;
        B = 1;
    }
    else if(color == 0x06){
        R = 1;
        G = 1;
        B = 0;
    }
    else if(color == 0x07){
        for(i=0;i<30;i++){
            R = 0;
            G = 0;
            B = 0;
            delay_ms(1000);


            R = 0;
            G = 0;
            B = 1;
            delay_ms(1000);


            R = 0;
            G = 1;
            B = 0;
            delay_ms(1000);


            R = 0;
            G = 1;
            B = 1;
            delay_ms(1000);


            R = 1;
            G = 0;
            B = 0;
            delay_ms(1000);


            R = 1;
            G = 0;
            B = 1;
            delay_ms(1000);


            R = 1;
            G = 1;
            B = 0;
            delay_ms(1000);
        }
    }
}

void get_mode(char mode){

    int i;

    if(mode == 0x00){
        // off
        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;
    }
    else if(mode == 0x10){
        // party 1
        for(i=0;i<20;i++){
        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;

        delay_ms(150);

        PORTA = 0xFF;
        PORTB = 0xFF;
        PORTC = 0xFF;

        delay_ms(150);
        }

    }
    else if(mode == 0x20){
        // party 2
        for(i=0;i<20;i++){
            PORTA = 0x95;
            PORTB = 0x5A;
            PORTC = 0xA9;

            delay_ms(150);

            PORTA = 0x6A;
            PORTB = 0xA5;
            PORTC = 0xD6;

            delay_ms(150);
        }
    }
    else if(mode == 0x30){
        // party 3
        for(i=0;i<20;i++){

            PORTA = 0x3F;
            PORTB = 0x00;
            PORTC = 0xFC;

            delay_ms(150);

            PORTA = 0xC0;
            PORTB = 0xFF;
            PORTC = 0x03;

            delay_ms(150);
        }
    }
    else if(mode == 0x40){
        //party 4
        for(i=0;i<256;i++){
            PORTA = i;
            PORTB = i;
            PORTC = i;

            delay_ms(50);
        }
    }
    else if(mode == 0x50){
        // Luminous
        PORTA = 0xFF;
        PORTB = 0xFF;
        PORTC = 0xFF;
    }
    else if(mode == 0x60){
        // dim
        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;

        delay_ms(10);

        L8 = 1;
        L11 = 1;
        L14 = 1;
        L17 = 1;
    }
    else if(mode == 0x70){
        // normal
        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;

        delay_ms(10);

        L8 = 1;
        L9 = 1;
        L10 = 1;
        L11 = 1;
        L14 = 1;
        L15 = 1;
        L16 = 1;
        L17 = 1;

    }
    else if(mode == 0x80){
        // star

        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;

        delay_ms(10);

        L2 = 1;
        L9 = 1;
        L16 = 1;
        L23 = 1;
        L20 = 1;
        L15 = 1;
        L10 = 1;
        L5 = 1;
    }
    else if(mode == 0x90){
        // half
        PORTA = 0x00;
        PORTB = 0x00;
        PORTC = 0x00;

        delay_ms(10);

        PORTA = 0x95;
        PORTB = 0x5A;
        PORTC = 0xA9;
    }
}