/*
vierGewinnt: vierGewinnt-Spiel für die Konsole.
Copyright (C) 2010  Patrick "paedubucher" Bucher

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *initializeField();
void printField(char *field, _Bool withHeader);
_Bool putStone(char *field, char stone, int col);
int switchPlayer(int player);
int getStone(int player);
int enterColumn(int player, char stone);
_Bool hasWon(char *field, char stone);
_Bool hasRow(char *field, char stone);
_Bool hasCol(char *field, char stone);
_Bool hasCross(char *field, char stone);

const char FIELD_EMPTY = '_';
const char FIELD_P1 = 'x';
const char FIELD_P2 = 'o';

const int ROWS = 6;
const int COLS = 7;

const int VICTORY = 4;

int main(void) {
    int input = 0, player = 2, counter = 0;
    char stone = FIELD_EMPTY;
    _Bool won = false;
    char *field = initializeField(ROWS, COLS, FIELD_EMPTY);
    system("clear"); // UNIX only (Windows: "cls")
    printField(field, true);
    while (!won && counter < ROWS * COLS) {
        player = switchPlayer(player);
        stone = getStone(player);
        do {
            input = enterColumn(player, stone);
        } while (!putStone(field, stone, input));
        counter++;
        system("clear"); // UNIX only (Windows: "cls")
        printField(field, true);
        if (counter >= VICTORY * 2 - 1)
            won = hasWon(field, stone);
    }
    if (won)
        printf("Player %d is the winner!", player);
    else
        printf("Draw");
    getchar();
    getchar();
    return EXIT_SUCCESS;
}

char *initializeField() {
    char *field = malloc(sizeof(char) * ROWS * COLS);
    int index = 0;
    for (; index < ROWS * COLS; index++)
        field[index] = FIELD_EMPTY;
    field[++index] = '\0';
    return field;
}

void printField(char *field, _Bool withHeader) {
    int index = 1;
    putchar('\n');
    if (withHeader) {
        for (; index <= COLS; index++)
            printf(" %d ", index);
        putchar('\n');
    }
    for (index = 1; index <= ROWS * COLS; index++) {
        printf(" %c ", field[index - 1]);
        if (index >= COLS && index % COLS == 0)
            putchar('\n');
    }
    putchar('\n');
    fflush(stdout);
}

_Bool putStone(char *field, char stone, int col) {
    int row = ROWS, try;
    for (; row > 0; row--) {
        try = (row - 1) * COLS + col - 1;
        if (field[try] == FIELD_EMPTY) {
            field[try] = stone;
            return true;
        }
    }
    return false;
}

int switchPlayer(int player) {
    if (player == 1)
        return 2;
    else if (player == 2)
        return 1;
    else
        return -1;
}

int getStone(int player) {
    if (player == 1)
        return FIELD_P1;
    else if (player == 2)
        return FIELD_P2;
    else
        return FIELD_EMPTY;
}

int enterColumn(int player, char stone) {
    int input = 0;
    do {
        printf("Player %d [%c] (%d to %d): ", player, stone, 1, COLS);
        fflush(stdout);
        scanf("%d", &input);
    } while (input < 1 || input > COLS);
    return input;
}

_Bool hasWon(char *field, char stone) {
    return hasRow(field, stone) || hasCol(field, stone) || hasCross(field, stone);
}

_Bool hasRow(char *field, char stone) {
    int counter = 0, row = 0, col = 0;
    for (; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            if (field[COLS * row + col] == stone)
                counter++;
            else
                counter = 0;
            if (counter == VICTORY)
                return true;
        }
        counter = 0;
    }
    return false;
}

_Bool hasCol(char *field, char stone) {
    int counter = 0, col = 0, row = 0;
    for (; col < COLS; col++) {
        for (row = 0; row < ROWS; row++) {
            if (field[COLS * row + col] == stone)
                counter++;
            else
                counter = 0;
            if (counter == VICTORY)
                return true;
        }
        counter = 0;
    }
    return false;
}

_Bool hasCross(char *field, char stone) {
    int counter = 0, index = 0;
    // 1. ascending
    int start = COLS * (VICTORY - 1);
    for (; start < COLS * ROWS; start++) {
        if ((start + VICTORY - 1) / COLS == start / COLS) {
            for (index = start; index >= start - (VICTORY - 1) * (COLS - 1); index -= COLS - 1) {
                if (field[index] == stone)
                    counter++;
                else
                    break;
                if (counter == VICTORY)
                    return true;
            }
            counter = 0;
        }
    }
    // 2. descending
    start = COLS * (VICTORY - 1) + VICTORY - 1;
    for (; start < COLS * ROWS; start++) {
        if ((start - (VICTORY - 1)) / COLS == start / COLS) {
            for (index = start; index >= start - (VICTORY - 1) * (COLS + 1); index -= COLS + 1) {
                if (field[index] == stone)
                    counter++;
                else
                    break;
                if (counter == VICTORY)
                    return true;
            }
            counter = 0;
        }
    }
    return false;
}

