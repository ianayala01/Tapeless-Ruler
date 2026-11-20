/**************************************************************
* Class:: CSC-615-01 Spring 2026
* Name:: Ian Ayala
* Student ID:: 
* Github-Name:: ianayala01
* Project:: Assignment 2 - Tapeless Ruler
*
* File:: hw2_pigpio.h
*
* Description:: 
*
**************************************************************/

#ifndef HW2_PIGPIO_H
#define HW2_PIGPIO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>

// button pin
extern int button;

// HC-SR04 pins
extern int triggerPin;
extern int echoPin;

// LCD pins
extern int rs;
extern int e;
extern int d4;
extern int d5;
extern int d6;
extern int d7;

void initLCD();
void clearLCD();
void setCursor(int col, int row);
void printLCD(const char *str);
void writeChar(char c);

// sonar variables
extern uint32_t startTick, endTick;
extern int diffTick;
extern float cm;

void setupButton();
void setupSonar();
void setupLCD();

#endif
