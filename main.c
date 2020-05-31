#include "stm32f4xx.h"                  // Device header

void Led_Init(void);
void SysTick_Init(void);
uint32_t getTick(void);
void delayS(uint32_t seconds);
void Led_On(void);
void Led_Off(void);

volatile uint32_t tick, _tick;

int main(void){
	Led_Init();
	SysTick_Init();
	
	while(1){
		Led_On();
		delayS(1);
		Led_Off();
		delayS(1);
	}
}

void Led_Init(void){
	RCC->AHB1ENR |= 0x01;		//ENABLE CLOCK FOR PORTA FROM BUS AHB1
	GPIOA->MODER |= 0x400;		//OUTPUT MODE PA5
	GPIOA->MODER |= 0X01;
	GPIOA->MODER |= 0X02;
	GPIOA->MODER |= 0X04;
	
}

void SysTick_Init(void){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100u);
	__enable_irq();
}

void SysTick_Handler(void){
	tick++;
}

uint32_t getTick(void){
	__disable_irq();
	_tick =  tick;
	__enable_irq();
	
	return _tick;
}

void delayS(uint32_t seconds){
	seconds *= 100;
	uint32_t temp = getTick();
	while((getTick() - temp) < seconds){}
}

void Led_On(void){
	GPIOA->ODR |= (1<<5);
}

void Led_Off(void){
	GPIOA->ODR &= ~(1<<5);
}
