#include "TM4C123.h"                    // Device header

#define RED (1<<1)
#define BLUE (1<<2)
#define GREEN (1<<3)

void Timer1_OneShot(int mdelay);

int main(void){
	
	SYSCTL->RCGCGPIO |= (1<<5);
	GPIOF->DIR |= RED | BLUE | GREEN;
	GPIOF->DEN |= RED | BLUE | GREEN;
	
	while(1){
		GPIOF->DATA ^= RED;
		Timer1_OneShot(4);
	}
}



void Timer1_OneShot(int mdelay){

	SYSCTL->RCGCTIMER |= 0x01; // CLOCK FOR TIMER 0
	TIMER0->CTL = 0x00;
	TIMER0->CFG = 0X04; //16 bit mode
	TIMER0->TAMR = 0x01; //one shot mode
	TIMER0->TAILR |= 1600 *mdelay-1;
	TIMER0->ICR = 0x1;
	TIMER0->CTL |= 0x01;
	while((TIMER0->RIS & 0x01) == 0){}
}

