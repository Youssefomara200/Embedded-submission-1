#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "uart.h"

void init();
int main(void){
  init();
  Serial.begin(9600);

  while (1)
  {
  
    unsigned short reading = Adc_ReadChannel(3);

    if (reading > 1000){
        PORTD = PORTD | (1 << 7);
        PORTB = PORTB | (1 << 0);
        // send warning through uart
       
    }else if( reading > 500){
        PORTD = PORTD & ~(1 << 7);
        PORTB = PORTB | (1 << 0);
    }else{
        PORTD = PORTD & ~(1 << 7);
        PORTB = PORTB & ~(1 << 0);
    }

    
    int switchA = PIND & (1 << 6);
    Serial.println(switchA);
     if(switchA)  
    {
      PORTB = PORTB & ~(1 << 4);    // Switch OFF lED
    }  
    else 
    {
      PORTB = PORTB | (1 << 4);      // Switch ON lED
    }
  }
  return 0; 
}

void init(){

  adc_Init();
// uart init
  DDRC = 0X00;  //
  
  DDRD = DDRD | (1<< 7);
  DDRB = DDRB | (1 << 0);

  PORTD = PORTD & ~(1 << 7);

  DDRB = DDRB | (1 << 4);

  DDRD = DDRD & ! (1 << 6);  //
  PORTD = PORTD | (1 << 6);


}