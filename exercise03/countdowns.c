#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct params {
    int sec;
    int counter;
} params;

void *countdown(void *args) {
    params *input = (params*) args;
    sleep(input->sec);
    printf("\nThe %d. countdown finished after %d seconds.\nGimme mooore seconds: ", input->counter, input->sec);
    fflush(stdout);
    free(args);
    return EXIT_SUCCESS;
}


int main(void) {
    int count = 1;

    while (true) {
        params *args = malloc(sizeof(params));
        args->counter = count;
        pthread_t tid;
        printf("Gimme those seconds: ");
        int x = scanf("%d", &args->sec);

        // ... https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
        if (x != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Gimme a positive natural number pls!\n");
            continue;
        }
        printf("Countdown with %d seconds begins.\n", args->sec);
        int success = pthread_create(&tid, NULL, &countdown, (void*) args);
        count++;
    }
 
	return EXIT_SUCCESS;
}