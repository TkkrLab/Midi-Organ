#define F_CPU 16e6l
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NUMROWS 8
#define NUMCOLS 14
#define NUMKEYS 49
#define START_NOTE 36

typedef struct
{
    uint8_t start_id;
    uint8_t end_id;
    uint64_t start_time;
    uint64_t end_time;
    bool triggerd;
} note_t;

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

void toggle_led()
{
    PORTB ^= (1 << PB7);
}

void setup_pins()
{
    DDRK = 0xFF;

    DDRL = 0x00;
    DDRL |= (1<<6)|(1<<7);
    DDRF = 0x00;
}

void setRow(uint8_t row)
{
    PORTK = (1 << row);
}

uint16_t readCol()
{
    uint16_t data = (PINL << 8) | PINF ;
    return data;
}

volatile uint8_t row = 0;
uint8_t data;
ISR(TIMER0_COMPA_vect)
{
    // read pin data
    data = readCol();
    // set rows.
    setRow(row);
    row++;
    if(row == NUMCOLS)
    {
        row = 0;
    }
}

int main(void)
{
    setup_scan_timer();
    DDRB = (1 << PB7);
    PORTB = 0;
    while(1);
    return 0;
}