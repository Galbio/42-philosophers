#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>  // For O_CREAT
#include <errno.h>  // For error handling

#define NUM_PROCESSES 5

void process_task(int pid, sem_t *semaphore) {
    // Wait on the semaphore to access the shared resource
    sem_wait(semaphore);

    printf("Process %d is using the shared resource\n", pid);
    sleep(2);  // Simulate some task that takes time
    printf("Process %d is done using the shared resource\n", pid);

    // Signal that the process is done with the resource
    sem_post(semaphore);
}

int main() {
    sem_t *semaphore = sem_open("/mysemaphore", O_CREAT, 0644, 1); // Create and initialize semaphore

    if (semaphore == SEM_FAILED) {
        perror("sem_open failed");
        return 1;
    }

    pid_t pids[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();

        if (pids[i] == 0) {  // Child process
            process_task(i, semaphore);
            return 0;  // Exit child process after finishing the task
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < NUM_PROCESSES; i++) {
        waitpid(pids[i], NULL, 0);
    }

    // Close and unlink the semaphore after use
    sem_close(semaphore);
    sem_unlink("/mysemaphore");

    return 0;
}

