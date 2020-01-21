/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 1/15/2020
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

//===============
//   Headers :
//===============

#include <mega32.h>     // Chip type
#include <string.h>     // Strcmp
#include <delay.h>      // delay_ms , delay_us
#include <glcd.h>       // Graphical lcd (240 * 128)
#include <font5x7.h>    // Graphical lcd Default font
#include <stdio.h>      // Standard C functions (sprintf)
#include "title.c"       // Logo image (made by Lcd Vision


//===================
// PORTS Defenition :
//===================

//KEYPAD OUTSPUTS :
#define KEY0 PORTC.5
#define KEY1 PORTC.6
#define KEY2 PORTC.7
#define KEY3 PORTD.0

//KEYPAD INPUTS :
#define KEY4 PIND.2
#define KEY5 PIND.3
#define KEY6 PIND.4
#define KEY7 PIND.5

#define M1 PORTD.6
#define M2 PORTD.7



//===================
// Global variables :
//===================
int temp[4];
float avg_temp;
char str[128];
char str_temp[3];
char str_req[3];
int main_selector = 0; // 0 : Nothing , 1 : temp , 2 : light
int Key_ret;
int current_menu = 0; // 0 : main , 1 : Temp , 2 : light
bool first_run_function = true; // false : if more than 1 time ran a funtion
int Req_temp = 20; // required temp by user
char order = 0b00000000;



//===================
// Functions :
//===================
void show_logo();   // show my logo on glcd
void read_temps();  // Read lm35 temps (use read_adc)
void show_menu(int selector);   // Show main menu
void clacute_average_temp(); // clacute average temp using read_temps()
int Keypad();       // Check all the keys on keypad and return a special number for each key
void check_key_main(); // check keypad inputs in main menu
void Temp_menu();   // temp menu functions
void Show_temp_menu();  // show temp menu
void Temp_controller(); // control motor for Setting temperature
void Light_menu();  // Light menu
void show_light_menu(); // display light menu
void set_type(int mode); // set type to order char
void show_color_menu(); // to select color
void color_menu();
void set_color(int color); //  set color to order char



#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)

// USART Transmitter buffer
#define TX_BUFFER_SIZE 8
char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE <= 256
unsigned char tx_wr_index=0,tx_rd_index=0;
#else
unsigned int tx_wr_index=0,tx_rd_index=0;
#endif

#if TX_BUFFER_SIZE < 256
unsigned char tx_counter=0;
#else
unsigned int tx_counter=0;
#endif

// USART Transmitter interrupt service routine
interrupt [USART_TXC] void usart_tx_isr(void)
{
if (tx_counter)
   {
   --tx_counter;
   UDR=tx_buffer[tx_rd_index++];
#if TX_BUFFER_SIZE != 256
   if (tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
#endif
   }
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
while (tx_counter == TX_BUFFER_SIZE);
#asm("cli")
if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer[tx_wr_index++]=c;
#if TX_BUFFER_SIZE != 256
   if (tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
#endif
   ++tx_counter;
   }
else
   UDR=c;
#asm("sei")
}
#pragma used-
#endif

// Standard Input/Output functions
#include <stdio.h>

// Voltage Reference: Int., cap. on AREF
#define ADC_VREF_TYPE ((1<<REFS1) | (1<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void)
{
// local variables :

// GLCD Setting and variables :
GLCDINIT_t glcd_init_data;

// Input/Output Ports initialization :
// Port A initialization
// Function: Bit7=Out Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);

// State: Bit7=0 Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);

// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);

// State: Bit7=0 Bit6=0 Bit5=0 Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T
PORTC=(1<<PORTC7) | (1<<PORTC6) | (1<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=Out
DDRD=(1<<DDD7) | (1<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (1<<DDD0);

// State: Bit7=0 Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=0
PORTD=(0<<PORTD7) | (0<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (0<<PORTD1) | (1<<PORTD0);

// Timmer and counter 0 is OFF :
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timmer and counter 1 is OFF :
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

// Timmer and counter 2 is OFF :
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2=0x00;
OCR2=0x00;

// Timers and Counters Interrupts are OFF :
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupts are OFF :
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// This chip is transmitter :

UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;

// ADC settings :
ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);

// Graphic lcd Controllers :
glcd_init_data.font=font5x7;
glcd_init_data.readxmem=NULL;
glcd_init_data.writexmem=NULL;
glcd_init(&glcd_init_data);
delay_ms(20);

// Begin of main process :

    show_logo(); // show my logo on lcd

    while (1)
    {
        if(current_menu == 0){  // main menu
            clacute_average_temp();

            //Temp_controller();

            show_menu(main_selector);

            check_key_main();
        }
        else if(current_menu == 1){ // Temp menu
             Temp_menu();
        }
        else if(current_menu == 2){ // light menu
             Light_menu();
        }


    }
}



void show_logo(){

    glcd_clear(); // clear lcd

    glcd_putimagef(0,0, title,GLCD_PUTCOPY); // show logo on lcd

    delay_ms(3000); // wait for 3 secends

    glcd_clear(); // clear lcd

}

void read_temps(){

    temp[0] = read_adc(0);
    temp[0] = temp[0] / 4;

    temp[1] = read_adc(1);
    temp[1] = temp[1] / 4;

    temp[2] = read_adc(2);
    temp[2] = temp[2] / 4;

    temp[3] = read_adc(3);
    temp[3] = temp[3] / 4;
}

void show_menu(int selector){

    if(first_run_function == true){
        glcd_clear();
        first_run_function = false;
    }

    glcd_outtextxy(60,20,".:: MAIN MENU ::.");

    glcd_rectround(25,15,185,40,5);

    sprintf(str,"Average temperature : %2.1f ^c",avg_temp);

    glcd_outtextxy(30,40,str);

    if(selector == 0){
        glcd_outtextxy(30,70,"  ");
        glcd_outtextxy(30,90,"  ");
        glcd_outtextxy(45,70,"TEMPERATURE Settings");
        glcd_outtextxy(47,90,"LIGHT Settings");
    }
    else if(selector == 1){

        glcd_outtextxy(30,70,"=>");
        glcd_outtextxy(30,90,"  ");
        glcd_outtextxy(45,70,"TEMPERATURE Settings");
        glcd_outtextxy(47,90,"LIGHT Settings");

    }
    else if(selector == 2){

        glcd_outtextxy(30,70,"  ");
        glcd_outtextxy(30,90,"=>");
        glcd_outtextxy(45,70,"TEMPERATURE Settings");
        glcd_outtextxy(47,90,"LIGHT Settings");

    }
}

void clacute_average_temp(){
    read_temps();

    avg_temp = (temp[0] + temp[1] + temp[2] + temp[3]) / 4.0 ;
}

int Keypad(){
    // Row 1 is Active :
    KEY0 = 0;
    KEY1 = 1;
    KEY2 = 1;
    KEY3 = 1;

    if(KEY4 == 0){
        // 7 pressed
        while(KEY4 == 0);
        return 7;
    }

    if(KEY5 == 0){
        // 8 pressed
        while(KEY5 == 0);
        return 8;
    }

    if(KEY6 == 0){
        // 9 pressed
        while(KEY6 == 0);
        return 9;
    }

    if(KEY7 == 0){
        // UP pressed
        while(KEY7 == 0);
        return 10;
    }

    KEY0 = 1;

    delay_ms(5);

    // Row 2 is Active :
    KEY1 = 0;

    if(KEY4 == 0){
        // 4 pressed
        while(KEY4 == 0);
        return 4;
    }

    if(KEY5 == 0){
        // 5 pressed
        while(KEY5 == 0);
        return 5;
    }

    if(KEY6 == 0){
        // 6 pressed
        while(KEY6 == 0);
        return 6;
    }

    if(KEY7 == 0){
        // OK pressed
        while(KEY7 == 0);
        return 11;
    }

    KEY1 = 1;

    delay_ms(5);

    // row3 is Active :
    KEY2 = 0;

    if(KEY4 == 0){
        // 1 pressed
        while(KEY4 == 0);
        return 1;
    }

    if(KEY5 == 0){
        // 2 pressed
        while(KEY5 == 0);
        return 2;
    }

    if(KEY6 == 0){
        // 3 pressed
        while(KEY6 == 0);
        return 3;
    }

    if(KEY7 == 0){
        // DOWN pressed
        while(KEY7 == 0);
        return 12;
    }

    KEY2 = 1;

    delay_ms(5);

    // row 4 is Active :
    KEY3 = 0;

    if(KEY4 == 0){
        // Clear pressed
        while(KEY4 == 0);
        return 13;
    }

    if(KEY5 == 0){
        // 0 pressed
        while(KEY5 == 0);
        return 0;
    }

    KEY3 = 1;

    delay_ms(5);

    return -1;
}

void check_key_main(){

    Key_ret = Keypad();

    if(Key_ret == 10){  // UP Pressed
        main_selector = 1;
    }
    else if(Key_ret == 12){ // DOWN Pressed
        main_selector = 2;
    }
    else if(Key_ret == 13){ //Clear Pressed
        main_selector = 0;
    }
    else if(Key_ret == 11){ //OK Pressed
        if(main_selector == 1){  // Go to temp menu
            current_menu = 1;
            first_run_function = true;
        }
        if(main_selector == 2){ // go to light menu
            current_menu = 2;
            first_run_function = true;
        }
    }
}

void Temp_menu(){

    int i;
    int input_number = 0;
    Key_ret = -1;


    Show_temp_menu();

    for(i=0;i<2;i++){

        while(Key_ret == -1){
            Key_ret = Keypad();
        }

        if(Key_ret == 13){
            break;
        }
        else if(Key_ret == 11){
            if(input_number != 0){
                Req_temp = input_number;
            }
        }
        else if(Key_ret == 12 || Key_ret == 10){
            i--;
            continue;
        }
        else{
            input_number = input_number * 10 + Key_ret;
            sprintf(str,"%d",input_number);
            glcd_outtextxy(110,70,str);

            if(input_number != 0){
                Req_temp = input_number;
            }

        }
        Key_ret = -1;
    }

    current_menu = 0;
    first_run_function = true;
    return;

}
void Show_temp_menu(){
    if(first_run_function == true){
        glcd_clear();
        first_run_function = false;
    }

    glcd_outtextxy(45,20,".:: TEMPERATURE MENU ::.");

    glcd_rectround(25,15,185,20,5);

    glcd_outtextxy(20,50,".:: Your Required Temperature ::.");

    glcd_rectangle(105,65,125,85);

    //sprintf(str,"%d",Req_temp);

    //glcd_outtextxy(110,70,str);



}


void Temp_controller(){
    sprintf(str_temp,"%2d",avg_temp);
    sprintf(str_req,"%2d",Req_temp);

    if(strcmp(str_req,str_temp)==0){
        M1 = 0;
        M2 = 0;
    }
    else{
        M1 = 1;
        M2 = 0;
    }

}

void Light_menu(){

    int current_mode =0; // off
    int x = 25;
    int y = 65;
    show_light_menu();
    glcd_outtextxy(x,y,"=>");

    do{
        Key_ret = Keypad();

        if( Key_ret == 12){

            if(current_mode == 9){
                continue;
            }

            glcd_outtextxy(x,y,"  ");

            current_mode++;
            y += 10;

            if(y > 105){
                y = 65;

                if ( x == 25){
                    x = 115;
                }
                else{
                    x = 25;
                }
            }

            glcd_outtextxy(x,y,"=>");

        }
        else if( Key_ret == 10){
            if(current_mode == 0){
                continue;
            }

            glcd_outtextxy(x,y,"  ");

            current_mode--;

            y -= 10;

            if(y < 65){
                y = 65;

                if(x == 25){
                    x = 115;
                }
                else {
                    x = 25;
                }
            }

            glcd_outtextxy(x,y,"=>");
        }
        else if(Key_ret == 13){
            current_menu = 0;
            first_run_function = true;
            return;
        }
        else  if(Key_ret == 11){
            set_type(current_mode);
            glcd_clear();
            color_menu();
            return;
        }

    }while(Key_ret != 13 || Key_ret!=11);
}

void show_light_menu(){

    if(first_run_function == true){
        glcd_clear();
        first_run_function = false;
    }

    glcd_outtextxy(65,20,".:: LIGHT MENU ::.");

    glcd_rectround(25,15,185,20,5);

    glcd_outtextxy(20,50,".:: Select Your mode :");

    glcd_outtextxy(40,65,"OFF");
    glcd_outtextxy(40,75,"Party 1");
    glcd_outtextxy(40,85,"Party 2");
    glcd_outtextxy(40,95,"Party 3");
    glcd_outtextxy(40,105,"Party 4 ");

    glcd_outtextxy(130,65,"Luminous");
    glcd_outtextxy(130,75,"Dim");
    glcd_outtextxy(130,85,"Normal");
    glcd_outtextxy(130,95,"Star");
    glcd_outtextxy(130,105,"Half");
}

void set_type(int mode){
    order &= 0x00;
    switch (mode) {
        case 0 :
            order |= 0x00;
            break;
        case 1 :
            order |= 0x10;
            break;
        case 2 :
            order |= 0x20;
            break;
        case 3 :
            order |= 0x30;
            break;
        case 4 :
            order |= 0x40;
            break;
        case 5 :
            order |= 0x50;
            break;
        case 6 :
            order |= 0x60;
            break;
        case 7 :
            order |= 0x70;
            break;
        case 8 :
            order |= 0x80;
            break;
        case 9 :
            order |= 0x90;
            break;
    };

}

void color_menu(){
    int current_color = 0;
    int x = 25;
    int y = 65;
    show_color_menu();
    glcd_outtextxy(x,y,"=>");

    do{
        Key_ret = Keypad();

        if(Key_ret == 12){

            if(current_color == 7){
                continue;
            }

            glcd_outtextxy(x,y,"  ");

            current_color++;
            y += 10;

            if(y > 95){
                y = 65;

                if ( x == 25){
                    x = 115;
                }
                else{
                    x = 25;
                }
            }

            glcd_outtextxy(x,y,"=>");

        }
        else if(Key_ret == 10){

            if(current_color == 0){
                continue;
            }

            glcd_outtextxy(x,y,"  ");

            current_color--;

            y -= 10;

            if(y < 65){
                y = 65;

                if(x == 25){
                    x = 115;
                }
                else {
                    x = 25;
                }
            }

            glcd_outtextxy(x,y,"=>");
        }
        else if(Key_ret == 13){
            current_menu = 0;
            first_run_function = true;
            return;
        }
        else if(Key_ret == 11){

            set_color(current_color);

            putchar(order);

            current_menu = 0;
            first_run_function = true;
            return;
        }

    }while(Key_ret != 13 || Key_ret != 11);

}

void show_color_menu(){

    glcd_outtextxy(65,20,".:: LIGHT MENU ::.");

    glcd_rectround(25,15,185,20,5);

    glcd_outtextxy(20,50,".:: Select Your Color :");

    glcd_outtextxy(40,65,"Purple");
    glcd_outtextxy(40,75,"Orange");
    glcd_outtextxy(40,85,"Pink");
    glcd_outtextxy(40,95,"Red");

    glcd_outtextxy(130,65,"Light Blue");
    glcd_outtextxy(130,75,"Green");
    glcd_outtextxy(130,85,"Dark Blue");
    glcd_outtextxy(130,95,"Color Full");
}

void set_color(int color){

    order &= 0xF0;

    switch (color) {
        case 0:
            order |=0x00;
            break;
        case 1:
            order |=0x01;
            break;
        case 2:
            order |=0x02;
            break;
        case 3:
            order |=0x03;
            break;
        case 4:
            order |=0x04;
            break;
        case 5:
            order |=0x05;
            break;
        case 6:
            order |=0x06;
            break;
        case 7:
            order |=0x07;
            break;
    };
}