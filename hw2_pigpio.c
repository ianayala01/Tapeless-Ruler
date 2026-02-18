/**************************************************************
* Class:: CSC-615-01 Spring 2026
* Name:: Ian Ayala
* Student ID:: 923102528
* Github-Name:: ianayala01
* Project:: Assignment 2 - Tapeless Ruler
*
* File:: hw2_pigpio.c
*
* Description:: 
*
**************************************************************/

#include <hw2_pigpio.h>


int main(void){
	int init = gpioInitialise();
	printf("initialised: %d\n", init);
}

void setupSonar(){
	gpioSetMode(triggerPin, 1);
	gpioSetMode(echoPin, 0);
}

void setupLCD(){
	gpioSetMode(
}
