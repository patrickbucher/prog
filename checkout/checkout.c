#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SMALLEST_UNIT 0.05
#define MAX_AMOUNT 200

float random_amount(int, float);
float amount_pay(float);

float currency_units[] = {
    0.05, 0.10, 0.20, 0.50, 1.00, 2.00, 5.00,
    10.00, 20.00, 50.00, 100.00, 200.00
};

int
main(int argc, char *argv[])
{
    float due, paid, change;

    srand(time(NULL));
    while (1) {
        due = random_amount(MAX_AMOUNT, SMALLEST_UNIT);
        paid = amount_pay(due);
        printf("Betrag:  %6.2f\n", due);
        printf("Bezahlt: %6.2f\n", paid);
        printf("Zurück: ");
        scanf("%f", &change);
        if (due + change == paid) {
            printf("korrekt\n");
        } else {
            printf("falsch, richtige Lösung: %3.2f\n", paid - due);
        }
        putchar('\n');
    }

    return 0;
}

float
random_amount(int max, float smallest_unit)
{
    assert(max >= smallest_unit);

    int factor, n_units;
    float result;

    factor = 1 / smallest_unit;
    n_units = rand() % (factor * max);
    result = (float)n_units / factor;

    // result must be dividable by smallest_unit
    assert((int)(max * factor) % (int)(smallest_unit * factor) == 0);

    return result;
}

float
amount_pay(float amount_due)
{
    float amount_pay = 0.0;
    int i;

    for (i = 0; i < sizeof(currency_units) / sizeof(float); i++) {
        if (currency_units[i] >= amount_due) {
            return currency_units[i];
        }
    }
    return 0.00;
}
