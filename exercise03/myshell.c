#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//#define MAX_THREADS 100;

//pthread_t thread_id[MAX_THREADS];



void *selection(){
    int program;
    printf("Please choose:\n1) ls\n2) ps\n3) cal\n4) exit\n>>");
    scanf("%d", &program); 
    if (program == 1) {
        execlp("ls", "ls", NULL);
    } else if (program == 2) {
        execlp("ps", "ps", NULL);
    } else if (program == 3) {
        execlp("cal", "cal", NULL);
    } else if (program == 4) {
        //pthread_exit(0);
        return EXIT_SUCCESS;
    }
    
    printf("Hello, Thread: %d!\n", program);
		
}

int main(void) {
    pid_t son = fork();
    pthread_t tid;
    int success = pthread_create(&tid, NULL, &selection, NULL);
    pthread_join(tid, NULL);
    printf("Success: %d\n", success);

    if (son == 0) {
        printf("printed from child process - %d\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        printf("printed from parent process - %d\n", getpid());
        wait(NULL);
    }

	return EXIT_SUCCESS;
}