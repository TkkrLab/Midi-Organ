#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>
#include <avr/interrupt.h>

#define NUMROWS 8
#define NUMCOLS 14
#define NUMKEYS 49
#define PIANOKEYSTART 36

uint8_t key_map[NUMKEYS*2];
uint8_t notes[NUMKEYS*2];

uint16_t matrix[NUMROWS];
uint16_t matrix_old[NUMROWS];

// generates a map, to transform key indexes to some nice note number
// for instance.
void generate_keymap();

// looks for which keys to update and send.
void handle_keyboard();

#endif