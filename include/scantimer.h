#ifndef __SCANTIMER_H__
#define __SCANTIMER_H__

/*
    st_ prefix for scan timer related variables.
*/

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <scanner.h>
#include <keyboard.h>

void setup_scan_timer();
bool get_scanned();
void set_scanned(bool);

#endif