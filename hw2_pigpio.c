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

#include "hw2_pigpio.h"


int main(void){
	int init = gpioInitialise();
	printf("initialised: %d\n", init);

	setupSonar();
	setupLCD();

	printf("entering loop, button state = %d\n", gpioread(button));
	while(gpioRead(button) != 1){
		//send pulse
		gpioWrite(triggerPin, 1);
		// wait 10 micro seconds
		time_sleep(.00001);
		//turn trigger pin off
		gpioWrite(triggerPin, 0);

		// start waiting for the echo to read HIGH
		while(gpioRead(echoPin) == 0);
		// get the current system tick
		startTick = gpioTick();

		while(gpioRead(echoPin) == 1);
		endTick = gpioTick();
		diffTick = endTick - startTick;
		distance = (diffTick/2) * .034;
		printf("pulse length was %d\n", diffTick);
		time_sleep(.1);
	}

	gpioTerminate();
}

void setupButton(){
	// set button pin as input
	gpioSetMode(button, 0);
	//using a pulldown resistor
}

// initialize all sonar pins
void setupSonar(){
	printf("setting GPIO %d to output\n", triggerPin);
	gpioSetMode(triggerPin, 1);
	printf("setting GPIO %d to input\n", echoPin);
	gpioSetMode(echoPin, 0);
}

// initialize all lcd pins
void setupLCD(){
	gpioSetMode(rs, 1);
	gpioSetMode(e, 1);
	gpioSetMode(d4, 1);
	gpioSetMode(d5, 1);
	gpioSetMode(d6, 1);
	gpioSetMode(d7, 1);

	gpioWrite(rs, 0);
	gpioWrite(e, 0);
}
