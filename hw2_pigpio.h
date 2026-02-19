/**************************************************************
* Class:: CSC-615-01 Spring 2026
* Name:: Ian Ayala
* Student ID:: 923102528
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
const int button = 21;

// HC-SR04 pins
const int triggerPin = 4;
const int echoPin = 17;

// LCD pins
const int rs = 27;
const int e = 22;
const int d4 = 23;
const int d5 = 24;
const int d6 = 25;
const int d7 = 26;

// sonar variables
uint32_t startTick, endTick;
int diffTick;
float cm;

void setupButton();
void setupSonar();
void setupLCD();

#endif
