#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <stdint.h>
#include <avr/io.h>

#include <keyboard.h>

void setup_scanner();
void setRow(uint8_t);
uint16_t readCol();

#endif