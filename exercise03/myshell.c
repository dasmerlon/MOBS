#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>


void run_process(char *program) {
    char argument[100];
    pid_t son = fork();

    if (son == 0) {
        printf("Do you want to add an argument?\n>>");
        scanf("%s", argument); 

        if (strcmp(argument, "no") == 0){
            execlp(program, program, NULL);
        }
        execlp(program, program, argument, NULL);

    } else {
        int status;
        wait(&status);

         // Check if child process exited normally and print the exit status
        if (WIFEXITED(status)) {
            printf("Exit status: %d\n", WEXITSTATUS(status));
        }
    }
}


int main(void) {

    while (true) {
        int program;
        printf("Please choose:\n1) ls\n2) ps\n3) cal\n4) exit\n>>");
        int x = scanf("%d", &program); 

        // Check if scanf fails to convert the input to an integer.
        // In this case, break the loop by clearing the input buffer
        // and print a hint that an integer is expected.
        if (x != 1) {
            int ch;
            // Read and discard all characters up to the end of the line
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Please enter a the number to choose a program.\n");
            continue;
        }

        if (program == 1) {
            run_process("ls");
        } else if (program == 2) {
            run_process("ps");
        } else if (program == 3) {
            run_process("cal");
        } else if (program == 4) {
            return EXIT_SUCCESS;
        }
    }
    
	return EXIT_SUCCESS;
}