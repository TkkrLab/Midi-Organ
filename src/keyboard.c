#include "keyboard.h"

uint8_t key_map[NUMKEYS*2] = 
{
    44, 43, 30, 29, 16, 15, 2, 1, 
    98, 101, 84, 87, 70, 73, 56, 59, 
    42, 45, 28, 31, 14, 17, 0, 3, 
    105, 104, 91, 90, 77, 76, 63, 62, 
    49, 48, 35, 34, 21, 20, 7, 6, 
    103, 102, 89, 88, 75, 74, 61, 60, 
    47, 46, 33, 32, 19, 18, 4, 5, 
    107, 109, 93, 95, 79, 81, 65, 67, 
    51, 53, 37, 39, 23, 25, 9, 11, 
    111, 110, 97, 96, 83, 82, 69, 68, 
    55, 54, 41, 40, 27, 26, 13, 12, 
    108, 106, 94, 92, 80, 78, 66, 64, 
    52, 50, 
};

static uint16_t note_index = 0;
static uint16_t note = 0;
static uint16_t new_val = 0;
static uint16_t old_val = 0;

void generate_keymap()
{
    for(int i = 0; i < NUMKEYS; i++)
    {
        uint8_t mapped = key_map[i*2];
        notes[mapped] = PIANOKEYSTART + i;
    }
}

void handle_keyboard()
{
    cli();
    note_index = 0;
    for(int row = 0; row < NUMROWS; row++)
    {
        for(int col = 0; col < NUMCOLS; col++)
        {
            note = notes[note_index];
            new_val = matrix[row] & (1 << col);
            old_val = matrix_old[row] & (1 << col);
            if(new_val > old_val)
            {
                PORTB |= (1 << PB7);
            }
            if(new_val < old_val)
            {
                PORTB &= ~(1 << PB7);
            }
            matrix_old[row] = matrix[row];
            note_index++;
        }
    }
    sei();
}
