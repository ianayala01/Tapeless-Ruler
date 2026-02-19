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

	setupButton();
	setupSonar();
	setupLCD();

	//set cursor to first column and row on lcd then print
	setCursor(0,0);
	printLCD("Distance:");

	// buffered i/o for writing to lcd
	char buf[17];

	// execute this loop until the kill switch is pressed
	while(gpioRead(button) != 1){

		// set cursor to seond row
		setCursor(0,1);
		// clear
		memset(buf, ' ', 16);
		// null terminate c string
		buf[16] = '\0';

		//send pulse
		gpioWrite(triggerPin, 1);
		// wait 10 micro seconds
		gpioDelay(10);
		//turn trigger pin off
		gpioWrite(triggerPin, 0);

		// start waiting for the echo to read HIGH
		while(gpioRead(echoPin) == 0);
		// get the current system tick
		startTick = gpioTick();

		// wait for echo to read low
		while(gpioRead(echoPin) == 1);
		// get tick for the end of the puls
		endTick = gpioTick();
		// find delta t
		diffTick = endTick - startTick;
		// distance in cm
		cm = (diffTick/2) * .0343;
		// also convert to freedom units
		float inch = cm / 2.54;

		snprintf(buf, 17, "%.2f cm %.1f in", cm, inch);
		printLCD(buf);

		// my tape measure is in inches so printing both
		printf("distance: %.3f cm, %.3f in.\n", cm, inch);
		gpioDelay(100000);
	}

	// if the button is pressed, terminate the process safely
	printf("kill switch pressed, terminating...\n");
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

	gpioDelay(50000);

	initLCD();
}
