/**************************************************************
* Class:: CSC-615-01 Spring 2026
* Name:: Ian Ayala
* Student ID:: 923102528
* Github-Name:: ianayala01
* Project:: Assignment 2 - Tapeless Ruler
*
* File:: lcd.h
*
* Description:: declare functions for manipulating the lcd
*
**************************************************************/

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void initLCD();
void clearLCD();
void setCursor(int col, int row);
void printLCD(const char *str);
void writeChar(char c);

#endif
