/*
Comway's Game of Life

Rules:
- Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 10

#define DEAD ' '
#define ALIVE 'X'

int neighbours_alive(char *, int, int);

int main()
{
    int i, j;
    int pos, neighbours;
    char *old = NULL, *new = NULL;

    do {
        system("clear");
        if (old == NULL && new == NULL) {
            old = (char *)malloc(sizeof(char) * (ROWS * COLS));
            new = (char *)malloc(sizeof(char) * (ROWS * COLS));
            for (i = 0; i < ROWS; i++) {
                for (j = 0; j < COLS; j++) {
                    old[i * COLS + j] = DEAD;
                }
            }
            // initialize a glider
            old[2] = ALIVE;
            old[1 * COLS + 3] = ALIVE;
            old[2 * COLS + 1] = ALIVE;
            old[2 * COLS + 2] = ALIVE;
            old[2 * COLS + 3] = ALIVE;

            // ...and one extra cell
            old[3 * COLS + 4] = ALIVE;
        }
        printf("  0 1 2 3 4 5 6 7 8 9\n");
        for (i = 0; i < ROWS; i++) {
            printf("%d ", i);
            for (j = 0; j < COLS; j++) {
                printf("%c ", old[i * COLS + j]);
            }
            putchar('\n');
        }
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                neighbours = neighbours_alive(old, i, j);
                pos = i * COLS + j;
                if (neighbours > 0 || old[pos] == ALIVE) {
                    printf("[%d][%d] is %s and has %d alive neighbours\n",
                        i, j, old[pos] == ALIVE ? "alive" : "dead", neighbours);
                }
                switch (old[pos]) {
                case DEAD:
                    if (neighbours == 3) {
                        new[pos] = ALIVE;
                    } else {
                        new[pos] = DEAD;
                    }
                    break;
                case ALIVE:
                    if (neighbours < 2 || neighbours > 3) {
                        new[pos] = DEAD;
                    } else {
                        new[pos] = ALIVE;
                    }
                    break;
                }
            }
        }
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                pos = i * COLS + j;
                old[pos] = new[pos];
            }
        }
    }
    while (getchar() != EOF);

    free(new);
    free(old);

    return 0;
}

int neighbours_alive(char *array, int row, int col)
{
    int alive, pos, n_fields;
    int up, down, right, left;
    int top_left, top_right, bottom_left, bottom_right;

    n_fields = ROWS * COLS;
    pos = row * COLS + col;

    up = pos - COLS;
    down = pos + COLS;
    right = pos + 1;
    left = pos - 1;

    alive = 0;
    if (up > 0 && array[up] == ALIVE) {
        alive++;
    }
    if (down < n_fields && array[down] == ALIVE) {
        alive++;
    }
    if (right % COLS != 0) {
        if (right < n_fields && array[right] == ALIVE) {
            alive++;
        }
        top_right = right - COLS;
        if (top_right >= 0 && array[top_right] == ALIVE) {
            alive++;
        }
        bottom_right = right + COLS;
        if (bottom_right < n_fields && array[bottom_right] == ALIVE) {
            alive++;
        }
    }
    if ((left + 1) % COLS != 0) {
        if (left >= 0 && array[left] == ALIVE) {
            alive++;
        }
        top_left = left - COLS;
        if (top_left >= 0 && array[top_left] == ALIVE) {
            alive++;
        }
        bottom_left = left + COLS;
        if (bottom_left < n_fields && array[bottom_left] == ALIVE) {
            alive++;
        }
    }
    return alive;
}
