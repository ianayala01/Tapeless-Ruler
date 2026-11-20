/**************************************************************
* Class:: CSC-615-01 Spring 2026
* Name:: Ian Ayala
* Student ID::
* Github-Name:: ianayala01
* Project:: Assignment 2 - Tapeless Ruler
*
* File:: lcd.c
*
* Description:: This file implements pigpio versions of the 
*	LiquidCrystal.cpp files like the ones that can be found
*	in the official arduino library.
*
*	https://github.com/arduino-libraries/LiquidCrystal/blob/master/src/LiquidCrystal.cpp
*
**************************************************************/

#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include "hw2_pigpio.h"

// similar to LiquidCrystal::pulseEnable()
static void pulseEnable(){

	// ensure the pin starts low
	gpioWrite(e, 0);
	gpioDelay(1);

	// pulsing the enable pin signals the LCD that data is ready
	gpioWrite(e, 1);
	gpioDelay(1);

	gpioWrite(e, 0);
	// this is a pretty safe wait time
	gpioDelay(100);
}

// my lcd is in 4 bit mode using data pins 4-7
// modified version of LiquidCrystal::write4bits()

static void writeNibble(uint8_t nibble){

	// bit 0 to d4
	gpioWrite(d4, (nibble >> 0) & 1);
	// bit 1 to d5
	gpioWrite(d5, (nibble >> 1) & 1);
	// bit 2 to d6
	gpioWrite(d6, (nibble >> 2) & 1);
	// bit 3 to d7
	gpioWrite(d7, (nibble >> 3) & 1);

	// tell LCD to read the data set above^
	pulseEnable();
}

static void writeByte(uint8_t byte, int reg){
	// rs = 0 -> command
	// rs = 1 -> data
	gpioWrite(rs, reg);

	// since lcd is in 4 bit mode and a char is 1 byte,
	// split it into two nibbles and write them to data pins
	writeNibble(byte >> 4);
	writeNibble(byte & 0x0F);
}

void initLCD(){

	// LCD initializes into 8-bit mode when powered on
	writeNibble(0x03);
	gpioDelay(5000);
	writeNibble(0x03);
	gpioDelay(150);
	writeNibble(0x03);


	// now set 4-bit
	writeNibble(0x02);

	// 4-bits, 2 lines, 5x8 font
	writeByte(0x28, 0);
	//display on, cursor off, blink off
	writeByte(0x0C, 0);
	// increment cursor after each char
	writeByte(0x06, 0);
	clearLCD();
}

void clearLCD(void){
	// clear display instruction
	writeByte(0x01, 0);
	gpioDelay(2000);
}

void setCursor(int col, int row){
	// first row starts at 0x00
	// second row starts at 0x40
	int rowOffsets[] = {0x00, 0x40};
	// make sure not to exceed max row somehow
	if (row > 1) row = 1;
	// 0x80 = set DDRAM Address instruction code
	writeByte(0x80 | (col + rowOffsets[row]), 0);
}

void writeChar(char c){
	// for each character in the string write that byte
	writeByte((uint8_t)c, 1);
}

void printLCD(const char *str){
	//iterate through a string
	while(*str){
		writeChar(*str++);
	}
}
