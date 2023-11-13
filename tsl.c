#include <stdio.h>

int main() {
  int lock = 0;

  // Process P0
  if (test_and_set(&lock) == 0) {
    // Enter critical section
    printf("Process P0 entered the critical section.\n");
    // Do something
    printf("Process P0 left the critical section.\n");
  } else {
    // Wait for critical section to become available
    printf("Process P0 is waiting for the critical section.\n");
    while (lock == 1) {
      // Do nothing
    }
    // Enter critical section
    printf("Process P0 entered the critical section.\n");
    // Do something
    printf("Process P0 left the critical section.\n");
  }

  // Process P1
  if (test_and_set(&lock) == 0) {
    // Enter critical section
    printf("Process P1 entered the critical section.\n");
    // Do something
    printf("Process P1 left the critical section.\n");
  } else {
    // Wait for critical section to become available
    printf("Process P1 is waiting for the critical section.\n");
    while (lock == 1) {
      // Do nothing
    }
    // Enter critical section
    printf("Process P1 entered the critical section.\n");
    // Do something
    printf("Process P1 left the critical section.\n");
  }

  return 0;
}