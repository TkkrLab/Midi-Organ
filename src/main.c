#define F_CPU 16000000UL
#define BAUD 115200
#define BAUD_PRESCALER ((F_CPU / (8UL * BAUD)) - 1)

#include <util/delay.h>
#include <stdint.h>

#include <utils.h>
#include <keyboard.h>
#include <scanner.h>
#include <scantimer.h>

void uart_init()
{
    UBRR0H = BAUD_PRESCALER >> 8;
    UBRR0L = BAUD_PRESCALER & 0xFF;
    UCSR0A = (1 << U2X0);
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

void uart_write(unsigned char c)
{
    /* wait for UDR0 to be empty. */
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    /* wait for transmission complete. */
    loop_until_bit_is_set(UCSR0A, TXC0);
}

void uart_putstr(const char *str)
{
    uint16_t i = 0;
    while(str[i])
    {
        uart_write(str[i]);
        i++;
    }
}

int main(void)
{
    DDRB = (1 << PB7);
    PORTB = 0;

    uart_init();

    setup_scanner();
    generate_keymap();
    setup_scan_timer();
    while(1)
    {
        uart_putstr("Hello World!\n");
        if(get_scanned())
        {
            set_scanned(false);
            handle_keyboard();
        }
    };
    return 0;
}