#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DOORS 3

#define GOAT 'G'
#define CAR 'C'

char **alloc_games(int, int);
void free_games(char **, int);
int random_number(int, int);
void fail(char *);

int main(int argc, char *argv[])
{
    char **games = NULL;
    int n_games = 0;
    int game, door, car;
    int pick, open, chance;
    int kept = 0, changed = 0;
    int win_keep = 0, win_change = 0;
    int win_keep_percent = 0, win_change_percent = 0;

    if (argc < 2 || (n_games = atoi(argv[1])) < 1) {
        fail("usage: monty_hall [number of games]");
    }

    srand((unsigned int)time(NULL));

    games = alloc_games(n_games, DOORS);
    for (game = 0; game < n_games; game++) {
        for (door = 0; door < DOORS; door++) {
            games[game][door] = GOAT;
        }
        car = random_number(0, DOORS);
        games[game][car] = CAR;

        // player picks random door
        pick = random_number(0, DOORS);

        // show master opens a goat door the player didn't pick 
        for (open = 0; open < DOORS; open++) {
            if (open != pick && open != car) {
                break;
            }
        }

        // player either ...
        if (game % 2 == 0) {
            // keeps or ...
            kept++;
            if (games[game][pick] == CAR) {
                win_keep++;
            }
        } else {
            // changes the door randomly
            changed++;
            do {
                chance = random_number(0, DOORS);
            } while (chance == pick || chance == open);
            if (games[game][chance] == CAR) {
                win_change++;
            }
        }
    }

    if (kept > 0) {
        win_keep_percent = (int)((float)win_keep / kept * 100);
    }
    if (changed > 0) {
        win_change_percent = (int)((float)win_change / changed * 100);
    }

    printf("%d games with %d doors played.\n", n_games, DOORS);
    printf("%d times kept and %d times won (%d%%).\n",
        kept, win_keep, win_keep_percent);
    printf("%d times changed and %d times won (%d%%).\n",
        changed, win_change, win_change_percent);

    free_games(games, n_games);

    return 0;
}

int random_number(int min_in, int max_ex)
{
    return rand() % (max_ex - min_in) + min_in;
}

char **alloc_games(int n_games, int doors)
{
    int game;
    char **games;

    games = (char**)malloc(sizeof(char *) * n_games * doors);
    if (games == NULL) {
        fail("cannot allocate memory for games");
    }

    for (game = 0; game < n_games; game++) {
        games[game] = (char*)malloc(sizeof(char) * doors);
        if (games[game] == NULL) {
            fail("cannot allocate memory for doors");
        }
    }

    return games;
}

void free_games(char **games, int n_games)
{
    int game;

    for (game = 0; game < n_games; game++) {
        free(games[game]);
    }
    free(games);
}

void fail(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}
