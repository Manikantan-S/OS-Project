#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

int turn;
int flag[2];

void enter_critical_section(int process) {
    int other = 1 - process;  // Index of the other process

    flag[process] = TRUE;     // Mark current process wants to enter
    turn = process;           // Set turn to the other process

    // Busy wait until it's the current process's turn and the other process doesn't want to enter
    while (flag[other] == TRUE && turn == process) {
        // Do nothing
    }
}

void exit_critical_section(int process) {
    flag[process] = FALSE;  // Mark that the current process has exited the critical section
}

void* process(void* arg) {
    int process_id = *(int*)arg;

    for (int i = 0; i < 5; ++i) {
        enter_critical_section(process_id);

        // Critical Section
        printf("Process %d is in the critical section\n", process_id);

        exit_critical_section(process_id);

        // Remainder Section
        printf("Process %d is in the remainder section\n", process_id);

        // Sleep for a short time to simulate other work
        usleep(100000);
    }

    return NULL;
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {0, 1};

    // Initialize variables
    turn = 0;
    flag[0] = FALSE;
    flag[1] = FALSE;

    // Create two threads
    for (int i = 0; i < 2; ++i) {
        if (pthread_create(&threads[i], NULL, process, &thread_ids[i]) != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    // Join threads
    for (int i = 0; i < 2; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
