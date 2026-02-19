/**************************************************************
* Class:: CSC-615-01 Spring 2026
* Name:: Ian Ayala
* Student ID:: 923102528
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
#include "lcd.h"
#include "hw2_pigpio.h"

// similar to LiquidCrystal::pulseEnable()
static void pulseEnable(){
	gpioWrite(e, 0);
	gpioDelay(1);
	gpioWrite(e, 1);
	gpioDelay(1);
	gpioWrite(e, 0);
	gpioDelay(100);
}

// my lcd is in 4 bit mode using data pins 4-7
// modified version of LiquidCrystal::write4bits()

static void writeNibble(uint8_t nibble){
	gpioWrite(d4, (nibble >> 0) & 1);
	gpioWrite(d5, (nibble >> 1) & 1);
	gpioWrite(d6, (nibble >> 2) & 1);
	gpioWrite(d7, (nibble >> 3) & 1);

	pulseEnable();
}

static void writeByte(uint8_t byte, int register){
	gpioWrite(rs, register);	//rs 0 = command, rs 1 = data
	writeNibble(byte >> 4);
	writeNibble(byte & 0x0F);
}

void initLCD(){
	writeNibble(0x03);
	gpioDelay(5000);
	writeNibble(0x03);
	gpioDelay(150);
	writeNibble(0x03);
	writeNibble(0x02);

	// 4-bits, 2 lines, 5x8 font
	writeByte(0x28, 0);
	writeByte(0x0C, 0);
	writeByte(0x06, 0);
	clearLCD();
}

void clearLCD(void){
	writeByte(0x01, 0);
	gpioDelay(2000);
}

void setCursor(int col, int row){
	int rowOffsets[] = {0x00, 0x40};
	if (row > 1) row = 1;
	writeByte(0x80 | col + rowOffsets[row]), 0);
}

void writeChar(char c){
	writeByte((uint8_t)c, 1);
}

void printLCD(const char *str){
	while(*str){
		writeChar(*str++);
	}
}
