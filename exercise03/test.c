#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//#define MAX_THREADS 100;

//pthread_t thread_id[MAX_THREADS];

int success;

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
    int run = 1;
    while(run = 1) {
        pid_t son = fork();
        pthread_t tid;
        if (son == 0) {
            int success = pthread_create(&tid, NULL, &selection, NULL);
        pthread_join(tid, NULL);
            printf("printed from child process");
        } else {
            
            printf("Success: %d\n", success);
            printf("printed from parent process");
            wait(NULL);
            run=0;
        }
        
        exit(EXIT_SUCCESS);
        //run=0;

    }
    

    

	return EXIT_SUCCESS;
}