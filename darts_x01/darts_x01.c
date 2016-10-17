/*
 darts_x01: tracks score for Dart games like 301 or 501
 Copyright (C) 2014  Patrick Bucher

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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BULLSEYE 25
#define MAX_ROUND 180
#define CLEAR_CMD "clear" // use "cls" for Windows

bool valid_score(short score);
void print_score(char *names[], short scores[], int n, bool clear);
bool compute_hint(short score_due, char *factor, short *target);

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s [score] [player 1], ..., [player n]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    short score = (short)atoi(argv[1]);
    if (!valid_score(score)) {
        printf("score must be 301, 401, ..., 901\n");
        exit(EXIT_FAILURE);
    }

    int no_players = argc - 2, n, tmp_players = no_players;
    char *player_names[no_players];
    short player_scores[no_players];
    bool finished = false;

    for (n = 2; n < argc; n++) {
        player_names[n - 2] = argv[n];
        player_scores[n - 2] = score;
    }

    do {
        for (int i = 0; i < no_players && tmp_players > 1; i++) {
            print_score(player_names, player_scores, no_players, true);
            if (player_scores[i] == 0)
                continue;
            bool done;
            short darts;
            short round_score = 0;
            short bounce = player_scores[i];
            for (done = false, darts = 0; !done && darts < 3; darts++) {
                char c;
                short n = 0;
                if (player_scores[i] <= MAX_ROUND) {
                    char factor[10];
                    short target = 0;
                    if (compute_hint(player_scores[i], factor, &target)) {
                        if (target == BULLSEYE) {
                            printf("\n%s, you can finish with a %s bullseye.",
                                player_names[i], factor);
                        } else {
                            printf("\n%s, you can finish with a %s %hd.",
                                player_names[i], factor, target);
                        }
                    }
                }
                printf("\n%s, enter your score: ", player_names[i]);
                c = getchar();
                if (c == '\n') {
                    done = true;
                    break;
                }
                do {
                    if (c >= '0' && c <= '9') {
                        n *= 10;
                        n += c - '0';
                    } else {
                        done = true;
                        break;
                    }
                } while ((c = getchar()) != '\n');
                if (round_score + n > MAX_ROUND) {
                    printf("\n%d points in one round?\n", round_score + n);
                    round_score = 0;
                    continue;
                } else {
                    round_score += n;
                }
                if (player_scores[i] - n >= 0) {
                    player_scores[i] -= n;
                } else {
                    printf("\n%s, you're bust!\n", player_names[i]);
                    player_scores[i] = bounce;
                    done = true;
                    getchar();
                    break;
                }
                print_score(player_names, player_scores, no_players, true);
                if (player_scores[i] == 0) {
                    printf("\n%s, you finished the game!\n", player_names[i]);
                    getchar();
                    if (--tmp_players < 2) {
                        finished = true;
                        break;
                    }
                }
            }
        }
    } while (!finished);

    exit(EXIT_SUCCESS);
}

bool valid_score(short score)
{
    return score % 100 == 1 && score < 1000 && score >= 301;
}

void print_score(char *names[], short scores[], int n, bool clear)
{
    int i, len = n * (10 + 1);

    if (clear)
        system(CLEAR_CMD);

    for (i = 0; i < len; i++)
        putchar('=');
    putchar('\n');

    for (i = 0; i < n; i++) {
        printf(" %10.10s", names[i]);
    }
    putchar('\n');

    for (i = 0; i < len; i++)
        putchar('=');
    putchar('\n');

    for (i = 0; i < n; i++)
        printf(" %10d", scores[i]);
    putchar('\n');
}

bool compute_hint(short score_due, char *factor, short *target)
{
    static const int no_fields = 21;
    short fields[no_fields];
    int i;
    for (i = 0; i < no_fields - 1; i++)
        fields[i] = i + 1;
    fields[no_fields - 1] = BULLSEYE;

    for (i = 0; i < no_fields; i++) {
        if (score_due == fields[i]) {
            strcpy(factor, "single");
            *target = fields[i];
            return true;
        }
    }
    for (i = 0; i < no_fields; i++) {
        if (score_due == 2 * fields[i]) {
            strcpy(factor, "double");
            *target = fields[i];
            return true;
        }
    }
    for (i = 0; i < no_fields; i++) {
        if (score_due == 3 * fields[i] && fields[i] != BULLSEYE) {
            strcpy(factor, "triple");
            *target = fields[i];
            return true;
        }
    }
    return false;
}
