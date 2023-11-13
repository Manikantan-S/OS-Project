#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    // Wait (decrement) the semaphore
    sem_wait(&semaphore);

    // Critical Section
    printf("Thread %d is in the critical section\n", thread_id);

    // Simulate some work
    usleep(1000000);

    // Signal (increment) the semaphore to release the lock
    sem_post(&semaphore);

    // Non-critical section
    printf("Thread %d is in the non-critical section\n", thread_id);

    return NULL;
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {0, 1};

    // Initialize binary semaphore
    if (sem_init(&semaphore, 0, 1) != 0) {
        perror("Semaphore initialization failed");
        return 1;
    }

    // Create two threads
    for (int i = 0; i < 2; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < 2; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            return 1;
        }
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}
