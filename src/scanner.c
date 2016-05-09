#include "scanner.h"

void setup_scanner()
{
    DDRK = 0xFF;

    DDRL = 0x00;
    DDRL |= (1<<6)|(1<<7);
    DDRF = 0x00;
}

void setRow(uint8_t row)
{
    if(row >= NUMROWS)
    {
        return;
    }
    PORTK = (1 << row);
}

uint16_t readCol()
{
    uint16_t data = (PINL << 8) | PINF ;
    return data;
}