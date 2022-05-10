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
    printf("\033[0;31m\nThe %d. countdown finished after %d seconds!\033[0m\n", input->counter, input->sec);
    printf("Enter a number of seconds to start a countdown: ");
    
    // Clear the buffer to print the second line
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

        printf("Enter a number of seconds to start a countdown: ");
        int x = scanf("%d", &args->sec);

        // Check if scanf fails to convert the input to an integer.
        // In this case, break the loop by clearing the input buffer
        // and print a hint that an integer is expected.
        if (x != 1) {
            int ch;
            // Read and discard all characters up to the end of the line
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Please enter a positive natural number!\n");
            continue;
        }

        printf("\033[0;33mYour %d. Countdown with %d seconds begins.\033[0m\n", args->counter, args->sec);
        pthread_create(&tid, NULL, &countdown, (void*) args);
        count++;
    }
 
	return EXIT_SUCCESS;
}