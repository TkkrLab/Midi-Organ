#include <avr/io.h>

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

int main(void)
{
    return 0;
}