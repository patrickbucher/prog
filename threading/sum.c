#include <pthread.h> // threading
#include <stdio.h> // input/output
#include <stdlib.h> // random numbers, string to int conversion
#include <time.h> // seed the random number generator

#define MIN 1
#define MAX 10

char random_number(char, char);
static void *partial_sum(void *);
void fail(int, char *);

// parameter object for threads
struct sum_job {
    char *numbers;
    int start_at;
    int n;
};

int
main(int argc, char *argv[])
{
    int n_numbers; // number of random integers to be summed up
    char *numbers; // the actual numbers to be summed up
    long expected_sum; // the sum calculated non-concurrently
    int i;

    pthread_t t1, t2; // two threads to build the sum
    struct sum_job *j1, *j2; // two sets of parameters
    void *sum1, *sum2; // the partial sums of the threads
    int state, split;

    clock_t start, end; // for benchmarks

    // command line parsing
    if (argc < 2) {
        fprintf(stderr, "usage: %s [number]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    n_numbers = atoi(argv[1]);
    if (n_numbers < 1) {
        fprintf(stderr, "given: %d, needed: positive integer\n", n_numbers);
        exit(EXIT_FAILURE);
    }

    // build array of random numbers
    printf("start generating %d random numbers\n", n_numbers);
    srand(time(NULL));
    numbers = (char*)malloc(sizeof(char) * n_numbers);
    for (i = 0; i < n_numbers; i++) {
        numbers[i] = random_number(MIN, MAX);
    }
    printf("finished generating %d random numbers\n", n_numbers);

    printf("start summing up (one thread)\n");
    expected_sum = 0;
    start = clock();
    for (i = 0; i < n_numbers; i++) {
        expected_sum += numbers[i];
    }
    end = clock();
    printf("expected sum: %ld, calculated in %f millis\n",
            expected_sum, (end - start)/1000.0f);

    // split up the work
    j1 = (struct sum_job*)malloc(sizeof(struct sum_job));
    j2 = (struct sum_job*)malloc(sizeof(struct sum_job));
    j1->numbers = numbers;
    j2->numbers = numbers;

    split = n_numbers / 2;
    j1->start_at = 0;
    j1->n = split;
    j2->start_at = split;
    j2->n = n_numbers - split;

    // start the threads
    printf("start summing up (two threads)\n");
    start = clock();
    state = pthread_create(&t1, NULL, partial_sum, j1);
    if (state != 0) {
        fail(state, "pthread_create t1");
    }
    state = pthread_create(&t2, NULL, partial_sum, j2);
    if (state != 0) {
        fail(state, "pthread_create t2");
    }

    // join the threads
    state = pthread_join(t1, &sum1);
    if (state != 0) {
        fail(state, "pthread_join t1");
    }
    state = pthread_join(t2, &sum2);
    if (state != 0) {
        fail(state, "pthread_join t2");
    }
    end = clock();

    printf("actual sum:   %ld, calculated in %f millis\n",
            *(long*)sum1 + *(long*)sum2, (end - start)/1000.0f);
    
    exit(EXIT_SUCCESS);
}

void
fail(int code, char *message)
{
    fprintf(stderr, "%s, exit code: %d\n", message, code);
    exit(code);
}

static void *
partial_sum(void *arg)
{
    struct sum_job *job;
    long *sum;
    int i;
    
    job = (struct sum_job*)arg;
    sum = (long*)malloc(sizeof(long));
    *sum = 0;
    for(i = job->start_at; i < job->start_at + job->n; i++) {
        *sum += job->numbers[i];
    }

    return (void *)sum;
}

char
random_number(char min, char max)
{
    return rand() % (max - min + 1) + min;
}
