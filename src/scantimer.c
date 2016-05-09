#include "scantimer.h"

volatile uint16_t st_row = 0;
volatile bool st_scanned = false;
uint16_t st_data;

void setup_scan_timer()
{
    // setup timer to generate a interrupt 1ms.
    // enable ctc mode 
    // prescaling of 64 so that we can compare against a nice value of 250/2
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS00) | (1 << CS01);
    TIMSK0 = (1 << OCIE0A);
    // pulse width so divide by 2 to get the freq instead of freq/2
    // and also divide by NUMROWS so we get the actuall compare value for
    // scanning a thousand times a second. +- a fiddle to get it closer to 8KHz
    OCR0A = 128 / NUMROWS - 2;
    sei();
}

bool get_scanned()
{
    return st_scanned;
}

void set_scanned(bool val)
{
    st_scanned = val;
}

ISR(TIMER0_COMPA_vect)
{
    // // read pin data
    // st_data = readCol();
    // matrix[st_row] = st_data;

    // // set rows.
    // setRow(st_row);
    // st_row++;
    // if(st_row < NUMROWS)
    // {
    //     st_row++;
    // }
    // else
    // {
    //     st_row = 0;
    //     st_scanned = true;
    // }
    if(!st_scanned)
    {
        setRow(0);
        for(int r = 0; r < NUMROWS; r++)
        {
            matrix[r] = readCol();
            setRow(r);
        }
        st_scanned = true;
    }
}