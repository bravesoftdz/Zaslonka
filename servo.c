/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Evaluation
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 27.10.2015
Author  : Mykola Fedan
Company :  kolja153.com
Comments: 


Chip type               : ATtiny13
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 16

PORTB.0 - up
PORTB.1 - down       
PORTB.2 - Led
PORTB.3  - Motor pot    ADC2
PORTB.4  - Reguljstor   pot   ADC3
*****************************************************/

#include <tiny13.h>

#include <delay.h>

#define ADC_VREF_TYPE 0x00

#define min 20
#define max 1000

#define led   PORTB.2

#define up   PORTB.0
#define down  PORTB.1

#define motor   2
#define reguljator 3


void GoUp()
{
    up=1;
    down=0;      
    led=0;
    
}

void GoDown()
{
    up=0;
    down=1;         
     led=0;
   
}

void Stop()
{
    up=0;
    down=0;     
    led=1;
  
}

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func5=In Func4=In Func3=In Func2=Out Func1=Out Func0=Out 
// State5=P State4=P State3=P State2=0 State1=0 State0=0 
PORTB=0x38;
DDRB=0x07;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// Interrupt on any change on pins PCINT0-5: Off
GIMSK=0x00;
MCUCR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
ACSR=0x80;
ADCSRB=0x00;
DIDR0=0x00;

// ADC initialization
// ADC Clock frequency: 1000,000 kHz
// ADC Bandgap Voltage Reference: Off
// ADC Auto Trigger Source: ADC Stopped
// Digital input buffers on ADC0: Off, ADC1: Off, ADC2: On, ADC3: On
DIDR0&=0x03;
DIDR0|=0x24;
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x83;

 led=0;
delay_ms(1000);
  led=1;

while (1)
      {        
      
        if (read_adc(motor)<=read_adc(reguljator)+10 &&    read_adc(motor)>=read_adc(reguljator)-10   )
        
             {
         Stop();
        } 
         else
                {
      
     while(read_adc(reguljator)<read_adc(motor) && read_adc(motor)>min )
      {
     GoDown();
      }          
           
       while(read_adc(reguljator)>read_adc(motor) && read_adc(motor)<max)
      {
     GoUp();
      } 
       if  (read_adc(reguljator)==read_adc(motor))
      {
    Stop();
      } ;
        
      }
      
      }    
}
