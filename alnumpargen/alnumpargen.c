#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PARAGRAPHS 1000
#define CHARS_PER_PARAGRAPH 500

#define MIN_BLOCK_LEN 2
#define MAX_BLOCK_LEN 5

int rand_block_len();
char rand_number_char();
char rand_letter_char();
int rand_int(int, int);

int main()
{
    int paragraph, chars_written, block_length;

    srand(time(NULL));

    for (paragraph = 0; paragraph < PARAGRAPHS; paragraph++) {
        chars_written = 0;
        block_length = 0;
        do {
            if (block_length == 0) {
                block_length = rand_block_len();
            }

            putchar(rand_number_char());
            block_length--;
            chars_written++;
            if (block_length == 0) {
                putchar(' ');
                chars_written++;
                block_length = rand_block_len();
            }

            putchar(rand_letter_char());
            block_length--;
            chars_written++;
            if (block_length == 0) {
                putchar(' ');
                chars_written++;
                block_length = rand_block_len();
            }
        } while (chars_written < CHARS_PER_PARAGRAPH);
        putchar('\n');
        putchar('\n');
    }

    return 0;
}

int rand_block_len()
{
    return rand_int(MIN_BLOCK_LEN, MAX_BLOCK_LEN + 1);
}

int rand_int(int min_incl, int max_excl)
{
    return rand() % (max_excl - min_incl) + min_incl;
}

char rand_number_char()
{
    return '0' + rand_int(0, 10);
}

char rand_letter_char()
{
    return 'a' + rand_int(0, 26);
}
