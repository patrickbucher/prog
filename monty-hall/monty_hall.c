#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GAMES 1000000
#define DOORS 3

#define GOAT 'Z'
#define CAR 'C'

int random_number(int, int);

int main(int argc, char *argv[])
{
    char games[GAMES][DOORS];
    int game, door, car;
    int pick, open, chance;
    int kept = 0, changed = 0;
    int win_keep = 0, win_change = 0;

    srand(time(NULL));

    for (game = 0; game < GAMES; game++) {
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

    printf("%d games with %d doors played.\n", GAMES, DOORS);
    printf("%d times kept and %d times won (%d%%).\n",
        kept, win_keep, (int)((float)win_keep / kept * 100));
    printf("%d times changed and %d times won (%d%%).\n",
        changed, win_change, (int)((float)win_change / changed * 100));

    return 0;
}

int random_number(int min_in, int max_ex)
{
    return rand() % (max_ex - min_in) + min_in;
}
